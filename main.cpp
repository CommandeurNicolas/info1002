#include <iostream>
#include <sstream>
#include <iomanip>
#include "hash.cpp"

using namespace std;

string hexStr(Byte *data, int len)
{
    stringstream ss;
    ss << hex;

    for (int i(0); i < len; ++i)
        ss << setw(2) << setfill('0') << (int)data[i];
    return ss.str();
}

int main(int argc, char *argv[])
{

    Byte b[32];

    char *s = "Salut";
    char *s2 = "Bob";

    hash_MD5(s, b);
    string res = hexStr(b, 32);
    cout << res << endl;

    hash_SHA1(s2, b);
    res = hexStr(b, 32);
    cout << res << endl;

    return 0;
}