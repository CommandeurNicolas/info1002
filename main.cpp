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
int size = 0;
Byte *b;
auto hashFunction = hash_MD5_string;
int min_size = 4;
int max_size = 5;
string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int value;
int d = 5;
string hashName;
Inverter myInverter;



void setMD5HashFunction() {
    hashFunction = hash_MD5_string;
}

void setSHA1HashFunction() {
    hashFunction = hash_SHA1_string;
}

void hashTest(string s) {
    string res;
    // Inverter myInverter(alphabet, min_size, max_size, hashFunction, 32, "");

    if (hashFunction == hash_MD5_string) {
        hash_MD5_string(s, b);
        res = myInverter.hexStr(b);
        cout << "Hashing \"" << s << "\" with MD5 function : " << res << endl << endl;
    }
    if (hashFunction == hash_SHA1_string) {
        hash_SHA1_string(s, b);
        res = myInverter.hexStr(b);
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

    // Inverter myInverter(alphabet, min_size, max_size, hashFunction);
    cout << "When alphabet is "<< alphabet << ", min = "<< min_size << " and max = " << max_size << " : " << myInverter.i2c(i) << endl << endl;
}

void h2iTest(vector<string> args) {
    hash_MD5_string(args[0],b);
    cout << "alphabet = " << alphabet << endl << "taille_min = " << min_size << endl << "taille_max = " << max_size << endl << "N = " << myInverter.N << endl;
    cout << "MD5(\"oups\") = " << myInverter.hexStr(b) << endl << "h2i(MD5(\"oups\"), "<< args[1] << ") = " << myInverter.h2i(b, stoi(args[1])) << endl << endl;
}

void i2iTest(vector <string> args) {
    cout << args[0] << endl;
    // TODO: faire le test de i2i (QUESTION 6)
}

void rainbow_table(vector<string> args) {
    myInverter.table = myInverter.creer_table(stoi(args[0]), stoi(args[1]));
    myInverter.write(args[2]);
}

void rainbow_info(vector<string> args) {
    myInverter.read(args[0]);
    myInverter.afficheTable(stoi(args[1]));
}

void rainbow_stats(vector<string> args) {
    
}

void rainbow_crack(vector<string> args) {
    
}

void rainbow_bruteforce(vector<string> args) {
    
}

int main(int argc, char *argv[]) {

    // CLI PARSING
    CLI::App app{};
    // Create subcommand (via options)
    vector<string> createArgs, infoArgs, statsArgs, crackArgs, bruteforceArgs;
    auto create = app.add_option("--create", createArgs, "create the corresponding rainbow tables (M=height, T=width)")->expected(3);
    auto info = app.add_option("--info", infoArgs, "display some information about the table from given file")->expected(2);
    auto stats = app.add_option("--stats", statsArgs, "give some information (cover, size) about rainbow tables without computing them (M=height, T=width)")->expected(2);
    auto crack = app.add_option("--crack", crackArgs, "crack the given hash with the rainbow tables")->allow_extra_args(true);
    auto bruteforce = app.add_option("--bruteforce", bruteforceArgs, "brute force the given hash")->expected(1);
    
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

    // Callback for main command
    app.callback([&]() {

        if (isMD5){
            hashName = "MD5";
            hashFunction = hash_MD5_string;
            b = new Byte[16];
            size = 16;
        }
        if (isSHA1){
            hashFunction = hash_SHA1_string;
            hashName = "SHA1";
            b = new Byte[20];
            size = 20;
        }

        string method;
        if (hashFunction == hash_MD5_string)
            method = "MD5";
        if (hashFunction == hash_SHA1_string)
            method = "SHA1";
        
        myInverter = Inverter(alphabet, min_size, max_size, hashFunction, size, method);
        
        if (!createArgs.empty())
            rainbow_table(createArgs);
        if (!infoArgs.empty())
            rainbow_info(infoArgs);
        if (!statsArgs.empty())
            rainbow_stats(statsArgs);
        if (!crackArgs.empty())
            rainbow_crack(crackArgs);
        if (!bruteforceArgs.empty())
            rainbow_bruteforce(bruteforceArgs);
    });

    // Test subcommand
    bool isConfig = false;
    vector <string> sTab;
    vector <string> iTab;
    vector <string> h2iArgs;
    vector <string> i2iArgs;
    auto test = app.add_subcommand("test", "development tests (\"./main test --list\" for available tests)");

    // Test flag and options
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
    test->add_option("--list", "this list")->expected(0);

    // Callback for test subcommand
    test->callback([&]() {
        if (isConfig) {
            cout << "CONFIG : \n" << endl;
            cout << "Byte b[32]" << endl << "hashFunction = hash_MD5_string" << endl << "min_size = 4" << endl
                 << "max_size = 5" << endl
                 << "alphabet = \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\"" << endl << "d = 5" << endl;
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
    CLI11_PARSE(app, argc, argv);

    return 0;
}

int main2(int argc, char *argv[]) {

    // string s = "Salut";
    // string s2 = "Bob";

    // Inverter myInverter1("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1, 3, hash_SHA1_string, 20, "MD5");
    // Inverter myInverter2("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4, 4, hash_SHA1_string, 20, "MD5");
    Inverter myInverter3("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4, 4, hash_MD5_string, 16, "MD5");

    // hash_MD5_string(s, myInverter3.b);
    // string res = hexStr(myInverter3.b, myInverter3.sizeByte);
    // cout << res << endl;

    // hash_SHA1_string(s2, myInverter3.b);
    // res = hexStr(myInverter3.b, myInverter3.sizeByte);
    // cout << res << endl;

    // cout << myInverter1.i2c(12345) << endl;
    // cout << myInverter2.i2c(1234) << endl;
    // cout << myInverter3.i2c(382537153) << endl;

    // hash_MD5_string("oups", myInverter3.b);
    // cout << hexStr(myInverter3.b, myInverter3.sizeByte) << endl <<
    //      myInverter3.N << endl
    //      << "h2i : " << myInverter3.h2i(myInverter3.b, 1) << endl;

    // cout << myInverter3.i2i(1, 1) << endl;

    // Chaine chaine = myInverter3.nouvelle_chaine(1, 1);
    // cout << "begin de taille 1 a " << 1 << ":" << chaine.b << " ..... " << chaine.e << endl;
    // chaine = myInverter3.nouvelle_chaine(1, 2);
    // cout << "begin de taille 1 a " << 2 << ":" << chaine.b << " ..... " << chaine.e << endl;
    // chaine = myInverter3.nouvelle_chaine(1, 10);
    // cout << "begin de taille 1 a " << 10 << ":" << chaine.b << " ..... " << chaine.e << endl;
    // chaine = myInverter3.nouvelle_chaine(1, 100);
    // cout << "begin de taille 1 a " << 100 << ":" << chaine.b << " ..... " << chaine.e << endl;

    myInverter3.table = myInverter3.creer_table(1000, 100000);
    myInverter3.write("res");
    myInverter3.read("res");
    // myInverter2.write("res2");
   // myInverter3.afficheTable(100);

    vector<Chaine>::iterator a, b;
    Byte by[myInverter3.sizeByte];
    string abcd = "ABCD";
    myInverter3.hash(abcd, by);
    cout << myInverter3.hexStr(by) << endl;
    string reversedString = "";
    myInverter3.couverture();
    if (myInverter3.inverse(by, reversedString))
        cout << "Foudn  it" << endl;
    else
        cout << "Fuck " << endl;
    cout << reversedString << endl;
    const char footprint[]="08054846bbc9933fd0395f8be516a9f9";
    Byte em[sizeof(footprint)];
    strcpy((char *)em,"08054846bbc9933fd0395f8be516a9f9");
    cout << myInverter3.hexStr(em) << endl;
    if (myInverter3.inverse(em, reversedString))
        cout << "Foudn  it" << endl;
    else
        cout << "Fuck " << endl;
    cout << reversedString << endl;
    return 0;
}
