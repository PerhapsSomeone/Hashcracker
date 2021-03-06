#include <iostream>
#include "sha512.h"
#include "md5.h"
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <string>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
 
using std::string;
using std::cout;
using std::endl;
using std::cin;
 
bool checkHash(string hash, string mode);
void numericCracker(string hash, string mode);
string hasher(string content, string mode);
void wordlistCracker(string hash, string mode);
 
int main(int argc, char *argv[]) {

    string input = "grape";
    string output1 = sha512(input);
    cout << "C++ Hashcracker (SHA512, MD5)" << endl;
    cout << "1 - SHA512" << endl;
    cout << "2 - MD5" << endl;
    cout << "Enter Number: ";
    int mode;
    cin >> mode;
    string hash;
    cout << "Enter Hash: ";
    cin >> hash;
    cout << "Attack Mode" << endl;
    cout << "1 - Numeric Cracker" << endl;
    cout << "2 - Wordlist" << endl;
    cout << "Enter Number: ";
    int attackVector;
    cin >> attackVector;

    if(attackVector == 1) {
        switch(mode) {
            case 1:
                if(checkHash(hash, "SHA512")) {
                    numericCracker(hash, "SHA512");
                }
                break;
            case 2:
                if(checkHash(hash, "MD5")) {
                    numericCracker(hash, "MD5");
                }
                break;
        }
        return 0;
    }
    if(attackVector == 2) {
        switch(mode) {
            case 1:
                if(checkHash(hash, "SHA512")) {
                    wordlistCracker(hash, "SHA512");
                }
                break;
            case 2:
                if(checkHash(hash, "MD5")) {
                    wordlistCracker(hash, "MD5");
                }
                break;
        }
        return 0;
    }
    else {
        exit(0);
    }
 }
 
 bool checkHash(string hash, string mode) {
     if(mode == "SHA512") {
         if(hash.length() == 128) {
             return true;
         }
     }
 
     if(mode == "MD5") {
         if(hash.length() == 32) {
             return true;
         }
     }
 
     return false;
 }
 
 string hasher(string content, string mode) {
     if(mode == "SHA512") {
         return sha512(content);
     }
     if(mode == "MD5") {
         return md5(content);
     }
 }
 
 void numericCracker(string hash, string mode) {
     int i = 0;
     string bHash;
     string iterator;
 
     while (true) {
         iterator = patch::to_string(i);
         bHash = hasher(iterator, mode);
         cout << "[*] Cracking... | " << i << " : " << hash << "\r";
         if(hash == bHash) {
             cout << "\nMatch found! " << "Number: " << i << " Hash: " << hash << endl;
             exit(0);
         }
         i++;
     }
 }

void wordlistCracker(string hash, string mode) {
    int linecount = 0;
    std::string line;
    
    cout << "Wordlist Filename/Path: ";
    string filepath;
    cin >> filepath;

    std::ifstream file(filepath.c_str());

    if (!file) {
        cout << "Unable to open file";
        exit(1);
    }

    string s;
    string bHash;
    int i = 1;
    while (std::getline(file, s))
    {
        bHash = hasher(s, mode);
        cout << "[*] Cracking... | " << i << " : " << s << "\r\e[K";
        if(hash == bHash) {
            cout << "\nMatch found! " << "Entry: " << s << " Hash: " << hash << " Try: " << i << endl;
            exit(0);
        }
        i++;
    }
    cout << "No match found!" << endl;
    exit(0);
}