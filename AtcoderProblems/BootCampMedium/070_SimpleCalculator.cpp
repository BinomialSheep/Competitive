#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
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
  /* input */
  ll x, y;
  cin >> x >> y;

  if (abs(x) == abs(y)) {
    cout << 1 << endl;
    return 0;
  }

  if (x == 0 && y < 0) {
    cout << x - y + 1 << endl;
    return 0;
  }
  if (x > 0 && y == 0) {
    cout << x - y + 1 << endl;
    return 0;
  }
  // 符号が違う場合
  if ((y < 0 && 0 < x) || (x < 0 && 0 < y)) {
    // 反転してからプラスか、プラスしてから反転
    cout << abs(abs(y) - abs(x)) + 1 << endl;
    return 0;
  }

  if (x < y && y <= 0) {
    cout << y - x << endl;
    return 0;
  }
  if (0 <= x && x < y) {
    cout << y - x << endl;
    return 0;
  }
  if (0 <= y && y < x) {
    // 反転して、-yまで押して、再反転
    cout << x - y + 2 << endl;
    return 0;
  }
  if (y < x && x <= 0) {
    cout << x - y + 2 << endl;
    return 0;
  }

  assert(false);

  /* solve */

  /* output */

  return 0;
}