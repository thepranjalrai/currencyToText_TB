#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include<iostream>
#include<fstream>

#include"support.h"

using namespace std;

bool isFile(string input)
{
    if(input.length() < 5)
        return false;

    return input.substr(input.length()-4, 4) == ".txt" ? true : false;
}

//Function Incomplete
/*
string findAmount(string line)
{
    string probableAmount = "";
    char k;

    for(int i=0; i< line.length(); i++)
    {
        k = line[i];
        if(k == '₹')
        {
            for(int j = i+1; j< line.length(); j++)
            {
                if(line[j] == ' ' && j != i+1)
                    break;
                
            }
        }
    }
}
*/

bool processFile(string filepath, char language_choice = 'e', char system_choice = 'w')
{
    fstream inputFile(filepath, fstream::in);
    
    string outputAddress = filepath.substr(0, filepath.length()-4);
    outputAddress += "_converted.txt";
    fstream outputFile(outputAddress, fstream::out);

    if(!inputFile.is_open())
    {
        cout << "This file does not exist";
        return false;
    }

    if(!outputFile.is_open())
    {
        cout << "Failed to create output file";
        return false;
    }
    
    outputFile << "Converting from " << filepath << "\n";
    while(!inputFile.eof())
    {
        string word;
        getline(inputFile, word);
        if(word[word.length()-1] == '\r') word = word.substr(0, word.length()-1);

        if(!checkInput(word))
        {
            outputFile << "\"" << word << "\" is an " << "Invalid Amount.\n";
        }
        else
            outputFile << word << ", " << currencyToText(refitNumber(word), language_choice, system_choice) << "\n";
    }

    outputFile.close();
    inputFile.close();
    return true;
}

#endif