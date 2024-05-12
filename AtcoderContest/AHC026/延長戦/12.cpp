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

/*
 * 012.昇順に戻すときにも操作2をする
 *
 */

int N, M;

int bestScore = 1000000;
vpii bestAns;

void solve(vvi& B) {
  int score = 0;
  vpii ans;
  int now = 1;

  /* functions */
  // 操作１：山iの下からj個目を、山i2に移す
  auto operation1 = [&](int i, int j, int i2) {
    ans.emplace_back(B[i][j], i2 + 1);
    score += (int)B[i].size() + 1 - j;
    for (int k = j; k < (int)B[i].size(); k++) B[i2].push_back(B[i][k]);
    while ((int)B[i].size() > j) B[i].pop_back();
  };
  // 操作２：山iの1番上を消す
  auto operation2 = [&](int i) {
    assert(B[i].back() == now);
    ans.emplace_back(now, 0);
    now++;
    B[i].pop_back();
  };
  // 操作2ができるならできるだけやる
  auto topCheck = [&]() {
    int flag = 1;
    while (flag) {
      flag = 0;
      rep(j, M) {
        if (B[j].size() && B[j].back() == now) {
          flag = 1;
          operation2(j);
        }
      }
    }
  };
  // B[i][j]をi2列に移動できるか
  auto isPuttable = [&](int i, int j, int i2, unordered_map<int, int>& mp) {
    if (i == i2) return false;
    return B[i2].empty() || mp.count(B[i2].back()) == 0 ||
           B[i2].back() < B[i][j];
  };

  rep(i, M) {
    // 座圧
    unordered_map<int, int> mp;
    vi sorted = B[i];
    {
      sort(all(sorted));
      rep(j, sorted.size()) mp[sorted[j]] = j;
    }
    // 逆順になるように取り出す
    while (B[i].size()) {
      topCheck();
      if (B[i].empty()) break;
      // 既に残りが昇順なら取り出さなくてよい
      {
        int flag = 1;
        rep(j, B[i].size()) if (B[i][j] != sorted[sorted.size() - 1 - j]) flag =
            0;
        if (flag) {
          while (sorted.size() && B[i].back() <= sorted.back())
            sorted.pop_back();
          break;
        }
      }

      // B[i][k]より上を取り出す
      int k = (int)B[i].size() - 1;
      // 降順になっているならまとめて取る
      while (k >= 1 && B[i][k] > B[i][k - 1] && B[i][k - 1] != now) {
        // 降順に取っても置く場所に困らない時だけ取る
        int flag = 0;
        rep(i2, M) if (isPuttable(i, k - 1, i2, mp)) flag = 1;
        if (!flag) break;
        k--;
      }

      rep(j, M) {
        if (isPuttable(i, k, j, mp)) {
          operation1(i, k, j);
          break;
        }
        if (j == M - 1) {
          // 詰んだ。仕方ないので適当なところに突っ込む
          rep(j2, M) {
            if (j2 == i) continue;
            if (B[j2].size() == 1 ||
                mp.count(B[j2][(int)B[j2].size() - 2]) == 0 ||
                B[j2][(int)B[j2].size() - 2] < B[i][k]) {
              operation1(j2, (int)B[j2].size() - 1, i);
              operation1(i, (int)B[i].size() - 2, j2);
              break;
            }
            assert(j2 != M - 1);
          }
        }
      }
    }
    // 昇順に戻す
    while (sorted.size() && sorted.back() >= now) {
      int oldNow = now;
      topCheck();
      if (oldNow != now) continue;

      rep(j, M) {
        if (j != i && B[j].back() == sorted.back()) {
          int k = (int)B[j].size() - 1;
          operation1(j, k, i);
          sorted.pop_back();
          break;
        }
        if (j == M - 1) {
          debug(i, sorted, B);
        }
        assert(j != M - 1);  // どこかで見つかるはず
      }
    }
  }

  // 操作2をする
  topCheck();

  // 最適解を更新
  assert(now == 201);
  rep(i, M) assert(B[i].size() == 0);
  if (chmin(bestScore, score)) swap(bestAns, ans);
}

int main() {
  /* input */
  cin >> N >> M;
  vvi OB(M, vi(N / M));
  rep(i, M) rep(j, N / M) cin >> OB[i][j];

  vvi B(M, vi(N / M));

  B = OB;
  solve(B);
  cerr << bestScore << endl;

  out(bestAns);
}