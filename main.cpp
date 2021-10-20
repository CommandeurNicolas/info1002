#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <typeinfo>
#include "hash.cpp"
#include "Inverter.cpp"
#include "CLI11.hpp"

using namespace std;

string hexStr(Byte *data, int len) {
    stringstream ss;
    ss << hex;

    for (int i(0); i < len; ++i)
        ss << setw(2) << setfill('0') << (int) data[i];
    return ss.str();
}

void hashTest(string s) {
    if (s != "hash")
    {
        Byte b[32];
        string res;

        cout << "______________ " << s << " ______________" << endl;
        hash_MD5_string(s, b);
        res = hexStr(b, 32);
        cout << "Hashing \"" << s << "\" with MD5 function : " << res << endl; 

        hash_SHA1_string(s, b);
        res = hexStr(b, 32);
        cout << "Hashing \"" << s << "\" with SHA1 function : " << res << endl;
    }
}

void i2cTest(string s) {

    int i = stoi(s);

    auto hash = hash_MD5_string;

    cout << "______________ " << i << " ______________" << endl;
    Inverter myInverter1("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1, 3, hash);
    cout << "When alphabet is ABCDEFGHIJKLMNOPQRSTUVWXYZ, min = 1 and max = 3 : " << myInverter1.i2c(i) << endl;
    Inverter myInverter2("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4, 4, hash);
    cout << "When alphabet is ABCDEFGHIJKLMNOPQRSTUVWXYZ, min = 4 and max = 4 : " << myInverter2.i2c(i) << endl;
    Inverter myInverter3("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 4, 5, hash);
    cout << "When alphabet is ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz, min = 4 and max = 5 : " << myInverter3.i2c(i) << endl; 
}

int main(int argc, char *argv[]) {

    // CLI PARSING
    CLI::App app{};

    // Test command
    vector<string> sTab;
    vector<string> iTab;
    auto test = app.add_subcommand("test", "development tests (\"./main test --list\" for available tests)");

    test->add_option("--hash", sTab, "compute hash of string s1, s2, ...")->each(hashTest);
    test->add_option("--i2c", iTab, "compute i2c(i1), i2c(i2), ...")->each(i2cTest);
    test->add_option("--h2i", iTab, "compute h2i(H(s), t)");
    test->add_option("--i2i", iTab, "compute i2i(i1, t1), i2i(i2, t2), ...");
    // test->add_option("--time-i2i", iTab, "compute average time of single i2i call over N calls");
    // test->add_option("--full-chain", iTab, "compute (full) chains starting at i1, i2, ...");
    // test->add_option("--FULL-chain", iTab, "compute (full, with details) chains starting at i1, i2, ...");
    // test->add_option("--chain", iTab, "compute chains starting at i1, i2, ...");
    // test->add_option("--search", iTab, "search the first and last occurences of i in table");
    test->add_option("--list", "this list");


    // App command flags
    bool isMD5{false};
    bool isSHA1{false};
    app.add_flag("--md5", isMD5, "use md5 hash function (default)");
    app.add_flag("--sha1", isSHA1, "use sha1 hash function");

    // App options
    string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
    app.add_option("--alphabet", alphabet, "allowed letters for cleartext");

    int min_size = 0;
    int max_size = 0;
    app.add_option("--min-size", min_size, "minimum size of clear text");
    app.add_option("--max-size", max_size, "maximum size of clear text");

    int value = 0;
    app.add_option("--value", value, "value that will be treated");

    int d = 5;
    app.add_option("-d, --delay", d, "number of seconds between consecutive log messages (default 5)");

    // PARSING argv
    CLI11_PARSE(app, argc, argv);

    // Work to do
    auto hash = hash_MD5_string;
    if (isMD5) {
        hash = hash_MD5_string;
    }
    if (isSHA1) {
        hash = hash_SHA1_string;
    }
    
    Inverter myInverter2(alphabet, min_size, max_size, hash);
    cout << "When alphabet is "<< alphabet << ", min = "<< min_size << " and max = " << max_size << " : " << myInverter2.i2c(value) << endl;

    hash_MD5_string("oups",b);
    cout << hexStr(b,32)<<endl << myInverter3.N <<endl << myInverter3.h2i(b,0) << endl;

    return 0;
}