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

/*
 * 019.降順に取り出す時、できるだけソート済みではない箇所から使う
 *
 */

int N, M;

int bestScore = 1000000;
vpii bestAns;

void solve(vvi& B, vi& C) {
  int score = 0;
  vpii ans;
  int now = 1;
  set<int> sortedTowerSet;

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
  // B[i].back()はソート前に削除されるか
  auto willRemove = [&](int i) {
    int cnt = 0, idx = -1;
    rep(ci, M) if (C[ci] == i) {
      idx = ci;
      break;
    }
    rep(ci, idx) for (auto v : B[C[ci]]) if (B[i].back() > v) cnt++;

    for (int ci = idx + 1; ci < M; ci++) {
      for (int j = (int)B[C[ci]].size() - 1; j >= 0; j--) {
        if (B[i].back() > B[C[ci]][j]) cnt++;
        if (j > 0 && B[C[ci]][j - 1] < B[C[ci]][j]) break;
      }
    }
    return cnt + now == B[i].back();
  };

  // 列ごとにソートする
  rep(ci, M) {
    int i = C[ci];
    // 座圧
    unordered_map<int, int> mp;
    vi sorted = B[i];
    {
      sort(all(sorted));
      rep(j, sorted.size()) mp[sorted[j]] = j;
    }
    // 降順に置いた個数
    vi puttedNum(M);
    // 逆順になるように取り出す
    while (B[i].size()) {
      topCheck();
      if (B[i].empty()) break;
      // 既に残りが昇順なら取り出さなくてよい
      {
        int flag = 1;
        if (B[i].size() > sorted.size()) debug(sorted, i, B);
        rep(j, B[i].size()) if (B[i][j] != sorted[(int)sorted.size() - 1 - j])
            flag = 0;
        if (flag) {
          while (sorted.size() && B[i].back() <= sorted.back())
            sorted.pop_back();
          break;
        }
      }
      // 昇順の塊をソート済みタワーの上に置けるなら置きたい（帰ってこなくてよくなるので）
      {
        int k = (int)B[i].size() - 1;
        int idx = -1;
        while (true) {
          int flag = 0;
          rep(i2, M) {
            if (!puttedNum[i2] && B[i2].size() && sortedTowerSet.count(i2) &&
                B[i2].back() > B[i][k]) {
              if (idx == -1 || B[idx].back() < B[i2].back()) {
                flag = 1;
                idx = i2;
              }
            }
          }
          if (!flag) {
            k++;  // B[i][k+1]までは置ける
            break;
          }
          if (k == 0) break;  // B[i][0]まで置ける
          k--;  // B[i][k]は置ける、B[i][k-1]が置けるかチェックする
        }

        if (idx != -1) {
          // この場合はsortedから消しておく必要がある
          unordered_set<int> st;
          for (int j = k; j < (int)B[i].size(); j++) st.insert(B[i][j]);
          if (B[idx].size()) st.insert(B[idx].back());
          vi tmp;
          for (auto v : sorted)
            if (!st.count(v)) tmp.push_back(v);
          swap(sorted, tmp);
          // debug(sorted, tmp, st, i, k, idx, B[i][k], B[idx].back());
          operation1(i, k, idx);
          continue;
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
      vpii priority;
      rep(i2, M) {
        if (isPuttable(i, k, i2, mp)) {
          if (puttedNum[i2]) {
            // 優先度１
            priority.emplace_back(B[i2].back(), i2);
          } else if (B[i2].empty()) {
            // 優先度２
            priority.emplace_back(-1, i2);
          } else {
            // 優先度３
            priority.emplace_back(-2, i2);
          }
        }
      }
      sort(all(priority));
      reverse(all(priority));

      if (priority.size()) {
        int i2 = priority[0].second;
        puttedNum[i2] += (int)B[i].size() - k;
        operation1(i, k, i2);
      } else {
        // 詰んだ。仕方ないので適当なところに突っ込む
        rep(i3, M) {
          if (i3 == i) continue;
          if (B[i3].size() == 1 ||
              mp.count(B[i3][(int)B[i3].size() - 2]) == 0 ||
              B[i3][(int)B[i3].size() - 2] < B[i][k]) {
            operation1(i3, (int)B[i3].size() - 1, i);
            operation1(i, (int)B[i].size() - 2, i3);
            puttedNum[i3]++;
            break;
          }
          assert(i3 != M - 1);
        }
      }
    }
    // 昇順に戻す
    while (sorted.size() && sorted.back() >= now) {
      int oldNow = now;
      topCheck();
      if (oldNow != now) continue;

      rep(i2, M) {
        if (i2 != i && B[i2].size() && B[i2].back() == sorted.back()) {
          int k = (int)B[i2].size() - 1;
          if (sortedTowerSet.count(i2)) {
            // 戻さなくていい山なら戻さない
            if (B[i2].size() == 1 ||
                (mp.count(B[i2][k - 1]) == 0 && B[i2][k - 1] > B[i2][k])) {
              sorted.pop_back();
              break;
            } else {
              // ソート済みなら下を巻き込む得がない
              operation1(i2, k, i);
              sorted.pop_back();
              break;
            }
          } else {
            // 昇順に下を巻き込めるなら巻き込んでから戻す
            k = (int)B[i2].size() - 1;
            while (k != 0 && B[i2][k - 1] > B[i2][k] &&
                   (B[i].empty() || B[i2][k - 1] < B[i].back()))
              k--;
            operation1(i2, k, i);
            topCheck();
            sorted.pop_back();

            // 間に挟めるなら挟んじゃう（最適でないこともある）
            int flag = 1;
            while (flag) {
              flag = 0;
              rep(i3, M) {
                if (B[i3].empty()) continue;
                if (sortedTowerSet.count(i3)) continue;
                if ((sorted.empty() || B[i3].back() > sorted.back()) &&
                    (B[i].empty() || B[i].back() > B[i3].back())) {
                  k = (int)B[i3].size() - 1;
                  // 昇順に下を巻き込めるなら巻き込む
                  while (k != 0 && B[i3][k - 1] > B[i3][k] &&
                         (B[i].empty() || B[i3][k - 1] < B[i].back()))
                    k--;
                  operation1(i3, k, i);
                  topCheck();
                  flag = 1;
                  break;
                }
              }
            }
            break;
          }
        }
        if (i2 == M - 1) debug(B, sorted);
        assert(i2 != M - 1);  // どこかで見つかるはず
      }
    }
    sortedTowerSet.insert(i);
  }

  // 操作2をする
  topCheck();

  // 最適解を更新
  if (now != 201) debug(now, B);
  assert(now == 201);
  rep(i, M) assert(B[i].size() == 0);
  if (chmin(bestScore, score)) swap(bestAns, ans);
}

int main() {
  /* input */
  cin >> N >> M;
  vvi OB(M, vi(N / M));
  rep(i, M) rep(j, N / M) cin >> OB[i][j];

  vvi B = OB;

  // どの順でタワーをソートするか。初期値は最小値昇順
  vi C;
  {
    vi rev(N);
    rep(i, M) rep(j, N / M) rev[B[i][j] - 1] = i;
    set<int> st;
    rep(i, N) if (st.count(rev[i]) == 0) st.insert(rev[i]), C.push_back(rev[i]);
  }
  // 初期解
  solve(B, C);

  // 時間計測
  auto startClock = system_clock::now();
  // const static double START_TEMP = 4000;  // 開始時の温度
  // const static double END_TEMP = 100;     // 終了時の温度
  const static double END_TIME = 1.95;  // 終了時間（秒）
  double time = 0.0;                    // 経過時間（秒）
  int loopCount;
  do {
    loopCount++;
    // 進捗。開始時が0.0で、終了時が1.0
    // const double progressRatio = time / END_TIME;
    // const double temp = START_TEMP + (END_TEMP - START_TEMP) *
    // progressRatio;

    int prevBest = bestScore;
    // swapする
    int i = randXor() % M, j = randXor() % M;
    swap(C[i], C[j]);

    B = OB;
    solve(B, C);

    if (prevBest > bestScore) {
      // ok
    } else {
      // 確率的に戻す
      if (randXor() % 5) swap(C[i], C[j]);
    }

    // 時間更新
    time =
        ((double)duration_cast<microseconds>(system_clock::now() - startClock)
             .count() *
         1e-6);
  } while (time < END_TIME);
  // debug(loopCount);

  cerr << bestScore << endl;

  out(bestAns);
}