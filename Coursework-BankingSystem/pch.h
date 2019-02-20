// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>  
#include <algorithm>
#include <vector>
#include "variadicTable/include/VariadicTable.h"
#include "database.h"
#include "user.h"
#include "menu.h"
#include "sqlite3.h"
#include "picosha2.h"
#include "fmt-master/format.h"




#endif //PCH_H
