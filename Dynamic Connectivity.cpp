#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
 
#include <bits/stdc++.h>
using namespace std;
 
int dsu[100005];
int sz[100005];
vector<pair<int, int>> nodes[800005];
bool queries[200005];
int curr;
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
 
void upd(int n, int l, int r, int ql, int qr, int e1, int e2) {
    if (l > qr or r < ql) return;
    if (ql <= l and r <= qr) {
        nodes[n].push_back({e1, e2});
        return;
    }
    int mid = (l+r)/2;
    upd(2*n, l, mid, ql, qr, e1, e2);
    upd(2*n+1, mid+1, r, ql, qr, e1, e2);
}
 
void dfs(int n, int l, int r) {
    int saved = curr;
    for (auto [a, b]:nodes[n]) {
        if (find(a) != find(b)) curr --;
        merge(a, b);
    }
    if (l == r) {
        // cout << "at time " << l << " there are " << curr << " connected components\n";
        if (queries[l]) cout << curr << "\n";
    } else {
        int mid = (l+r)/2;
        dfs(2*n, l, mid);
        dfs(2*n+1, mid+1, r);
    }
    for (int i = 0; i < nodes[n].size(); i ++) rollback();
    curr = saved;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) dsu[i] = i, sz[i] = 1;
    map<pair<int, int>, int> insertions;
    for (int i = 1; i <= q; i ++) {
        char c;
        cin >> c;
        if (c == '?') queries[i] = 1;
        else {
            int a, b;
            cin >> a >> b;
            if (a > b) swap(a, b);
            if (c == '+') insertions[{a, b}] = i;
            else {
                upd(1, 1, q+1, insertions[{a, b}], i, a, b);
                insertions.erase({a, b});
            }
        }
    }
    for (pair<pair<int, int>, int> extra:insertions) upd(1, 1, q+1, extra.second, q+1, extra.first.first, extra.first.second);
    curr = n;
    dfs(1, 1, q+1);
}