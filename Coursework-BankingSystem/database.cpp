#include "pch.h"
#include "database.h"

database::database(const char* path)
{
	sqlite3_open(path, &db);
}
//User specific database functions
bool database::createUser(string* name, string* surname, string* eMail, string* password, bool isAdmin)
{	
	string admin = "No";
	if (isAdmin)
		admin = "Yes";
	bool exists = checkUser(eMail).isValid;

	if (exists == false) {
		char* zErrMsg = 0;
		char* sql = nullptr;
		std::string _query = fmt::format("INSERT INTO `users`(`name`,`surname`,`eMail`,`password`,`isAdmin`,`lastLogOut`) VALUES ('{0}','{1}','{2}','{3}','{4}','{5}');", *(name), *(surname), *(eMail), hash(password), admin, "Never");
		bool rc = executeQuery(&_query, noCallback);
		
	
		
		if (rc) {
			createUserBalance(eMail);
			return (true);
		}
		else {
			
			
			return (false);
		}
	}
	std::cout << "DATABASE: User probably already exists" << std::endl;
	return (false);
}
bool database::createUserBalance(string * email)
{
	std::string query = fmt::format("INSERT into balance ('eMail') VALUES ('{0}');", *email);
	return(executeQuery(&query, noCallback));
}
bool database::deleteUser(string * email)
{
	if (checkUser(email).isValid) {
		string query = fmt::format("DELETE from users where eMail = '{0}';", *email);
		deleteUserBalance(email);
		return executeQuery(&query, noCallback);
	}
	
	else {
		
		return(false);
	
	}
}
bool database::loginUser(string* email, string* password, UserData &_data)
{
	UserData data;
	data = checkUser(email);
	_data = data;

	if (data.isValid == true) {

		if (data.password == hash(password)) {

			if (data.lastLogOut != "Never") {
				system("CLS");
				std::cout << "DATABASE: Login Succesfull" << std::endl;
				
			}
			cout << "Last Logout " << data.lastLogOut << endl;
			return (true);
		}
		else {
			system("CLS");
			std::cout << "DATABASE: Wrong password" << std::endl;
			return (false);
		}
	}

	else {
		system("CLS");
		std::cout << "DATABASE: User with this eMail address does not exist in database!" << std::endl;
		return (false);
	}
}
bool database::changePassword(string * email, string * oldpass, string * newpass)
{
	std::string query1 = fmt::format("SELECT password from users where eMail = '{0}';", *email);
	std::string dbpass;
	bool a = executeQuery(&query1, callbackOneString, (void*)&dbpass);
	if (a) {
		if (hash(oldpass) == dbpass) {
			query1 = fmt::format("UPDATE 'users' set 'password' = '{0}' where email = '{1}';", hash(newpass), *email);
			return(executeQuery(&query1, noCallback));
		}
	}

	return false;


}
bool database::setlastLogOut(string* email)
{
	std::string query = fmt::format("UPDATE `users` SET `lastLogOut`= '{0}' WHERE eMail = '{1}';", returnTime(), *email);
	return (executeQuery(&query, noCallback));
}
bool database::updateUserDetails(string * email, additionalData &data)
{
	std::string query = fmt::format("UPDATE `users` SET `title`='{0}', `nationality` = '{1}', `dateOfBirth` = '{2}', `placeOfBirth` = '{3}', `address` = '{4}', `phonenum` = '{5}' WHERE eMail = '{6}';", data.title, data.nationality, data.dateOfBirth, data.placeOfBirth, data.address, data.phonenum, *email);
	bool exec = executeQuery(&query, noCallback);

	return(exec);
}
bool database::checkAllDetails(string * email, std::vector<std::string>* data)
{
	if (checkUser(email).isValid) {
		std::string query = fmt::format("SELECT name,surname,eMail,lastLogOut,title,nationality,dateOfBirth,placeOfBirth,address,phoneNum FROM users where eMail = '{0}';", *email);
		return(executeQuery(&query, callbackToVector, (void*)data));
	}
	return(false);
}
bool database::listAllUsers(std::vector<string> *a)
{

	std::string query = "SELECT name ,surname,eMail FROM users;";
	bool exec = executeQuery(&query, callbackToVector, (void*)a);
	return exec;

}

//Banking specific database functions
bool database::checkCurrencies(std::vector <std::string> *currset)
{

	std::string query = "SELECT currency,label FROM currencies;";
	return(executeQuery(&query, callbackToVector, (void*)currset));
}
bool database::addCurrency(string * name, string * label)
{
	std::string testQuery = fmt::format("SELECT *  from currencies where currency = '{0}';", *name);

	std::vector<std::string> currset;
	checkCurrencies(&currset);

	bool exsist = std::find(currset.begin(), currset.end(), *name) != currset.end();

	if (exsist == false) {
		std::string query = fmt::format("INSERT into currencies ('currency','label') VALUES ('{0}','{1}');", *name, *label);
		std::string query2 = fmt::format("ALTER TABLE balance ADD column '{0}' REAL default '0';", *label);
		bool exec1 = executeQuery(&query, noCallback);
		bool exec2 = executeQuery(&query2, noCallback);

		if (exec1 || exec2)
			return true;
	}


	cout << "This currency already is present in the system" << endl;

	return false;

}

