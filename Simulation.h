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
#include <algorithm>

using namespace std;
class Simulation {
public:
    /** parameters for the Simulation **/
    int num_of_step;
    int dim;
    int num_of_vir;
    char* target_string;
    vector<SARS_COV2*> ancestors;
    vector<SARS_COV2*> current_viruses;
    double strongest_val = 0;
    char* strongest_string;
    char strongest_type;

    /** constructor **/
    Simulation(ifstream &config, ifstream &first_gen) {
        char buff[10];
        if(config >> buff) {
            this->dim = stoi(buff);
        }//exception
        this->target_string = new char[dim];
        this->strongest_string = new char[dim];
        for(int i=0; i<dim; i++){
            if(config >> buff){
                target_string[i] = buff[0];
            }
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
                }
            }
            switch(type){
                case 'a':
                    ancestors.push_back(new Alpha(string_init, type, dim));
                    current_viruses.push_back(new Alpha(static_cast<Alpha*>(ancestors[i]), ancestors[i]->current_string));
                    break;
                case 'd':
                    ancestors.push_back( new Delta(string_init, type, dim));
                    current_viruses.push_back(new Delta(static_cast<Delta*>(ancestors[i]), ancestors[i]->current_string));
                    break;
                case 'o':
                    ancestors.push_back( new Omicron(string_init, type, dim));
                    current_viruses.push_back(new Omicron(static_cast<Omicron*>(ancestors[i]), ancestors[i]->current_string));
                    break;
            }
        }
    }

    void run(){
        for(int step=0; step < num_of_step; step++){
            for(int j=0; j<num_of_vir; j++){
                current_viruses[j]->change_chars();
                current_viruses[j]->calc_sim_to_target(target_string);
            }
            std::sort(current_viruses.begin(), current_viruses.end(), [](const SARS_COV2* v1, const SARS_COV2* v2){
                return v1->sim_to_target < v2->sim_to_target;
            });
            srand((unsigned) time(NULL));
            int rand_anc_1 = rand() % num_of_vir;
            int rand_anc_2 = rand() % num_of_vir;
            int rand_inx_low = rand() % dim;
            int rand_inx_high = rand() % dim;
            if(rand_inx_low > rand_inx_high){
                int temp = rand_inx_high;
                rand_inx_high = rand_inx_low;
                rand_inx_low = temp;
            }
            char* new_anc_1 = new char[dim];
            strcpy(new_anc_1 ,ancestors[rand_anc_1]->current_string);
            char* new_anc_2 = new char[dim];
            strcpy(new_anc_2 ,ancestors[rand_anc_2]->current_string);
            for(int i=rand_inx_low; i < rand_inx_high; i++){
                char temp = new_anc_1[i];
                new_anc_1[i] = new_anc_2[i];
                new_anc_2[i] = temp;
            }
            delete current_viruses[0];
            current_viruses.erase(current_viruses.begin());
            switch (ancestors[rand_anc_1]->type) {
                case 'a':
                    current_viruses.push_back(new Alpha(static_cast<Alpha*>(ancestors[rand_anc_1]), new_anc_1));
                    break;
                case 'd':
                    current_viruses.push_back(new Delta(static_cast<Delta*>(ancestors[rand_anc_1]), new_anc_1));
                    break;
                case 'o':
                    current_viruses.push_back(new Omicron(static_cast<Omicron*>(ancestors[rand_anc_1]), new_anc_1));
                    break;
            }
            current_viruses[num_of_vir-1]->calc_sim_to_target(target_string);
            delete current_viruses[0];
            current_viruses.erase(current_viruses.begin());

            switch (ancestors[rand_anc_2]->type) {
                case 'a':
                    current_viruses.push_back(new Alpha(static_cast<Alpha*>(ancestors[rand_anc_2]), new_anc_2));
                    break;
                case 'd':
                    current_viruses.push_back( new Delta(static_cast<Delta*>(ancestors[rand_anc_2]), new_anc_2));
                    break;
                case 'o':
                    current_viruses.push_back( new Omicron(static_cast<Omicron*>(ancestors[rand_anc_2]), new_anc_2));
                    break;
            }
            current_viruses[num_of_vir-1]->calc_sim_to_target(target_string);
            std::sort(current_viruses.begin(), current_viruses.end(), [](const SARS_COV2* v1, const SARS_COV2* v2){
                return v1->sim_to_target < v2->sim_to_target;
            });
            if (current_viruses[num_of_vir-1]->sim_to_target > strongest_val){
                strongest_val = current_viruses[num_of_vir-1]->sim_to_target;
                strcpy(strongest_string, current_viruses[num_of_vir-1]->current_string);
                strongest_type = current_viruses[num_of_vir-1]->type;
            }
            if(strongest_val == 1){
                printAll();
                return;
            }
        }
        printAll();
    }
    void printAll(){
        for(int i=0; i< num_of_vir; i++){
            cout << current_viruses[i]->type;
            for (int j=0; j< dim; j++){
                cout<<" "<<current_viruses[i]->current_string[j];
            }
            cout<<endl;
        }
        cout<<endl;
        for(int i=0; i< num_of_vir; i++){
            cout << ancestors[i]->type;
            for (int j=0; j< dim; j++){
                cout<<" "<<ancestors[i]->current_string[j];
            }
            cout<<" "<<ancestors[i]->get_anc()->refCounter<<endl;
        }
        cout<<endl;
        cout<< strongest_type;
        for(int i=0;i<dim;i++){
            cout<<" "<<strongest_string[i];
        }
    }
};


#endif //COVIDVIEROSESSIMOLATION_SIMULATION_H
