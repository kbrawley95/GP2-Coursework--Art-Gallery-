#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <list>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>
#include <fbxsdk.h>

//maths headers
#include <glm/glm.hpp>


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>

const std::string ASSET_PATH = "assets/";
const std::string SHADER_PATH = ASSET_PATH + "shaders/";
const std::string TEXTURE_PATH = ASSET_PATH + "textures/";
const std::string FONT_PATH = ASSET_PATH + "fonts/";
const std::string MODEL_PATH = ASSET_PATH + "models/";


#endif
