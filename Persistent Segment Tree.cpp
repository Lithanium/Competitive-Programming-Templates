#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
struct Node {
    Node *lc, *rc;
    int val; // Min
    Node (int num) {
        val = num;
        lc = rc = nullptr;
    }
    Node (Node *l, Node *r) {
        lc = l, rc = r;
        val = min(lc -> val, rc -> val);
    }
};
 
Node* build(int l, int r) {
    if(l == r) {
        return new Node(1048576);
    }
    int mid = (l+r)/2;
    return new Node(build(l, mid), build(mid+1, r));
}
int query(Node *n, int l, int r, int ql, int qr) {
    if (l > qr or r < ql) return 1048576;
    if (ql <= l and r <= qr) return n -> val;
    int mid = (l+r)/2;
    return min(query(n -> lc, l, mid, ql, qr), query(n -> rc, mid+1, r, ql, qr));
}
Node* upd(Node *n, int l, int r, int p, int x) {
    if (l == r) return new Node(x);
    int mid = (l+r)/2;
    if (p <= mid) {
        return new Node(upd(n -> lc, l, mid, p, x), n -> rc);
    } else {
        return new Node(n -> lc, upd(n -> rc, mid+1, r, p, x));
    }
}
 
Node *roots[100005];
 
signed main() {
    roots[1] = build(0, 262144);
    int upto = 2;
    int q;
    int sum = 0;
    cin >> q;
    while (q --) {
        char a;
        int b, c, d;
        cin >> a >> b >> c >> d;
        if (a == 'q') {
            int t = query(roots[b - sum], 0, 262144, c, d);
            sum += t;
            cout << t << "\n";
        } else {
            roots[upto] = upd(roots[b - sum], 0, 262144, c, d);
            upto ++;
        }
    }
}