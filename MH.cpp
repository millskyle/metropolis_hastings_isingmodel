#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

int main( int argc, char *argv[] )
{
    srand (time(NULL));
    system("mkdir output");
    cout.precision(4);
//OPTIONS /////////
    int const L = 64;
    double const Tc = 2./log(1 + sqrt(2.0)); 
    double const T = Tc * atof(argv[1]);
    double const k = 1.0 ;
    long int T_eq = 1e10;
    int correlation_interval = 1e6;
    long int number_to_keep = 1e3;
//DECLARATIONS
    double allM = 0;
    int M = 0;
    long int step=-1;
    int output_counter = 0;
    int si,sj,dE;
    int config[L][L];
    string tag(argv[2]);
    bool equilibration = 1;


    //Generate a random configuration of 1s and -1s
    for (int i=0; i<L; i++) {
        for (int j=0; j<L; j++) {
            config[i][j] = int(float(rand()%2) / 0.5 - 1);
        }
    }
     
    cout << "T = " << T << endl;

    ofstream out_magnet;
    out_magnet.open("M_" + tag + ".dat");
    
    while (output_counter < number_to_keep) {
        step ++;
        
        if (step%correlation_interval == 0 ) {
            cout << "Equilibration Step 10^(" << log10(step) << ") " << endl;
        }
        si = rand()%L;
        sj = rand()%L;
        
        if (step > T_eq) {
            if (step%correlation_interval ==0 ) {
                cout << "Saved " << output_counter << " configurations" << endl;

                ofstream out_config;
                out_config.open("output/config_" + tag + "_" + to_string(output_counter) + ".dat");
                M = 0;
                for (int i=0; i<L; i++) {
                    for (int j=0; j<L; j++) {
                        out_config << config[i][j] << " ";
                        M += config[i][j];
                    }
                    out_config << endl; 
                }
                out_config.close();
                allM += abs(M);
                output_counter += 1;
                out_magnet << float(allM) / float(output_counter) << endl;
            }
        }



        dE =  2*config[si][sj]*( config[(si+1)%L][sj] + config[(si-1+L)%L][sj] + config[si][(sj+1)%L] + config[si][(sj-1+L)%L]);


        if (dE < 0) {
            config[si][sj] *= -1;
        } else {
            if (float(rand())/RAND_MAX > exp(-dE / (k*T))) {
            //do nothing
            } else {
                config[si][sj] *= -1;
            }
        }
    } 
}
