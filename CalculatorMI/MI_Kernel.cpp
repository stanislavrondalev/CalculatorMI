#include "MI_Kernel.h"

Kernel::Kernel(double m, double L) {
    this->m = m;
    this->L = L;
}

string Kernel::name_body() {
    return "kernel";
}

vector<double> Kernel::get_data() {
    return { m, L };
}

istream& operator >> (istream& stream, Kernel& kernel) {
    while (true) {
        cout << "m = ";
        stream >> kernel.m;
        if (!valid_input(stream)) {
            continue;
        }
        break;
    }
    
    while (true) {
        cout << "L = ";
        stream >> kernel.L;
        if (!valid_input(stream)) {
            continue;
        }
        break;
    }

    return stream;
}
