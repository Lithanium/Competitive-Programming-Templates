#include <bits/stdc++.h>
using namespace std;

int K = 400;

struct Query {
    int l, r, id;
    bool operator < (Query t){
        if (l/K != t.l/K) return l < t.l;
        if ((l/K)%2) return r < t.r;
        else return r > t.r;
    }
};

void upd(int p, int val) {
    // Updates neighbour
}

int main() {
    vector<Query> queries;
    // Fill in queries
    int l = 1, r = 0;
    for (Query q:queries) {
        for (int i = l; i < q.l; i ++) upd(p, 1);
        for (int i = q.l; i < l; i ++) upd(p, -1);
        for (int i = r+1; i <= q.l; i ++) upd(p, 1);
        for (int i = q.l+1; i <= r; i ++) upd(p, -1);
        l = q.l, r = q.r;
        ans[q.id] = some_value;
    }
}