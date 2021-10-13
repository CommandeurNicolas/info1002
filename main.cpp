#include <iostream>
#include <string>
#include "empreinte.cpp"

using namespace std;

int main(int argc, char *argv[]){
    cout << "Hello Uiii !" << endl;

    byte res[32];

    cout << hash_MD5("Salut", res) << endl;
    cout << hash_SHA1("Bob", res) << endl;
    return 0;
}