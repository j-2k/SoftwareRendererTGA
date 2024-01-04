#include <iostream>
#include <fstream>
#include <string>
#include "runfile.h"

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int ArgHandler(int argc, char** argv)
{
	if(argv[1] == nullptr){std::cout << "No Arg default continue " << "\n";return 0;}

	if(is_number(argv[1]) && argc == 2){
		std::cout << "Arg is a number! it is " << argv[1] << "\n";
		return std::stoi(argv[1]);}
	else{
		std::cout << "Arg is not a number or too many arguments, exiting... " << argv[1] << "\n";
		exit(0);}
}

int FileRunIndex(int argc, char** argv)
{
    int num = ArgHandler(argc, argv);
    //starting with important vars
    std::string runAmountStr = "";
    int runAmount = 0;
    std::ifstream ReadRunIndexFile("./RunIndex.txt");

    //find file first
    if(ReadRunIndexFile)
    {
        std::getline(ReadRunIndexFile, runAmountStr);
        runAmount = std::stoi(runAmountStr);
        ReadRunIndexFile.close();
    }
    else
    {
        std::cout << "RunIndex.txt not found, creating new one..." << "\n";
        std::ofstream WriteRunIndexFile("RunIndex.txt");
        WriteRunIndexFile.close();
    }
    
    //manage file second
    if(num == 0)
    {
        runAmount++;
    }
    else
    {
        runAmount = num;
    }

    //write file last
    std::cout << "Hello, Rasterizer! from FileRunIndex, Amount here > " << runAmount << "\n";
    std::ofstream WriteRunIndexFile("RunIndex.txt");
    WriteRunIndexFile << runAmount;
    WriteRunIndexFile.close();
    return runAmount;
}