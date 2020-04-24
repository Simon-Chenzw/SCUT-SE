/**
 *  @brief:code of 14.13
 *  @author:Simon_Chen
 */

#include <bits/stdc++.h>
using namespace std;
#define print(str) fout << setw(20) << "str" << setw(2) << sizeof(str) << '\n';

int main() {
    ofstream fout("datasize.dat");
    print(char);
    print(unsigned char);
    print(short int);
    print(int);
    print(unsigned int);
    print(long int);
    print(unsigned long int);
    print(float);
    print(double);
    print(long double);
}