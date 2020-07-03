#include<iostream>
#include<fstream>
#include<stdio.h>
#include<time.h>

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

    cout << "Choose Language (e/h/m/b/g) : ";
    char language_choice;
    cin >> language_choice;
    {
        char languages[] = {'e','h','b','g','m'};
        bool language_ok = false;
        for(char k : languages)
            if(k == language_choice) language_ok = true;
        if(!language_ok)
        {
            cout << "ERR : Invalid Input, please try again.\n\n";
            goto start;
        }
    }

    cout << "Select Number System (w/i) : ";
    char system_choice;
    cin >> system_choice;
    if(system_choice != 'w' && system_choice != 'i')
    {
        cout << "ERR : Invalid Input, please try again.\n\n";
        goto start;
    }

    

    time_t startTime;
    time(&startTime);
    //cout << "\nProcess Begins at : " << startTime <<endl;

    if(isFile(input_amount))
    {
        //cout<<"This one's a file.\n";
        bool result = processFile(input_amount, language_choice, system_choice);

        if(result)
            cout << "\nFile converted succesfully.\n";
    }
    else if(checkInput(input_amount))
    {
        cout << "\n₹ " << input_amount << " = ";
        cout << currencyToText(input_amount, language_choice, system_choice);
    }
    else
    {
        cout << "ERR : Invalid Input, please try again.\n\n";
        goto start;
    }
    
    time_t endTime;
    time(&endTime);
    //cout << "\nProcess ends at : " << endTime << endl;

    double executionTime = difftime(startTime, endTime);
    cout << "\n\nProcess Duration : " << executionTime << " seconds";

    cout << "\nConvert again? (y/n) : ";
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
