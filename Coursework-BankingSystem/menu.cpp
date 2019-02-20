#include "pch.h"
#include "menu.h"


menu::menu(UserData *data, user &_user)
{
	userdata = data;
	userset = &_user;

	email = data->email;
	name = data->name;
	surname = data->surname;
	lastLogin = data->lastLogin;
	isAdmin = data->isAdmin;
	admin = false;

	if (isAdmin == "Yes")
		admin = true;

}


menu::~menu()
{
}

void menu::display(void)
{
	if (admin) {
		if (lastLogin == "Never")
			completeData();
		adminMenu();
	}
	else{
		if (lastLogin == "Never")
			completeData();
	}
}

void menu::adminMenu(void)
{
	cout << "1.Add user" << endl;
	cout << "2.Remove user" << endl;
	cout << "3.List all users" << endl;
	cout << "4.Check user by eMail" << endl;

	
}

void menu::completeData(void)
{
	additionalData data;
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

	userset->writeAdditionalInfo(&email, data);
}
