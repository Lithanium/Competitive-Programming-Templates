#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int id = 2;

struct Info {
    int max = 0;
    ll sum = 0;
    int lazy_set = -1;
    ll lazy_sum = 0;
    int lc, rc;
};

Info nodes[400005];

void clean(int i, int l, int r) {
    if (!nodes[i].lc) {
        nodes[i].lc = id;
        id ++;
    }
    if (!nodes[i].rc) {
        nodes[i].rc = id;
        id ++;
    }
    ll sz = r - l + 1;
    int leftc = nodes[i].lc;
    int rightc = nodes[i].rc;
    if (nodes[i].lazy_set != -1) {
        nodes[i].max = nodes[i].lazy_set;
        nodes[i].sum = sz * nodes[i].lazy_set;
        if (l != r) {
            nodes[leftc].lazy_set = nodes[i].lazy_set;
            nodes[rightc].lazy_set = nodes[i].lazy_set;
            nodes[leftc].lazy_sum = 0;
            nodes[rightc].lazy_sum = 0;
        }
        nodes[i].lazy_set = -1;
    }
    nodes[i].max += nodes[i].lazy_sum;
    nodes[i].sum += nodes[i].lazy_sum * sz;
    if (l != r) {
        nodes[leftc].lazy_sum += nodes[i].lazy_sum;
        nodes[rightc].lazy_sum += nodes[i].lazy_sum;
    }
    nodes[i].lazy_sum = 0;
}

void upd_set(int i, int l, int r, int ql, int qr, int x) {
    clean(i, l, r);
    if (qr < l or ql > r) return;
    if (ql <= l and qr >= r) {
        nodes[i].lazy_set = x;
        nodes[i].lazy_sum = 0;
        clean(i, l, r);
        return;
    }
    int m = (l + r) / 2;
    int leftc = nodes[i].lc;
    int rightc = nodes[i].rc;
    upd_set(leftc, l, m, ql, qr, x);
    upd_set(rightc, m + 1, r, ql, qr, x);
    nodes[i].max = max(nodes[leftc].max, nodes[rightc].max);
    nodes[i].sum = nodes[leftc].sum + nodes[rightc].sum;
}

void upd_add(int i, int l, int r, int ql, int qr, int x) {
    clean(i, l, r);
    if (qr < l or ql > r) return;
    if (ql <= l and qr >= r) {
        nodes[i].lazy_sum += x;
        clean(i, l, r);
        return;
    }
    int m = (l + r) / 2;
    int leftc = nodes[i].lc;
    int rightc = nodes[i].rc;
    upd_add(leftc, l, m, ql, qr, x);
    upd_add(rightc, m + 1, r, ql, qr, x);
    nodes[i].max = max(nodes[leftc].max, nodes[rightc].max);
    nodes[i].sum = nodes[leftc].sum + nodes[rightc].sum;
}

int query_max(int i, int l, int r, int ql, int qr) {
    clean(i, l, r);
    if (qr < l or ql > r) return -1;
    if (ql <= l and qr >= r) return nodes[i].max;
    int m = (l + r) / 2;
    int leftc = nodes[i].lc;
    int rightc = nodes[i].rc;
    return max(query_max(leftc, l, m, ql, qr), query_max(rightc, m + 1, r, ql, qr));
}

ll query_sum(int i, int l, int r, int ql, int qr) {
    clean(i, l, r);
    if (qr < l or ql > r) return 0;
    if (ql <= l and qr >= r) return nodes[i].sum;
    int m = (l + r) / 2;
    int leftc = nodes[i].lc;
    int rightc = nodes[i].rc;
    return query_sum(leftc, l, m, ql, qr) + query_sum(rightc, m + 1, r, ql, qr);
}

int main() {
    //The Main Code
}