//
// Created by neptune on 18/10/2021.
//

#ifndef CRYPTO_INVERTER_H
#define CRYPTO_INVERTER_H

#include <vector>


using namespace std;

struct Chaine{
    uint64_t b, e;
};



class Inverter {
public:
    // Member
    string alphabet;
    uint64_t minSize, maxSize;
    uint64_t size;
    uint64_t N;
    vector<uint64_t> powT;

    string texte;
    Byte *b;
    int sizeByte;

    Chaine chaine;

    void (*hash)(string s, Byte *empreinte);

    // Constructor
    Inverter(string alphabet, uint64_t min, uint64_t max, void hashingMethod(string, Byte *), int sizeByte);

    // Functions

    string i2c(uint64_t code);

    uint64_t h2i(Byte *empreinte, int t);

    uint64_t i2i(uint64_t code, int indice);

    char codeToLetter(uint64_t code);

    Chaine nouvelle_chaine(uint64_t idxl, int largeur);

    uint64_t index_aleatoire();

    vector<Chaine> creer_table(int largeur, int hauteur);
};


#endif //CRYPTO_INVERTER_H
