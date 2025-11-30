#include "MI_Cylinder.h"

Cylinder::Cylinder(double m, double R) {
    this->m = m;
    this->R = R;
}

string Cylinder::name_body() {
    return "cylinder";
}

vector<double> Cylinder::get_data() {
    return { m, R };
}

istream& operator >> (istream& stream, Cylinder& cylinder) {
    while (true) {
        cout << "m = ";
        stream >> cylinder.m;
        if (!valid_input(stream)) {
            continue;
        }
        break;
    }

    while (true) {
        cout << "R = ";
        stream >> cylinder.R;
        if (!valid_input(stream)) {
            continue;
        }
        break;
    }
    return stream;
}
