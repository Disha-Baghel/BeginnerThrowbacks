class TABLE
{
    char name[30];
    int roll;
    int Class;
public:
    friend void show(std::string);
    friend void add(std::string file_name,const char* name,int roll,int Class);
};

void show(std::string);
void add(std::string file_name,const char* name = "NULL",int roll = 0,int Class = 0);
