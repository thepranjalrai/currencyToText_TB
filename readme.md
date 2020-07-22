# CurrencyToText Converter

This is a program to convert a Currency amount to Text.

Conversion is currently supported in five languges.

	*English
	*Hindi
	*Bengali
	*Marathi
	*Gujarati
	
Two number systems are available.

	*Western Number System
	*Indian Number System
	
Allowed Inputs are :

	1. Any Number with at max 12 whole digits. The fractional part is truncated to 2 digits.
	2. Any File which ends in ".txt". The values must be one on each line
		
Note : If you want to send a file as input, keep the file in the repo directory, i.e., currencyToText_TB-master and input the file name along with it's extension.

## Instructions to access the WEB API

Address : http://13.235.248.42:18080/params?

In order to make this work, you have to append a query string to the given url.
It may take 3 parameters :

	1. amount
	2. lang
	3. sys

A proper method will look like this : http://13.235.248.42:18080/params?amount=12345.67&sys=i&lang=h

The API's implementation is far from perfect right now, but I hope you all can try it out, and let me know if it goes down or if there are any other bugs.

> File processing through API is currently not available.
> I encourage you to try and find bugs. Break my server pls.

## Instructions to run the program locally

### If you are using a linux OS.

1. Clone the repo to your computer, it downloads as "currencyToText_TB-master.zip".
2. Unzip the repo and enter it.
3. Right-click in the folder and select "Open Terminal here" option.
2. Make sure you have GCC 7 installed by entering
	> gcc --version
3. Compile the project by entering
	> make ctt
4. Execute by the command
	> ./ctt

### If you are using other OS, such as windows

1. Clone the repo to your computer, it downloads as "currencyToText_TB-master.zip".
2. In your web browser, go to the website
	> cocalc.com
3. Click on the green button
	> Run CoCalc Now
4. Click on the "Files" tab near top left.
5. Click the "+ New" button next to search box.
6. Drag and drop the downloaded repo (It should be uploaded)
7. In the "Name your file, folder or paste in a link" field, type a name such as "Terminal" and do not press enter.
8. In the dropdown menu next to it, select ">_Terminal(.term)" option. (A GNU terminal should appear)
9. Enter these commands one by one
	> unzip currencyToText_TB-master.zip
	
	> cd currencyToText_TB-master
	
	> make ctt
	
	> ./ctt
	
