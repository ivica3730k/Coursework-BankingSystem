#include "pch.h"
#include "user.h"


user:: user(database &_db)
{
	db = &_db;
}

bool user:: add(void)
{
	string name;
	string surname;
	string email;
	string password;
	string isAdmin;

	cout << "Input user first name: ";
	//cin >> name;
	getline(std::cin, name);
	cout << "\nInput user last name: ";
	//cin >> surname;
	getline(std::cin, surname);
	cout << "\nInput user eMail address: ";
	//cin >> email;
	getline(std::cin, email);
	std::transform(email.begin(), email.end(), email.begin(), ::tolower);
	cout<< "\nInput user password,user can change later: ";
	//cin >> email;
	getline(std::cin, password);

	while (password.length() < 8) {
		cout << "\nSorry, password must be 8 letters minimum!";
		cout << "\nInput user password,user can change later: ";
		//cin >> email;
		getline(std::cin, password);
	}

	cout << "\nIs user administrator y/n: ";
	//cin >> isAdmin;
	getline(std::cin, isAdmin);
	std::transform(isAdmin.begin(), isAdmin.end(), isAdmin.begin(), ::tolower);

	while (isAdmin != "y" && isAdmin != "n") {
		cout << "\nWrong input, try again!";
		cout << "\nIs user administrator y/n: ";
		cin >> isAdmin;
	}

	bool admin = false;

	if (isAdmin == "y") {
		admin = true;
	}

	return(db->createUser(&name, &surname, &email, &password, admin));

	
}

bool user::add(string * name, string * surname, string * eMail, string * password, bool isAdmin)
{
	string pass = *password;
	if (pass.length() < 8)
		return false;
	return(db->createUser(name, surname, eMail, &pass, isAdmin));
}

bool user::add(const char *name, const char *surname, const char * eMail, const char * password, bool isAdmin)
{
	string _name(name);
	string _surname(surname);
	string _email(eMail);
	string _password(password);
	bool Admin = isAdmin;
	return(db->createUser(&_name, &_surname, &_email, &_password, Admin));
}

bool user::del(void)
{
	cout << "Input email of the user you want to delete:";
	string mail;
	getline(std::cin, mail);
	std::transform(mail.begin(), mail.end(), mail.begin(), ::tolower);
	bool exec = db->deleteUser(&mail);
	return(false);
}

bool user::del(string * email)
{
	string _email = *email;
	std::transform(_email.begin(), _email.end(), _email.begin(), ::tolower);
	bool exec = db->deleteUser(email);
	return (exec);
}