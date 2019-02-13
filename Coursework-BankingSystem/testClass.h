#pragma once
#include "pch.h"
class testClass
{
public:
	testClass(database &_db);
	string getPass(string * email);

private:
	database *db ;
};


