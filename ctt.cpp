#include<iostream>
#include<fstream>
#include<stdio.h>

#include"support.h"

using namespace std;

string currencyToText(string amount, char language_choice = 'e', char system_choice = 'w')
{
    switch (language_choice)
    {
        case 'h' :  setLanguage("dictionaries/hindiNumbers.txt");
                    break;
        case 'm' :  setLanguage("dictionaries/marathiNumbers.txt");
                    break;
        case 'b' :  setLanguage("dictionaries/bengaliNumbers.txt");
                    break;
        case 'g' :  setLanguage("dictionaries/gujaratiNumbers.txt");
                    break;
        case 'e' :  setLanguage("dictionaries/englishNumbers.txt");
                    break;
    }

    string returnString = "";

    if(system_choice == 'w') // Western Number system ... 999,001,101,010.89
    {
        //Substrings should be read from indices {0, 3, 6, 9};

        string lables[] = { languageSymbols[104],   // "Billion "
                            languageSymbols[105],   // "Million "
                            languageSymbols[102]};  // "Thousand "

        int lable_no = 0;
        for(int pos = 0; pos < 12; pos +=3)
        {
            returnString += symbol( stoi( amount.substr(pos, 3) ) );    // Symbol function gives a three
            if(stoi(amount.substr(pos,3)))                              // digit number's text equivalent
                if(lable_no < 3)                                        // in any language
                    returnString += lables[lable_no];

            lable_no++;
        }
    }

    if(system_choice == 'i') // Indian Number system ... 9,99,00,11,01,010.89  or 9,00,00,10,00,111.89
    {
        //Substrings should be read from indices {0, 1, 3, 5, 7, 9};

        string lables[] = { languageSymbols[106],   //"खरब "
                            languageSymbols[107],   //"अरब "
                            languageSymbols[100],   //"करोड़ "
                            languageSymbols[101],   //"लाख "
                            languageSymbols[102]};  //"हज़ार "

        //Fixing the left most possible digit, if exists
        returnString += symbol( stoi( amount.substr(0, 1) ) );          // Symbol function gives a three
        if(stoi(amount.substr(0,1)))                                    // digit number's text equivalent
                returnString += lables[0];                              // in any language

        //Fixing intermediate digits
        int lable_no = 1;
        for(int pos = 1; pos < 9; pos +=2)
        {
            returnString += symbol( stoi( amount.substr(pos, 2) ) );
            if(stoi(amount.substr(pos,2)))
                if(lable_no < 5)
                    returnString += lables[lable_no];

            lable_no++;
        }

        //Fixing the last 3 digits
        returnString += symbol( stoi( amount.substr(9, 3) ) );
    }

    fstream logFile("ignored/output-logs/outputs.txt", fstream::app);
    if(logFile.is_open())
    {
        logFile << amount << endl;
        logFile << '\t' << uniformSpacing(returnString) << endl;
    }
    logFile.close();

    return uniformSpacing(returnString);
}

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
