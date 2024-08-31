#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll dist[100005];
int status[100005]; //0: Done, 1: Processing, 2: Unseen
vector<pair<int, int>> adj[100005];

int main() {
    int n, start;
    //Input...
    for (int i = 1; i <= n; i ++) status[i] = 2;
    memset(dist, 0x3f, sizeof(dist));
    dist[start] = 0;
    deque<int> todo;
    todo.push_back(start);
    while (!todo.empty()) {
        int temp = todo.front();
        todo.pop_front();
        status[temp] = 0;
        for (auto [a, b]:adj[temp]) {
            if (dist[a] > dist[temp] + b) {
                dist[a] = dist[temp] + b;
                if (status[a] == 2) {
                    status[a] = 1;
                    todo.push_back(a);
                } else if (status[a] == 0) {
                    status[a] = 1;
                    todo.push_front(a);
                }
            }
        }
    }
}