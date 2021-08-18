#include "Config.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

bool Config::ReadConfig(string& cfgFilePath)
{
    //ifstream file(cfgFilePath);
    //if (!file)
    //{
    //    cout << "error opening Config File: " << cfgFilePath << endl;
    //    return true;
    //}
    
    ifstream file;
    file.open(cfgFilePath);
    if ((file.rdstate() & std::ifstream::failbit) != 0)
    {
        cout << "error opening Config File: " << cfgFilePath << endl << endl;
        //std::cerr << "Error opening" << cfgFilePath << endl;
        return true;
    }
    cout << "Config File opened: " << cfgFilePath << endl << endl;
   
    string fileRow;

    getline(file, fileRow);
    bool fail = GetPathFromRow(fileRow, pickListFolderPath);

    getline(file, fileRow);
    fail |= GetPathFromRow(fileRow, menuFolderPath);

    getline(file, fileRow);
    fail |= GetPathFromRow(fileRow, uploadFolderPath);

    getline(file, fileRow);
    fail |= GetIntFromRow(fileRow, maxRowsUploadFile);

    return fail;
}
    
bool Config::GetIntFromRow(string& fileRow, int& intNum)
{
    size_t posColon = fileRow.find(":");
    if (posColon == string::npos)
        cout << "config file has misplaced colon: " << fileRow << endl << endl;
    string num = fileRow.substr(posColon + 1);

    try
    {
        intNum = stoi(num);
    }
    catch (exception & err)
    {
        cout << "Conversion error 'max rows in Upload File is not an integer' " << err.what() << endl << endl;
    }
    return false;
}

bool Config::GetPathFromRow(string& fileRow, string& filePath)
{
    size_t posColon = fileRow.find(":");
    if (posColon == string::npos)
        cout << "config file has misplaced colon: " << fileRow << endl << endl;
    filePath = fileRow.substr(posColon + 1);

    string last = filePath.substr(filePath.length() - 1, 1);
    if (last != "\\")
        filePath += "\\";
    return false;
}