#ifndef _TEXT2D_H
#define _TEXT2D_H

#include "Common.h"
#include "Text2D.h"
#include "Material.h"

using namespace glm;
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

class Text2D
{
public:
	Text2D(const char * texturePath);
	~Text2D();

	void Render(const char * text, int x, int y, int size);
private:
	unsigned int Text2DTextureID;
	unsigned int Text2DVertexBufferID;
	unsigned int Text2DUVBufferID;
	std::shared_ptr<Material> Text2DShaderID;
	unsigned int Text2DUniformID;

	GLuint LoadDDS(const char* filename);
};
#endif