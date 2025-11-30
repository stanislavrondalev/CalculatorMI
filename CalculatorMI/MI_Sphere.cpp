#include "MI_Sphere.h"

Sphere::Sphere(double m, double R) {
    this->m = m;
    this->R = R;
}

string Sphere::name_body() {
    return "sphere";
}

vector<double> Sphere::get_data() {
    return { m, R };
}

istream& operator >> (istream& stream, Sphere& sphere) {
    while (true) {
        cout << "m = ";
        stream >> sphere.m;
        if (!valid_input(stream)) {
            continue;
        }
        break;
    }

    while (true) {
        cout << "R = ";
        stream >> sphere.R;
        if (!valid_input(stream)) {
            continue;
        }
        break;
    }
    return stream;
}
