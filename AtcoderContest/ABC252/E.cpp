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

static const int WHITE = 0;
static const int GRAY = 1;
static const int BLACK = 2;

vi used;

void dijkstra(int N, vvi &to) {
  int minv;
  int d[N + 1], color[N + 1];
  // 初期化
  rep(i, N + 1) {
    d[i] = INFTY;
    color[i] = WHITE;
  }
  d[0] = 0;
  color[0] = GRAY;
  while (true) {
    minv = INFTY;
    int u = -1;
    // rootからの距離d[i]が最小の頂点を、最短経路木に確定させる
    // ただしcolor grayの辺は取らない
    rep(i, N) {
      if (minv > d[i] && color[i] == WHITE) {
        u = i;
        minv = d[i];
      }
    }
    // 足す頂点がなければbreak;
    if (u == -1) break;

    color[u] = BLACK;
    // uと接していてBLACKでない頂点について、d[i]を更新する
    rep(v, N) {
      if (color[v] != BLACK && to[u][v] != INFTY) {
        if (d[v] > d[u] + to[u][v]) {
          d[v] = d[u] + to[u][v];
          color[v] = GRAY;
        }
      }
    }
  }
  // rep(i, n) cout << i << " " << (d[i] == INFTY ? -1 : d[i]) << endl;
}

int main() {
  /* input */
  int N, M;
  cin >> N >> M;
  vvi to(N, vi(N));
  rep(i, M) {
    int a, b, c;
    cin >> a >> b >> c;
    --a;
    --b;
    to[a][b] = c;
    to[b][a] = c;
  }

  dijkstra(N, to);

  /* solve */

  /* output */

  return 0;
}