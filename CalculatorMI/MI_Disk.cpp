#include "MI_Disk.h"

Disk::Disk(double m, double R) {
    this->m = m;
    this->R = R;
}

string Disk::name_body() {
    return "disk";
}

vector<double> Disk::get_data() {
    return { m, R };
}

istream& operator >> (istream& stream, Disk& disk) {
    while (true) {
        cout << "m = ";
        stream >> disk.m;
        if (!valid_input(stream)) {
            continue;
        }
        break;
    }

    while (true) {
        cout << "R = ";
        stream >> disk.R;
        if (!valid_input(stream)) {
            continue;
        }
        break;
    }
    return stream;
}
