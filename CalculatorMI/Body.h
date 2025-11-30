#pragma once
#include "string"
#include "vector"
#include "Valid_input.h"
using namespace std;

class Body
{
public:
	virtual string name_body() = 0;
	virtual vector<double> get_data() = 0;
};

