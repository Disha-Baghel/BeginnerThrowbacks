#include <vector>
#include <iostream>
#include <sstream>
#include "SQL.h"

int main()
{
    std::string cmd;
    bool running  = true;
    while(running)
    {
        std::vector<std::string> command;
        std::cout<<"SQL >> ";
        getline(std::cin,cmd);
        std::stringstream stream(cmd);
        while(stream>>cmd)
            command.push_back(cmd);

        uint8_t i = 0;

        do{
            if(command[0] == "quit")
                running = false;
            else if(command[0] == "help")
            {
                std::cout<<"Commands\n"
                         <<"quit\t\t\t\t closes the program\n"
                         <<"cls\t\t\t\t clears the screen\n"
                         <<"CREATE TABLE <table-name>\t creates a new table with given table name\n"
                         <<"SELECT* FROM <table-name>\t shows all the rows of the table\n"
                         <<"INSERT INTO <table-name> VALUES\t insert new row into the table\n";
            }
            else if(command[0] == "cls")
                system("cls");
            else if(command[i] == "CREATE" && command[i+1] == "TABLE")
            {
                add(command[i+2]);
                break;
            }
            else if(command[i] == "SELECT*" && command[i+1] == "FROM")
            {
                show(command[i+2]);
                break;
            }
            else if(command[i] == "INSERT" && command[i+1] == "INTO" && command[i+3] == "VALUES")
            {
                add(command[i+2],command[i+4].c_str(),atoi(command[i+5].c_str()),atoi(command[i+6].c_str()));
                break;
            }
            else
            {
                std::cout<<"Wrong syntax!\n";
                break;
            }
        }while(++i != command.size());
    }


    return 0;
}
