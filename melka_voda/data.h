#pragma once

class Data
{
public:
    Data();
	Data(double _h, double _u);

	double phi;
	double m;

	double h();
	double u();
    Data F();

	void count_phi(double _h);
	void count_m(double _u);
	void display();

	Data operator+ (const Data& B);
	Data operator- (const Data& B);

    double g = 9.80665;
};
