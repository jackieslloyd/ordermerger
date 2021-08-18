#include <ctime>
#include "UploadFile.h"
#include "Config.h"
#include <iostream>

bool UploadFile::CreateFilePath(const Config& cfg, string timeHrsMinsSecs, string& filePath, int fileIndex)
{
    time_t ltime;
    time(&ltime);
    struct tm timeNow;
    errno_t err = localtime_s(&timeNow, &ltime);
    if (err != 0)
    {
        printf("Invalid Arguments for ctime_s. Error Code: %d\n", err);
        return true;
    }
    string month;
    if (timeNow.tm_mon + 1 < 10)
        month = "0" + to_string(timeNow.tm_mon + 1);
    else
        month = to_string(timeNow.tm_mon + 1);
    string day;
    if (timeNow.tm_mon < 10)
        day = "0" + day = to_string(timeNow.tm_mday);
    else
        day = day = to_string(timeNow.tm_mday);
    string dateTime = day + "_" + month + "_" + to_string(timeNow.tm_year + 1900) + "_" + timeHrsMinsSecs;
    if (err != 0)
    {
        printf("Invalid Arguments for ctime_s. Error Code: %d\n", err);
    }
    
    filePath = cfg.uploadFolderPath + dateTime + "_" + to_string(fileIndex) + ".csv";
    return false;
}

bool UploadFile::FillUploadFileColHeadings(vector<vector<string>>& uploadFile)
{
    vector<string> uploadRow(16, "");
    uploadRow[0] = "ORDERNUMBER";
    uploadRow[1] = "ORDERID";
    uploadRow[2] = "NAME";
    uploadRow[3] = "EMAIL";
    uploadRow[4] = "PHONE";
    uploadRow[5] = "DELIVERYLINE1";
    uploadRow[6] = "DELIVERYLINE2";
    uploadRow[7] = "DELIVERYLINE3";
    uploadRow[8] = "DELIVERYTOWN";
    uploadRow[9] = "DELIVERYPOSTCODE";
    uploadRow[10] = "DELIVERYCOUNTRY";
    uploadRow[11] = "QTYORDERED";
    uploadRow[12] = "STOCKCODE";
    uploadRow[13] = "COMMENTS";
    uploadRow[14] = "DELIVERYDATE";
    uploadRow[15] = "CARRIERCODE";
    uploadFile.push_back(uploadRow);
    return false;
}

//bool CSVFile::FillUploadFileCommonValues(const vector<string>& pickListRow, vector<string>& uploadRow, string& despatchDate)
bool UploadFile::FillUploadFileCommonValues(const vector<string>& pickListRow, vector<vector<string>>& upload, const string& despatchDate, const vector<string>& menuFileRow, const int order_qty)
{
    int max_cols = 31;

    try
    {
        // names in wesupply_picklist
        string orderNumber = pickListRow[4];
        string lineNumber = pickListRow[5];//temp
        string picklist = pickListRow[2];                       //picklist
        string deliverToName = pickListRow[7];
        string email = "";
        string deliverToAddress1 = pickListRow[8].substr(0, 29);
        string deliverToAddress2 = pickListRow[9];
        string deliverToAddress3 = pickListRow[10];             //town
        string deliverToAddress4 = pickListRow[11];             //county
        string customerCountry = pickListRow[12];
        string deliverToPostcode = pickListRow[13];
        string customerAccountCode = pickListRow[14];           //eg 7161598
        string customerTelephone = pickListRow[15];
        string customerEmail = pickListRow[16];
        string supplierItem = pickListRow[20];                  // use to open the menu file eg IW20DVCHOC.csv

        vector<string> uploadRow(16, "");
        uploadRow[0] = orderNumber;
        uploadRow[1] = picklist + "." + despatchDate;
        uploadRow[2] = deliverToName;
        uploadRow[3] = email;
        uploadRow[4] = customerTelephone;
        uploadRow[5] = deliverToAddress1;
        uploadRow[6] = deliverToAddress2;
        uploadRow[7] = "";
        uploadRow[8] = deliverToAddress3;
        uploadRow[9] = deliverToPostcode;
        if (customerCountry == "UNITED KINGDOM")
            uploadRow[10] = "GB";                          // deliveryCountry // DONE TO HERE!!!!
        else
            uploadRow[10] = customerCountry;
        int qtyOrdered;

        try
        {
            qtyOrdered = stoi(menuFileRow[0]);
        }
        catch (exception & err)
        {
            cout << "Conversion error 'Qty Orderd' " << err.what() << endl << endl;
        }
        uploadRow[11] = to_string(qtyOrdered * order_qty);
        uploadRow[12] = menuFileRow[1];
        upload.push_back(uploadRow);

        //// fill with picklist col data                          // UploadFile col name
        //uploadRow.push_back(orderNumber);//0                       // order number picklist col 4 despatch ref
        //uploadRow.push_back(picklist + "." + despatchDate);//1     // orderID
        //uploadRow.push_back(deliverToName);//2                     // name
        //uploadRow.push_back(email);//3
        //uploadRow.push_back(customerTelephone);//4                 // phone
        //uploadRow.push_back(deliverToAddress1);//5                 // deliveryLine1
        //uploadRow.push_back(deliverToAddress2);//6                 // deliveryLine2 - should be empty
        //uploadRow.push_back("");//7//no longer needed                 // deliveryLine3 == TOWN
        //uploadRow.push_back(deliverToAddress3);//8                 // deliveryTown == COUNTY
        //uploadRow.push_back(deliverToPostcode);                 // deliveryPostcode
        //if (customerCountry == "UNITED KINGDOM")
        //    uploadRow.push_back("GB");                          // deliveryCountry // DONE TO HERE!!!!
        //else
        //    uploadRow.push_back(customerCountry);
        //uploadFile.push_back(uploadRow);
    }
    catch (...)
    {
        cout << "error accessing picklist column" << endl << endl;
        return true;
    }

    return false;
}

string UploadFile::Time()
{
    time_t ltime;
    time(&ltime);
    struct tm timeNow;
    errno_t err = localtime_s(&timeNow, &ltime);
    if (err != 0)
    {
        printf("Invalid Arguments for ctime_s. Error Code: %d\n", err);
        //return true;
    }
   
    return to_string(timeNow.tm_hour) + to_string(timeNow.tm_min) + to_string(timeNow.tm_sec);
}