#include "Common.h"
#include "Graphics.h"
#include "Vertices.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "FBXLoader.h"
#include "FileSystem.h"
#include "Core.h"
#include "Scene.h"

#define SDL_main main

int main()
{
	CoreInitialise();
	//Create scene/level
	Scene* level = new Scene();

	//Model 1 (Armored Vehicle)
	string modelPath = ASSET_PATH + MODEL_PATH + "/Art_Gallery1.fbx";
	auto currentGameObject = loadFBXFromFile(modelPath);

	currentGameObject->loadShader(ASSET_PATH + SHADER_PATH + "/specularVS.glsl", ASSET_PATH + SHADER_PATH + "/specularFS.glsl");

	level->gameObjects.push_back(currentGameObject);
	currentGameObject->setPosition(vec3(0.0f, -10.0f, 0.0f));

	CoreMainLoop();

	return 0;
}