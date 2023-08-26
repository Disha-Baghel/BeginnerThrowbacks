#include "Error.h"
#include <windows.h>

Error::Error(std::string Err_str,Error_enum Err_enum)
{
	Error_str   = Err_str;
	Err_enum	= this->Err_enum;
}

void Error::what()
{
	UINT ErrorFlag;
	std::string Error_Title;

	switch(Err_enum)
	{
		default:
		case Err_Warning:	ErrorFlag = MB_ICONWARNING;		Error_Title	= "Warning";		break;
		case Err_ShutDown:	ErrorFlag = MB_ICONEXCLAMATION;	Error_Title = "ShutDown";		break;
	}
	MessageBox(NULL,Error_str.c_str(),Error_Title.c_str(),ErrorFlag);

	exit(0);
}
