#include <bits/stdc++.h>
using namespace std;

int mod = 31337;
#define Fsolve 8

vector<vector<int>> F = {{3, 0, 1, 1, 0, 1, 0, 0}};
vector<vector<int>> T =
{
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0}
};

vector<vector<int>> multiply(const vector<vector<int>> &a, const vector<vector<int>> &b) {
    vector<vector<int>> c (a.size(), vector<int> (b[0].size(), 0));
    for (int i = 0; i < a.size(); i ++) {
        for (int j = 0; j < b[0].size(); j ++) {
            for (int k = 0; k < a[0].size(); k ++) {
                c[i][j] += a[i][k]*b[k][j];
                c[i][j] %= mod;
            }
        }
    }
    return c;
}

vector<vector<int>> power(const vector<vector<int>> &a, long long p) {
    if (p == 1) return a;
    vector<vector<int>> res = power(a, p/2);
    if (p%2 == 0) return multiply(res, res);
    else return multiply(a, multiply(res, res));
}

signed main() {
    long long n;
    cin >> n;
    if (n > Fsolve) {
        vector<vector<int>> res = multiply(F, power(T, n-Fsolve));
        cout << res[0][0];
    } else {
        cout << F[0][Fsolve-n];
    }
}