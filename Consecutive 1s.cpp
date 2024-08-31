#include <bits/stdc++.h>
using namespace std;

struct Node {
    int sz = 0;
    int l = 0, r = 0;
    int best = 0;
};

Node nodes[400005];

bool dt[100005];

void merge(int n, int l, int r) {
    if (l == r) return;
    nodes[n].best = max({nodes[2*n].r + nodes[2*n+1].l, nodes[2*n].best, nodes[2*n+1].best});
    if (nodes[2*n].l == nodes[2*n].sz) {
        nodes[n].l = nodes[2*n].l + nodes[2*n+1].l;
    } else {
        nodes[n].l = nodes[2*n].l;
    }
    if (nodes[2*n+1].r == nodes[2*n+1].sz) {
        nodes[n].r = nodes[2*n+1].r + nodes[2*n].r;
    } else {
        nodes[n].r = nodes[2*n+1].r;
    }
    return;
}

void build(int n, int l, int r) {
    nodes[n].sz = (r - l + 1);
    if (l == r) {
        if (dt[l]) {
            nodes[n].l = nodes[n].r = nodes[n].best = 1;
        } else {
            nodes[n].l = nodes[n].r = nodes[n].best = 0;
        }
        return;
    }
    int mid = (l + r)/2;
    build(2*n, l, mid);
    build(2*n+1, mid+1, r);
    merge(n, l, r);
    return;
}

void upd(int n, int l, int r, int p, bool x) {
    if (l > p or p > r) return;
    if (l == r) {
        if (x) {
            nodes[n].l = nodes[n].r = nodes[n].best = 1;
        } else {
            nodes[n].l = nodes[n].r = nodes[n].best = 0;
        }
        return;
    }
    int mid = (l + r)/2;
    upd(2*n, l, mid, p, x);
    upd(2*n+1, mid+1, r, p, x);
    merge(n, l, r);
    return;
}