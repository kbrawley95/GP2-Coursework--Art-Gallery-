#version 150

in vec3 vertexPosition;

out vec3 vertexTexCoords;

uniform vec3 cameraPosition;
uniform mat4 MVP;

void main()
{
	vertexTexCoords = normalize(vertexPosition);
	gl_Position = MVP * vec4(vertexPosition + cameraPosition, 1.0);
}
