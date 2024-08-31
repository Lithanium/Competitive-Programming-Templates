#include <bits/stdc++.h>
using namespace std;

int dsu[500005];
int sz[500005];

stack<pair<int, int>> pdsu, psz;
// storing the history

int find(int n) {
    if (dsu[n] == n) return n;
    return find(dsu[n]);
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (sz[a] < sz[b]) swap(a, b);
    pdsu.push({b, dsu[b]});
    psz.push({a, sz[a]});
    if (a != b) {
        dsu[b] = a;
        sz[a] += sz[b];
    }
}

void rollback() {
    dsu[pdsu.top().first] = pdsu.top().second;
    sz[psz.top().first] = psz.top().second;
    pdsu.pop();
    psz.pop();
}