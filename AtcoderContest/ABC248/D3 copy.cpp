#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
// 浮動小数点の誤差を考慮した等式

int main() {
  int n;
  cin >> n;
  vector<vector<int>> idx(n + 1);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    idx[a].push_back(i);
  }
  int q;
  cin >> q;
  while (q--) {
    int l, r, x;
    cin >> l >> r >> x;
    cout << lower_bound(idx[x].begin(), idx[x].end(), r) -
                lower_bound(idx[x].begin(), idx[x].end(), l - 1)
         << endl;
  }
}