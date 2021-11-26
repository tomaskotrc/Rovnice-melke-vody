#include <iostream>
#include <vector>
#include <cmath>
#include "data.h"
#include "include/Sit.h"
#include "to_file.h"

#define Log(x) std::cout << x << std::endl;

Data operator*(const double& k, const Data& B){
    Data A;

    A.phi = B.phi * k;
    A.m = B.m * k;

    return A;
}

Data operator*(const Data& B, const double& k){
    Data A;

    A.phi = B.phi * k;
    A.m = B.m * k;

    return A;
}

int main() {
	Sit S(0, 1, 5000, 0.5);

	std::vector<Data> w(S.n+1);
	std::vector<Data> wn(S.n+1);

    //pocatecni podminka
    for (int i=0; i<S.n+1; i++){
        Data Y;
        if (S.xi[i] <= S.x_barrier){
            Y.count_phi(0.8);
            Y.count_m(0);
        } else {
            Y.count_phi(0.2);
            Y.count_m(0);
        }
        w[i] = Y;
    }

    double t_max = 0.5;
    double CFL = 0.7;
    double t = 0;
    double vmax;
    double dt;
    int it = 0;
    double v_temp;

    std::ofstream file("output.txt");
    file << "t;x;h;u" << std::endl;

    while (t < t_max){
        if (w[0].u() < 0){
            vmax = w[0].u() - std::sqrt(w[0].g+ w[0].h());
        } else {
            vmax = w[0].u() + std::sqrt(w[0].g+ w[0].h());
        }

        for (int i=0; i<S.n+1; i++){
            if (w[i].u() < 0){
                v_temp = std::fabs(w[i].u() - std::sqrt(w[0].g + w[i].h()));
            } else {
                v_temp = std::fabs(w[i].u() + std::sqrt(w[0].g + w[i].h()));
            }

            if (v_temp > vmax){
                vmax = v_temp;
            }
        }

        dt = CFL * S.dx / vmax;
        t += dt;

        for (int i=1; i<S.n; i++){
            wn[i] = w[i] + 0.5 * ( w[i+1] - 2*w[i] + w[i-1] )
                    - dt / (2*S.dx) * ( w[i+1].F() - w[i-1].F() ) ;
        }

        wn[0] = wn[1];
        wn[S.n] = wn[S.n-1];

        w = wn;

        if (it%100 == 0){
            std::cout << "Time: " << t << ", dt = " << dt << std::endl;
            to_file(file, w, S, t);
        }

        it++;

    }

    file.close();

    std::ofstream file1("endtime.txt");
    file1 << "t;x;h;u" << std::endl;
    to_file(file1, w, S, 0);
    file1.close();

    }
