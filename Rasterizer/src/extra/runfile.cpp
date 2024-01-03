#include <iostream>
#include <fstream>
#include <string>
#include "runfile.h"

void FileRunIndex()
{
    std::string runAmountStr = "";
    std::ifstream ReadRunIndexFile("RunIndex.txt");
    runAmountStr = ReadRunIndexFile.get();
    int runAmount = std::stoi(runAmountStr);
    runAmount++;
    ReadRunIndexFile.close();
    std::cout << "Hello, Rasterizer! from FileRunIndex, Amount here > " << runAmount << "\n";
    std::ofstream WriteRunIndexFile("RunIndex.txt");
    WriteRunIndexFile << runAmount;
    WriteRunIndexFile.close();
}