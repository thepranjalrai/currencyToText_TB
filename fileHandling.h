#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include<iostream>
#include<fstream>

#include"support.h"
#include"parser.hpp"

using namespace std;
using namespace aria::csv;  //from parser.hpp

string fileType(string input)   //To detect the filetype
{
    if(input.length() < 5)      //Rejects names such as ".txt" or ".csv"
        return "false";

    if(input.substr(input.length()-4, 4) == ".txt")
        return "txt";
    else if(input.substr(input.length()-4, 4) == ".csv")
        return "csv";
    else return "false";
}

bool processCSV(string filepath, char language_choice = 'e', char system_choice = 'w')
{    
    fstream inputFile(filepath, fstream::in);                           //Check for input file
    if(!inputFile.is_open())
    {
        cout << "\"" << filepath << "\" This file does not exist";
        return false;
    }

    cout << "\nEnter the delimiter and the column number of amount.";
    cout << "\nDelimiter : ";
    char delim;
    cin >> delim;
    cout << "Column No : ";
    int amtColumn = 0;
    cin >> amtColumn;

    string outputAddress = filepath.substr(0, filepath.length()-4);     //Create an output file
    outputAddress += "_converted.csv";
    fstream outputFile(outputAddress, fstream::out);
    if(!outputFile.is_open())                                           //Check if the outfile is created
    {
        cout << "Failed to create output file";
        return false;
    }

    outputFile << "Converting from " << filepath << "\n";

    CsvParser parser(inputFile);    //Parsing and converting
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
    fstream inputFile(filepath, fstream::in);                           //Check for input file
    if(!inputFile.is_open())
    {
        cout << "\"" << filepath << "\" This file does not exist";
        return false;
    }
    
    string outputAddress = filepath.substr(0, filepath.length()-4);     //Create an output file
    outputAddress += "_converted.txt";
    fstream outputFile(outputAddress, fstream::out);                    //Check if the outfile is created
    if(!outputFile.is_open())                                           
    {
        cout << "Failed to create output file";
        return false;
    }
    
    outputFile << "Converting from " << filepath << "\n";               //Convert line by line and write to putput file
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