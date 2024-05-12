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

int D;
vi ans;
vl scores;
vl scores2(26);
// last[i][j]はコンテストiが最後に開催された日のリスト
vvi last(26);

void greedy(vi &c, vvi &s) {
  ll score = 0;

  rep(i, D) {
    int idx;
    ll value = -1 * INFTY;
    rep(j, 26) {
      // d日目にjが開催された時のスコアの差分を求める
      ll diff = 0;
      //　上がる分
      diff += s[i][j];
      // 下がる分
      rep(k, 26) {
        if (j == k) continue;
        diff -= c[k] * (i + 1 - last[k].back());
      }
      if (diff > value) {
        idx = j;
        value = diff;
      }
    }
    // 一番満足度が上がるものを採用する
    ans[i] = idx;
    last[idx].push_back(i + 1);
    // スコアの更新（今は使っていない）
    score += value;
    scores[i] = score;
  }
}

// 日付ごとに計算
void deterministic(vi &c, vvi &s, vi &t) {
  ll score = 0;

  rep(i, D) {
    // d日目はt[i]が開催される
    //　上がる分
    score += s[i][t[i]];
    // lastの更新
    last[t[i]].push_back(i + 1);
    // 下がる分
    rep(j, 26) { score -= c[j] * (i + 1 - last[j].back()); }
    scores[i] = score;
  }
}

// コンテストごとに計算
void deterministic2(vi &c, vvi &s, vi &t) {
  rep(i, 26) {
    ll score = 0;
    rep(j, D) {
      // j日目はt[j]が開催される
      if (t[j] == i) {
        score += s[j][i];
        last[i].push_back(j + 1);
      } else {
        score -= c[i] * (j + 1 - last[i].back());
      }
    }
    scores2[i] = score;
  }
}

ll nc2(int n) {
  if (n < 2) return 0;
  return n * (n - 1) / 2;
}

// di日目をqiに変更
void change(int di, int qi, vi &c, vvi &s) {
  // scores2は独立なので2本だけ考えればいい
  //
  int oq = ans[di];
  ans[di] = qi;
  // debug
  // cout << scores2[oq] << " " << scores2[qi] << " ";
  //  di日目の満足度が変わる
  scores2[oq] -= s[di][oq];
  scores2[qi] += s[di][qi];
  // 減らす満足度が変わる
  // 1つ前、1つ後のidxを求める
  int origPrev = 0, origNex = D + 1, qPrev = 0, qNex = D + 1;
  for (auto v : last[oq]) {
    if (v == di + 1) continue;
    (v < di + 1 ? chmax(origPrev, v) : chmin(origNex, v));
  }
  for (auto v : last[qi]) {
    if (v == di + 1) continue;
    (v < di + 1 ? chmax(qPrev, v) : chmin(qNex, v));
  }
  // lastが変わるo
  rep(i, last[oq].size()) {
    if (last[oq][i] == di + 1) last[oq][i] = 0;
  }
  // last[oq].remove_if([di](int x) { return x == di + 1; });
  last[qi].push_back(di + 1);

  // scores2[oq] = 0;
  // sort(last[oq].begin(), last[oq].end());
  // rep(j, last[oq].size()) {
  //   if (last[oq][j] == 0) continue;
  //   scores2[oq] += s[last[oq][j] - 1][oq];
  //   if (j + 1 < last[oq].size()) {
  //     scores2[oq] -= nc2(last[oq][j + 1] - last[oq][j]) * c[oq];
  //   }
  // }
  // scores2[qi] = 0;
  // sort(last[qi].begin(), last[qi].end());
  // rep(j, last[qi].size()) {
  //   if (last[oq][j] == 0) continue;
  //   scores2[qi] += s[last[qi][j] - 1][qi];
  //   if (j + 1 < last[qi].size()) {
  //     scores2[qi] -= nc2(last[qi][j + 1] - last[qi][j]) * c[qi];
  //   }
  // }

  // 計算パート
  // scores2[oq] -= nc2(di + 1 - qPrev) * c[oq];
  // scores2[oq] -= nc2(origNex - di - 1) * c[oq];
  // scores2[oq] += nc2(origNex - origPrev) * c[oq];
  // scores2[qi] += nc2(di + 1 - qPrev) * c[qi];
  // scores2[qi] -= nc2(qNex - qPrev) * c[qi];
  // scores2[qi] += nc2(qNex - di - 1) * c[qi];

  // cout << scores2[oq] << " " << scores2[qi] << endl;
}

int main() {
  /* input */
  cin >> D;
  vi c(26);
  rep(i, 26) cin >> c[i];
  vvi s(D, vi(26));
  rep(i, D) rep(j, 26) cin >> s[i][j];

  vi t(D);
  rep(i, D) {
    cin >> t[i];
    --t[i];
  }

  int M;
  cin >> M;
  vi d(M);
  vi q(M);
  rep(i, M) {
    cin >> d[i] >> q[i];
    --d[i];
    --q[i];
  }

  /* solve */
  // init
  ans.resize(D);
  scores.resize(D);
  rep(i, 26) last[i].push_back(0);
  //  初期解
  // greedy(c, s);

  // スコア計算
  // WARNING: 2つ使う場合はlastの初期化が必要
  // deterministic(c, s, t);
  deterministic2(c, s, t);
  ll lastDayScore = 0;
  rep(i, 26) lastDayScore += scores2[i];

  //
  rep(i, D) ans[i] = t[i];
  rep(i, M) {
    int orig = t[d[i]];
    lastDayScore -= scores2[orig];
    lastDayScore -= scores2[q[i]];
    // change(d[i], q[i], c, s);
    //   temp
    t[d[i]] = q[i];
    rep(j, 26) {
      last[j].clear();
      last[j].push_back(0);
    }
    deterministic2(c, s, t);
    //
    lastDayScore += scores2[orig];
    lastDayScore += scores2[q[i]];
    cout << lastDayScore << endl;
  }

  /* output */
  // rep(i, D) cout << scores[i] << endl;
  // rep(i, D) cout << ans[i] + 1 << endl;

  return 0;
}