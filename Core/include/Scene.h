#ifndef _SCENE_H
#define _SCENE_H

#include <map>

class Camera;
class GameObject;
class DirectionalLight;

extern std::shared_ptr<Camera> MainCamera;
extern std::shared_ptr<DirectionalLight> MainLight;
extern std::shared_ptr<GameObject> SkyBox;
extern std::vector<std::shared_ptr<GameObject>> GameObjects;
#endif