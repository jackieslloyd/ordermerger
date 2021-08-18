#include "CSVFile.h"

#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;

bool CSVFile::ReadCSV(string& filePath, vector<vector<string>>& fileContents)
{
    ifstream file;
    file.open(filePath);
    if ((file.rdstate() & std::ifstream::failbit) != 0)
    {
        cout << "error opening File: " << filePath << endl << endl;
        //std::cerr << "Error opening" << filePath << endl;
        return true;
    }
    else
    {
        cout << "opened file: " << filePath << endl << endl;
    }
    
    string fileRow;
    getline(file, fileRow); // skip col titles
    while (getline(file, fileRow))
    {
        size_t l1 = fileRow.length();
        fileRow.erase(remove(fileRow.begin(), fileRow.end(), '\"'), fileRow.end());
        //fileRow.erase(std::remove_if(fileRow.begin(), fileRow.end(), IsSpeechMarks()), fileRow.end());
        //fileRow.erase(std::remove_if(fileRow.begin(), fileRow.end(), isspace), fileRow.end());
        size_t l2 = fileRow.length();
        string pickListItem = string("");
        size_t posComma = -1;
        vector<string> row;
        size_t posNextComma = fileRow.find(",", posComma + 1);
        size_t count = posNextComma - posComma - 1;
        string colItem = fileRow.substr(posComma + 1, count);
        row.push_back(colItem);
        posComma = posNextComma;
        while (posComma != string::npos)
        {
            posNextComma = fileRow.find(",", posComma + 1);
            count = posNextComma - posComma - 1;
            colItem = fileRow.substr(posComma + 1, count);            
            row.push_back(colItem);
            posComma = posNextComma;
        }
        fileContents.push_back(row);
    }
    return false;
}

bool CSVFile::ReadCSVWithSpeechMarks(string& filePath, vector<vector<string>>& fileContents)
{
    ifstream file;
    file.open(filePath);
    if ((file.rdstate() & std::ifstream::failbit) != 0)
    {
        cout << "error opening File: " << filePath << endl << endl;
        //std::cerr << "Error opening" << filePath << endl;
        return true;
    }
    else
    {
        cout << "opened file: " << filePath << endl << endl;
    }
    string first;
    bool speechMarks;
    size_t count;
    string colItem;
    size_t posNextComma;
    size_t posComma;
    size_t posSpeechMarks;
    size_t posNextSpeechMarks;


    string fileRow;
    getline(file, fileRow); // skip col titles
    while (getline(file, fileRow))
    {        
        posComma = -1;
        posSpeechMarks = 0;
        posNextSpeechMarks = 0;
        vector<string> row;
        size_t l = fileRow.length();//test
      
        do
        {
            first = fileRow.substr(posComma + 1, 1);               
            speechMarks = first.compare("\"") == 0 ? true : false;
            if (speechMarks)
            {
                posNextSpeechMarks = fileRow.find("\"", posComma + 2);
                count = posNextSpeechMarks - posSpeechMarks - 1;
                colItem = fileRow.substr(posSpeechMarks + 1, count);
                posComma = posNextSpeechMarks + 1;
                posSpeechMarks = posNextSpeechMarks + 2;
            }
            else
            { 
                posNextComma = fileRow.find(",", posComma + 1);
                count = posNextComma - posComma - 1;
                colItem = fileRow.substr(posComma + 1, count);
                posComma = posNextComma;
                posSpeechMarks = posNextComma + 1;
            }
            colItem.erase(remove(colItem.begin(), colItem.end(), ','), colItem.end()); // TODO: rmv all special chars
            //colItem.erase(remove(colItem.begin(), colItem.end(), '\''), colItem.end()); // TODO: rmv all special chars
            //colItem.erase(remove(colItem.begin(), colItem.end(), '|'), colItem.end()); // TODO: rmv all special chars
            //colItem.erase(remove(colItem.begin(), colItem.end(), '¬'), colItem.end()); // TODO: rmv all special chars
            //colItem.erase(remove(colItem.begin(), colItem.end(), '"'), colItem.end()); // TODO: rmv all special chars
            //colItem.erase(remove(colItem.begin(), colItem.end(), '$'), colItem.end()); // TODO: rmv all special chars
            //colItem.erase(remove(colItem.begin(), colItem.end(), '%'), colItem.end()); // TODO: rmv all special chars
            //colItem.erase(remove(colItem.begin(), colItem.end(), '&'), colItem.end()); // TODO: rmv all special chars
            //colItem.erase(remove(colItem.begin(), colItem.end(), '*'), colItem.end()); // TODO: rmv all special chars
            //colItem.erase(remove(colItem.begin(), colItem.end(), '+'), colItem.end()); // TODO: rmv all special chars
            //colItem.erase(remove(colItem.begin(), colItem.end(), '='), colItem.end()); // TODO: rmv all special chars
            row.push_back(colItem);
        } while (posComma != string::npos && posComma < fileRow.length());
        fileContents.push_back(row);
       // ` | ¬ “ $ % &*+= { }[] :; ‘ # ~, < > . ? @.
    }
    return false;
}

