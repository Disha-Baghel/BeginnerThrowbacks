#include <fstream>
#include <iostream>
#include <string.h>
#include "SQL.h"

void show(std::string file_name)
{
    file_name += ".dat";
    TABLE table;
    std::fstream file(file_name.c_str());
    std::cout<<"\n\tName\t\tRoll\t\tClass\n";
    while(file.read((char*)&table,sizeof(table)))
    {
        std::cout<<"\n\t"<<table.name<<"\t\t"<<table.roll<<"\t\t"<<table.Class;
    }
    std::cout<<std::endl;
    file.close();
}

void add(std::string file_name,const char* name,int roll,int Class)
{
    file_name += ".dat";
    TABLE temp;
    strcpy(temp.name,name);
    temp.roll = roll;
    temp.Class = Class;
    std::ofstream file(file_name.c_str(),std::ios::app);
    if(roll != 0 && Class != 0)
        file.write((char*)&temp,sizeof(temp));
    file.close();
}
