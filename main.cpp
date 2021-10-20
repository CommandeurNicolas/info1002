#include <iostream>
#include <sstream>
#include <iomanip>
#include "hash.cpp"
#include "Inverter.cpp"
#include <algorithm>

using namespace std;

string hexStr(Byte *data, int len) {
    stringstream ss;
    ss << hex;

    for (int i(0); i < len; ++i)
        ss << setw(2) << setfill('0') << (int) data[i];
    return ss.str();
}


int main(int argc, char *argv[]) {

    string s = "Salut";
    string s2 = "Bob";

    Inverter myInverter1("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1, 3, hash_SHA1_string, 20);
    Inverter myInverter2("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4, 4, hash_SHA1_string, 20);
    Inverter myInverter3("abcdefghijklmnopqrstuvwxyz", 4, 5, hash_MD5_string, 20);

    hash_MD5_string(s, myInverter3.b);
    string res = hexStr(myInverter3.b, myInverter3.sizeByte);
    cout << res << endl;

    hash_SHA1_string(s2, myInverter3.b);
    res = hexStr(myInverter3.b, myInverter3.sizeByte);
    cout << res << endl;

    cout << myInverter1.i2c(12345) << endl;
    cout << myInverter2.i2c(1234) << endl;
    cout << myInverter3.i2c(382537153) << endl;

    hash_MD5_string("oups", myInverter3.b);
    cout << hexStr(myInverter3.b, myInverter3.sizeByte) << endl <<
         myInverter3.N << endl
         << "h2i : " << myInverter3.h2i(myInverter3.b, 1) << endl;

    cout << myInverter3.i2i(1, 1) << endl;

    Chaine chaine = myInverter3.nouvelle_chaine(1, 1);
    cout << "begin de taille 1 a " << 1 << ":" << chaine.b << " ..... " << chaine.e << endl;
    chaine = myInverter3.nouvelle_chaine(1, 2);
    cout << "begin de taille 1 a " << 2 << ":" << chaine.b << " ..... " << chaine.e << endl;
    chaine = myInverter3.nouvelle_chaine(1, 10);
    cout << "begin de taille 1 a " << 10 << ":" << chaine.b << " ..... " << chaine.e << endl;
     chaine = myInverter3.nouvelle_chaine(1, 100);
    cout << "begin de taille 1 a " << 100 << ":" << chaine.b << " ..... " << chaine.e << endl;

    vector<Chaine> tab = myInverter3.creer_table(10,1000);
    for (const auto &item : tab){
        cout << item.b << "...." << item.e << endl;
    }

    return 0;
}

