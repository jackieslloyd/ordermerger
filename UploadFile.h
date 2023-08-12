#pragma once

#include <vector>
#include <string>
#include "PickListRow.h"

using namespace std;

class UploadFile
{
public:
	//vector<string> row;
	//vector<vector<string>> component_file;

	bool CreateFilePath(const class Config& cfg, string timeHrsMinsSecs, string& filePath, int fileIndex);
	bool FillUploadFileColHeadings(vector<vector<string>>& uploadFile);
	bool FillUploadFileCommonValues(const PickListRow& pickListRow, vector<vector<string>>& upload, const string& despatchDate, const vector<string>& menuFileRow, const int order_qty);
	string Time();
};

