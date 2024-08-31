#include <bits/stdc++.h>
using namespace std;

double temperature = 1e7, a = 0.99;
//let temperature be worst possible state
 
int check() {
    // return score
}

double P(double Old, double New) {
    if (New < Old) return 1.0;
    return exp((Old - New)/temperature);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    srand(time(NULL));
    auto start = clock();

    while ((double)(clock()-start)/CLOCKS_PER_SEC < 0.2) {
        temperature *= a;
    }
}