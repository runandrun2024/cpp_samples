#include <vector>
#include <string>
#include <sstream>      // std::ostringstream
#include <iostream>
#include <string.h>
#include <algorithm>

#if 0
void split(const std::string &str, const std::string& delim, std::vector<std::string>& i_tokens)
{
	
    std::stringstream ss(str);
    std::string buffer;
    while( std::getline(ss, buffer, sep) ) {
        v.push_back(buffer);
    }
    return v;
}
#endif

void split(const std::string& str, const std::string& delim, std::vector<std::string>& i_tokens)
{
	std::string tmp_str{str};

	char* p_last;
	auto p = strtok_r(const_cast<char*>(tmp_str.c_str()), delim.c_str(), &p_last);
	while(p)
	{
		std::string token{p};
		std::transform(token.begin(), token.end(), token.begin(), [](char c){
				return std::toupper(c, std::locale());
			});
		i_tokens.push_back(token);
		p = strtok_r(nullptr, delim.c_str(), &p_last);
	}
}


int main()
{
	static const char* sqls[] = {
		"   select * from \t tbl1   ",
		"create database my_database",
		"create schema my_schema",
		"create table tbla (COl integer)",
	};
	
	std::vector<std::string> tokens;

	for (auto p : sqls)
	{
		tokens.clear();
		split(p, " \t()", tokens);

		std::cout << "SQL : [" << p << "]" << std::endl;
		
		for (auto token : tokens)
			std::cout << token << std::endl;
	}
	return 0;
}

