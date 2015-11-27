#ifndef _SCENE_H
#define _SCENE_H

#include <map>

class Camera;
class GameObject;
class Light;

extern std::shared_ptr<Camera> MainCamera;
extern std::shared_ptr<Light> MainLight;
extern std::vector<std::shared_ptr<GameObject>> GameObjects;
#endif