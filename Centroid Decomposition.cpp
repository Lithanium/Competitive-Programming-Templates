#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> adj[200005];
int sz[200005];
bool dead[200005];
int N, K;
int ans = 1e9;
gp_hash_table<int, int> temp;

int dfs(int n, int p) {
    sz[n] = 1;
    for (auto[i, j]:adj[n]) if (p != i and !dead[i]) sz[n] += dfs(i, n);
    return sz[n];
}

int centroid(int n, int p, int T) {
    for (auto [i, j]:adj[n]) if (p != i and !dead[i]) {
        if (sz[i]*2 > T) return centroid(i, n, T);
    }
    return n;
}

void _dfs(int n, int p, int depth, int d) {
    if (depth > K) return;
    if (temp[depth] == 0) {
        temp[depth] = d;
    } else {
        temp[depth] = min(temp[depth], d);
    }
    for (auto [i, j]:adj[n]) if (i != p and !dead[i]) {
        _dfs(i, n, depth + j, d + 1);
    }
}

void clear(int n) {
    sz[n] = 0;
    for (auto [i, j]:adj[n]) if (sz[n] != 0 and !dead[i]) clear(i);
}

void solve(int n) {
    unordered_map<int, int> freq;
    dfs(n, -1);
    int c = centroid(n, -1, sz[n]);
    //cout << "centroid is: " << c << "\n";
    dead[c] = 1;
    n = c;
    for (auto [i, j]:adj[n]) if (!dead[i]) {
        temp.clear();
        //cout << "\ncurrently at: " << i << "\n";
        _dfs(i, -1, j, 1);
        for (auto [k, v]:temp) {
            if (freq[K-k] > 0) {
                ans = min(ans, freq[K-k] + v);
            }
            if (k == K) ans = min(ans, v);
        }
        for (auto [k, v]:temp) {
            if (freq[k] == 0) freq[k] = v;
            else freq[k] = min(freq[k], v);
            //cout << "Key: " << k << " " << v << "\n";
        }
    }
    if (freq[K] > 0) ans = min(ans, freq[K]);
    for (auto [i, j]:adj[n]) if (!dead[i]) solve(i);
}

int best_path(int _n, int _k, int _h[][2], int _l[]) {
    N = _n, K = _k;
    for (int i = 0; i < N-1; i ++) {
        adj[_h[i][0]].push_back({_h[i][1], _l[i]});
        adj[_h[i][1]].push_back({_h[i][0], _l[i]});
    }
    solve(0);
    if (ans == 1e9) ans = -1;
    return ans;
}