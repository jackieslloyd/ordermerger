#include "PickListRowQVC.h"

void PickListRowQVC::ExtractValues(const vector<string>& pickListRow) // TODO: edit this
{
    order_qty = stoi(pickListRow[21]);
    supplierItem = pickListRow[20];
    orderNumber = pickListRow[4];
    lineNumber = pickListRow[5];                     //temp - why?
    picklist = pickListRow[2];                       //picklist
    deliverToName = pickListRow[7];
    email = "";
    deliverToAddress1 = pickListRow[8].substr(0, 29);
    deliverToAddress2 = pickListRow[9];
    deliverToAddress3 = pickListRow[10];             //town
    deliverToAddress4 = pickListRow[11];             //county
    customerCountry = pickListRow[12];
    deliverToPostcode = pickListRow[13];
    customerAccountCode = pickListRow[14];           //eg 7161598
    customerTelephone = pickListRow[15];
    customerEmail = pickListRow[16];
    supplierItem = pickListRow[20];                  // use to open the menu file eg IW20DVCHOC.csv
}

