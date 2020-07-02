#include<iostream>
#include<fstream>
#include<stdio.h>

#include"support.h"
#include"fileHandling.h"

using namespace std;

//ENTRY-POINT MAIN FUNCTION
int main()
{
    cout << "\n\n.........................\n\n";

start:
    cout << "Enter the AMOUNT or FILE PATH (.txt) : ";
    string input_amount;
    cin >> input_amount;

    if(isFile(input_amount))
    {
        //cout<<"This one's a file.\n";
        bool result = processFile(input_amount);

        if(result)
            cout << "\nFile converted succesfully.\n";
            
        exit(0);
    }

    if(!checkInput(input_amount))
    {
        cout << "ERR : Invalid Input, please try again.\n\n";
        goto start;
    }

    string amount = refitNumber(input_amount);  //Standardises string as "000000000000.00"
    
    cout << "Choose Language (e/h/m/b/g) : ";
    char language_choice;
    cin >> language_choice;

    cout << "Select Number System (w/i) : ";
    char system_choice;
    cin >> system_choice;

    cout << "\n₹ " << amount << " = ";
    cout << currencyToText(amount, language_choice, system_choice);

    cout << "\n\nConvert again? (y/n) : ";
    char ans;
    cin >> ans;
    if(ans == 'y')
    {
        cout << endl;
        goto start;
    }

end:
    cout << "\n\n.........................\n\n";
}
