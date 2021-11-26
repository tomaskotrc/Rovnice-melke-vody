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

Data Data::F() {
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

//Data Data::multiply(double& k) {
//    Data A;
//
//    A.rho = k * rho;
//    A.rho_u = k * rho_u;
//    A.e = k * e;
//
//    return A;
//}
//
//Data Data::operator* (double& k) {
//    return multiply(k);
//}

//Data Data::operator* (const Data& B, const double& k) const{
//    data A;
//
//    A.rho = k * B.rho;
//    A.rho_u = k * B.rho_u;
//    A.e = k * B.e;
//
//    return A;
//}
