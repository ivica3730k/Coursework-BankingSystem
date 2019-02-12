#include "pch.h"




database::database(const char *path)
{
	std::cout << sqlite3_open(path, &db) << std::endl;
	
}

string database::hash(string * data)
{
	string src_str = *(data);
	std::vector<unsigned char> hash(picosha2::k_digest_size);
	picosha2::hash256(src_str.begin(), src_str.end(), hash.begin(), hash.end());
	std::string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
	//std::cout << hex_str << std::endl;
	return(hex_str);
}

bool database::createUser(string * name, string * surname, string * eMail, string * password, bool isAdmin)
{
	
	return false;
}
