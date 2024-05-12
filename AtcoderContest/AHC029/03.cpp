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

int N, M, K, T;
struct NewHands {
  vi t2, w2, p2;
  // コンパイルの都合で引数を取っているだけ
  NewHands(int _K) {
    t2.resize(_K);
    w2.resize(_K);
    p2.resize(_K);
    rep(i, _K) { cin >> t2[i] >> w2[i] >> p2[i]; }
  };
};

const double THRESHOLD_BOMB_1 = 0.8;
const double THRESHOLD_BOMB_ALL = 0.7;

pair<int, int> selectIdx1(vi& t, vi& w, vi& h, vi& v, int& money,
                          int increaceCount, int turn) {
  // カードの強さを評価付ける

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
  // 労働カードがあれば選ぶ
  int restTurn = 1000 - turn;
  ll canWork = restTurn * (int)(pow(2, increaceCount) + 0.0001);
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

int selectIdx2(vi& t, vi& w, vi& h, vi& v, int& money, NewHands& newHands,
               int increaceCount, int turn) {
  // 終盤はとりあえず0を選んでおく
  if (turn >= 950) return 0;
  // カードの強さを評価付ける
  vpii handsTier;
  handsTier.emplace_back(50, 0);  // 基準
  for (int i = 1; i < K; i++) {
    if (newHands.t2[i] == 0) {
      handsTier.emplace_back(newHands.w2[i] / newHands.p2[i], i);
    } else if (newHands.t2[i] == 1) {
      handsTier.emplace_back(newHands.w2[i] / newHands.p2[i] * M, i);
    } else if (newHands.t2[i] == 2) {
      // 使いたい場面で安い爆弾があれば取る
      int ok = 0;
      rep(j, M) {
        // 閾値以上で爆破する
        if (v[j] * THRESHOLD_BOMB_1 <= h[j]) ok = 1;
      }
      if (ok) {
        handsTier.emplace_back(55 - newHands.p2[i], i);
      } else {
        handsTier.emplace_back(1 - newHands.p2[i], i);
      }
    } else if (newHands.t2[i] == 3) {
      // 使いたい場面で安い爆弾があれば取る
      int ok = 1;
      rep(j, M) {
        // 閾値値未満があれば爆破しない
        if (v[j] * THRESHOLD_BOMB_ALL > h[j]) ok = 0;
      }
      if (ok) {
        handsTier.emplace_back(55 - newHands.p2[i], i);
      } else {
        handsTier.emplace_back(1, i);
      }
    } else if (newHands.t2[i] == 4) {
      if (increaceCount < 2 && turn < 800) {
        handsTier.emplace_back(1e9, i);
      } else {
        handsTier.emplace_back(-1e9, i);
      }
    }
  }
  sort(handsTier.rbegin(), handsTier.rend());
  rep(i, K) {
    int idx = handsTier[i].second;
    if (newHands.p2[idx] <= money) return idx;
  }

  return 0;
}

// N：手札、M：プロジェクトサイズ、K：選べる次のカード
// t:カード種類、w:労働力、h:PJ残務量、v:PJ価値
void play1(vi& t, vi& w, vi& h, vi& v) {
  int increaceCount = 0;  // 増資カードの使用回数
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

    // 選ぶ
    int idx2 = selectIdx2(t, w, h, v, money, newHands, increaceCount, turn);
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