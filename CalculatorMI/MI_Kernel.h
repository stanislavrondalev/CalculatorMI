#pragma once
#include "Body.h"
#include "iostream"

class Kernel : public Body
{
    double m;
    double L;
public:
    Kernel(double m = 0, double L = 0);
    string name_body();
    vector<double> get_data();
    friend istream& operator >> (istream& stream, Kernel& kernel);
};

