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

void user::getAditionalInfo(string* email)
{
	additionalData data;
	menu::completeData(data);
	db->updateUserDetails(email, data);
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

int menu::adminMenu(void)
{
	cout << "1.Add user" << endl;
	cout << "2.Remove user" << endl;
	cout << "3.List all users" << endl;
	cout << "4.Check user by eMail" << endl;

	return 0;
}

void menu::completeData(additionalData& data)
{

	cout << "Input your Title, Mr., Mrs., Ms. and Miss: ";
	
	getline(std::cin, data.title);
	std::transform(data.title.begin(), data.title.end(), data.title.begin(), ::tolower);
	data.title[0] = toupper(data.title[0]);

	while (data.title != "Mr" && data.title != "Mrs" && data.title != "Ms" && data.title != "Miss") {
		cout << "\nWrong input,try again!" << endl;
		cout << "Input your Title, Mr., Mrs., Ms. and Miss: ";
		
		getline(std::cin, data.title);
		std::transform(data.title.begin(), data.title.end(), data.title.begin(), ::tolower);
		data.title[0] = toupper(data.title[0]);
	}

	cout << "\nInput your Nationality: ";
	
	getline(std::cin, data.nationality);
	std::transform(data.nationality.begin(), data.nationality.end(), data.nationality.begin(), ::tolower);
	data.nationality[0] = toupper(data.nationality[0]);
	cout << "\nInput birth date > DAY: ";
	unsigned int day;
	cin >> day;
	while ((getchar()) != '\n');

	while (day > 31 || day < 1) {
		cout << "\nWrong input,try again (Day must be from 1 to 31)" << endl;
		cout << "Input birth date > DAY:";
		cin >> day;
		while ((getchar()) != '\n');
	}

	cout << "\nInput birth date > MONTH: ";
	unsigned int month;
	cin >> month;
	while ((getchar()) != '\n');

	while (month > 12 || month < 1) {
		cout << "\nWrong input,try again (Month must be from 1 to 12)" << endl;
		cout << "Input birth date > DAY:";
		cin >> month;
		while ((getchar()) != '\n');
	}

	cout << "\nInput birth date > YEAR: ";
	unsigned int year;
	cin >> year;
	while ((getchar()) != '\n');

	data.dateOfBirth = fmt::format("{0}/{1}/{2}", day, month, year);

	cout << "\nInput place of birth: ";
	
	getline(std::cin, data.placeOfBirth);

	cout << "\nInput your full Address: ";
	
	getline(std::cin, data.address);

	cout << "\nInput full phone number: ";
	
	getline(std::cin, data.phonenum);
}
