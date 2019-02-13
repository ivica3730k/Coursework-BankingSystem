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
		char* zErrMsg = 0;
		char* sql = nullptr;
		std::string _query = fmt::format("INSERT INTO `users`(`name`,`surname`,`eMail`,`password`,`isAdmin`,`lastLogin`) VALUES ('{0}','{1}','{2}','{3}','{4}','{5}');", *(name), *(surname), *(eMail), hash(password), isAdmin, "Never");
		bool rc = executeQuery(&_query, noCallback);
		if (rc) {
			return (false);
		}
		else {

			return (true);
		}
	}
	std::cout << "User probably already exists" << std::endl;
	return (false);
}

dbUserData database::checkUser(string* email)
{
	char* zErrMsg = 0;
	int rc = 0;
	char* sql = nullptr;

	dbUserData dataread;
	dbUserData* data = &dataread;
	std::string _query = fmt::format("SELECT * from users where eMail = '{0}';", *email);

	const char* query = _query.c_str();

	rc = sqlite3_exec(db, query, callbackUsers, (void*)data, &zErrMsg);

	if (rc) {

		dataread.isValid = false;
	}
	else {
	}

	return dataread;
}

dbUserData database::checkUserTest(string* email)
{

	dbUserData dataread;
	dbUserData* data = &dataread;
	std::string _query = fmt::format("SELECT * from users where eMail = '{0}';", *email);

	bool rc = executeQuery(&_query, callbackUsers, (void*)data);

	if (rc == false) {

		dataread.isValid = false;
	}
	else {
	}

	return dataread;
}

int database::callbackUsers(void* dataptr, int argc, char** argv, char** azColName)
{

	dbUserData* store = &*(dbUserData*)dataptr;
	store->isValid = true;
	store->name = argv[1];
	store->surname = argv[2];
	store->email = argv[3];
	store->password = argv[4];
	store->isAdmin = (bool)argv[5];
	store->lastLogin = argv[6];
	return 0;
}

int database::noCallback(void* dataptr, int argc, char** argv, char** azColName)
{
	return 0;
}


bool database::executeQuery(string* _query, int(*f)(void*, int, char**, char**), void* data)
{
	char* zErrMsg = 0;
	int rc = 0;
	char* sql = nullptr;
	std::string exec = *_query;
	const char* query = exec.c_str();
	rc = sqlite3_exec(db, query, f, data, &zErrMsg);

	if (rc) {
		return (false);
	}
	else {

		return (true);
	}
}

bool database::executeQuery(string* _query, int(*f)(void*, int, char**, char**))
{
	char* zErrMsg = 0;
	int rc = 0;
	char* sql = nullptr;
	std::string exec = *_query;
	const char* query = exec.c_str();
	rc = sqlite3_exec(db, query, f, 0, &zErrMsg);

	if (rc) {
		return (false);
	}
	else {

		return (true);
	}
	return false;
}

bool database::setLastLogin(string* email)
{
	return (false);
}

string database::returnTime(void)
{

	auto end = std::chrono::system_clock::now();
	std::time_t _time = std::chrono::system_clock::to_time_t(end);
	string s = std::ctime(&_time);
	return s;
}

string database::hash(string* data)
{

	string src_str = *(data);
	std::vector<unsigned char> hash(picosha2::k_digest_size);
	picosha2::hash256(src_str.begin(), src_str.end(), hash.begin(), hash.end());
	std::string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
	return (hex_str);
}
