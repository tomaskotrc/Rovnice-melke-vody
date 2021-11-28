#include "Data.h"
#include <cmath>
#include <iostream>

Data::Data(){
}

Data::Data(double _h, double _u){
     count_phi(_h);
     count_m(_u);
}


double Data::h() {
	return phi / g;
}

double Data::u() {
	return m / (g * h());
}

Data Data::F() { //fyzikalni tok
	Data F;

	F.phi = m;
	F.m = ( std::pow(m, 2)/phi + std::pow(phi, 2)/2 );

	return F;
}

void Data::count_phi(double _h) {
	phi = g * _h;
}

void Data::count_m(double _u){
    m = g * h() * _u;
}

void Data::display(){
    std::cout << "phi = " << phi << std::endl;
    std::cout << "m = " << m << std::endl;
}

Data Data::operator+(const Data& B) {
	Data A;
	A.phi = phi + B.phi;
	A.m = m + B.m;

	return A;
}

Data Data::operator-(const Data& B) {
	Data A;
	A.phi = phi - B.phi;
	A.m = m - B.m;

	return A;
}
