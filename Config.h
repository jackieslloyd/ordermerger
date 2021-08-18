#pragma once
#include <string>

using namespace std;

class Config
{
public:

	string menuFolderPath;
	string pickListFolderPath;
	string uploadFolderPath;
	int maxRowsUploadFile = 0;

	bool GetIntFromRow(string& fileRow, int& intNum);
	bool GetPathFromRow(string& fileRow, string& filePath);
	bool ReadConfig(string& path);

};

