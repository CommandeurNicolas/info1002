//
// Created by neptune on 18/10/2021.
//

#include "Inverter.h"
#include <math.h>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <limits>
#include <bitset>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <climits>

typedef unsigned char Byte; // facultatif

using namespace std;

// Empty constructor
Inverter::Inverter() {}

Inverter::Inverter(string alphabet, uint64_t min, uint64_t max, void hashMethod(string, Byte *), int sizeByte,
                   string hashingMethod) {
    this->alphabet = alphabet;

    this->minSize = min;
    this->maxSize = max;
    this->hash = hashMethod;
    this->hashingMethod = hashingMethod;
    this->N = 0;
    this->size = (uint64_t)
    this->alphabet.length();

    this->sizeByte = sizeByte;
    this->b = new Byte[this->sizeByte];
    this->texte = new char[this->maxSize];

    this->chaine.b = 0;
    this->chaine.e = 0;

    this->table.hauteur = 0;
    this->table.largeur = 0;

    this->powT = {};
    for (uint64_t i = this->minSize; i <= this->maxSize; i++) {
        this->N += pow(this->size, i);
        this->powT.push_back(pow((uint64_t)
        this->size, i));
    }

}

string Inverter::i2c(uint64_t code) {
    uint64_t codeTemp = code;
    string res = "";
    int n = 0;
    int i;
    for (i = this->minSize; i <= this->maxSize; i++) {
        if (this->powT[n] < codeTemp) {
            codeTemp -= this->powT[n];
            n++;
        } else {
            break;
        }
    }

    char letter = codeToLetter(codeTemp % this->size);

    for (int j = 0; j < i; j++) {
        res.append(string(1, letter));
        codeTemp = codeTemp / this->size;
        letter = codeToLetter(codeTemp % this->size);
    }

    reverse(res.begin(), res.end());
    return res;
}

char Inverter::codeToLetter(uint64_t code) {
    return this->alphabet[code];
}

// t begin at 0 instead of 1
uint64_t Inverter::h2i(Byte *empreinte, int t) {
    Byte *temp = empreinte;
    return (*((uint64_t *) temp) + t) % this->N;
}

uint64_t Inverter::i2i(uint64_t code, int indice) {
    this->hash(i2c(code), this->b);
    return h2i(this->b, indice);
}

Chaine Inverter::nouvelle_chaine(uint64_t idxl, int largeur) {
    Chaine chaine;
    chaine.b = idxl;
    uint64_t code = idxl;
    for (int i = 1; i < largeur; ++i) {
        code = i2i(code, i);
    }
    chaine.e = code;
    return chaine;
}

uint64_t Inverter::index_aleatoire() {
    random_device rd;
    mt19937_64 eng(rd());
    uniform_int_distribution <uint64_t> distr;
    return (distr(eng)) % this->N;
}

bool compare2Chaine(const Chaine &a, const Chaine &b) {
    return a.e < b.e;
}

Table Inverter::creer_table(int largeur, int hauteur) {
    Table t;
    t.hauteur = hauteur;
    t.largeur = largeur;
    for (int i = 0; i < t.hauteur; ++i) {
        t.chaines.push_back(nouvelle_chaine(this->index_aleatoire(), t.largeur));
    }
    sort(t.chaines.begin(), t.chaines.end(), compare2Chaine);
    return t;
}

bool Inverter::write(string namefile) {
    // Create and open a text file
    ofstream MyFile(namefile);

    if (!MyFile.good())
        return false;

    MyFile << this->hashingMethod << " " <<
           this->alphabet << " " <<
           this->minSize << " " <<
           this->maxSize << " " <<
           this->table.hauteur << " " <<
           this->table.largeur << endl;


    for (const auto &item: this->table.chaines) {

        MyFile << item.b << endl << item.e << endl;
    }
    MyFile.close();
    return true;
}

