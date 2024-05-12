#pragma region header
#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
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

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
#define INT(...)   \
  int __VA_ARGS__; \
  in(__VA_ARGS__)
#define LL(...)   \
  ll __VA_ARGS__; \
  in(__VA_ARGS__)
#define STR(...)      \
  string __VA_ARGS__; \
  in(__VA_ARGS__)
#define Sort(a) sort(all(a))
#define VEC(type, name, size) \
  vector<type> name(size);    \
  in(name)
[[maybe_unused]] void print() {}
template <class T, class... Ts>
void print(const T& t, const Ts&... ts);
template <class... Ts>
void out(const Ts&... ts) {
  print(ts...);
  cout << '\n';
}

namespace IO {
#define VOID(a) decltype(void(a))
struct S {
  S() {
    cin.tie(nullptr)->sync_with_stdio(0);
    fixed(cout).precision(12);
  }
} S;
template <int I>
struct P : P<I - 1> {};
template <>
struct P<0> {};
template <class T>
void i(T& t) {
  i(t, P<3>{});
}
void i(vector<bool>::reference t, P<3>) {
  int a;
  i(a);
  t = a;
}
template <class T>
auto i(T& t, P<2>) -> VOID(cin >> t) {
  cin >> t;
}
template <class T>
auto i(T& t, P<1>) -> VOID(begin(t)) {
  for (auto&& x : t) i(x);
}
template <class T, size_t... idx>
void ituple(T& t, index_sequence<idx...>) {
  in(get<idx>(t)...);
}
template <class T>
auto i(T& t, P<0>) -> VOID(tuple_size<T>{}) {
  ituple(t, make_index_sequence<tuple_size<T>::value>{});
}
template <class T>
void o(const T& t) {
  o(t, P<4>{});
}
template <size_t N>
void o(const char (&t)[N], P<4>) {
  cout << t;
}
template <class T, size_t N>
void o(const T (&t)[N], P<3>) {
  o(t[0]);
  for (size_t i = 1; i < N; i++) {
    o(' ');
    o(t[i]);
  }
}
template <class T>
auto o(const T& t, P<2>) -> VOID(cout << t) {
  cout << t;
}
template <class T>
auto o(const T& t, P<1>) -> VOID(begin(t)) {
  bool first = 1;
  for (auto&& x : t) {
    if (first)
      first = 0;
    else
      o(' ');
    o(x);
  }
}
template <class T, size_t... idx>
void otuple(const T& t, index_sequence<idx...>) {
  print(get<idx>(t)...);
}
template <class T>
auto o(T& t, P<0>) -> VOID(tuple_size<T>{}) {
  otuple(t, make_index_sequence<tuple_size<T>::value>{});
}
#undef VOID
}  // namespace IO
#define unpack(a) \
  (void)initializer_list<int> { (a, 0)... }
template <class... Ts>
void in(Ts&... t) {
  unpack(IO::i(t));
}
template <class T, class... Ts>
void print(const T& t, const Ts&... ts) {
  IO::o(t);
  unpack(IO::o((cout << ' ', ts)));
}
#undef unpack
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

