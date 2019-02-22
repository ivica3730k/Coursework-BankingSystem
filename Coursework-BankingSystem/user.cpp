#include "pch.h"
#include "user.h"

user::user(database& _db)
{
	db = &_db;
}

bool user::login(UserData& data)
{
	std::string email;
	std::string pass;

	std::cout << "Enter User eMail: ";
	getline(std::cin, email);
	std::transform(email.begin(), email.end(), email.begin(), ::tolower);

	std::cout << "\nEnter user password: ";
	getline(std::cin, pass);

	return db->loginUser(&email, &pass, data);
}

bool user::login(string* email, string* password, UserData& data)
{
	return db->loginUser(email, password, data);
}
bool user::checkByeMail(string * mail)
{
	std::vector<string> data;
	bool exec = db->checkAllDetails(mail, &data);
	if (exec) {
		/*VariadicTable<std::string, std::string, std::string, string, std::string, std::string, string, std::string, std::string, string> vt({ "name","surname","eMail","lastLogOut","title","nationality","dateOfBirth","placeOfBirth","address","phoneNum" });
		vt.addRow({data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9] });
		vt.print(std::cout);*/

		std::vector<std::string> fields = { "First Name","Surname","eMail","Last LogOut","Title","Nationality","Date Of Birth","Place Of Birth","Address","Phone number" };

		for (int i = 0; i < 10; i++) {
			std::cout << fields[i] << ": " << data[i] << endl;
		}
	}
	return false;
}
bool user::writeAdditionalInfo(string * email, additionalData  data)
{
	return(db->updateUserDetails(email,data));
}

bool user::logout(string* email)
{
	db->setlastLogOut(email);
	return true;
}

bool user::add(void)
{
	string name;
	string surname;
	string email;
	string password;
	string isAdmin;

	cout << "Input user first name: ";
	getline(std::cin, name);
	cout << "\nInput user last name: ";
	getline(std::cin, surname);
	cout << "\nInput user eMail address: ";
	getline(std::cin, email);
	std::transform(email.begin(), email.end(), email.begin(), ::tolower);
	cout << "\nInput user password,user can change later: ";
	getline(std::cin, password);
	
	while (password.length() < 8) {
		cout << "\nSorry, password must be 8 letters minimum!";
		cout << "\nInput user password,user can change later: ";
		getline(std::cin, password);
	}
	
	cout << "\nIs user administrator y/n: ";
	getline(std::cin, isAdmin);
	std::transform(isAdmin.begin(), isAdmin.end(), isAdmin.begin(), ::tolower);

	while (isAdmin != "y" && isAdmin != "n") {
		cout << "\nWrong input, try again!";
		cout << "\nIs user administrator y/n: ";
		getline(std::cin, password);
	}

	bool admin = false;

	if (isAdmin == "y") {
		admin = true;
	}

	return (db->createUser(&name, &surname, &email, &password, admin));
}

bool user::add(string* name, string* surname, string* eMail, string* password, bool isAdmin)
{
	string pass = *password;
	if (pass.length() < 8)
		return false;
	return (db->createUser(name, surname, eMail, &pass, isAdmin));
}

bool user::add(const char* name, const char* surname, const char* eMail, const char* password, bool isAdmin)
{
	string _name(name);
	string _surname(surname);
	string _email(eMail);
	string _password(password);
	bool Admin = isAdmin;
	return (db->createUser(&_name, &_surname, &_email, &_password, Admin));
}

bool user::del(void)
{
	cout << "Input email of the user you want to delete:";
	string mail;
	getline(std::cin, mail);
	std::transform(mail.begin(), mail.end(), mail.begin(), ::tolower);
	bool exec = db->deleteUser(&mail);
	return (false);
}

bool user::del(string* email)
{
	string _email = *email;
	std::transform(_email.begin(), _email.end(), _email.begin(), ::tolower);
	bool exec = db->deleteUser(email);
	return (exec);
}

bool user::listAll(void)
{
	std::vector<string> userData;
	bool exec = db->listAllUsers(&userData);
	if (exec) {
		VariadicTable<std::string, std::string, std::string> vt({ "Name", "Surname", "EMail" });

		std::vector<string>::iterator i;

		for (i = userData.begin(); i < userData.end(); ++i) {

			std::string name = *i;
			++i;
			std::string surname = *i;
			++i;
			std::string email = *i;

			vt.addRow({ name, surname, email });
		}

		vt.print(std::cout);
	}
	else {
		std::cout << "Failed creating table!" << std::endl;
	}
	return exec;
}
