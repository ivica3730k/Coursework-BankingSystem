#include "pch.h"

int main()
{	
	
	database db("database.db"); 
   

	std::string a = "olakilowatt";
	std::string hash_a = db.hash(&a);

	std::string b = "olakilowatt";
	std::string hash_b = db.hash(&b);
	std::cout << hash_b;

	if (a == b) {
		std::cout << "Uspjesno" << std::endl;
	}
	
	
}
