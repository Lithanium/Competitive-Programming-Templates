#include <bits/stdc++.h>
using namespace std;

int A[205][205], B[205][205];
int ans[205][205];

int main() {
    int a, b, c, d;
    cin >> a >> b;
    for (int i = 1; i <= a; i ++) for (int j = 1; j <= b; j ++) cin >> A[i][j];
    cin >> c >> d;
    for (int i = 1; i <= c; i ++) for (int j = 1; j <= d; j ++) cin >> B[i][j];
    for (int i = 1; i <= a; i ++) {
        for (int j = 1; j <= d; j ++) {
            for (int k = 1; k <= c; k ++) {
                ans[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    for (int i = 1; i <= a; i ++) {
        for (int j = 1; j <= d; j ++) cout << ans[i][j] << " ";
        cout << "\n";
    }
}