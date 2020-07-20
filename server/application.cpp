#ifndef APP_CPP
#define APP_CPP

#include "crow_all.h"
#include "../support.h"
#include <iostream>
#include <fstream>

void setAPP(crow::SimpleApp *application)
{
    //Following macro is used in crow_all.h
    //#define CROW_ROUTE(app, url) app.route<crow::black_magic::get_parameter_tag(url)>(url)

    //Greeting, the main page
    application->route<crow::black_magic::get_parameter_tag("/")>("/")([](){
        return "Hello from Pranjal!"; currencyToText("909090");
    });

    application->route<crow::black_magic::get_parameter_tag("/params")>("/params")
    ([](const crow::request& req)
    {
        string lang = "e (default)", sys = "w (default)", amount = "0.00";

        if(req.url_params.get("amount")) amount = req.url_params.get("amount");
        if(req.url_params.get("lang")) lang = req.url_params.get("lang");
        if(req.url_params.get("sys")) sys = req.url_params.get("sys");

        //Trimming the input amount to max length
        if(amount.length() >= inputLength) amount = amount.substr(0, inputLength);

        //Keeping a log of the input, before processing
        fstream logFile("requestLog.txt", fstream::app);
        if(logFile.is_open())
        {
            logFile <<"\n" << req.url_params << "\n";
        }
        logFile.close();

        //Creating JSON to be returned
        crow::json::wvalue object;
        object["amount"] = amount;
        object["language"] = lang;
        object["system"] = sys;
        object["conversion"] = (checkInput(amount) ? currencyToText(amount, lang[0], sys[0]) : "Invalid amount");

        return object;
    });
}

#endif