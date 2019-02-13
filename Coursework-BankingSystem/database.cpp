#include "pch.h"
#include "database.h"
database::database(const char* path)
{
	sqlite3_open(path, &db);
}

bool database::createUser(string* name, string* surname, string* eMail, string* password, bool isAdmin)
{
	bool exists = checkUser(eMail).isValid;
	if (exists == false) {
		//sqlite3 *db already defined as private in .h file
		//callback already defined as private in .h file
		char* zErrMsg = 0;
		int rc = 0;
		char* sql =nullptr;
		std::string _query = fmt::format("INSERT INTO `users`(`name`,`surname`,`eMail`,`password`,`isAdmin`,`lastLogin`) VALUES ('{0}','{1}','{2}','{3}','{4}','{5}');", *(name), *(surname), *(eMail), *(password), isAdmin,"Never");
		const char* query = _query.c_str();
		std::cout << query << std::endl;
		rc = sqlite3_exec(db, query, callbackUsers, 0, &zErrMsg);

		if (rc) {
			//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			return (false);
		}
		else {
			//fprintf(stdout, "Opened database successfully\n");
			return (true);
		}

	}
	std::cout << "User probably already exists" << std::endl;
	return(false);

}

dbUserData database::checkUser(string * email)
{
	//std::cout << "Checking" << std::endl;
	//sqlite3 *db already defined as private in .h file
	//callback already defined as private in .h file
	char* zErrMsg = 0;
	int rc = 0;
	char* sql =nullptr;

	dbUserData dataread;
	dbUserData *data = &dataread;
	std::string _query = fmt::format("SELECT * from users where eMail = '{0}';", *email);
	//std::string _query = "SELECT * from users where eMail = 'ivica3730k@outlook.com';";
	const char* query = _query.c_str();
	std::cout << query << std::endl;
	rc = sqlite3_exec(db, query, callbackUsers, (void*)data, &zErrMsg);

	if (rc) {;
		//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		//return (false);
	}
	else {
	
		//fprintf(stdout, "Opened database successfully\n");
		//return (true);
	}
	//std::cout <<"Output should be"<< dataread.password << std::endl;
	return dataread;

	
	
}



int database::callbackUsers(void* dataptr, int argc, char** argv, char** azColName)
{
	//std::cout << "Uso u callback" << std::endl;
	dbUserData *store = &*(dbUserData*)dataptr;
	/*
	int i;

	for (i = 0; i < argc; i++) {
	//	std::cout << argv[i] << std::endl;

	}
	printf("\n");
	*/
	store->isValid = true;
	store->name = argv[1];
	store->surname = argv[2];
	store->email = argv[3];
	store->password = argv[4];
	store->isAdmin = (bool)argv[5];
	store->lastLogin = argv[6];
	return 0;
}
