#include <bits/stdc++.h>
using namespace std;

struct Node {
    // max tree
    int def = 0;
    int val = 0;
    bool lazy = 0;
};

Node nodes[2000005];
int dt[500005];

void build(int n, int l, int r) {
    if (l == r) {
        nodes[n].def = dt[l];
        return;
    }
    int mid = (l + r)/2;
    build(2*n, l, mid);
    build(2*n+1, mid+1, r);
    nodes[n].def = max(nodes[2*n].def, nodes[2*n+1].def);
}

void clean(int n, int l, int r) {
    if (nodes[n].lazy) {
        nodes[n].val = nodes[n].def;
        if (l != r) {
            nodes[2*n].lazy = 1;
            nodes[2*n+1].lazy = 1;
        }
        nodes[n].lazy = 0;
    }
}

void reset(int n, int l, int r, int ql, int qr) {
    clean(n, l, r);
    if (r < ql or l > qr) return;
    if (ql <= l and r <= qr) {
        nodes[n].lazy = 1;
        clean(n, l, r);
        return;
    }
    int mid = (l + r)/2;
    reset(2*n, l, mid, ql, qr);
    reset(2*n+1, mid+1, r, ql, qr);
    nodes[n].val = max(nodes[2*n].val, nodes[2*n+1].val);
}

void upd(int n, int l, int r, int p, int x) {
    clean(n, l, r);
    if (p < l or p > r) return;
    if (l == r) {
        nodes[n].val = x;
        return;
    }
    int mid = (l + r)/2;
    upd(2*n, l, mid, p, x);
    upd(2*n+1, mid+1, r, p, x);
    nodes[n].val = max(nodes[2*n].val, nodes[2*n+1].val);
}

int query(int n, int l, int r, int p) {
    clean(n, l, r);
    if (p < l or p > r) return 0;
    if (l == r) return nodes[n].val;
    int mid = (l + r)/2;
    return max(query(2*n, l, mid, p), query(2*n+1, mid+1, r, p));
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> dt[i];
    build(1, 1, n);
    int q;
    cin >> q;
    while (q --) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 0) reset(1, 1, n, b, c);
        else upd(1, 1, n, b, c);
        for (int i = 1; i <= n; i ++) cout << query(1, 1, n, i) << " ";
        cout << "\n\n";
    }
}