//bool CSVFile::ReadCSVWithSpeechMarks(string& filePath, vector<vector<string>>& fileContents)
//{
//    ifstream file;
//    file.open(filePath);
//    if ((file.rdstate() & std::ifstream::failbit) != 0)
//    {
//        cout << "error opening File: " << filePath << endl << endl;
//        //std::cerr << "Error opening" << filePath << endl;
//        return true;
//    }
//    else
//    {
//        cout << "opened file: " << filePath << endl << endl;
//    }
//
//    string fileRow;
//    getline(file, fileRow); // skip col titles
//    while (getline(file, fileRow))
//    {
//        //size_t l1 = fileRow.length();
//        // use later for each field: fileRow.erase(remove(fileRow.begin(), fileRow.end(), '\"'), fileRow.end());
//        //fileRow.erase(std::remove_if(fileRow.begin(), fileRow.end(), IsSpeechMarks()), fileRow.end());
//        //fileRow.erase(std::remove_if(fileRow.begin(), fileRow.end(), isspace), fileRow.end());
//        //size_t l2 = fileRow.length();
//
//        //string pickListItem = string("");
//
//        string first = fileRow.substr(0, 1);
//        bool speechMarks = first.compare("\"") == 0 ? true : false;
//        size_t count;
//        string colItem;
//        size_t posNextComma;
//        vector<string> row;
//        size_t posComma = -1;
//        size_t posSpeechMarks = 0;
//        size_t posNextSpeechMarks = 0;
//
//        if (speechMarks)
//        {
//            posNextSpeechMarks = fileRow.find("\"", posComma + 2);
//            count = posNextSpeechMarks - posSpeechMarks - 1;
//            colItem = fileRow.substr(posSpeechMarks + 1, count);
//            posComma = posNextSpeechMarks + 1;
//            posSpeechMarks = posNextSpeechMarks + 2;
//        }
//        else
//        {
//            posNextComma = fileRow.find(",", posComma + 1);
//            count = posNextComma - posComma - 1;
//            colItem = fileRow.substr(posComma + 1, count);
//            posComma = posNextComma;
//            posSpeechMarks = posNextComma + 1;
//        }
//        row.push_back(colItem);
//
//        while (posComma != string::npos)
//        {
//            first = fileRow.substr(posComma + 1, 1);
//            speechMarks = first.compare("\"") == 0 ? true : false;
//            if (speechMarks)
//            {
//                posNextSpeechMarks = fileRow.find("\"", posComma + 2);
//                count = posNextSpeechMarks - posSpeechMarks - 1;
//                colItem = fileRow.substr(posSpeechMarks + 1, count);
//                posComma = posNextSpeechMarks + 1;
//                posSpeechMarks = posNextSpeechMarks + 2;
//            }
//            else
//            {
//                posNextComma = fileRow.find(",", posComma + 1);
//                count = posNextComma - posComma - 1;
//                colItem = fileRow.substr(posComma + 1, count);
//                posComma = posNextComma;
//                posSpeechMarks = posNextComma + 1;
//            }
//            colItem.erase(remove(colItem.begin(), colItem.end(), ','), colItem.end());
//            row.push_back(colItem);
//        }
//        fileContents.push_back(row);
//    }
//    return false;
//}
//bool single_digit(const char value) { return (value < 10); }
//bool CSVFile::IsSpeechMarks(const char val)
//{
//    return (val == '\"');
//}

int CSVFile::IsSpeechMarks(const char& val)
{
    if (val == '\"')
        return 1;
    else
        return 0;
}

bool CSVFile::WriteCSV(const string& filePath, vector<vector<string>>& content)
{
    ofstream file;
    //file.open(filePath, ofstream::out | ofstream::trunc);
    file.open(filePath);
    
    if (!file.is_open()) // if (!file)
    {
        cout << "error writing Upload File: " << filePath << endl;
        cout << "Check if file is open!" << endl << endl;
        return true;
    }
    else
    {
        cout << "Created Upload File: " << filePath << endl << endl;
    }

    for (vector<vector<string>>::iterator it = content.begin(); it != content.end(); it++)
    {
        vector<string> row = *it;
        for (vector<string>::iterator it_row = row.begin(); it_row != row.end(); it_row++)
        {
            file << *it_row << ",";
        }
        file << endl;
    }
    file.flush();
    file.close();
    return false;
}

