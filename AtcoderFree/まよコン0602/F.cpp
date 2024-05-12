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
  void solve() {
    /* input */
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, pii>>> G(N);

    rep(i, M) {
      int A, B, C, D;
      cin >> A >> B >> C >> D;
      --A;
      --B;
      G[A].emplace_back(B, make_pair(C, D));
      G[B].emplace_back(A, make_pair(C, D));
    }

    /* solve */
    // 変則ダイクストラ
    vi dist(N);
    rep(i, N) dist[i] = INFTY;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, 0);
    dist[0] = 0;

    while (!q.empty()) {
      int pos = q.top().second;
      q.pop();
      for (auto us : G[pos]) {
        int to = us.first;
        // 現在時刻dist[pos]以降で、toに最短でたどり着く時間を知りたい～～
        int cost = us.second.first + us.second.second;
        rep(i, 10) {
          chmin(cost, us.second.first + i + us.second.second / (i + 1));
        }

        if (chmin(dist[to], dist[pos] + cost)) {
          q.emplace(dist[to], to);
        }
      }
    }

    /* output */
    cout << (dist[N - 1] == INFTY ? -1 : dist[N - 1]) << endl;
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