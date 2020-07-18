#ifndef SUPPORT_H
#define SUPPORT_H

#include<iostream>
#include<string>
using namespace std;
//////////////////////////////////////////////////////

#define inputLength 16

string languageSymbols[108];    //Stores number dictionary of a given language
string symbol(int n)            //retrieves required symbol
{
    string returnWord = "";
    
    if(n > 99)
    {
        returnWord += languageSymbols[n/100];
        returnWord += languageSymbols[103];
    }

    returnWord += languageSymbols[n%100];
    //cout<<returnWord<<endl;
    return returnWord;
}

//Sets the text langauge i.e. loads languageSymbols[]
void setLanguage(string file)
{
    fstream dict(file, fstream::in);

    int i=0;
    while(!dict.eof())
    {
        string word;
        getline(dict, word);
        languageSymbols[i++] = word;
    }

    dict.close();
}

bool checkInput(string input)
{
    bool pastDecimal = false;

    if(input.length() > inputLength || !input.length())
        return false;

    if(input.length() > 12)
        if(input[12] != '.') return false;

    for(int i=0; i < input.length(); i++)
    {   
        if( input[i] > 47 && input[i] < 58)
            continue;
        else if(input[i] == '.' && !pastDecimal)
            pastDecimal = true;
        else 
        {
            //cout << "\n" << input << "_has invalid character : " << int(input[i]);
            return false;
        }

    }

    return true;
}

//Standardises string in "000000000000.00" format
string refitNumber(string amount)
{   
    string returnNumber = "000000000000.00";
    string whole = "";
    string fraction = "";

    //Seperating the $amount as $whole and $fraction
   {
        int i=-1;
        while(++i<amount.length())
        {
            if(amount[i] == '.') break;
            else whole += amount[i];
        }

        while(++i<amount.length())
        {
            fraction += amount[i];
        }

        //cout << whole << '\t' << fraction << endl;
    }

    //Refitting the amount into a 15 character format
    for(int i=0; i<whole.length(); i++)
        returnNumber[11-i] = whole[whole.length()-i-1];
    for(int i=0; i<fraction.length(); i++)
        returnNumber[13+i] = fraction[i];

    return returnNumber;
}

//To omit any unnecessary whitespaces in a string
//Does not let two consecutive whitespaces be
string uniformSpacing(string inputString)
{
    string returnString = "";

    int i_pos = 0;
    int r_pos = 0;
    while(i_pos < inputString.length())
    {
        if(returnString[r_pos-1] == ' ' && inputString[i_pos] == ' ')
        {
            i_pos++;    continue;
        }
        
        returnString += inputString[i_pos++];
        r_pos++;
    }

    return returnString;
}

string currencyToText(string amount, char language_choice = 'e', char system_choice = 'w')
{
    amount = refitNumber(amount);

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
        default  :  return "INVALID LANGUAGE";
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
    else if(system_choice == 'i') // Indian Number system ... 9,99,00,11,01,010.89  or 9,00,00,10,00,111.89
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
    else return "Invalid Number System";

    //Seperates two digit fraction
    string fraction_part = amount.substr(13,2);
    returnString += " ";
    returnString += fraction_part;
    returnString += "/100";

    fstream logFile("ignored/output-logs/outputs.txt", fstream::app);
    if(logFile.is_open())
    {
        logFile << amount << endl;
        logFile << '\t' << uniformSpacing(returnString) << endl;
    }
    logFile.close();

    return uniformSpacing(returnString);
}

/////////////////////////////////////////////////////
#endif
