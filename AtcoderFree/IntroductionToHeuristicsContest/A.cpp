#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
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

// 焼きなまし法の参考にしたページ
// https://shindannin.hatenadiary.com/entry/2021/03/06/115415

int D;
vi ans;
vl scores2(26);
// コンテストiが開催された日のリスト
vector<set<int>> lastSet(26);

// 0以上UINT_MAX(0xffffffff)以下の整数をとる乱数 xorshift
// https://ja.wikipedia.org/wiki/Xorshift
static uint32_t randXor() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

// 0以上1未満の小数をとる乱数
static double rand01() { return (randXor() + 0.5) * (1.0 / UINT_MAX); }

const static int NUM_TYPES = 26;  // コンテストの種類数

void greedy(vl &c, vvl &s) {
  rep(i, D) {
    int idx = 0;
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
  }
}

// randomに初期化
void randomInit() {
  rep(i, D) {
    const int t = randXor() % NUM_TYPES;
    ans[i] = t;
    lastSet[t].insert(i + 1);
  }
}

ll nc2(int n) {
  if (n < 2) return 0;
  return (ll)n * (n - 1) / 2;
}

// コンテストごとに計算
void deterministic2(vl &c, vvl &s) {
  rep(i, 26) {
    ll score = 0;
    int prev = 0;
    for (auto v : lastSet[i]) {
      if (v == 0) continue;
      score += s[v - 1][i];
      score -= c[i] * nc2(v - prev);
      prev = v;
    }
    score -= c[i] * nc2(D + 1 - prev);
    scores2[i] = score;
  }
}

// di日目をqiに変更
void change(int di, int qi, vl &c, vvl &s) {
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
  for (auto v : lastSet[qi]) {
    if (v == 0) continue;
    score += s[v - 1][qi];
    score -= c[qi] * nc2(v - prev);
    prev = v;
  }
  score -= c[qi] * nc2(D + 1 - prev);
  scores2[qi] = score;
  // cout << scores2[oq] << " " << scores2[qi] << endl;
}

int main() {
  // 時間計測
  auto startClock = system_clock::now();
  /* input */
  cin >> D;
  vl c(26);
  rep(i, 26) cin >> c[i];
  vvl s(D, vl(26));
  rep(i, D) rep(j, 26) cin >> s[i][j];

  /* solve */
  ans.resize(D);
  rep(i, 26) lastSet[i].insert(0);
  // 初期解
  // greedy(c, s);
  randomInit();

  // スコア計算
  deterministic2(c, s);
  ll nowScore = 0;
  rep(i, 26) nowScore += scores2[i];

  // デバッグ用：初期解
  // cout << "初期解のスコア：" << nowScore << endl;

  /* 焼きなまし法 */
  vi bestAns(D);

  const static double START_TEMP = 1500;  // 開始時の温度
  const static double END_TEMP = 100;     // 終了時の温度
  const static double END_TIME = 1.9;     // 終了時間（秒）
  double time = 0.0;                      // 経過時間（秒）
  do {
    // 進捗。開始時が0.0で、終了時が1.0
    const double progressRatio = time / END_TIME;
    const double temp = START_TEMP + (END_TEMP - START_TEMP) * progressRatio;

    // 近傍： d日目のコンテストをtに変えてみる。d,tはランダムに選ぶ。
    const int d = randXor() % D;
    const int t = randXor() % NUM_TYPES;
    // バックアップを取る
    const int backupAns = ans[d];
    const ll backupScore1 = scores2[backupAns];
    const ll backupScore2 = scores2[t];
    // 変えてみる
    ll beforeScore = scores2[backupAns] + scores2[t];
    change(d, t, c, s);
    ll afterScore = scores2[backupAns] + scores2[t];

    double deltaScore = (double)(afterScore - beforeScore);
    // 焼きなまし法の遷移確率
    const double probability = exp(deltaScore / temp);

    if (probability < rand01()) {
      // cout << "変更を拒否：" << afterScore - beforeScore << endl;
      lastSet[t].erase(d + 1);
      lastSet[backupAns].insert(d + 1);
      scores2[backupAns] = backupScore1;
      scores2[t] = backupScore2;
      ans[d] = backupAns;
    } else {
      // cout << "変更を受け入れ：" << afterScore - beforeScore << endl;
    }

    assert(0 <= ans[d] && ans[d] < NUM_TYPES);

    // cout << backupAns << " " << ans[d] << endl;

    // 時間更新
    time =
        ((double)duration_cast<microseconds>(system_clock::now() - startClock)
             .count() *
         1e-6);

  } while (time < END_TIME);

  /* output */
  rep(i, D) {
    assert(0 <= ans[i] && ans[i] < NUM_TYPES);
    cout << ans[i] + 1 << endl;
  }

  // デバッグ用：改良後のスコア
  // nowScore = 0;
  // rep(i, 26) nowScore += scores2[i];
  // cout << "出力するスコア：" << nowScore << endl;

  return 0;
}