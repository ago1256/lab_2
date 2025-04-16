#pragma once

#include<iostream>
#include <stdexcept>
#include <string>

class Error{
    private:
        int code;
        std::string mess;
        const std::string errors[6]{
            "ОК",//0
            "Неизменяемая последовательность.\n ",//1
            "Неправильный индекс.\n ",//2
            "Неправильный аргумент.\n ",//3
            "Пустая последовательность.\n",//4,
            "Несовместимые типы.\n "//5
        };
    public:
    Error(int c){
        code = c;
        mess = errors[c];
    }
    std::string get_mess(){
        return mess;
    }
    int get_code(){
        return code;
    }

    void errors_detection(int c) {
    Error error = Error(c);
    if (error.get_code() == 0) {
        std::cout << error.get_mess();
        return;
    }
    else{
        std::cout << error.get_mess();
    }
}
};

void errors_detection(int er);
