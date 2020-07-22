#include<iostream>
#include<fstream>
#include<chrono>

#include"support.h"
#include"fileHandling.h"

using namespace std;
using namespace std::chrono;

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

    //Timing the process since input
    auto startTime = high_resolution_clock::now(); 

    if(fileType(input_amount) == "txt")         //Check if the input is a TXT, process.
    {
        bool result = processTXT(input_amount, language_choice, system_choice);

        if(result)
            cout << "\nFile converted succesfully.\n";
        else
            cout << "\nThere was a problem converting the file.\n";       
    }
    else if(fileType(input_amount) == "csv")    //Check if the input is a CSV, process.
    {
        bool result = processCSV(input_amount, language_choice, system_choice);

        if(result)
            cout << "\nFile converted succesfully.\n";
        else
            cout << "\nThere was a problem converting the file.\n";
    }
    else if(checkInput(input_amount))          //Check if the input is an amount, process.
    {
        cout << "\n₹ " << input_amount << " = ";
        cout << currencyToText(input_amount, language_choice, system_choice);
    }
    else
    {
        cout << "ERR : Invalid Input, please try again.\n\n";
        goto start;
    }

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime); 
    cout << "\n\nProcess Duration : " << duration.count() << "ms";

    //Repeat Loop
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
