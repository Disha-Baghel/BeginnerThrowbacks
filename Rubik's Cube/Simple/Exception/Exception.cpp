#include <windows.h>
#include "Exception.h"

Exception::Exception(std::string error,Error_Type Et)
{
    this->errorStr = error;
    ErrType = Et;
}

Error_Type Exception::what()
{
    UINT Msg;
    std::string ErrTitle;

    switch(ErrType)
    {
        default:
        case SHOW_ERROR:        Msg = MB_ICONERROR;         ErrTitle = "Error";             break;
        case SHOW_INFORMATION:  Msg = MB_ICONINFORMATION;   ErrTitle = "Information";       break;
        case SHOW_WARNING:      Msg = MB_ICONWARNING;       ErrTitle = "Warning";           break;
        case SHOW_SHUTDOWN:     Msg = MB_ICONEXCLAMATION;   ErrTitle = "Shutting Down";     break;
    }

    MessageBox(NULL,errorStr.c_str(),ErrTitle.c_str(),MB_OK|Msg);

    if(ErrType == SHOW_SHUTDOWN)
        exit(0);

    return ErrType;
}
