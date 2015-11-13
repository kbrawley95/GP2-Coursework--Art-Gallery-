#include "FileSystem.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void ChangeWorkingDirectory()
{
#ifdef _WIN32
	char buffer[MAX_PATH];
#endif
}