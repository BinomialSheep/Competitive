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
    int N;
    cin >> N;

    vector<pii> LRs(N);
    vector<pii> LInv(N);
    vector<pii> RInv(N);
    rep(i, N) {
      int L, R;
      cin >> L >> R;
      LRs[i] = make_pair(L, R);
      LInv[i] = make_pair(L, i);
      RInv[i] = make_pair(R, i);
    }

    /* solve */
    deque<pii> q;
    vb color(N, false);
    sort(LInv.begin(), LInv.end());
    sort(RInv.begin(), RInv.end());

    q.emplace_back(LRs[RInv[0].second]);
    color[RInv[0].second] = true;
    for (int left = 0; left < N; left++) {
      // もう使ってたら進める
      if (color[LInv[left].second]) continue;

      auto p = q.back();
      if (LInv[left].first <= p.second) {
        // 結合する
        pii p2 = LRs[LInv[left].second];
        q.pop_back();
        pii newP = make_pair(min(p.first, p2.first), max(p.second, p2.second));
        q.push_back(newP);
      } else {
        // 結合しない
        q.emplace_back(LRs[LInv[left].second]);
      }
      color[LInv[left].second] = true;
    }

    /* output */
    rep(i, (int)q.size()) { cout << q[i].first << " " << q[i].second << "\n"; }
    cout << endl;
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