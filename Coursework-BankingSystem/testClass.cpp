#include "pch.h"
#include "testClass.h"


testClass::testClass(database &_db)
{
	db = &_db;
}

string testClass::getPass(string * email)
{
	return (db->checkUser(email).password);
}


