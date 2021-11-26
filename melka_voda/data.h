#pragma once

class Data
{
public:
	double phi;
	double m;

	double h();
	double u();

	Data();
	Data(double _h, double _u);
	Data F() ;
	void count_phi(double _h);
	void count_m(double _u);
	void display();

	Data operator+ (const Data& B);
	Data operator- (const Data& B);

//	Data multiply(double& k);
//
//	Data operator* (double& k);
//	Data operator* (const Data& B, const double& k) ;

    double g = 9.80665;

};

