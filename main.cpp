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
    Inverter myInverter("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 4, 5, hash_SHA1_string);

    cout << myInverter.i2c(142678997) << endl;
    return 0;
}

