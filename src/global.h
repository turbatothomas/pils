#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <filesystem>
#include <SDL2/SDL.h>

#define str(s) #s
#define FILELINE(line) __FILE__ ":" str(line)

namespace fs = std::filesystem;

extern char *DATA_PATH;
void InitializeDataPath();
void FreeDataPath();
std::string getAbsolutePath(std::string path);

/*
 * TYPE ID per gli oggetti
 * */
const char ID_ALTRO = 'u';
const char ID_VITA = 'v';

#endif
