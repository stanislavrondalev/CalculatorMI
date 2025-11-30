#pragma once
#include "Body.h"
#include "iostream"

class Cylinder : public Body
{
    double m;
    double R;
public:
    Cylinder(double m = 0, double R = 0);
    string name_body();
    vector<double> get_data();
    friend istream& operator >> (istream& stream, Cylinder& cylinder);
};

