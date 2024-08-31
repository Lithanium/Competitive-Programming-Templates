#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
struct Line {
    int a = 0, b = 1e18;
    int value(int x) {
        return x*a+b;
    }
};
 
struct LiChao {
    struct Node {
        Line line{};
        Node *lc, *rc;
        Node() {
            lc = rc = nullptr;
        }
    };
 
    int L, R;
    Node *root;
    LiChao(int a, int b) {
        L = a, R = b;
        root = new Node();
    }
 
    void insert(Node *n, int l, int r, Line line) {
        int mid = (l + r)/2;
        bool c1 = (line.value(mid) < n->line.value(mid));
        bool c2 = (line.value(l) < n->line.value(l));
        if (c1) swap(line, n->line);
        if (l == r) return;
        if (c1 != c2) {
            if (!n->lc) n->lc = new Node();
            insert(n->lc, l, mid, line);
        } else {
            if (!n->rc) n->rc = new Node();
            insert(n->rc, mid+1, r, line);
        }
    }
 
    void insert(Line line) {
        insert(root, L, R, line);
    }
 
    int query(Node *n, int l, int r, int x) {
        if (!n) return 1e18;
        if (l == r) return n->line.value(x);
        int mid = (l+r)/2;
        if (x <= mid) {
            return min(n->line.value(x), query(n->lc, l, mid, x));
        } else {
            return min(n->line.value(x), query(n -> rc, mid+1, r, x));
        }
    }
 
    int query(int x) {
        return query(root, L, R, x);
    }
};
 
int dt[1000005];
int dp[1000005];
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, c;
    cin >> n >> c;
    LiChao *lichao = new LiChao(0, 1e9);
    for (int i = 1; i <= n; i ++) {
        cin >> dt[i];
        dp[i] = dt[i]*dt[i] + c;
        lichao -> insert({-2 * dt[i], dt[i] * dt[i] + dp[i-1]});
        int res = lichao -> query(dt[i]);
        if (res < 1e18) dp[i] += res;
    }
    cout << dp[n];
}