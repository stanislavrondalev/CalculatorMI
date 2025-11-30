#pragma once
#include "Body.h"
#include "iostream"

class Sphere : public Body
{
    double m;
    double R;
public:
    Sphere(double m = 0, double R = 0);
    string name_body();
    vector<double> get_data();
    friend istream& operator >> (istream& stream, Sphere& sphere);
};

