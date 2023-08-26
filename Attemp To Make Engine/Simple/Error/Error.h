#ifndef ERROR_H
#define ERROR_H

#include <string>

enum Error_enum{Err_Warning,Err_ShutDown};

class Error
{
	std::string Error_str;
	Error_enum 	Err_enum;
public:
	Error(std::string Err_str,Error_enum Err_enum);
	void what();
};

#endif // ERROR_H
