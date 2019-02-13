#include "pch.h"
#include "auth.h"
using std::string;

string auth::hash(string* data)
{
	string src_str = *(data);
	std::vector<unsigned char> hash(picosha2::k_digest_size);
	picosha2::hash256(src_str.begin(), src_str.end(), hash.begin(), hash.end());
	std::string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
	return (hex_str);
}

auth::auth()
{
	
}


