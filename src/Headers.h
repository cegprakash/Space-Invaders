#ifndef HEADERS_H
#define HEADERS_H

#ifdef _MSC_VER
// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "IrrKlang.lib")
#endif

#include <irrlicht.h>
#include <iostream>
#include <vector>
#include <irrKlang.h>
#include <cstring>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;
using namespace gui;
using namespace io;
using namespace std;


#endif