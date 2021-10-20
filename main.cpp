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

    Byte b[32];

    string s = "Salut";
    string s2 = "Bob";

    hash_MD5_string(s, b);
    string res = hexStr(b, 32);
    cout << res << endl;

    hash_SHA1_string(s2, b);
    res = hexStr(b, 32);
    cout << res << endl;

    Inverter myInverter1("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1, 3, hash_SHA1_string);
    cout << myInverter1.i2c(12345) << endl;
    Inverter myInverter2("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4, 4, hash_SHA1_string);
    cout << myInverter2.i2c(1234) << endl;
    Inverter myInverter3("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4, 5, hash_SHA1_string);
    cout << myInverter3.i2c(142678997) << endl;

    hash_MD5_string("oups",b);
    cout << hexStr(b,32)<<endl << myInverter3.N <<endl << myInverter3.h2i(b,0) << endl;

    return 0;
}

