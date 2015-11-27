#ifndef _TEXTURELOADER_H
#define _TEXTURELOADER_H

#include "Common.h"

GLuint loadTextureFromFile(const std::string& filename);
GLuint convertSDLSurfaceToTexture(SDL_Surface * surface);

#endif