#include "pch.h"

database::database(const char* path)
{
	std::cout << sqlite3_open(path, &db) << std::endl;
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

	//sqlite3 *db already defined as private in .h file
	char* zErrMsg = 0;
	int rc;
	char* sql;
	std::string _query = fmt::format("INSERT INTO `users`(`name`,`surname`,`eMail`,`password`,`isAdmin`) VALUES ('{0}','{1}','{2}','{3}','{4}');", *(name), *(surname), *(eMail), hash(password), isAdmin);
	const char* query = _query.c_str();

	rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return (false);
	}
	else {
		return (true);
		fprintf(stdout, "Opened database successfully\n");
	}
}

int database::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	int i;
	for (i = 0; i < argc; i++) {
		std::cout << azColName[i] << argv[i] << argv[i] << "NULL" << std::endl;
	}
	printf("\n");
	return 0;
}
