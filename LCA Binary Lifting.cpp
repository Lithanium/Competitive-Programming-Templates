#include <bits/stdc++.h>
using namespace std;
 
int g[25][100005], depth[100005];
bool seen[100005];
vector<int> adj[100005];
 
void dfs (int n, int d) {
    depth[n] = d;
    seen[n] = 1;
    for (int i:adj[n]) {
        if (seen[i] == 0) {
            g[0][i] = n;
            dfs(i, d+1);
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i ++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 1);
    g[0][1] = 1;
    for (int i = 1; i < 25; i ++) {
        for (int j = 1; j <= n; j ++) {
            g[i][j] = g[i-1][g[i-1][j]];
        }
    }
    while (q --) {
        int a, b;
        cin >> a >> b;
        if (depth[a] < depth[b]) {
            swap(a, b);
        }
        for (int i = 24; i >= 0; i --) {
            if (depth[g[i][a]] >= depth[b]) {
                a = g[i][a];
            }
        }
        if (a == b) {
            cout << a << "\n";
            continue;
        }
        for (int i = 24; i >= 0; i --) {
            if (g[i][a] != g[i][b]) {
                a = g[i][a];
                b = g[i][b];
            }
        }
        cout << g[0][a] << "\n";
    }
}