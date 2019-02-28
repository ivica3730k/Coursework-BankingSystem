#include "pch.h"
#include "menu.h"


menu::menu(UserData *data, user &_user,bank &_bk)
{
	userdata = data;
	userset = &_user;
	banking = &_bk;

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
	if (lastLogOut == "Never") {
		completeData();
		userset->logout(&email);
		system("CLS");
		cout << "Now, please login again!" << endl;
		return(1);

	}

	if (admin) {
		
		adminMenu();
	}
	else{
		
		userMenu();
	}

	return(1);
}

void menu::adminMenu(void)
{
	int choice = 0;
	
	do{

		cout << "1.Display user area" << endl;
		cout << "2.Add user" << endl;
		cout << "3.Remove user" << endl;
		cout << "4.List all users" << endl;
		cout << "5.Check user by eMail" << endl;
		cout << "6.List all currencies on system" << endl;
		cout << "7.Add currency to system" << endl;
		cout << "0.LogOut from system" << endl;
		cout << "\nInput your choice: ";
		cin >> choice;
		while ((getchar()) != '\n');

		

		switch (choice) {

		case 1:
			userMenu();
			return;
			break;
		case 2:
			clear();
			userset->add();
			//wait();
			break;
		case 3:
			clear();
			userset->listAll();
			userset->del();
			//wait();
			break;
		case 4:
			clear();
			userset->listAll();
			//wait();
			//clear();
			break;
		case 5:
			clear();
			userset->checkByeMail();
			//wait();
			//clear();
			break;
		case 6:
			clear();
			banking->getCurenciesTable();
			break;
		case 7:
			clear();
			banking->addCurrency();
			break;
		}
		
		if (choice != 0) {
			wait();
			clear();
		}
	} while (choice != 0);

	userset->logout(&email);
	system("CLS");
	
}

void menu::userMenu(void)
{
	int choice = 0;
	do {
		
		std::cout << "1.Display personal information" << std::endl;
		std::cout << "2.Change password" << std::endl;
		std::cout << "3.Check personal balance" << std::endl;
		std::cout << "4.Send virtual currency to other user on platform" << std::endl;
		std::cout << "5.Export virual currency to a file." << std::endl;

		if (admin)
			std::cout << "Return to Admin menu!" << std::endl;
		std::cout << "0.LogOut from system" << std::endl;
		cout << "\nInput your choice: ";
		std::cin >> choice;
		while ((getchar()) != '\n');

		switch (choice) {
		case 1:
			clear();
			userset->checkByeMail(&email);
			break;
		case 2:
			clear();
			userset->changePass(&email);
			break;
		case 3:
			clear();
			banking->printAllBalance(&email);
			break;

		case 4:
			clear();
			banking->transferBalance(&email);
			break;
		case 5:
			clear();
			banking->exportBalance(&email);
			break;
		}
		
		

		if (choice != 0) {
			wait();
			clear();
		}
	} while (choice != 0);

	
}

void menu::completeData(void)
{
	additionalData data;
	std::cout << std::endl;
	system("CLS");
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

	
}


void menu::updateData(void)
{
	additionalData data;
	std::cout << std::endl;
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

void menu::wait(void)
{
	std::cout << "\nPress any key to continue." << std::endl;
	cin.get();
}

void menu::clear(void)
{
	system("CLS");
}

bool menu::boolInput(void)
{
	std::string input;
	cout << "Input 'y' for yes and 'n' for no: ";
	getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);

	while (input != "y" && input != "n") {
		cout << "\nWrong input, try again!";
		cout << "\nIs user administrator y/n: ";
		getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	}
	
	

	if (input == "y") {
		return(true);
	}
	return false;
}
