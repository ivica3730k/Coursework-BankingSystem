#include "pch.h"

database::database(const char* path)
{
	sqlite3_open(path, &db);
}

string database::hash(string* data)
{
	string src_str = *(data);
	std::vector<unsigned char> hash(picosha2::k_digest_size);
	picosha2::hash256(src_str.begin(), src_str.end(), hash.begin(), hash.end());
	std::string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
	//std::cout << hex_str << std::endl;
	return (hex_str);
}

bool database::createUser(string* name, string* surname, string* eMail, string* password, bool isAdmin)
{
	bool exists = checkUser(eMail).isValid;
	if (exists == false) {
		//sqlite3 *db already defined as private in .h file
		//callback already defined as private in .h file
		char* zErrMsg = 0;
		int rc;
		char* sql;
		std::string _query = fmt::format("INSERT INTO `users`(`name`,`surname`,`eMail`,`password`,`isAdmin`,`lastLogin`) VALUES ('{0}','{1}','{2}','{3}','{4}','{5}');", *(name), *(surname), *(eMail), hash(password), isAdmin,"Never");
		const char* query = _query.c_str();

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
	//sqlite3 *db already defined as private in .h file
	//callback already defined as private in .h file
	char* zErrMsg = 0;
	int rc;
	char* sql;

	dbUserData dataread;
	dbUserData *data = &dataread;
	std::string _query = fmt::format("SELECT * from users where eMail = '{0}';", *email);
	//std::string _query = "SELECT * from users where eMail = 'ivica3730k@outlook.com';";
	const char* query = _query.c_str();
	//std::cout << query << std::endl;
	rc = sqlite3_exec(db, query, callbackUsers, (void*)data, &zErrMsg);

	if (rc) {;
		//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		//return (false);
	}
	else {
	
		//fprintf(stdout, "Opened database successfully\n");
		//return (true);
	}
	//std::cout << dataread.name << std::endl;
	return dataread;

	
	
}



int database::callbackUsers(void* dataptr, int argc, char** argv, char** azColName)
{
	
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
