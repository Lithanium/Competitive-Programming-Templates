
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define int long long
 
struct Node {
    ll sum = 0;
    int cd = 0;
    ll ft = 0;
    int lc = 0;
};
 
Node nodes[8050005];
int upto = 1;
int N, L;
 
void clean(int n, int l, int r) {
    // update this current node
    // adds 1, 2, 3, ..., R-L+1
    // (R-L+2)*(R-L+1)/2
    nodes[n].sum += (ll)(r-l+2)*(r-l+1)*nodes[n].cd/2 + (ll)(r-l+1)*nodes[n].ft;
    if (l != r) {
        if (nodes[n].lc == 0) {
            nodes[n].lc = ++upto;
            upto ++;
        }
        int mid = (l+r)/2;
        nodes[nodes[n].lc].cd += nodes[n].cd;
        nodes[nodes[n].lc].ft += nodes[n].ft;
        nodes[nodes[n].lc+1].ft += (ll)(mid - l + 1)*nodes[n].cd + (ll)nodes[n].ft;
        nodes[nodes[n].lc+1].cd += nodes[n].cd;
    }
    nodes[n].ft = nodes[n].cd = 0;
}
 
void upd(int n, int l, int r, int ql, int qr, int v, ll ft) {
    if (l > qr or r < ql) return;
    clean(n, l, r);
    if (ql <= l and r <= qr) {
        nodes[n].ft = (ll)(l - ql)*(v) + (ll)ft;
        nodes[n].cd = v;
        clean(n, l, r);
        return;
    }
    int mid = (l+r)/2;
    upd(nodes[n].lc, l, mid, ql, qr, v, ft);
    upd(nodes[n].lc+1, mid+1, r, ql, qr, v, ft);
    nodes[n].sum = nodes[nodes[n].lc].sum + nodes[nodes[n].lc+1].sum;
}
 
ll query(int n, int l, int r, int ql, int qr) {
    if (l > qr or r < ql) return 0;
    clean(n, l, r);
    if (ql <= l and r <= qr) return nodes[n].sum;
    int mid = (l+r)/2;
    return query(nodes[n].lc, l, mid, ql, qr) + query(nodes[n].lc+1, mid+1, r, ql, qr);
}

// void build(int n, int l, int r) {
//     clean(n, l, r);
//     if (l == r) {
//         nodes[n].sum = dt[l];
//         return;
//     }
//     int mid = (l+r)/2;
//     build(nodes[n].lc, l, mid);
//     build(nodes[n].rc, mid+1, r);
//     nodes[n].sum = nodes[nodes[n].lc].sum + nodes[nodes[n].rc].sum;
// }

int32_t main() {
    int N, Q;
    cin >> N >> Q;
    for (int i = 1; i <= N; i ++) {
        cin >> dt[i];
        upd(1, 1, N, i, i, dt[i]);
    }
    // build(1, 1, N);
    while (Q --) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) upd(1, 1, N, b, c, 1);
        else cout << query(1, 1, N, b, c) << "\n";
    }
}