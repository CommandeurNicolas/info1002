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
    long minSize, maxSize;
    long size;
    long N;
    vector<long> T;

    void (*hash)(string s, Byte *empreinte);

    Inverter(string alphabet, long min, long max, void hashingMethod(string, Byte *));

    string i2c(long code);

    char codeToLetter(long code);

};


#endif //CRYPTO_INVERTER_H
