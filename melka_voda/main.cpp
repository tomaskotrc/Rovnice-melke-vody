#include <iostream>
#include <vector>
#include <cmath>
#include "data.h"
#include "Sit.h"
#include "to_file.h"
#include <fstream>

#define Log(x) std::cout << x << std::endl;

using namespace std;

Data operator*(const double& k, const Data& B){ //nasobeni skalarem komutativni
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
	Sit S(0, 5, 5000, 2.5);

	std::vector<Data> w(S.n+1);
	std::vector<Data> wn(S.n+1);
	std::vector<Data> w_polovicni_plus(S.n+1);
	std::vector<Data> w_polovicni_minus(S.n+1);

	/*fstream soubor_u_LF("u_LF.txt", ios::out);
	fstream soubor_h_LF("h_LF.txt", ios::out);
	fstream soubor_u_LW("u_LW.txt", ios::out);
	fstream soubor_h_LW("h_LW.txt", ios::out);*/

    double t_max = .5;
    double CFL = 0.7;
    double t = 0;
    double vmax;
    double dt;
    int it = 0;
    double v_temp;

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

    std::ofstream file_LF("output_LF.txt");
    file_LF << "t;x;h;u" << std::endl;
    to_file(file_LF, w, S, t);

    while (t < t_max) //Lax-Friedrichs
    {
        if (w[0].u() < 0){
            vmax = w[0].u() - std::sqrt(w[0].g*w[0].h());
        } else {
            vmax = w[0].u() + std::sqrt(w[0].g*w[0].h());
        }

        for (int i=0; i<S.n+1; i++){
            if (w[i].u() < 0){
                v_temp = std::fabs(w[i].u() - std::sqrt(w[0].g*w[i].h()));
            } else {
                v_temp = std::fabs(w[i].u() + std::sqrt(w[0].g*w[i].h()));
            }

            if (v_temp > vmax){
                vmax = v_temp;
            }
        }

        dt = CFL * S.dx / vmax;
        if ((t + dt) > t_max) {
            dt = t_max - t;
        }

        t += dt;

        for (int i=1; i<S.n; i++){
            wn[i] = w[i] + 0.5 * ( w[i+1] - 2*w[i] + w[i-1] )
                    - dt / (2*S.dx) * ( w[i+1].F() - w[i-1].F() ) ;
        }

        wn[0] = wn[1]; //Neumannova OP
        wn[S.n] = wn[S.n-1];

        w = wn;

        if (it%50 == 0){
            //std::cout << "Time: " << t << ", dt = " << dt << std::endl;
            to_file(file_LF, w, S, t);
//            for (int i=0; i<S.n+1; i++)
//            {
//                soubor_h_LF<<w[i].h()<<" ";
//                soubor_u_LF<<w[i].u()<<" ";
//            }
//            soubor_h_LF<<"\n";
//            soubor_u_LF<<"\n";
        }

        it++;

    }
    to_file(file_LF, w, S, t);

    file_LF.close();
    cout<<"pocet iteraci LF schematem: "<<it;

    std::ofstream file_end_LF("endtime_LF.txt");
    file_end_LF << "t;x;h;u" << std::endl;

    to_file(file_end_LF, w, S, 0);
    file_end_LF.close();

    t=0;
    it=0;

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

    std::ofstream file_LW("output_LW.txt");
    file_LW << "t;x;h;u" << std::endl;

    while (t < t_max){ //Lax-Wendroff
        if (w[0].u() < 0){
            vmax = w[0].u() - std::sqrt(w[0].g*w[0].h());
        } else {
            vmax = w[0].u() + std::sqrt(w[0].g*w[0].h());
        }

        for (int i=0; i<S.n+1; i++){
            if (w[i].u() < 0){
                v_temp = std::fabs(w[i].u() - std::sqrt(w[0].g*w[i].h()));
            } else {
                v_temp = std::fabs(w[i].u() + std::sqrt(w[0].g*w[i].h()));
            }

            if (v_temp > vmax){
                vmax = v_temp;
            }
        }

        dt = CFL * S.dx / vmax;
        if ((t + dt) > t_max) {
            dt = t_max - t;
            }
        t += dt;

        for (int i=0; i<S.n; i++){
            w_polovicni_plus[i] = 0.5*w[i] + 0.5*w[i+1] - (dt/2/S.dx)*(w[i+1].F() - w[i].F());
        }

        for (int i=1; i<S.n+1; i++){
            w_polovicni_minus[i] = 0.5*w[i] + 0.5*w[i-1] - (dt/2/S.dx)*(w[i].F() - w[i-1].F());
        }

        w_polovicni_minus[0] = w_polovicni_minus[1];

        for (int i=0; i<S.n; i++)
        {
            wn[i]=w[i] - (dt/S.dx)*(w_polovicni_plus[i].F() - w_polovicni_minus[i].F());
        }

        wn[0] = wn[1];
        wn[S.n] = wn[S.n-1];

        w=wn;

        if (it%50 == 0)
        {
            std::cout << "Time: " << t << ", dt = " << dt << std::endl;
            to_file(file_LW, w, S, t);
//            for (int i=0; i<S.n+1; i++)
//            {
//                soubor_h_LW<<w[i].h()<<" ";
//                soubor_u_LW<<w[i].u()<<" ";
//            }
//            soubor_h_LW<<"\n";
//            soubor_u_LW<<"\n";
//        }

        it++;

    }

    file_LW.close();
    cout<<", pocet iteraci LW schematem: "<<it;

    std::ofstream file_end_LW("endtime_LW.txt");
    file_end_LW << "t;x;h;u" << std::endl;

    to_file(file_end_LW, w, S, 0);
    file_end_LW.close();

    return 0;
}
