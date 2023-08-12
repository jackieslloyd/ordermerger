// CSVOrdersMerger.cpp : This file contains the 'main' function.Program execution begins and ends there.
//
// Disable warning messages 4507 and 4034.
#pragma warning( disable : 26444 )

#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include "Config.h"
#include "CSVFile.h"
#include "Log.h"
#include "UploadFile.h"
#include "PickListRowIdealWorld.h"


using namespace std;

namespace fs = std::filesystem;

int main()
{
    cout << "Enter despatch date as an integer day of a month (e.g. for despatch on the 3rd of the month, enter '3'): ";
    string despatchDate;
    cin >> despatchDate;
    Log log;
    const fs::path workingDir{ fs::current_path() };
    cout << "working directory: " << workingDir << endl;

    string configFilePath(workingDir.string() + "\\UploadConfig.txt");

    Config cfg;
    bool fail = cfg.ReadConfig(configFilePath);
    if (fail)
        return log.Pause(1);
    CSVFile csv;

    vector<string> pickListFile;
    fail = csv.GetDirContents(cfg.pickListFolderPath, pickListFile); // all the picklist files in the directory
    if (fail)
        return log.Pause(1);

    UploadFile ul;
    vector<vector<string>> allUploadFileData;
    vector<int> uploadFileRowCount; // track how many rows per each order, determined by how many non-zero quantities in menu file
    for (vector<string>::iterator itPickList = pickListFile.begin(); itPickList != pickListFile.end(); itPickList++)// for each picklist file in directory
    {
        vector<vector<string>> pickList;
        string pickListFilePath = cfg.pickListFolderPath + *itPickList;
        fail = csv.ReadCSVWithSpeechMarks(pickListFilePath, pickList);
        if (fail)
            return log.Pause(1);

        for (vector<vector<string>>::iterator it = pickList.begin(); it != pickList.end(); it++) // for each row in picklist file orderfile == upload file
        {
            int orderFileRowCount = 0; // for num file in upload file change
            //vector<string> pickListRow = *it;

            PickListRow* pickListRow;
            PickListRowIdealWorld plRowIdealWorld;
            pickListRow = &plRowIdealWorld;
            pickListRow->ExtractValues(*it);
            //plRow->ExtractValues(pickListRow);

            vector<vector<string>> upload;
            ul.FillUploadFileColHeadings(upload);

            vector<vector<string>> menuFile;
            string menuFilePath = cfg.menuFolderPath + pickListRow->supplierItem + ".csv";
            fail = csv.ReadCSV(menuFilePath, menuFile);
            if (fail)
                return log.Pause(1);

            for (vector<vector<string>>::iterator it = menuFile.begin(); it != menuFile.end(); it++)
            {
                vector<string> menuFileRow = *it;
                bool zero_qty = false;
                if (menuFileRow[0] == "" || menuFileRow[0] == "0" || menuFileRow.empty())
                    zero_qty = true;

                if (!zero_qty)
                {
                    orderFileRowCount++;
                    // TODO: pass ref below?
                    fail = ul.FillUploadFileCommonValues(*pickListRow, allUploadFileData, despatchDate, menuFileRow, pickListRow->order_qty);
                    if (fail)
                        return log.Pause(1); // not sure if this will work - try catch...                    
                }
            }
            uploadFileRowCount.push_back(orderFileRowCount);
        }
        
    }
    // use each entry in the uploadFileRowCount in turn to determine how many times to loop through the rows in the 
    // check ho wmany rows in the 'upload' each time to check if the next batch will take it over the cfg.maxRowsInUploadFile limit
    //if (int row = n; row < )

    int fileIndex = 1;
    vector<vector<string>> upload;
    ul.FillUploadFileColHeadings(upload);
    string timeHrsMinsSecs = ul.Time();

    int endRow = -1;
    int startRow = 0;
    int outputFileRowTotal = 0;
    string uploadFilePath;
    
    for (vector<int>::iterator it = uploadFileRowCount.begin(); it != uploadFileRowCount.end(); it++)
    {
        endRow += *it;
        if (outputFileRowTotal + (endRow - startRow - 1) >= cfg.maxRowsUploadFile)// does num rows incl heading???
        {
            ul.CreateFilePath(cfg, timeHrsMinsSecs, uploadFilePath, fileIndex);
            fail = csv.WriteCSV(uploadFilePath, upload);
            if (fail)
                return log.Pause(1);
            upload.clear();
            outputFileRowTotal = 0;
            ul.FillUploadFileColHeadings(upload);
            fileIndex++;
        }

        for (int row = startRow; row <= endRow; row++)
        {
            upload.push_back(allUploadFileData[row]);
            outputFileRowTotal++;
        }
        startRow = endRow + 1;
    }
    ul.CreateFilePath(cfg, timeHrsMinsSecs, uploadFilePath, fileIndex);
    fail = csv.WriteCSV(uploadFilePath, upload);
    if (fail)
        return log.Pause(1);
      
    return log.Pause(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//int main()
//{
//    cout << "Enter despatch date: ";
//    string despatchDate;
//    cin >> despatchDate;
//    Log log;
//    const fs::path workingDir{ fs::current_path() };
//    cout << "working directory: " << workingDir << endl;
//    
//    string configFilePath(workingDir.string() + "\\UploadConfig.txt");
//    
//    Config cfg;
//    bool fail = cfg.ReadConfig(configFilePath);
//    if (fail)
//        return log.Pause(1);
//    CSVFile csv;
//
//    vector<string> pickListFile;
//    fail = csv.GetDirContents(cfg.pickListFolderPath, pickListFile);
//    if (fail)
//        return log.Pause(1);
//
//    for (vector<string>::iterator itPickList = pickListFile.begin(); itPickList != pickListFile.end(); itPickList++)
//    {
//        vector<vector<string>> pickList;
//        string pickListFilePath = cfg.pickListFolderPath + *itPickList;
//        fail = csv.ReadCSVWithSpeechMarks(pickListFilePath, pickList);
//        if (fail)
//            return log.Pause(1);
//
//        for (vector<vector<string>>::iterator it = pickList.begin(); it != pickList.end(); it++)
//        {
//            vector<string> pickListRow = *it;
//            string despatchRef = pickListRow[4].c_str();
//            int order_qty = stoi(pickListRow[21]); // TODO check why this is here
//            string uploadFilePath = cfg.uploadFolderPath + "Upload File " + despatchRef + ".csv";
//         
//            vector<vector<string>> upload;
//            csv.FillUploadFileColHeadings(upload);
//
//            string supplierItem = pickListRow[20];
//            string menuFilePath = cfg.menuFolderPath + supplierItem + ".csv";
//            vector<vector<string>> menuFile;
//            fail = csv.ReadCSV(menuFilePath, menuFile);
//            if (fail)
//                return log.Pause(1);
//
//            for (vector<vector<string>>::iterator it = menuFile.begin(); it != menuFile.end(); it++)
//            {
//                vector<string> menuFileRow = *it;
//                bool zero_qty = false;
//                if (menuFileRow[0] == "" || menuFileRow[0] == "0" || menuFileRow.empty())
//                    zero_qty = true;
//
//                if (!zero_qty)
//                {
//                    fail = csv.FillUploadFileCommonValues(pickListRow, upload, despatchDate, menuFileRow, order_qty);
//                    if (fail)
//                        return log.Pause(1); // not sure if this will work - try catch...                    
//                }
//            }
//            fail = csv.WriteCSV(uploadFilePath, upload); // make an array of uploads and then WriteCSV for each one at end or combine vectors, or keep same upload for multiple files
//            if (fail)
//                return log.Pause(1);
//        }
//    }
//    return log.Pause(0);
//}