bool Inverter::read(string namefile) {


    string str;
    ifstream MyFile(namefile);

    if (!MyFile.good())
        return false;

    getline(MyFile, str);

    istringstream inverterInfo(str);

    inverterInfo >> this->hashingMethod >>
                 this->alphabet >>
                 this->minSize >>
                 this->maxSize >>
                 this->table.hauteur >>
                 this->table.largeur;


    this->table.chaines = vector<Chaine>(this->table.hauteur);

    uint64_t begin, end;
    int n = 0;

    while (MyFile >> this->table.chaines[n].b >> this->table.chaines[n].e) {
        n++;
    }

    MyFile.close();
    return true;
}

void Inverter::afficheTable(int shift) {
    for (int i = 0; i < shift; ++i) {
        cout << "Index : " << i << " : " <<
             this->table.chaines[i].b << " ..... " <<
             this->table.chaines[i].e << endl;
    }
    cout << "....." << endl << "....." << endl;
    for (int i = shift; i > 0; --i) {
        cout << "Index : " << this->table.chaines.size() - i << " : " <<
             this->table.chaines[this->table.chaines.size() - i].b << " ..... " <<
             this->table.chaines[this->table.chaines.size() - i].e << endl;
    }
}

bool Inverter::inverse(Byte *empreinte, string &clair) {
    int nbCandidat = 0;
    uint64_t idx;
    for (int t = this->table.largeur - 1; t > 0; t--) {
        idx = this->h2i(empreinte, t);
        for (int i = t + 1; i < this->table.largeur; ++i) {
            idx = this->i2i(idx, i);
        }
        vector<Chaine>::iterator a, b;
        if (this->recherche(idx, a, b)) {
            for (vector<Chaine>::iterator i = a; i != b; ++i) {
                if (this->verifieCandidat(empreinte, t, i->b, clair)) {
                    return true;
                } else {
                    nbCandidat++;
                }
            }
        }
    }
    return false;
}

void Inverter::couverture() {
    auto m = (double) this->table.hauteur;
    auto v = 1.0f;
    for (auto i = 0; i < this->table.largeur; i++) {
        v *= 1 - (m / this->N);
        m = this->N * (1 - exp(-m / this->N));
    }
    cout << "Couverture ==> " << 100.0 * (1.0 - v) << " %" << endl;
}

// recherche dichotomique dans la table les premières et dernières lignes dont
// la seconde colonne est égale à idx
//   - table : table arc-en-ciel
//   - hauteur : nombre de chaines dans la table
//   - idx : indice à rechercher dans la dernière (deuxième) colonne
//   - a et b : (résultats) numéros des premières et dernières lignes dont les
//     dernières colonnes sont égale à idx
bool Inverter::recherche(uint64_t idx, vector<Chaine>::iterator &a, vector<Chaine>::iterator &b) {

    struct Comp {
        bool operator()(const Chaine &c, uint64_t idx) const { return c.e < idx; }

        bool operator()(uint64_t idx, const Chaine &c) const { return idx < c.e; }
    };

    pair <vector<Chaine>::iterator, vector<Chaine>::iterator> bounds;

    bounds = equal_range(this->table.chaines.begin(), this->table.chaines.end(), idx, Comp{});

    a = bounds.first;
    b = bounds.second;

    return (bounds.second - bounds.first) != this->table.chaines.size();
}

// vérifie si un candidat est correct
//   - h : empreinte à inverser
//   - t : numéro de la colonne où a été trouvé le candidat
//   - idx : indice candidat (de la colonne t)
//   - clair : résultat : contient le texte clair obtenu
bool Inverter::verifieCandidat(Byte *h, int t, uint64_t idx, string &clair) {
    for (int i = 1; i < t; i++) {
        idx = this->i2i(idx, i);
    }
    clair = this->i2c(idx);
    Byte h2[this->sizeByte];
    this->hash(clair, h2);
    return this->hexStr(h2) == this->hexStr(h);
}

string Inverter::hexStr(Byte *data) {
    stringstream ss;
    ss << hex;

    for (int i(0); i < this->sizeByte; ++i)
        ss << setw(2) << setfill('0') << (int) data[i];
    return ss.str();
}

