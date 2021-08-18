#include "Log.h"

#include <iostream>
#include <string>

using namespace std;

int Log::Pause(int retval)
{
    cout << "press any key then <enter> to close window..." << endl;
    string in;
    cin >> in;
    return retval;
}
