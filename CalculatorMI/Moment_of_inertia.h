#pragma once
#include "MI_Kernel.h"
#include "MI_Ball.h"
#include "MI_Sphere.h"
#include "MI_Cylinder.h"
#include "MI_Disk.h"
using namespace std;

template<class T>
class Moment_of_inertia
{
	T body;
public:
	Moment_of_inertia();
	double get_I();
	void set_data(T body);
};

//
template<class T>
Moment_of_inertia<T>::Moment_of_inertia() : body(T()) {}

template<class T>
void Moment_of_inertia<T>::set_data(T body) {
	this->body = body;
}

template<class T>
double Moment_of_inertia<T>::get_I() {
	if (body.name_body() == "kernel") {
		vector<double> data = body.get_data();
		double m = data[0];
		double L = data[1];
		return (m * L * L)/12;
	}
	if (body.name_body() == "ball") {
		vector<double> data = body.get_data();
		double m = data[0];
		double R = data[1];
		return (2 * m * R * R) / 5;
	}
	if (body.name_body() == "sphere") {
		vector<double> data = body.get_data();
		double m = data[0];
		double R = data[1];
		return (2 * m * R * R) / 3;
	}
	if (body.name_body() == "cylinder") {
		vector<double> data = body.get_data();
		double m = data[0];
		double R = data[1];
		return m * R * R;
	}
	if (body.name_body() == "disk") {
		vector<double> data = body.get_data();
		double m = data[0];
		double R = data[1];
		return (m * R * R)/ 2;
	}
}