#include <bits/stdc++.h>
using namespace std;

int nodes[400005];
int N;
vector<tuple<int, int, int>> walknodes;

int upd(int n, int l, int r, int p, int x) {
    if (l == r) {
        nodes[n] += x;
        return;
    }
    int mid = (l+r)/2;
    if (p <= mid) upd(2*n, l, mid, p, x);
    else upd(2*n+1, mid+1, r, p, x);
    nodes[n] = max(nodes[2*n], nodes[2*n+1]);
}

void walkpush(int n, int l, int r, int ql, int qr) {
    if (l > qr or r < ql) return;
    if (ql <= l and r <= qr) {
        walknodes.push_back({n, l, r});
        return;
    }
    int mid = (l+r)/2;
    walkpush(2*n, l, mid, ql, qr);
    walkpush(2*n+1, mid+1, r, ql, qr);
}

int walkhelp(int n, int l, int r, int val) {
    if (l == r) return l;
    int mid = (l+r)/2;
    if (nodes[2*n] >= val) return walkhelp(2*n, l, mid, val);
    else return walkhelp(2*n+1, mid+1, r, val);
}

int walk(int ql, int qr, int val) {
    walknodes.clear();
    walkpush(1, 1, N, ql, qr);
    for (auto [n, l, r]:walknodes) {
        if (nodes[n] >= val) return walkhelp(n, l, r, val);
    }
}