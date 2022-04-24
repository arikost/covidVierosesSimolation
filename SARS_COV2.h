//
// Created by USER on 4/23/2022.
//

#ifndef COVIDVIEROSESSIMOLATION_SARS_COV2_H
#define COVIDVIEROSESSIMOLATION_SARS_COV2_H

#include <string>
#include <string.h>

using namespace std;

class SARS_COV2 {
public:
    double sim_to_target;
    char* current_string;
    char type;
    int dimensions;
    struct SARS_COV2_ptr{
        int refCounter;
        char* initString;

        char type_o ;
        SARS_COV2_ptr(char* val, char t, int d): refCounter(0){
            initString = new char[d];
            strcpy(initString, val);
            type_o = t;
        };

        ~SARS_COV2_ptr(){
            delete[] initString;
        };
    };
    SARS_COV2_ptr *ancestor;

    void calc_sim_to_target(const char* target){
        int i;
        double k = 0;
        for(i = 0; i < dimensions; i++){
            if( current_string[i] == target[i]){
                k++;
            }
        }
        sim_to_target = k/dimensions;
    }
    bool operator>(const SARS_COV2 &rhs) const{
        return sim_to_target > rhs.sim_to_target;
    }
    virtual SARS_COV2_ptr* get_anc() = 0;
    virtual void change_chars() = 0;
    virtual ~SARS_COV2() {};
};


#endif //COVIDVIEROSESSIMOLATION_SARS_COV2_H
