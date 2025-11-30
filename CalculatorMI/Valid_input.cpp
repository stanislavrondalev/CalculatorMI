#include "Valid_input.h"

bool valid_input(istream& stream) {
    if (stream.fail()) {
        cout << "Input double, not string !" << endl;
        stream.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (stream.gcount() > 1) {
        cout << "Input double, not string !" << endl;
        return false;
    }
    return true;
}