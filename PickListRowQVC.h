#pragma once
#include "PickListRow.h"

using namespace std;

class PickListRowQVC : public PickListRow
{
	void ExtractValues(const vector<string>& pickListRow) override;
};

