#ifndef SUPPORT_H
#define SUPPORT_H

#include<iostream>
#include<string>
using namespace std;
//////////////////////////////////////////////////////

#define inputLength 16

string languageSymbols[107];    //Stores number dictionary of a given language
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

    for(int i=0; i < input.length(); i++)
    {   
        if( input[i] > 47 && input[i] < 58)
            continue;
        else if(input[i] == '.' && !pastDecimal)
            pastDecimal = true;
        else 
            return false;

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

/////////////////////////////////////////////////////
#endif
