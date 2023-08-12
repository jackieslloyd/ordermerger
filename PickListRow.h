#pragma once
#include <string>
#include <vector>

using namespace std;

class PickListRow
{
public: 
	int order_qty;
	string orderNumber;
	string lineNumber;
	string picklist;
	string deliverToName;
	string email;
	string deliverToAddress1;
	string deliverToAddress2;
	string deliverToAddress3;
	string deliverToAddress4;
	string customerCountry;
	string deliverToPostcode;
	string customerAccountCode;
	string customerTelephone;
	string customerEmail;
	string supplierItem;

public:
	virtual void ExtractValues(const vector<string>& pickListRow) = 0;
};

