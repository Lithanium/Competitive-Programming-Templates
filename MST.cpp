#include <bits/stdc++.h>
using namespace std;

vector<tuple<int, int, int>> adj; //Weight, Source, Destination

int dsu[100005];

int dsuFind(int x) {
    return (dsu[x] == x) ? x : dsu[x] = dsuFind(dsu[x]);
}

void dsuMerge(int x, int y) {
    dsu[find(x)] = find(y);
}

int main() {
    int n, m, cost = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) dsu[i] = i;
    while (m --) {
        int a, b, c; //A, B, Weight
        cin >> a >> b >> c;
        adj.push_back({c, a, b});
    }
    sort(adj.begin(), adj.end());
    for (auto [a, b, c]:adj) {
        if (dsuFind(b) != dsuFind(c)) {
            cost += a;
            dsuMerge(b, c);
        }
    }
}