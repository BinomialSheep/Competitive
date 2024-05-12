#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<unsigned long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<unsigned long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
using ull = unsigned long long;
#define INFTYL (1ULL << 63) + (1ULL << 62)
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
  int N, M;
  cin >> N >> M;
  vvl G(N, vl(N, INFTYL));
  vvl T(N, vl(N, 0));

  rep(i, M) {
    int s, t;
    ll d, time;
    cin >> s >> t >> d >> time;
    --s;
    --t;
    G[s][t] = d;
    G[t][s] = d;
    T[s][t] = time;
    T[t][s] = time;
  }

  /* solve */
  // dp[bit][現在地]
  int setbit = (1 << N);
  using pll = pair<ull, ull>;
  vector<vector<pll>> dp(setbit, vector<pll>(N, make_pair(INFTYL, 0)));
  dp[0][0] = make_pair(0, 1);

  for (ll bit = 0; bit < setbit; ++bit) {
    rep(i, N) {
      if (bit != 0 && !(bit & (1 << i))) continue;
      // 配る場所
      rep(j, N) {
        if (G[i][j] == INFTYL) continue;
        if (T[i][j] < dp[bit][i].first + G[i][j]) continue;
        if (bit != setbit && (bit & (1 << j))) continue;
        ull cost = dp[bit][i].first + G[i][j];
        ull nex = bit | (1 << j);
        if (cost < dp[nex][j].first) {
          dp[nex][j].first = cost;
          dp[nex][j].second = dp[bit][i].second;
        } else if (cost == dp[nex][j].first) {
          dp[nex][j].second += dp[bit][i].second;
        }
      }
    }
  }

  /* output */
  auto &res = dp[setbit - 1][0];
  if (res.second == 0)
    cout << "IMPOSSIBLE" << endl;
  else
    cout << res.first << " " << res.second << endl;
  return 0;
}