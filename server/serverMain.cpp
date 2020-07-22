//Compiled as
//g++ -o server serverMain.cpp -std=c++1y -L/usr/lib64/ -lboost_system -lboost_thread -pthread

#include "crow_all.h"
//#include "../support.h"
#include "application.cpp"

int main()
{
    crow::SimpleApp application;                    //Makes an app
    setAPP(&application);                           //Sets the rules for API
    
    application.port(18080).multithreaded().run();  //Runs the API
}