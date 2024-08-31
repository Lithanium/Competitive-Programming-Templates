#include <bits/stdc++.h>
using namespace std;
vector<int> adj[100005];
vector<int> edge;
vector<int> level;
int first[100005], n, q, sz;
bool vis[100005];
pair<int, int> segtree[4000005]; //Value, index

pair<int, int> query(int n, int low, int high, int start, int end) {
    if (end >= high && start <= low) {
        return segtree[n];
    } else if (start > high || end < low) {
        return {10e6, 10e6};
    }
    int mid = (high + low)/2;
    return min(query(2*n, low, mid, start, end), query(2*n+1, mid + 1, high, start, end));
}

void setNode(int n, int p, int x, int start, int end) {
    if (p < start || p > end) {
        return;
    } else if (start == end) {
        segtree[n] = {x, p};
        return;
    }
    int mid = (start + end)/2;
    setNode(2*n, p, x, start, mid);
    setNode(2*n+1, p, x, mid+1, end);
    segtree[n] = min(segtree[2*n], segtree[2*n+1]);
}

void dfs(int n, int d) {
    edge.push_back(n);
    level.push_back(d);
    vis[n] = 1;
    for (int i:adj[n]) {
        if (vis[i] == 0) {
            dfs(i, d+1);
            edge.push_back(n);
            level.push_back(d);
        }
    }
}

int lca(int a, int b) {
    int small = min(first[a], first[b]), large = max(first[a], first[b]);
    pair<int, int> temp = query(1, 0, sz, small, large);
    return edge[temp.second];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i < n; i ++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 1);
    for (int i = 0; i < 100005; i ++) {
        first[i] = -1;
    }
    for (int i = 0; i < edge.size(); i ++) {
        if (first[edge[i]] == -1) {
            first[edge[i]] = i;
        }
    }
    edge.erase(edge.end()-1);
    level.erase(level.end()-1);
    sz = edge.size();
    for (int i = 0; i < level.size(); i ++) {
        setNode(1, i, level[i], 0, sz);
    }
    while (q --) {
        int x, y;
        cin >> x >> y;
        cout << lca(x, y) << "\n";
    }
}