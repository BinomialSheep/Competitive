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
using pii = pair<int, int>;
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

struct Solver {
  int H, W;
  vs maze;

  ll dfs(int y, int x, string &s) {
    if (y == H - 1 && x == W - 1) {
      ll ret = 0;
      if (s[0] == '#') ret++;
      rep(i, (int)s.size() - 1) {
        if (s[i] == '.' && s[i + 1] == '#') ret++;
      }
      // cout << s << " " << ret << endl;
      return ret;
    }
    ll ret = INFTY;
    if (y != H - 1) {
      s.push_back(maze[y + 1][x]);
      chmin(ret, dfs(y + 1, x, s));
      s.pop_back();
    }
    if (x != W - 1) {
      s.push_back(maze[y][x + 1]);
      chmin(ret, dfs(y, x + 1, s));
      s.pop_back();
    }
    return ret;
  }

  void solve() {
    /* input */

    cin >> H >> W;
    maze.resize(H);

    rep(i, H) cin >> maze[i];

    /* solve */
    string tmp = {maze[0][0]};
    ll ans = dfs(0, 0, tmp);

    /* output */
    cout << ans << endl;
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}