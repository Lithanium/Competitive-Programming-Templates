#include <bits/stdc++.h>
using namespace std;

struct Node {
    int l, r;
    long long sum = 0;
    long long lazy = 0;

    Node *lc = nullptr, *rc = nullptr;

    Node(int left, int right) {
        l = left, r = right;
    }

    void create() {
        if (!lc and l != r) {
            int mid = (l + r)/2;
            lc = new Node(l, mid);
            rc = new Node(mid+1, r);
        }
    }

    void push() {
        sum += lazy * (r - l + 1);
        if (l != r) {
            create();
            lc -> lazy += lazy;
            rc -> lazy += lazy;
        }
        lazy = 0;
    }

    long long query(int ql, int qr) {
        create();
        push();
        if (ql > r or qr < l) return 0ll;
        if (ql <= l and r <= qr) return sum;
        return lc -> query(ql, qr) + rc -> query(ql, qr);
    }

    void update(int ql, int qr, int x) {
        create();
        push();
        if (ql > r or qr < l) return;
        if (ql <= l and r <= qr) {
            lazy += x;
            push();
            return;
        }
        lc -> update(ql, qr, x);
        rc -> update(ql, qr, x);
        sum = lc -> sum + rc -> sum;
    }
};

int main() {
    Node *st = new Node(1, 1e9);
    int n, q;
    cin >> n >> q;
    while (n --) {
        int a, b, c;
        cin >> a >> b >> c;
        b --;
        st -> update(a, b, c);
    }
    while (q --) {
        int a, b;
        cin >> a >> b;
        b --;
        cout << st -> query(a, b) << "\n";
    }
}