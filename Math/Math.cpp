#include "Math.h"

int carry = 0;

char itoa(int num){
    return num + 48;
}

int atoi(char ch){
    return ch - 48;
}

std::string operator+(Math& num1,Math& num2){
    std::string result = "";
    const int Lastindex1 = num1.size() - 1;
    const int Lastindex2 = num2.size() - 1;
    int ResultSize = (Lastindex1>Lastindex2)?Lastindex1:Lastindex2;

    for(int i=0;i<=ResultSize || carry;i++){
        int firstNum = atoi(num1[Lastindex1-i]);
        int SecondNum = atoi(num2[Lastindex2-i]);
        if(Lastindex1 - i < 0){
            firstNum = 0;
        }
        if(Lastindex2 - i < 0){
            SecondNum = 0;
        }
        int sum = firstNum + SecondNum + carry;
        carry = sum/10;
        sum = sum%10;
        result = itoa(sum) + result;
    }

    return result;
}

