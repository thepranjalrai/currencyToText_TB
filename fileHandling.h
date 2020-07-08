#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include<iostream>
#include<fstream>

#include"support.h"
#include"parser.hpp"

using namespace std;
using namespace aria::csv;

string fileType(string input)
{
    if(input.length() < 5)
        return "false";

    //return input.substr(input.length()-4, 4) == ".txt" ? true : false;
    if(input.substr(input.length()-4, 4) == ".txt")
        return "txt";
    else if(input.substr(input.length()-4, 4) == ".csv")
        return "csv";
    else return "false";
}

bool processCSV(string filepath, char language_choice = 'e', char system_choice = 'w')
{
    cout << "\nEnter the delimiter and the column number of amount.";
    
    fstream inputFile(filepath, fstream::in);
    if(!inputFile.is_open())
    {
        cout << "\"" << filepath << "\" This file does not exist";
        return false;
    }

    cout << "\nDelimiter : ";
    char delim;
    cin >> delim;
    cout << "Column No : ";
    int amtColumn = 0;
    cin >> amtColumn;

    string outputAddress = filepath.substr(0, filepath.length()-4);
    outputAddress += "_converted.csv";
    fstream outputFile(outputAddress, fstream::out);
    if(!outputFile.is_open())
    {
        cout << "Failed to create output file";
        return false;
    }

    outputFile << "Converting from " << filepath << "\n";

    CsvParser parser(inputFile);
    parser.delimiter(delim);

    for (auto& row : parser)
    {
        string amount = row[amtColumn-1];
        if(!checkInput(amount))
        {
            outputFile << "\"" << amount << "\" is an " << "Invalid Amount.\n";
        }
        else
            outputFile << amount << ", " << currencyToText(refitNumber(amount), language_choice, system_choice) << "\r";
    }
    
    outputFile.close();
    inputFile.close();
    return true;
}

bool processTXT(string filepath, char language_choice = 'e', char system_choice = 'w')
{
    fstream inputFile(filepath, fstream::in);
    if(!inputFile.is_open())
    {
        cout << "\"" << filepath << "\" This file does not exist";
        return false;
    }
    
    string outputAddress = filepath.substr(0, filepath.length()-4);
    outputAddress += "_converted.txt";
    fstream outputFile(outputAddress, fstream::out);
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
            outputFile << word << ", " << currencyToText(refitNumber(word), language_choice, system_choice) << "\r\n";
    }

    outputFile.close();
    inputFile.close();
    return true;
}

#endif