#define YESNO(yes, no)                          \
  void yes(bool i = 1) { out(i ? #yes : #no); } \
  void no() { out(#no); }
YESNO(first, second)
YESNO(First, Second)
YESNO(Yes, No)
YESNO(YES, NO)
YESNO(possible, impossible)
YESNO(POSSIBLE, IMPOSSIBLE)
#pragma endregion header
// #include <atcoder/all>
// using namespace atcoder;
using namespace chrono;
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

double gauss(double mu, double sigma) {
  // Box-Muller変換を使用
  double u1 = static_cast<double>(randXor()) / UINT32_MAX;
  double u2 = static_cast<double>(randXor()) / UINT32_MAX;
  double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
  return mu + sigma * z0;
}

int randP0(int L2, int w) {
  double w_ = (double)w / L2;
  int tmp = (int)gauss(w_, w_ / 3);
  return clamp(tmp, 1, 10000) * L2;
}
int randP1(int L2, int w) {
  double w_ = (double)w / L2;
  int tmp = (int)gauss(w_, w_ / 3) * L2;
  return clamp(tmp, 1, 10000) * L2;
}
int randP2(int L2) { return randXor() % 11 * L2; }
int randP3(int L2) { return randXor() % 11 * L2; }
int randP4(int L2) { return (randXor() % 801 + 200) * L2; }
int randW(int L2) { return (randXor() % 50 + 1) * L2; }

// p:コスト、w:労働力
pair<int, int> randP(int j, int L2) {
  if (j == 0) {
    int w = randW(L2);
    return make_pair(randP0(L2, w), w);
  }
  if (j == 1) {
    int w = randW(L2);
    return make_pair(randP1(L2, w), w);
  }
  if (j == 2) return make_pair(randP2(L2), 0);
  if (j == 3) return make_pair(randP3(L2), 0);
  if (j == 4) return make_pair(randP4(L2), 0);
  return make_pair(-1, -1);
}

// h:PJ残務量、v:PJ価値
pair<int, int> randProject(int L2) {
  double tmp = static_cast<double>(randXor()) / UINT32_MAX;
  double b = 2.0 + tmp * 6.0;
  int h = (1 << (int)b) * L2;
  int v = (int)pow(2, clamp(gauss(b, 0.5), 0.0, 10.0)) * L2;
  return make_pair(h, v);
}

int N, M, K, T;
vi xs = {10, 5, 5, 3, 2};
vi xs2 = {10, 15, 20, 23, 25};
struct NewHands {
  vi t2, w2, p2;
  // コンパイルの都合で引数を取っているだけ
  NewHands(int _K) {
    t2.resize(_K);
    w2.resize(_K);
    p2.resize(_K);
    rep(i, _K) { cin >> t2[i] >> w2[i] >> p2[i]; }
  };
  NewHands(int _K, int L, string dummy) {
    t2.resize(_K);
    w2.resize(_K);
    p2.resize(_K);
    rep(i, _K) {
      if (i == 0) {
        t2[0] = 0;
        w2[0] = 1 << L;
        p2[0] = 0;
        continue;
      }
      int num = randXor() % xs2[4];
      rep(j, 5) {
        if (num < xs2[j]) {
          auto [p, w] = randP(j, 1 << L);
          t2[i] = j;
          p2[i] = p;
          w2[i] = w;
          break;
        }
      }
    }
  };
};

const double THRESHOLD_BOMB_1 = 0.8;
const double THRESHOLD_BOMB_ALL = 0.7;

pair<int, int> selectIdx1(vi& t, vi& w, vi& h, vi& v, int& money,
                          int increaceCount, int turn) {
  // カードの強さを評価付ける

  // 爆弾を使いたい場面なら使う
  rep(i, N) {
    if (t[i] == 3) {
      int ok = 1;
      rep(j, M) {
        // 閾値値未満があれば爆破しない
        if (v[j] * THRESHOLD_BOMB_ALL > h[j]) ok = 0;
      }
      if (ok) return {i, 0};
    }
  }
  rep(i, N) {
    if (t[i] == 2) {
      rep(j, M) {
        // 閾値以上で爆破する
        if (v[j] * THRESHOLD_BOMB_1 <= h[j]) {
          return {i, j};
        }
      }
    }
  }

  // 増資カードがあれば選ぶ
  rep(i, N) {
    if (t[i] == 4 && increaceCount < 20) {
      return {i, 0};
    }
  }

  // 全力労働カードがあれば選ぶ
  rep(i, N) {
    if (t[i] == 1) {
      return {i, 0};
    }
  }
  int idx = -1, m = 0;
  // プロジェクトを終わらせられるなら終わらせる
  vector<pair<int, int>> ps;
  rep(i, N) {
    if (t[i] == 0) {
      rep(j, M) {
        if (h[j] <= w[i]) ps.emplace_back(i, j);
      }
    }
  }
  sort(all(ps), [&](pair<int, int> p1, pair<int, int> p2) -> int {
    if (h[p1.second] != h[p2.second]) {
      return h[p1.second] > h[p2.second];
    }
    if (w[p1.first] != w[p2.first]) return w[p1.first] > w[p2.first];
    if (p1.first != p2.first) return p1.first > p2.first;
    return p1.second > p2.second;
  });
  if (ps.size()) {
    return ps[0];
  }

  // 労働カードがあれば選ぶ
  int restTurn = 1000 - turn;
  ll canWork = restTurn * (1 << increaceCount);
  rep(i, N) {
    if (t[i] == 0) {
      m = 0;
      // 1番コスパがいいものを選ぶ
      double value = 0;
      rep(j, M) {
        // 終わる見込みがないならやらない方がいいけど
        if (canWork >= h[j] && chmax(value, (double)v[j] / h[j])) m = j;
      }
      return {i, m};
    }
  }

  // なに？？？
  while (idx == -1) {
    int i = randXor() % N;
    idx = i;
    if (t[idx] == 0) {
      m = 0;
      // 1番コスパがいいものを選ぶ
      double value = 0;
      rep(j, M) if (chmax(value, (double)v[j] / h[j])) m = j;
    } else if (t[idx] == 2) {
      m = 0;
      // 1番コスパが悪いものを選ぶ
      double value = 1e18;
      rep(j, M) if (chmin(value, (double)v[j] / h[j])) m = j;
    } else if (t[idx] == 4) {
      increaceCount++;
    }
  }
  return {idx, m};
}

// (価値, idx)
vpii evaluationValueListIdx2(vi& t, vi& w, vi& h, vi& v, int& money,
                             NewHands& newHands, int increaceCount, int turn) {
  vpii handsTier;
  // 終盤は終わる見込みがあるならとりあえず0を選んでおく
  if (turn >= 950) {
    int restTurn = 1000 - turn;
    ll canWork = restTurn * (int)(pow(2, increaceCount) + 0.0001);
    rep(j, M) if (canWork >= h[j]) {
      handsTier.emplace_back(0, 0);
      return handsTier;
    }
    // 終わる見込みがないならワンチャン狙って他のカードを引く
  }

  handsTier.emplace_back(50, 0);  // 基準
  for (int i = 1; i < K; i++) {
    if (newHands.t2[i] == 0) {
      handsTier.emplace_back(50 * (double)newHands.w2[i] / newHands.p2[i], i);
    } else if (newHands.t2[i] == 1) {
      // handsTier.emplace_back(
      //     50 * (double)newHands.w2[i] / newHands.p2[i] * min(M, 5), i);
      handsTier.emplace_back(50 * (double)newHands.w2[i] / newHands.p2[i] * M,
                             i);
    } else if (newHands.t2[i] == 2) {
      // 使いたい場面で安い爆弾があれば取る
      int ok = 0;
      rep(j, M) {
        // 閾値以上で爆破する
        if (v[j] * THRESHOLD_BOMB_1 <= h[j]) ok = 1;
      }
      if (ok) {
        handsTier.emplace_back(54 - newHands.p2[i], i);
      } else {
        handsTier.emplace_back(-1e8, i);
      }
    } else if (newHands.t2[i] == 3) {
      // 使いたい場面で安い爆弾があれば取る
      int ok = 1;
      rep(j, M) {
        // 閾値値未満があれば爆破しない
        if (v[j] * THRESHOLD_BOMB_ALL > h[j]) ok = 0;
      }
      if (ok) {
        handsTier.emplace_back(54 - newHands.p2[i], i);
      } else {
        handsTier.emplace_back(-1e8, i);
      }
    } else if (newHands.t2[i] == 4) {
      if (increaceCount < 15 && turn < 800) {
        handsTier.emplace_back(1e8, i);
      } else {
        handsTier.emplace_back(-1e8, i);
      }
    }
  }
  sort(handsTier.rbegin(), handsTier.rend());
  vpii ret;
  rep(i, K) {
    int idx = handsTier[i].second;
    if (newHands.p2[idx] <= money) {
      ret.push_back(handsTier[i]);
    }
  }
  return ret;
}

int selectIdx2(vi& t, vi& w, vi& h, vi& v, int& money, NewHands& newHands,
               int increaceCount, int turn) {
  // カードの強さを評価付ける
  vpii handsTier =
      evaluationValueListIdx2(t, w, h, v, money, newHands, increaceCount, turn);

  return handsTier[0].second;
}

// 仮想的にプレイする
// N：手札、M：プロジェクトサイズ、K：選べる次のカード
// t:カード種類、w:労働力、h:PJ残務量、v:PJ価値
int dummyPlay(vi t, vi w, vi h, vi v, int nowTurn, int increaceCount,
              int money) {
  for (int turn = nowTurn; turn < T; turn++) {
    // 手札使用
    auto [idx, m] = selectIdx1(t, w, h, v, money, increaceCount, turn);

    // 効果更新
    if (t[idx] == 0) {
      h[m] -= w[idx];
      if (h[m] <= 0) {
        money += v[m];
        pair<int, int> project = randProject(1 << increaceCount);
        h[m] = project.first;
        v[m] = project.second;
      }
    } else if (t[idx] == 1) {
      rep(i, M) {
        h[i] -= w[idx];
        if (h[i] <= 0) {
          money += v[i];
          pair<int, int> project = randProject(1 << increaceCount);
          h[i] = project.first;
          v[i] = project.second;
        }
      }
    } else if (t[idx] == 2) {
      pair<int, int> project = randProject(1 << increaceCount);
      h[m] = project.first;
      v[m] = project.second;
    } else if (t[idx] == 3) {
      rep(i, M) {
        pair<int, int> project = randProject(1 << increaceCount);
        h[i] = project.first;
        v[i] = project.second;
      }
    } else if (t[idx] == 4) {
      increaceCount++;
    }

    t[idx] = -1, w[idx] = -1;
    // 手札追加
    NewHands newHands(K, increaceCount, "dummy");
    // 選ぶ
    int idx2 = selectIdx2(t, w, h, v, money, newHands, increaceCount, turn);
    // 手札更新
    t[idx] = newHands.t2[idx2];
    w[idx] = newHands.w2[idx2];
    // money更新
    money -= newHands.p2[idx2];
  }
  return money;
}

double dummyPlayN(vi& t, vi& w, vi& h, vi& v, int turn, int increaceCount,
                  int money, int num) {
  double sum = 0;
  rep(i, num) sum += dummyPlay(t, w, h, v, turn, increaceCount, money);
  return sum / num;
}

// N：手札、M：プロジェクトサイズ、K：選べる次のカード
// t:カード種類、w:労働力、h:PJ残務量、v:PJ価値
void play1(vi& t, vi& w, vi& h, vi& v) {
  auto startClock = system_clock::now();
  const static double END_TIME = 1.8;  // 終了時間（秒）
  double time = 0.0;                   // 経過時間（秒）
  int increaceCount = 0;               // 増資カードの使用回数
  int money = 0;
  rep(turn, T) {
    // 手札使用
    auto [idx, m] = selectIdx1(t, w, h, v, money, increaceCount, turn);

    // 効果更新
    if (t[idx] == 4) {
      increaceCount++;
    }

    t[idx] = -1, w[idx] = -1;
    // 使用カード出力
    cout << idx << " " << m << endl;
    // プロジェクト更新
    rep(i, M) { cin >> h[i] >> v[i]; }

    // money更新
    cin >> money;
    // 手札追加
    NewHands newHands(K);

    rep(i, K) xs[newHands.t2[i]]++;
    rep(i, K) {
      xs2[i] = xs[i];
      if (i) xs2[i] += xs2[i - 1];
    }

    // 選ぶ
    int idx2 = -1;
    vpii handsTier = evaluationValueListIdx2(t, w, h, v, money, newHands,
                                             increaceCount, turn);

    time =
        ((double)duration_cast<microseconds>(system_clock::now() - startClock)
             .count() *
         1e-6);
    if (true || handsTier.size() == 1 ||
        handsTier[0].first - handsTier[1].first > 10 || turn < 500 ||
        time >= END_TIME) {
      idx2 = handsTier[0].second;
    } else {
      double maxPredict = 0;
      rep(i, 2) {
        int idx3 = handsTier[i].second;
        t[idx] = newHands.t2[idx3];
        w[idx] = newHands.w2[idx3];
        money -= newHands.p2[idx3];
        double predict = dummyPlayN(t, w, h, v, turn, increaceCount, money, 10);
        debug(turn, i, predict, handsTier[i]);
        // predict = predict / 10000 + handsTier[i].first;
        money += newHands.p2[idx3];
        if (chmax(maxPredict, predict)) idx2 = idx3;
      }
    }

    // 出力
    cout << idx2 << endl;
    // 手札更新
    t[idx] = newHands.t2[idx2];
    w[idx] = newHands.w2[idx2];
    // money更新
    money -= newHands.p2[idx2];
  }
}

int main() {
  // input
  cin >> N >> M >> K >> T;
  vi t(N), w(N), h(M), v(M);
  rep(i, N) cin >> t[i] >> w[i];
  rep(i, M) cin >> h[i] >> v[i];
  //
  play1(t, w, h, v);

  return 0;
}