#include <bits/stdc++.h>
using namespace std;

vector<tuple<int, int, int>> edge; //DIRECTED GRAPH A ->(C)-> B
int dist[100005];

int main() {
    memset(dist, 0x3f, sizeof(dist));
    int n, m;
    bool change;
    cin >> n >> m;
    for (int i = 0; i < m; i ++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge.push_back({a, b, c});
    }
    dist[1] = 0;
    for (int i = 1; i <= n; i ++) {
        change = 0
        for (auto[a, b, c]:edge) if (dist[a] < 1e9) {
            if (dist[a] + c < dist[b]) {
                dist[b] = max(-1e9, dist[a] + c);
                change = 1;
            }
        }
        if (!change) break;
    }
    if (change) //Neg Cycle, kill program
}