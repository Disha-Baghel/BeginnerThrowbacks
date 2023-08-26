#ifndef MATH_H
#define MATH_H

#include <string>

class Math{
    std::string num;
public:
    Math(std::string num){this->num = num;}
    int size(){return num.size();}
    char operator[](int index){
        return num[index];
    }
    friend std::string operator+(Math& num1,Math& num2);
};

std::string operator+(Math& num1,Math& num2);

#endif // MATH_H
