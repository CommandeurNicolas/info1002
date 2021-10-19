//
// Created by neptune on 18/10/2021.
//

#include "Inverter.h"
#include <math.h>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

Inverter::Inverter(string alphabet, long min, long max, void hashingMethod(string, Byte *)) {
    this->alphabet = alphabet;

    this->minSize = min;
    this->maxSize = max;
    this->hash = hashingMethod;
    this->N = 0;
    this->size = (long) this->alphabet.length();
    this->T = {};

    for (long i = this->minSize; i <= this->maxSize; i++) {
        this->N += pow((long) this->size, i);
        this->T.push_back(pow((long) this->size, i));
    }

}

string Inverter::i2c(long code) {
//    long codeTemp = code;
//    string res = "";
//    int n = 0;
//
//    for (int i = this->minSize; i <= this->maxSize; i++) {
//        if (this->T[i] < codeTemp) {
//            codeTemp -=  this->T[i];
//            n++;
//        }
//    }
//
//    char letter = codeToLetter(codeTemp % this->size);
//
//    for (int i = 0; i < this->maxSize; i++) {
//        res.append(string(1,letter));
//        codeTemp = codeTemp / this->size;
//        letter = codeToLetter(codeTemp % this->size);
//
//    }
//
//    reverse(res.begin(),  res.end());
//    return res;
    long num = code&;
    long new_n = num % this->size;
    int i = 0;
    for (int j = this->minSize; j <= this->maxSize; j++) {
        if (this->T[i] < code) {
            num = num - this->T[i];
            i++;
        }
    }
    string res;
    for (int i = 0; i < this->maxSize; i++) {
        res += (this->alphabet[new_n]);
        num = (num / this->size);
        new_n = (num % this->size);
    }
    reverse(res.begin(),res.end());
    cout << res << endl;
    return res;

}

char Inverter::codeToLetter(long code) {

    return this->alphabet[code];

}