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
  int H, W;
  cin >> H >> W;
  vvc A(H, vc(W));
  rep(i, H) rep(j, W) cin >> A[i][j];

  /* solve */
  vvb can(H, vb(W, false));
  vvb color(H, vb(W, false));

  queue<pair<int, int>> q;
  q.emplace(0, 0);
  color[0][0] = true;
  can[0][0] = true;

  while (!q.empty()) {
    auto p = q.front();
    q.pop();

    // 下と右を追加
    int b = p.first + 1;
    int r = p.second + 1;
    if (b < H && A[b][p.second] == '#') {
      if (!color[b][p.second]) {
        color[b][p.second] = true;
        can[b][p.second] = true;
        q.emplace(b, p.second);
      }
    }
    if (r < W && A[p.first][r] == '#') {
      if (!color[p.first][r]) {
        color[p.first][r] = true;
        can[p.first][r] = true;
        q.emplace(p.first, r);
      }
    }
  }

  /* output */
  rep(i, H) {
    rep(j, W) {
      if (A[i][j] == '#' && !can[i][j]) {
        cout << "Impossible" << endl;
        return 0;
      }
    }
  }
  // adhoc
  rep(i, H - 1) {
    rep(j, W - 1) {
      if (A[i][j] == '#') {
        if (A[i + 1][j] == '#' && A[i][j + 1] == '#') {
          cout << "Impossible" << endl;
          return 0;
        }
      }
    }
  }
  cout << "Possible" << endl;

  return 0;
}