#include <bits/stdc++.h>
using namespace std;

#define int long long

int P = 911382323;
int mod = 972663749;
int hsh[700005];
int expon[700005];

int calc(int a, int b) {
    return (hsh[b] - (hsh[a-1] * expon[b-a+1])%mod + mod)%mod;
}

signed main() {
    string in, s = ".";
    cin >> in;
    s = in;
    hsh[0] = s[0];
    expon[0] = 1;
    for (int i = 1; i < s.size(); i ++) {
        hsh[i] = (hsh[i-1] * P + s[i])%mod;
        expon[i] = (expon[i-1] * P)%mod;
    }
    // 0-indexed
}