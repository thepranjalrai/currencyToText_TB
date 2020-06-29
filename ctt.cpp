#include<iostream>
#include<fstream>
#include<stdio.h>

#include"support.h"

using namespace std;

//ENTRY-POINT MAIN FUNCTION
int main()
{
    cout << "\n\n.........................\n\n";

start:
    cout << "Enter the amount : ";
    string input_amount;
    cin >> input_amount;

    if(!checkInput(input_amount))
    {
        cout << "ERR : Invalid Input, please try again.\n\n";
        goto start;
    }

    string amount = refitNumber(input_amount);  //Standardises string as "000000000000.00"
    string fraction_part = amount.substr(13,2); //Seperates two digit fraction

    cout << "Choose Language (e/h/m/b/g) : ";
    char language_choice;
    cin >> language_choice;

    cout << "Select Number System (w/i) : ";
    char system_choice;
    cin >> system_choice;

    cout << "\n₹ " << amount << " = ";
    cout << currencyToText(amount, language_choice, system_choice);
    cout << "" << fraction_part << "/100.";

    cout << "\n\n.........................\n\n";
}
