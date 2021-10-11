#define TRACE
#include "tracer.hpp"
#include <bits/stdc++.h>
using namespace std;

int factorial(int);

int factorial(int n) {
    tr_begin(n);
    const int ans = n > 1 ? n*factorial(n-1) : 1;
    return tr_end(ans,n); }

inline istream& skip_endl(istream &is) {
    return is.ignore(numeric_limits<streamsize>::max(),'\n'); }

int main() {
    int n;
    cin >> n >> skip_endl, assert(n >= 0), cout << factorial(n);
 	return 0; }
