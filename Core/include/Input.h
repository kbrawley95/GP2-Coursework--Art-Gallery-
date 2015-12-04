#ifndef _INPUT_H
#define _INPUT_H

#include "Common.h"
#include "Vector.h"
#include <map>

extern Vector2 mousePosition;
extern Vector2 mouseDelta;
extern std::map<int, bool> keysPressed;

#endif