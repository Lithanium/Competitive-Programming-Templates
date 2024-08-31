#pragma GCC optimize("O3")
 
#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
struct Node {
    int sum = 0, min1 = 0, min2 = 1e9, num = 1;
    int l, r;
 
    Node *lc = nullptr, *rc = nullptr;
    Node (int L, int R) {l = L, r = R;}
 
    void push() {
        if (l == r) return;
        if (lc -> min1 < min1 and min1 < lc -> min2) {
            lc -> sum += (min1 - lc -> min1) * lc -> num;
            lc -> min1 = min1;
        }
        if (rc -> min1 < min1 and min1 < rc -> min2) {
            rc -> sum += (min1 - rc -> min1) * rc -> num;
            rc -> min1 = min1;
        }
    }
    void merge() {
        sum = lc -> sum + rc -> sum;
        if (lc -> min1 == rc -> min1) {
            min1 = lc -> min1;
            num = lc -> num + rc -> num;
            min2 = min(lc -> min2, rc -> min2);
        } else {
            if (lc -> min1 < rc -> min1) {
                min1 = lc -> min1;
                num = lc -> num;
                min2 = min(lc -> min2, rc -> min1);
            } else {
                min1 = rc -> min1;
                num = rc -> num;
                min2 = min(lc -> min1, rc -> min2);
            }
        }
    }
    void build() {
        if (l == r) return;
        int mid = (l+r)/2;
        lc = new Node(l, mid), rc = new Node(mid+1, r);
        lc -> build(), rc -> build();
        merge();
    }
    void upd(int ql, int qr, int x) {
        push();
        if (l > qr or r < ql or x <= min1) return;
        if (ql <= l and r <= qr and min1 < x and x < min2) {
            sum += (x - min1) * num;
            min1 = x;
            return;
        }
        lc -> upd(ql, qr, x);
        rc -> upd(ql, qr, x);
        merge();
    }
    int query(int ql, int qr) {
        push();
        if (l > qr or r < ql) return 0;
        if (ql <= l and r <= qr) return sum;
        return lc -> query(ql, qr) + rc -> query(ql, qr);
    }
};
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    Node *segtree = new Node(1, 500000);
    segtree -> build();
    int q;
    cin >> q;
    while (q --) {
        char a;
        int b, c;
        cin >> a >> b >> c;
        if (a == 'Q') {
            cout << segtree -> query(b, c) << "\n";
        } else {
            int d;
            cin >> d;
            segtree -> upd(b, c, d);
        }
    }
}