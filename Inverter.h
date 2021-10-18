//
// Created by neptune on 18/10/2021.
//

#ifndef CRYPTO_INVERTER_H
#define CRYPTO_INVERTER_H

#include <vector>


using namespace std;

class Inverter {
public:
    string alphabet;
    double minSize, maxSize;
    int size;
    double N;
    vector<double> T;

    void (*hash)(string s, Byte *empreinte);

    Inverter(string alphabet, double min, double max, void hashingMethod(string, Byte *));

    string i2c(int code);

    char codeToLetter(int code);

};


#endif //CRYPTO_INVERTER_H