bool database::checkBalance(std::vector<std::string>* balance, string * email)
{
	std::string query = fmt::format("SELECT * from balance where eMail = '{0}';", *email);
	bool exec = executeQuery(&query, callbackToVectorColNames, (void*)balance);
	
	if (exec) {
		balance->erase(balance->begin());
		balance->erase(balance->begin());
		return true;
	}
	return false;
}

bool database::checkBalance(std::string * balance, std::string * currency, std::string * email)
{

	std::string query = fmt::format("SELECT {1} from balance where eMail = '{0}';", *email,*currency);
	
	bool exec = executeQuery(&query, callbackOneString, (void*)balance);

	if (exec) {
		
		return true;
	}
	return false;
}



//"Helper" functions
UserData database::checkUser(string* email)
{
	UserData dataread;
	UserData* data = &dataread;
	std::string _query = fmt::format("SELECT * from users where eMail = '{0}';", *email);
	bool rc = executeQuery(&_query, callbackUsers, (void*)data);
	if (rc == false) {

		dataread.isValid = false;
	}
	else {
	}
	
	return dataread;
}
unsigned long int database::getLastTransferId(void)
{
	std::string query = "SELECT id FROM transfers ORDER BY id DESC LIMIT 1;";
	std::string data = "";
	executeQuery(&query, callbackOneString, (void*)&data);
	if (data == "")
		return (0);

	return (stoi(data));
}
bool database::logTransfer(string * senderMail, string * receiver, double amount,string* currency)
{
	std::string query = fmt::format("INSERT INTO transfers ('senderEmail','receiver','amount','currency','claimed','createdOn') VALUES ('{0}','{1}','{2}','{3}','{4}','{5}');", *senderMail, *receiver, amount, *currency, "No",returnTime());
	return(executeQuery(&query, noCallback));
}
bool database::logExportTransfer(string * senderMail, string * receiver, double amount, string * currency)
{
	std::string query = fmt::format("INSERT INTO transfers ('senderEmail','receiver','amount','currency','claimed','createdOn') VALUES ('{0}','{1}','{2}','{3}','{4}','{5}');", *senderMail, *receiver, amount, *currency, "No", returnTime());
	return(executeQuery(&query, noCallback));
}
bool database::readExportLog(unsigned long int id, balance & data)
{
	std::string query = fmt::format("SELECT * FROM transfers where id = {0};", id);
	std::vector <std::string> cache;
	bool exec = executeQuery(&query, callbackToVector, (void*)&cache);
	if (exec) {

		data.id = atol(cache[0].c_str());
		data.senderEmail = cache[1];
		data.receiver = cache[2];
		data.amount = atof(cache[3].c_str());
		data.currency = cache[4];
		data.createdOn = cache[5];
		data.claimed = cache[6];
		return true;
	}
	return false;
}
bool database::setClaimed(unsigned long int transferId)
{
	std::string query = fmt::format("UPDATE transfers SET claimed ='Yes' where id = '{0}';", transferId);
	return executeQuery(&query, noCallback);
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
bool database::deleteUserBalance(string * email)
{
	std::string query = fmt::format("DELETE from balance WHERE eMail = '{0}'; ", *email);
	return(executeQuery(&query, noCallback));
}

bool database::setUserBalance(string * email, string * currency, double & balance)
{
	std::string query = fmt::format("update balance set {0} = '{1}' where eMail = '{2}';",*currency,balance,*email);
	return executeQuery(&query, noCallback);
}

//Query specific functions
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

		return (0);
	}

	return (1);
}

//Query specific callback functions
int database::callbackCheckAllUserDetails(void * dataptr, int argc, char ** argv, char ** azColName)
{
	std::vector<string>* store = (std::vector<string>*)dataptr;
	for (int i = 0; i < argc; i++)
		store->push_back(argv[i]);
	return 0;
}
int database::callbackToVector(void * dataptr, int argc, char ** argv, char ** azColName)
{
	std::vector<string>* store = (std::vector<string>*)dataptr;

	for (int i = 0; i < argc; i++) {
		store->push_back(argv[i]);
	}
	return 0;
}
int database::callbackOneString(void * dataptr, int argc, char ** argv, char ** azColName)
{
	std::string * data = (std::string*)dataptr;
	std::string str(argv[0]);
	data[0] = str;

	return (0);
}
int database::callbackToVectorColNames(void * dataptr, int argc, char ** argv, char ** azColName)
{
	std::vector<string>* store = (std::vector<string>*)dataptr;

	for (int i = 0; i < argc; i++) {
		store->push_back(azColName[i]);
		store->push_back(argv[i]);
	}
	return 0;
}
int database::callbackUsers(void* dataptr, int argc, char** argv, char** azColName)
{

	UserData* store = (UserData*)dataptr;
	store->isValid = true;
	store->name = argv[1];
	store->surname = argv[2];
	store->email = argv[3];
	store->password = argv[4];
	store->isAdmin = argv[5];
	store->lastLogOut = argv[6];
	return 0;
}
int database::noCallback(void* dataptr, int argc, char** argv, char** azColName)
{
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}





