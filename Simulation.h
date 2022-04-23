//
// Created by USER on 4/23/2022.
//

#ifndef COVIDVIEROSESSIMOLATION_SIMULATION_H
#define COVIDVIEROSESSIMOLATION_SIMULATION_H
#include "SARS_COV2.h"
#include "Alpha.h"
#include "Delta.h"
#include "Omicron.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <memory>
using namespace std;
class Simulation {
public:
    /** parameters for the Simulation **/
    int num_of_step;
    int dim;
    int num_of_vir;
    char* target;
    vector<SARS_COV2*> ancestors;
    vector<SARS_COV2*> current_viruses;


    /** constructor **/
    Simulation(ifstream &config, ifstream &first_gen) {
        char buff[10];
        if(config >> buff) {
            this->dim = stoi(buff);
        }//exception
        for(int i=0; i < dim; i++) {
            if(config >> buff) {
                this->target[i] = buff[0];
            }//exception
        }
        if(config >> buff){
            this->num_of_step = stoi(buff);
        }//exception
        if(first_gen >> buff) {
            this->num_of_vir = stoi(buff);
        }//exception
        for(int i=0; i < num_of_vir; i++){
            char string_init[dim], type;
            if(first_gen >> buff) {
                type = buff[0];
            }//exception
            for(int j=0; j< dim ; j++){
                if(first_gen >> buff) {
                    string_init[j] = buff[0];
                }//exception
            }
            switch(type){
                case 'a': ancestors[i] = new Alpha(string_init, type, dim);
                case 'd': ancestors[i] = new Delta(string_init, type, dim);
                case 'o': ancestors[i] = new Omicron(string_init, type, dim);
            }
        }
    }
    void run(){

    }

};


#endif //COVIDVIEROSESSIMOLATION_SIMULATION_H