//bool CSVFile::FillUploadFileColHeadings(vector<vector<string>>& uploadFile)
//{
//    vector<string> uploadRow(16, "");
//    uploadRow[0] = "ORDERNUMBER";
//    uploadRow[1] = "ORDERID";
//    uploadRow[2] = "NAME";
//    uploadRow[3] = "EMAIL";
//    uploadRow[4] = "PHONE";
//    uploadRow[5] = "DELIVERYLINE1";
//    uploadRow[6] = "DELIVERYLINE2";
//    uploadRow[7] = "DELIVERYLINE3";
//    uploadRow[8] = "DELIVERYTOWN";
//    uploadRow[9] = "DELIVERYPOSTCODE";
//    uploadRow[10] = "DELIVERYCOUNTRY";
//    uploadRow[11] = "QTYORDERED";
//    uploadRow[12] = "STOCKCODE";
//    uploadRow[13] = "COMMENTS";
//    uploadRow[14] = "DELIVERYDATE";
//    uploadRow[15] = "CARRIERCODE";
//    uploadFile.push_back(uploadRow);
//    return false;
//}
//
////bool CSVFile::FillUploadFileCommonValues(const vector<string>& pickListRow, vector<string>& uploadRow, string& despatchDate)
//bool CSVFile::FillUploadFileCommonValues(const vector<string>& pickListRow, vector<vector<string>>& upload, const string& despatchDate, const vector<string>& menuFileRow, const int order_qty)
//{
//    int max_cols = 31;
//
//    try
//    {
//        // names in wesupply_picklist
//        string orderNumber = pickListRow[4];
//        string lineNumber = pickListRow[5];//temp
//        string picklist = pickListRow[2];                       //picklist
//        string deliverToName = pickListRow[7];
//        string email = "";
//        string deliverToAddress1 = pickListRow[8];
//        string deliverToAddress2 = pickListRow[9];
//        string deliverToAddress3 = pickListRow[10];             //town
//        string deliverToAddress4 = pickListRow[11];             //county
//        string customerCountry = pickListRow[12];
//        string deliverToPostcode = pickListRow[13];
//        string customerAccountCode = pickListRow[14];           //eg 7161598
//        string customerTelephone = pickListRow[15];
//        string customerEmail = pickListRow[16];
//        string supplierItem = pickListRow[20];                  // use to open the menu file eg IW20DVCHOC.csv
//        
//        vector<string> uploadRow(16, "");
//        if (lineNumber == "1") // temp 
//            uploadRow[0] = orderNumber + ".a"; // etc temp or + "." + lineNumber;
//        uploadRow[1] = picklist + "." + despatchDate;
//        uploadRow[2] = deliverToName;
//        uploadRow[3] = email;
//        uploadRow[4] = customerTelephone;
//        uploadRow[5] = deliverToAddress1;
//        uploadRow[6] = deliverToAddress2;
//        uploadRow[7] = "";
//        uploadRow[8] = deliverToAddress3;
//        uploadRow[9] = deliverToPostcode;
//        if (customerCountry == "UNITED KINGDOM")
//            uploadRow[10] = "GB";                          // deliveryCountry // DONE TO HERE!!!!
//        else
//            uploadRow[10] = customerCountry;
//        int qtyOrdered;
//        
//        try
//        {
//           qtyOrdered = stoi(menuFileRow[0]);
//        }
//        catch (exception & err)
//        {
//            cout << "Conversion error 'Qty Orderd' " << err.what() << endl << endl;
//        }
//        uploadRow[11] = to_string(qtyOrdered * order_qty);
//        uploadRow[12] = menuFileRow[1];
//        upload.push_back(uploadRow);
//        
//        //// fill with picklist col data                          // UploadFile col name
//        //uploadRow.push_back(orderNumber);//0                       // order number picklist col 4 despatch ref
//        //uploadRow.push_back(picklist + "." + despatchDate);//1     // orderID
//        //uploadRow.push_back(deliverToName);//2                     // name
//        //uploadRow.push_back(email);//3
//        //uploadRow.push_back(customerTelephone);//4                 // phone
//        //uploadRow.push_back(deliverToAddress1);//5                 // deliveryLine1
//        //uploadRow.push_back(deliverToAddress2);//6                 // deliveryLine2 - should be empty
//        //uploadRow.push_back("");//7//no longer needed                 // deliveryLine3 == TOWN
//        //uploadRow.push_back(deliverToAddress3);//8                 // deliveryTown == COUNTY
//        //uploadRow.push_back(deliverToPostcode);                 // deliveryPostcode
//        //if (customerCountry == "UNITED KINGDOM")
//        //    uploadRow.push_back("GB");                          // deliveryCountry // DONE TO HERE!!!!
//        //else
//        //    uploadRow.push_back(customerCountry);
//        //uploadFile.push_back(uploadRow);
//    }
//    catch (...)
//    {
//        cout << "error accessing picklist column" << endl << endl;
//        return true;
//    }
//
//    return false;
//}

namespace fs = std::filesystem;

bool CSVFile::GetDirContents(const string& path, vector<string>& files)
{
    if (fs::is_directory(path))
    {
        cout << "Read Pick List folder: " << path << endl << endl;
    }
    else
    {        
        cout << "Failed to read Pick List folder: " << path << endl << endl;
        return true;
    }
    cout << "picklist files:" << endl;
    for (const auto& entry : fs::directory_iterator(path))
    {
        const auto filename = entry.path().filename().string();
        std::cout << filename << '\n';
        files.push_back(filename);
    }
    cout << endl;
    return false;
}