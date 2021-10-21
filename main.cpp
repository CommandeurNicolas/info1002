#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <typeinfo>
#include "hash.cpp"
#include "Inverter.cpp"
#include "CLI11.hpp"

using namespace std;

// Global vars
Byte b[32];
auto hashFunction = hash_MD5_string;
int min_size = 4;
int max_size = 5;
string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int value;
int d = 5;
string hashName;

string hexStr(Byte *data, int len) {
    stringstream ss;
    ss << hex;

    for (int i(0); i < len; ++i)
        ss << setw(2) << setfill('0') << (int) data[i];
    return ss.str();
}

void setMD5HashFunction() {
    hashFunction = hash_MD5_string;
}

void setSHA1HashFunction() {
    hashFunction = hash_SHA1_string;
}

void hashTest(string s) {
    string res;

    if (hashFunction == hash_MD5_string) {
        hash_MD5_string(s, b);
        res = hexStr(b, 32);
        cout << "Hashing \"" << s << "\" with MD5 function : " << res << endl << endl;
    }
    if (hashFunction == hash_SHA1_string) {
        hash_SHA1_string(s, b);
        res = hexStr(b, 32);
        cout << "Hashing \"" << s << "\" with SHA1 function : " << res << endl << endl;
    }
}

void i2cTest(string s) {

    int i = stoi(s);
    // Inverter myInverter1("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1, 3, hashFunction);
    // cout << "When alphabet is ABCDEFGHIJKLMNOPQRSTUVWXYZ, min = 1 and max = 3 : " << myInverter1.i2c(i) << endl;
    // Inverter myInverter2("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4, 4, hashFunction);
    // cout << "When alphabet is ABCDEFGHIJKLMNOPQRSTUVWXYZ, min = 4 and max = 4 : " << myInverter2.i2c(i) << endl;
    // Inverter myInverter3("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 4, 5, hashFunction);
    // cout << "When alphabet is ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz, min = 4 and max = 5 : " << myInverter3.i2c(i) << endl;

    Inverter myInverter(alphabet, min_size, max_size, hashFunction, 32, "");
    cout << "When alphabet is " << alphabet << ", min = " << min_size << " and max = " << max_size << " : "
         << myInverter.i2c(i) << endl << endl;
}

void h2iTest(vector <string> args) {
    Inverter myInverter(alphabet, min_size, max_size, hashFunction, 32, "");

    hash_MD5_string(args[0], b);
    cout << "alphabet = " << alphabet << endl << "taille_min = " << min_size << endl << "taille_max = " << max_size
         << endl << "N = " << myInverter.N << endl;
    cout << "MD5(\"oups\") = " << hexStr(b, 32) << endl << "h2i(MD5(\"oups\"), " << args[1] << ") = "
         << myInverter.h2i(b, stoi(args[1])) << endl << endl;
}

void i2iTest(vector <string> args) {
    cout << args[0] << endl;
    // TODO: faire le test de i2i (QUESTION 6)
}

int main2(int argc, char *argv[]) {

    // CLI PARSING
    CLI::App app{};

    // App command flags
    bool isMD5{false};
    bool isSHA1{false};
    app.add_flag("--md5", isMD5, "use md5 hash function (default)");
    app.add_flag("--sha1", isSHA1, "use sha1 hash function");

    // App options
    app.add_option("--alphabet", alphabet, "allowed letters for cleartext");

    app.add_option("--min-size", min_size, "minimum size of clear text");
    app.add_option("--max-size", max_size, "maximum size of clear text");

    app.add_option("--value", value, "value that will be treated");

    app.add_option("-d, --delay", d, "number of seconds between consecutive log messages (default 5)");

    // Test command
    bool isConfig = false;
    vector <string> sTab;
    vector <string> iTab;
    vector <string> h2iArgs;
    vector <string> i2iArgs;
    auto test = app.add_subcommand("test", "development tests (\"./main test --list\" for available tests)");

    test->add_flag("--config", isConfig, "print the default config for the tests");
    test->add_option("--hash", sTab, "compute hash of string s1, s2, ...");
    test->add_option("--i2c", iTab, "compute i2c(i1), i2c(i2), ...");
    test->add_option("--h2i", h2iArgs, "compute h2i(H(s), t)")->allow_extra_args(true);
    test->add_option("--i2i", i2iArgs, "compute i2i(i1, t1), i2i(i2, t2), ...")->allow_extra_args(
            true); // TODO: revoir Q6
    // test->add_option("--time-i2i", iTab, "compute average time of single i2i call over N calls");
    // test->add_option("--full-chain", iTab, "compute (full) chains starting at i1, i2, ...");
    // test->add_option("--FULL-chain", iTab, "compute (full, with details) chains starting at i1, i2, ...");
    // test->add_option("--chain", iTab, "compute chains starting at i1, i2, ...");
    // test->add_option("--search", iTab, "search the first and last occurences of i in table");
    test->add_option("--list", "this list");

    test->callback([&]() {
        if (isConfig) {
            cout << "CONFIG : \n" << endl;
            cout << "Byte b[32]" << endl << "hashFunction = hash_MD5_string" << endl << "min_size = 4" << endl
                 << "max_size = 5" << endl
                 << "alphabet = \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\"" << endl << "d = 5" << endl;
        } else {
            std::cout << "Testing : \n\n";
        }

        if (isMD5){
            hashName = "MD5";
            hashFunction = hash_MD5_string;
        }

        if (isSHA1){
            hashFunction = hash_SHA1_string;
            hashName = "SHA1";
        }


        if (!sTab.empty())
            for (int i = 0; i < sTab.size(); i++)
                hashTest(sTab[i]);

        if (!iTab.empty())
            for (int i = 0; i < iTab.size(); i++)
                i2cTest(iTab[i]);

        if (!h2iArgs.empty())
            h2iTest(h2iArgs);

        if (!i2iArgs.empty())
            i2iTest(i2iArgs); // TODO: revoir Q6
    });

    // PARSING argv
    Byte b[32];

    CLI11_PARSE(app, argc, argv);

    return 0;
}

int main(int argc, char *argv[]) {

    string s = "Salut";
    string s2 = "Bob";

    Inverter myInverter1("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1, 3, hash_SHA1_string, 20, "MD5");
    Inverter myInverter2("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4, 4, hash_SHA1_string, 20, "MD5");
    Inverter myInverter3("abcdefghijklmnopqrstuvwxyz", 4, 5, hash_MD5_string, 20, "MD5");

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

    myInverter3.table = myInverter3.creer_table(10, 100);
    myInverter3.write("res");
    myInverter2.read("res");
    myInverter2.write("res2");
    myInverter3.afficheTable(10);
    return 0;
}