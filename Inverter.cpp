//
// Created by neptune on 18/10/2021.
//

#include "Inverter.h"
#include <math.h>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

Inverter::Inverter(string alphabet, double min, double max, void hashingMethod(string, Byte *)) {
    this->alphabet = alphabet;

    this->minSize = min;
    this->maxSize = max;
    this->hash = hashingMethod;
    this->N = 0;
    this->size = this->alphabet.length();
    this->T = {};

    for (double i = this->minSize; i <= this->maxSize; i++) {
        this->N += pow((double) this->size, i);
        this->T.push_back(pow((double) this->size, i));
    }

}

string Inverter::i2c(int code) {
    int codeTemp = code;
    int n = 1;
    while (codeTemp >= (int) pow(this->size, n)) {
        if (n > this->minSize){
            codeTemp -= (int) pow(this->size, n);
        }
        n++;
    }
    string res = string(this->maxSize, this->alphabet[0]);
    cout << "code temps init : "<< codeTemp<<endl;
    for (int i = 0; i < n; i++) {

        int codeNextLettre = codeTemp % this->size;
        cout <<i<<endl;

        cout << "Before : " << codeTemp << " " << res[i] << " --> "
        << codeToLetter(codeNextLettre)
        << " ("<<codeNextLettre<<")" << endl;

        res[i] = codeToLetter(codeNextLettre);
        cout << "After : " << floor(codeTemp / this->size)  << endl;
        codeTemp = floor(codeTemp / this->size);
    }
    reverse(res.begin(),  res.end());
    return res;
}

char Inverter::codeToLetter(int code) {

    return this->alphabet[code];

}