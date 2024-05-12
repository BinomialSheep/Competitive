#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  ll n, a, b, p, q, r, s;
  cin >> n >> a >> b >> p >> q >> r >> s;

  // P-Q, R-Sのことだけ考える
  vector<vector<char>> ans(q - p + 1, vector<char>(s - r + 1, '.'));

  ll rangeLeft = max(1 - a, 1 - b);
  if (a + rangeLeft <= p) rangeLeft = p - a;
  if (b + rangeLeft <= r) rangeLeft = r - b;
  ll rangeRight = min(n - a, n - b);
  if (a + rangeRight >= q) rangeRight = q - a;
  if (b + rangeRight >= s) rangeRight = s - b;

  // cout << rangeLeft << rangeRight << endl;

  for (ll k = rangeLeft; k <= rangeRight; k++) {
    ans[a - p + k][b - r + k] = '#';
  }

  rangeLeft = max(1 - a, b - n);
  rangeRight = min(n - a, b - 1);
  if (a + rangeLeft <= p) rangeLeft = p - a;
  if (b - rangeRight <= r) rangeRight = b - r;
  if (a + rangeRight >= q) rangeRight = q - a;
  if (b - rangeLeft >= s) rangeLeft = b - s;

  // cout << rangeLeft << rangeRight << endl;

  for (ll k = rangeLeft; k <= rangeRight; k++) {
    ans[a - p + k][b - r - k] = '#';
  }

  for (auto vec : ans) {
    for (auto v : vec) cout << v;
    cout << endl;
  }

  return 0;
}