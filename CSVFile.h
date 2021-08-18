#pragma once

#include <string>
#include <vector>

using namespace std;

class CSVFile
{
public:
	int IsSpeechMarks(const char& val);
	bool ReadCSV(string& pickListFilePath, vector<vector<string>>& pickList);
	bool ReadCSVWithSpeechMarks(string& filePath, vector<vector<string>>& fileContents);
	bool WriteCSV(const string& filepath, vector<vector<string>>& content);
	//bool FillUploadFileColHeadings(vector<vector<string>>& uploadFile);
	//bool FillUploadFileCommonValues(const vector<string>& pickListRow, vector<vector<string>>& upload, const string& despatchDate, const vector<string>& menuFileRow, const int order_qty);
	bool GetDirContents(const string& path, vector<string>& files);
};
