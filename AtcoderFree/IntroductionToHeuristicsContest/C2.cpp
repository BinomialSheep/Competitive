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
// コンテストiが開催された日のリスト
vector<set<int>> lastSet(26);

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
        diff -= c[k] * (i + 1 - *(--lastSet[k].end()));
      }
      if (diff > value) {
        idx = j;
        value = diff;
      }
    }
    // 一番満足度が上がるものを採用する
    ans[i] = idx;
    lastSet[idx].insert(i + 1);
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
    lastSet[t[i]].insert(i + 1);
    // 下がる分
    rep(j, 26) { score -= c[j] * (i + 1 - *(--lastSet[j].end())); }
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
        lastSet[i].insert(j + 1);
      } else {
        score -= c[i] * (j + 1 - *(--lastSet[i].end()));
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
  int oq = ans[di];
  ans[di] = qi;

  lastSet[oq].erase(di + 1);
  lastSet[qi].insert(di + 1);

  // 減った方
  ll score = 0;
  int prev = 0;
  for (auto v : lastSet[oq]) {
    if (v == 0) continue;
    score += s[v - 1][oq];
    score -= c[oq] * nc2(v - prev);
    prev = v;
  }
  score -= c[oq] * nc2(D + 1 - prev);
  scores2[oq] = score;

  // 増えた方
  score = 0;
  prev = 0;
  // cout << endl;
  for (auto v : lastSet[qi]) {
    if (v == 0) continue;
    score += s[v - 1][qi];
    score -= c[qi] * nc2(v - prev);
    prev = v;
  }
  score -= c[qi] * nc2(D + 1 - prev);
  scores2[qi] = score;
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
  rep(i, 26) lastSet[i].insert(0);
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
    int orig = ans[d[i]];
    lastDayScore -= scores2[orig];
    lastDayScore -= scores2[q[i]];
    change(d[i], q[i], c, s);
    lastDayScore += scores2[orig];
    lastDayScore += scores2[q[i]];
    cout << lastDayScore << endl;
  }

  /* output */
  // rep(i, D) cout << scores[i] << endl;
  // rep(i, D) cout << ans[i] + 1 << endl;
  // rep(i, 26) { cout << i << " " << scores2[i] << " "; }
  // cout << endl;

  return 0;
}