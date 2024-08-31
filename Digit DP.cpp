#include <bits/stdc++.h>
using namespace std;

#define int long long

int dp[20][15][2][2];
int digits[20];

int solve(int pos, int curr, bool limit, bool started) {
    if (pos == 1) return started;
    if (dp[pos][curr][started][limit] != -1) return dp[pos][curr][started][limit];
    int total = 0, mx = 9;
    if (limit) mx = min(mx, digits[pos-1]);
    if (!started) mx = 9;
    for (int i = 0; i <= mx; i ++) if (i != curr or !started) {
        int t = solve(pos-1, i, (limit and (i == digits[pos-1])), (started or (i != 0)));
        total += t;
    }
    return dp[pos][curr][started][limit] = total;
}

int process(int a) {
    if (a < 0) return 0;
    if (a == 0) return 1;
    memset(dp, -1, sizeof(dp));
    int ptr = 1, total = 0;
    while (a > 0) {
        digits[ptr++] = a%10;
        a /= 10;
    }
    for (int i = 0; i <= digits[ptr-1]; i ++) total += solve(ptr-1, i, (i == digits[ptr-1]), !(i == 0));
    return total+1;
}

int32_t main() {
    int a, b;
    cin >> a >> b;
    cout << process(b) - process(a-1);
}