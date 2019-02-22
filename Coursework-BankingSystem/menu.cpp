#include "pch.h"
#include "menu.h"


menu::menu(UserData *data, user &_user)
{
	userdata = data;
	userset = &_user;

	email = data->email;
	name = data->name;
	surname = data->surname;
	lastLogOut = data->lastLogOut;
	isAdmin = data->isAdmin;
	admin = false;

	if (isAdmin == "Yes")
		admin = true;

}


menu::~menu()
{
}

int menu::display(void)
{
	if (lastLogOut == "Never")
		completeData();

	if (admin) {
		
		adminMenu();
	}
	else{
		
		completeData();
	}

	return(1);
}

void menu::adminMenu(void)
{
	int choice = 0;
	do{
		cout << endl;
		cout << endl;
		cout << "1.Display user area" << endl;
		cout << "2.Add user" << endl;
		cout << "3.Remove user" << endl;
		cout << "4.List all users" << endl;
		cout << "5.Check user by eMail" << endl;
		cout << "0. LogOut from system" << endl;
		cout << "\nInput your choice: ";
		cin >> choice;
		while ((getchar()) != '\n');

		

		switch (choice) {
		case 2:
			userset->add();
			break;
		case 4:
			userset->listAll();
			break;
		case 5:
			userset->checkByeMail(&email);
			break;
		}
		
	
	} while (choice != 0);

	userset->logout(&email);
}

void menu::userMenu(void)
{
}

bool menu::completeData(void)
{
	additionalData data;
	cout << "It seams that you have never logged in before!" << endl;
	cout << "Please complete aditional details in order to use system.\n" << endl;
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

	cout << "Now, please login again!" << endl;
	userset->logout(&email);
	return true;
	
}
