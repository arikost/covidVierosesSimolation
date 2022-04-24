//
// Created by USER on 4/23/2022.
//

#ifndef COVIDVIEROSESSIMOLATION_ALPHA_H
#define COVIDVIEROSESSIMOLATION_ALPHA_H
#include "SARS_COV2.h"


class Alpha : public SARS_COV2{
public:
    double p ;
    SARS_COV2_ptr *ancestor;
    Alpha(char* string_val, char t, int d): ancestor(new SARS_COV2_ptr(string_val, t, d)){
        this->current_string = new char[d];
        strcpy(current_string, string_val);
        this->type = t;
        this->dimensions = d;
        this->p = 0.37;
    }
    Alpha(const Alpha* rhs,char* string_val): ancestor(rhs->ancestor){
        ++this->ancestor->refCounter;
        this->current_string = new char[rhs->dimensions];
        strcpy(current_string, string_val);
        this->dimensions = rhs->dimensions;
        this->type = rhs->type;
        this->p = 0.37;
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
                    case 'T':
                        current_string[i] = 'A';
                        break;
                }
            }
        }
    }
    SARS_COV2_ptr* get_anc(){
        return this->ancestor;
    }

    ~Alpha(){
        if(--ancestor->refCounter == -1){
            delete ancestor;
        }
        delete[] current_string;
    }
};


#endif //COVIDVIEROSESSIMOLATION_ALPHA_H
