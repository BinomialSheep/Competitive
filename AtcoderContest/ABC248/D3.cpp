#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
// 浮動小数点の誤差を考慮した等式

int main() {
  /* input */
  int N;
  cin >> N;

  /* solve */
  vector<vector<int>> vec(N + 1);
  // unordered_map<int, vector<int>> myMap;
  int A;
  rep(i, N) {
    scanf("%d", &A);
    vec[A].push_back(i + 1);
  }

  int Q;
  cin >> Q;

  int L, R, X;
  vector<int> x;
  vector<int>::iterator l;
  vector<int>::iterator r;
  rep(i, Q) {
    scanf("%d %d %d", &L, &R, &X);
    x = vec[X];
    // l = lower_bound(x.begin(), x.end(), L);
    // // if (l == x.end()) {
    // //   printf("0\n");
    // // } else {
    // r = lower_bound(x.begin(), x.end(), R + 1);
    // int dist = r - l;
    // // printf("%d\n", distance(l, r));
    // // printf("%d\n", dist);
    // cout << dist << endl;
    //}
    l = lower_bound(x.begin(), x.end(), L);
    r = lower_bound(x.begin(), x.end(), R + 1);
    cout << r - l << endl;
  }
  // cout << flush;

  /* output */

  return 0;
}