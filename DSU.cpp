#include <bits/stdc++.h>
using namespace std;

int dsu[100005];

int dsuFind(int x) {
    return (dsu[x] == x) ? x : dsu[x] = dsuFind(dsu[x]);
}

void dsuMerge(int x, int y) {
    dsu[find(x)] = find(y);
}

int main() {
    for (int i = 1; i <= 100000; i ++) dsu[i] = i;
}