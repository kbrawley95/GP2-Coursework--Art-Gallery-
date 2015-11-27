#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "Common.h"

GLuint	LoadTextureFromFile(const string& filename);

GLuint	LoadTextureFromFont(const string& fontFilename, int	pointSize, const string& text);

GLuint LoadCubemapTexture(const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ);

GLuint ConvertSDLSurfaceToTexture(SDL_Surface * surface);

void LoadCubeMapFace(const string&, GLenum face);

#endif