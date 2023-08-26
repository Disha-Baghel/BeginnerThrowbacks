#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

enum Error_Type{
                    SHOW_ERROR,
                    SHOW_INFORMATION,
                    SHOW_WARNING,
                    SHOW_SHUTDOWN
                };

class Exception
{
    std::string errorStr;
    Error_Type ErrType;
    public:
        Exception(std::string error,Error_Type Et = SHOW_ERROR);
        Error_Type what();
};

#endif // EXCEPTION_H
