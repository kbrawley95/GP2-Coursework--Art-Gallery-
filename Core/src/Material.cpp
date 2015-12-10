#include "Material.h"

Material::Material(std::string vsPath, std::string fsPath)
{
	ambientMaterial = glm::vec4(1.0f, 0.3f, 0.3f, 1.0f);
	diffuseMaterial = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	specularMaterial = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	specularPower = 25.0f;

	environmentMap = 0;

	std::cout << "Loading " << std::endl;
	std::cout << "-" << vsPath << std::endl;
	std::cout << "-" << fsPath << std::endl << std::endl;
	GLuint vertexShaderProgram = 0;
	vertexShaderProgram = LoadShaderFromFile(vsPath, VERTEX_SHADER);
	CheckForCompilerErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	fragmentShaderProgram = LoadShaderFromFile(fsPath, FRAGMENT_SHADER);
	CheckForCompilerErrors(fragmentShaderProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);

	//Link attributes
	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
	glBindAttribLocation(shaderProgram, 1, "vertexColour");
	glBindAttribLocation(shaderProgram, 2, "vertexTexCoords");

	glLinkProgram(shaderProgram);
	CheckForLinkErrors(shaderProgram);
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

Material::~Material()
{
	glDeleteTextures(1, &environmentMap);
}

void Material::LoadTexture(std::string filename)
{
	std::cout << "Loading " + filename << std::endl;
	//load texture & bind
	diffuseMap = LoadTextureFromFile(filename);

	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
}

GLuint Material::LoadCubemapTexture(const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ)
{
	GLuint textureObj;

	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &textureObj);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureObj);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	LoadCubeMapFace(posX, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	LoadCubeMapFace(negX, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	LoadCubeMapFace(posY, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	LoadCubeMapFace(negY, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	LoadCubeMapFace(posZ, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	LoadCubeMapFace(negZ, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);


	return textureObj;

}

void Material::LoadCubeMapFace(const std::string& filename, GLenum face)
{
	SDL_Surface	*imageSurface = IMG_Load(filename.c_str());
	if (!imageSurface){

		std::cout << "Can't Load	image " << filename << " " << IMG_GetError();
	}

	GLint		nOfColors = imageSurface->format->BytesPerPixel;

	GLenum	textureFormat = GL_RGB;
	GLenum	internalFormat = GL_RGB8;

	if (nOfColors == 4)					//	contains	an	alpha	channel
	{
		if (imageSurface->format->Rmask == 0x000000ff){
			textureFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
		}
		else{
			textureFormat = GL_BGRA;
			internalFormat = GL_RGBA8;
		}
	}
	else if (nOfColors == 3)					//	no	alpha	channel
	{
		if (imageSurface->format->Rmask == 0x000000ff){
			textureFormat = GL_RGB;
			internalFormat = GL_RGB8;
		}
		else{
			textureFormat = GL_BGR;
			internalFormat = GL_RGB8;
		}
	}
	else{
		std::cout << "warning: the image is not truecolor.. this will	probably break";
	}
	glTexImage2D(face, 0, internalFormat, imageSurface->w, imageSurface->h, 0, textureFormat,
		GL_UNSIGNED_BYTE, imageSurface->pixels);

	SDL_FreeSurface(imageSurface);
}

void Material::SetCubeMapTextures(const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ)
{
	environmentMap = LoadCubemapTexture(posX, negX, posY, negY, posZ, negZ);
}


GLuint Material::GetTexture()
{
	return diffuseMap;
}
GLuint Material::GetShader()
{
	return shaderProgram;
}

//PRIVATE

// Load it from a memory buffer
GLuint Material::LoadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType)
{
	GLuint program = glCreateShader(shaderType);
	glShaderSource(program, 1, &pMem, NULL);
	glCompileShader(program);
	return program;
}

//Load Shader from File
GLuint Material::LoadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType)
{
	std::string fileContents;
	std::ifstream file;
	file.open(filename.c_str(), std::ios::in);
	if (!file)
	{
		std::cout << "Shader file could not be loaded" << std::endl;
		return 0;
	}

	//calculate file size
	if (file.good())
	{
		file.seekg(0, std::ios::end);
		unsigned long len = file.tellg();
		file.seekg(std::ios::beg);
		if (len == 0)
		{
			std::cout << "Shader file has no contents " << std::endl;
			return 0;
		}

		fileContents.resize(len);
		file.read(&fileContents[0], len);
		file.close();
		GLuint program = LoadShaderFromMemory(fileContents.c_str(), shaderType);
		return program;
	}
	return 0;
}

bool Material::CheckForCompilerErrors(GLuint shaderProgram)
{
	GLint isCompiled = 0;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
		//The maxLength includes the NULL character
		std::string infoLog;
		infoLog.resize(maxLength);
		glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
		std::cout << "Shader not compiled " << infoLog << std::endl;
		//We don't need the shader anymore.
		glDeleteShader(shaderProgram);
		return true;
	}

	return false;
}

bool Material::CheckForLinkErrors(GLuint program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		//The maxLength includes the NULL character
		std::string infoLog;
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		std::cout << "Shader not linked " << infoLog << std::endl;
		//We don't need the shader anymore.
		glDeleteProgram(program);
		return true;
	}
	return false;
}

GLuint Material::LoadTextureFromFile(const std::string&	filename)
{
	SDL_Surface	*imageSurface = IMG_Load(filename.c_str());
	if (!imageSurface){

		std::cout << "Can't Load	image " << filename << " " << IMG_GetError();
		return	0;
	}

	GLuint textureID = ConvertSDLSurfaceToTexture(imageSurface);
	SDL_FreeSurface(imageSurface);

	return textureID;
}

GLuint Material::ConvertSDLSurfaceToTexture(SDL_Surface * surface)
{
	GLuint textureID = 0;
	GLint nOfColors = surface->format->BytesPerPixel;

	GLenum	textureFormat = GL_RGB;
	GLenum	internalFormat = GL_RGB8;

	if (nOfColors == 4)					//	contains	an	alpha	channel
	{
		if (surface->format->Rmask == 0x000000ff){
			textureFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
		}
		else
		{
			textureFormat = GL_BGRA;
			internalFormat = GL_RGBA8;
		}
	}
	else if (nOfColors == 3)					//	no	alpha	channel
	{
		if (surface->format->Rmask == 0x000000ff){
			textureFormat = GL_RGB;
			internalFormat = GL_RGB8;
		}
		else
		{
			textureFormat = GL_BGR;
			internalFormat = GL_RGB8;
		}
	}
	else
	{
		std::cout << "warning: the image is not truecolor.. this will	probably break";
		return 0;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, surface->w, surface->h, 0, textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

	return textureID;
}