//
// Created by USER on 4/23/2022.
//


#include <fstream>
#include <iostream>
#include "Simulation.h"
using namespace std;
int main(int argc, char** argv){
    ifstream config;
    config.open(argv[1]);
    if (!config){
        cerr<<"failed to open file: " << argv[1]<<endl;
    }
    ifstream first_gen;
    first_gen.open(argv[2]);
    if (!config){
        cerr<<"failed to open file: " << argv[2]<<endl;
    }
    Simulation sim(config, first_gen);
    srand( (unsigned)time( NULL ) );
    double t = (double) rand()/RAND_MAX;
    cout << t << endl;
    return 0;
}

