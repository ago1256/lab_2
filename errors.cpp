#include"errors.h"
#include<stdio.h>
#include<iostream>


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

