#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

int main() {
  // 正四面体数のリストの作成
  int LIM = 1e6;
  vi tetraNumList;
  for (int i = 1;; i++) {
    int num = i * (i + 1) * (i + 2) / 6;
    if (num > LIM) break;
    tetraNumList.push_back(num);
  }

  // 個数確認したら180個しかなかった
  // cout << tetraNumList.size() << endl;

  // 何個の整数で作れるかdp
  // dp1[i] 整数iを作るための最小の数
  vi dp1(1e6 + 1, INFTY);
  dp1[0] = 0;
  for (int t : tetraNumList) {
    rep(i, 1e6 + 1) {
      if (i + t > 1e6) break;
      chmin(dp1[i + t], dp1[i] + 1);
    }
  }
  // 何個の奇数の整数で作れるかdp
  vi dp2(1e6 + 1, INFTY);
  dp2[0] = 0;
  for (int t : tetraNumList) {
    if (t % 2 == 0) continue;
    rep(i, 1e6 + 1) {
      if (i + t > 1e6) break;
      chmin(dp2[i + t], dp2[i] + 1);
    }
  }

  while (true) {
    /* input */
    int n;
    cin >> n;
    if (n == 0) break;

    cout << dp1[n] << " " << dp2[n] << endl;

    /* solve */

    /* output */
  }

  return 0;
}