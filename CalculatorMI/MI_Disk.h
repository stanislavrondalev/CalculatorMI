#pragma once
#include "Body.h"
#include "iostream"

class Disk : public Body
{
    double m;
    double R;
public:
    Disk(double m = 0, double R = 0);
    string name_body();
    vector<double> get_data();
    friend istream& operator >> (istream& stream, Disk& disk);
};

