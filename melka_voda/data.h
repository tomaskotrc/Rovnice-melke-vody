#pragma once

class Data
{
public:
	double phi;
	double m;

	double h();
	double u();

	Data(); //konstruktor prazdny?
	Data(double _h, double _u); //konstruktor neprazdny?
	Data F() ;
	void count_phi(double _h);
	void count_m(double _u);
	void display();

	Data operator+ (const Data& B);
	Data operator- (const Data& B);

    double g = 9.80665;

};
