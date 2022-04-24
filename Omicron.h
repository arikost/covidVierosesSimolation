//
// Created by USER on 4/23/2022.
//

#ifndef COVIDVIEROSESSIMOLATION_OMICRON_H
#define COVIDVIEROSESSIMOLATION_OMICRON_H

#include "SARS_COV2.h"


class Omicron : public SARS_COV2 {
public:
    double p;
    SARS_COV2_ptr *ancestor;

    Omicron(char *string_val, char t, int d) : ancestor(new SARS_COV2_ptr(string_val, t, d)) {
        this->current_string = new char[d];
        strcpy(current_string, string_val);
        this->type = t;
        this->dimensions = d;
        this->p = 2/(double)d;
    }

    Omicron(Omicron *rhs, char *string_val) : ancestor(rhs->ancestor) {
        ++ancestor->refCounter;
        this->current_string = new char[rhs->dimensions];
        strcpy(current_string, string_val);
        this->dimensions = rhs->dimensions;
        this->type = rhs->type;
        this->p = 2/(double )dimensions;
    }

    void change_chars() override {
        srand((unsigned) time(NULL));
        for (int i = 0; i < dimensions; i++) {
            double t = (double) rand() / RAND_MAX;
            if (t < p) {
                switch (current_string[i]) {
                    case 'T':
                        current_string[i] = 'A';
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

    ~Omicron(){
        if(--ancestor->refCounter == -1){
            delete ancestor;
        }
        delete[] current_string;
    }

};
#endif //COVIDVIEROSESSIMOLATION_OMICRON_H
