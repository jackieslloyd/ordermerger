#pragma once
#include "PickListRow.h"

class PickListRowIdealWorld : public PickListRow
{
	void ExtractValues(const vector<string>& pickListRow) override;
};

