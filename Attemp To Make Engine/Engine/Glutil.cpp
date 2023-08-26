#include "Glutil.h"

bool OutErrorMsg(const char* message)
{
    MessageBox(NULL,message,NULL,MB_OK|MB_ICONERROR);
    return false;
}
