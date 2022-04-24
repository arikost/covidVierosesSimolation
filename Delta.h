//
// Created by USER on 4/23/2022.
//

#ifndef COVIDVIEROSESSIMOLATION_DELTA_H
#define COVIDVIEROSESSIMOLATION_DELTA_H
#include "SARS_COV2.h"

class Delta : public  SARS_COV2{
public:
    double p ;
    SARS_COV2_ptr *ancestor;
    Delta(char* string_val, char t, int d): ancestor(new SARS_COV2_ptr(string_val, t, d)){
        this->current_string = new char[d];
        strcpy(current_string, string_val);
        this->type = t;
        this->dimensions = d;
        this->p = 1/(double)d;
    }
    Delta(Delta *rhs, char* string_val): ancestor(rhs->ancestor){
        ++ancestor->refCounter;
        this->current_string = new char[rhs->dimensions];
        strcpy(current_string, string_val);
        this->dimensions = rhs->dimensions;
        this->type = rhs->type;
        this->p = 1/(double )dimensions;

    }

    void change_chars() override{
        srand((unsigned) time(NULL));
        for(int i=0; i < dimensions; i++) {
            double t = (double) rand() / RAND_MAX;
            if(t < p ){
                switch (current_string[i]) {
                    case 'A':
                        current_string[i] = 'T';
                        break;
                    case 'C':
                        current_string[i] = 'G';
                        break;
                    case 'G':
                        current_string[i] = 'C';
                        break;
                }
            }
        }
    }
    SARS_COV2_ptr* get_anc(){
        return this->ancestor;
    }
    ~Delta(){
        if(--ancestor->refCounter == -1){
            delete ancestor;
        }
        delete[] current_string;
    }

};


#endif //COVIDVIEROSESSIMOLATION_DELTA_H
