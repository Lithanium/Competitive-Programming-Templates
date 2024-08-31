#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll sz = 1 << 18;

struct CaterpillowTree {
    int freq[sz];
    ll tree[(sz - 1) / 63];
    
    CaterpillowTree() { 
        memset(freq, 0, sizeof(freq));
        memset(tree, 0, sizeof(tree)); 
    }
    
    void toggle(int i) {
        int j = (i >> 6) + ((sz >> 6) - 1) / 63;
        tree[j] ^= 1ll << (i & 63);
        do {
            i >>= 6;
            int p = (j - 1) >> 6;
            if ((1ll & (tree[p] >> (i & 63))) ^ (!!tree[j])) tree[p] ^= 1ll << (i & 63);
            j = p;
        } while (j);
    }

    int find_min() {
        ll r = sz, ans = 0;
        int i = 0;
        while (r != 1) {
            r >>= 6;
            int j = __builtin_ctzl(tree[i]);
            ans += j * r;
            i = (i << 6) + 1 + j;
        }
        return ans;
    }
    
    void insert(int x) { if (++freq[x] == 1) toggle(x); }
    void erase(int x) { if (--freq[x] == 0) toggle(x); }
};