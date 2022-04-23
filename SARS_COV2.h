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

    char* current_string;
    char type;
    static int dimensions;
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

    int h(SARS_COV2 &a, SARS_COV2 &t){
        int i, k = 0;
        for(i = 0; i < dimensions; i++){
            if( a.current_string[i] == t.current_string[i]){
                k++;
            }
        }
        return k;
    }
    virtual void change_chars() = 0;
    ~SARS_COV2() {
        if(--ancestor->refCounter == -1){
            delete ancestor;
        }
    };

};


#endif //COVIDVIEROSESSIMOLATION_SARS_COV2_H
