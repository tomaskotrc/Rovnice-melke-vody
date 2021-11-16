#include <iostream>
#include <vector>
#include <cmath>
#include "data.h"
#include "include/Sit.h"
#include "to_file.h"

#define Log(x) std::cout << x << std::endl;

Data operator*(const double& k, const Data& B){
    Data A;

    A.rho = B.rho * k;
    A.rho_u = B.rho_u * k;
    A.e = B.e * k;

    return A;
}

Data operator*(const Data& B, const double& k){
    Data A;

    A.rho = B.rho * k;
    A.rho_u = B.rho_u * k;
    A.e = B.e * k;

    return A;
}

int main() {
	Sit S(0, 1, 10000, 0.3);
    double k = 3.2;

	std::vector<Data> w(S.n+1);
	std::vector<Data> wn(S.n+1);

    //pocatecni podminka
    for (int i=0; i<S.n+1; i++){
        Data Y;

        if (S.xi[i] <= S.x_barrier){
            Y.rho = 1;
            Y.rho_u = 0;
            Y.count_e(1);
        } else {
            Y.rho = 0.125;
            Y.rho_u = 0.1;
            Y.count_e(0.1);
        }
        w[i] = Y;
    }

    double t_max = 0.2;
    double CFL = 0.7;
    double eps = 0.93;
    double t = 0;
    double den;
    double dt;
    int it = 0;
    std::ofstream file("output.txt");
    file << "t;x;rho;u;e;p" << std::endl;

    while (t < t_max){
        den = std::abs(w[0].u()) + w[0].a();

        for (int i=0; i<S.n+1; i++){
            if ((std::abs(w[i].u()) + w[i].a()) > den){
                den = abs(w[i].u()) + w[i].a();
            }
        }

        dt = CFL * S.dx / den;
        t += dt;


        for (int i=1; i<S.n; i++){
            wn[i] = w[i] - dt/(2*S.dx) * (w[i+1].F() - w[i-1].F()) +
                0.5 * eps * (w[i+1] - 2*w[i] + w[i-1]);
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
    file1 << "t;x;rho;u;e;p" << std::endl;
    to_file(file1, w, S, 0);
    file1.close();

    }
