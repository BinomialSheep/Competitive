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
  int N;
  cin >> N;
  vector<int> b(N);
  rep(i, N) cin >> b[i];

  /* solve */
  deque<int> q;

  while (!b.empty()) {
    // 最後に一緒な位置を求める
    int idx = 0;
    for (int i = (int)b.size() - 1; i >= 0; i--) {
      if (b[i] == i + 1) {
        idx = i + 1;
        break;
      }
    }
    //
    if (idx == 0) {
      cout << -1 << endl;
      return 0;
    }
    //
    q.push_back(idx);

    // vectorを再構成
    int m = (int)b.size() - 1;
    vector<int> c(m);
    rep(i, idx - 1) c[i] = b[i];
    for (int j = idx; j < m + 1; j++) {
      c[j - 1] = b[j];
    }
    b.resize(m);
    b = c;
  }

  /* output */
  while (!q.empty()) {
    cout << q.back() << endl;
    q.pop_back();
  }

  return 0;
}