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
 * 021.プロファイリングできるようにファンクションを外に出す
 *
 */

int N, M;

int bestScore = 1000000;
vpii bestAns;

/* functions */
// 操作１：山iの下からj個目を、山i2に移す
void operation1(int i, int j, int i2, vvi& B, vpii& ans, int& score) {
  ans.emplace_back(B[i][j], i2 + 1);
  score += (int)B[i].size() + 1 - j;
  for (int k = j; k < (int)B[i].size(); k++) B[i2].push_back(B[i][k]);
  while ((int)B[i].size() > j) B[i].pop_back();
}
// 操作２：山iの1番上を消す
void operation2(int i, vvi& B, vpii& ans, int& now) {
  assert(B[i].back() == now);
  ans.emplace_back(now, 0);
  now++;
  B[i].pop_back();
}
// 操作2ができるならできるだけやる
void topCheck(vvi& B, vpii& ans, int& now) {
  int flag = 1;
  while (flag) {
    flag = 0;
    rep(i, M) {
      if (B[i].size() && B[i].back() == now) {
        flag = 1;
        operation2(i, B, ans, now);
      }
    }
  }
}

// B[i][j]をi2列に移動できるか
bool isPuttable(int i, int j, int i2, unordered_map<int, int>& mp, vvi& B) {
  if (i == i2) return false;
  return B[i2].empty() || mp.count(B[i2].back()) == 0 || B[i2].back() < B[i][j];
}
// B[i2].back()がB[i][j]より（座圧上で）1大きいか
bool isPuttableAdjacent(int i, int j, int i2,
                        unordered_map<int, int>& adjacentMp, vvi& B) {
  if (B[i2].empty()) return false;
  if (i == i2) return false;
  return B[i2].back() == adjacentMp[B[i][j]];
}

int solve(vvi& B, vi& C, vi p) {
  int score = 0;
  vpii ans;
  int now = 1;
  set<int> sortedTowerSet;

  // B[i].back()はソート前に削除されるか
  // auto willRemove = [&](int i) {
  //   int cnt = 0, idx = -1;
  //   rep(ci, M) if (C[ci] == i) {
  //     idx = ci;
  //     break;
  //   }
  //   rep(ci, idx) for (auto v : B[C[ci]]) if (B[i].back() > v) cnt++;

  //   for (int ci = idx + 1; ci < M; ci++) {
  //     for (int j = (int)B[C[ci]].size() - 1; j >= 0; j--) {
  //       if (B[i].back() > B[C[ci]][j]) cnt++;
  //       if (j > 0 && B[C[ci]][j - 1] < B[C[ci]][j]) break;
  //     }
  //   }
  //   return cnt + now == B[i].back();
  // };

  // 列ごとにソートする
  rep(ci, M) {
    int i = C[ci];
    // 列内ソートと座圧パート
    vi sorted = B[i];
    unordered_map<int, int> mp;          // {値, 座圧後のidx}
    unordered_map<int, int> adjacentMp;  // {値, 1つ大きい値}
    {
      sort(all(sorted));
      rep(j, (int)sorted.size() - 1) adjacentMp[sorted[j]] = sorted[j + 1];
      rep(j, sorted.size()) mp[sorted[j]] = j;
    }
    vi puttedNum(M);                   // 降順に置いた個数
    unordered_map<int, int> leaderMp;  // {値, 昇順に隣接した塊の1番小さい値}
    for (auto v : B[i]) leaderMp[v] = v;  // 初期化
    unordered_set<int> poppedSet;         // 処理済み

    // 逆順になるように取り出すパート
    while (B[i].size()) {
      topCheck(B, ans, now);
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
      // if ((int)randXor() % 10 >= p[0])
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
          if (B[i][k - 1] < B[i][k]) break;
          k--;  // B[i][k]は置ける、B[i][k-1]が置けるかチェックする
        }
        if (idx != -1) {
          // この場合はsortedから消しておく必要がある
          for (int j = k; j < (int)B[i].size(); j++) poppedSet.insert(B[i][j]);
          operation1(i, k, idx, B, ans, score);
          continue;
        }
        // 1個外して置くとかどうでしょうか
        int tmp = 0;
        k = (int)B[i].size() - 1;
        while (true) {
          tmp++;
          int flag = 0;
          rep(i2, M) {
            if (!puttedNum[i2] && B[i2].size() >= 2 &&
                sortedTowerSet.count(i2) &&
                B[i2][(int)B[i2].size() - 2] > B[i][k] &&
                B[i][k] > B[i2].back()) {
              if (idx == -1 || B[idx][(int)B[idx].size() - 2] <
                                   B[i2][(int)B[i2].size() - 2]) {
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
          if (B[i][k - 1] < B[i][k]) break;

          k--;  // B[i][k]は置ける、B[i][k-1]が置けるかチェックする
        }
        // debug(tmp, i, k,k = (int)B[i].size() - 1; B);
        if (idx != -1 && B[i].size() - k >= 2) {
          // debug(B[i].size() - k, B[i][k], B[idx].back());
          // この場合はsortedから消しておく必要がある
          for (int j = k; j < (int)B[i].size(); j++) poppedSet.insert(B[i][j]);
          operation1(idx, (int)B[idx].size() - 1, i, B, ans, score);
          operation1(i, k, idx, B, ans, score);
          continue;
        }
      }

      // 昇順の塊の降順の塊を置く
      int k = (int)B[i].size() - 1;  // B[i][k]より上を取り出す
      while (k >= 1) {
        if (B[i][k - 1] == adjacentMp[B[i][k]]) {
          // debug(B[i][k], B[i][k - 1]);
          // 隣合って昇順ならまとめて取る
          leaderMp[B[i][k - 1]] = leaderMp[B[i][k]];
          k--;
        } else if (B[i][k] > B[i][k - 1] && B[i][k - 1] != now) {
          // 降順になってるならまとめて取る（置く場所に困らない時だけ取る）
          int flag = 0;
          // if ((int)randXor() % 10 >= p[1])
          rep(i2, M) if (isPuttable(i, k - 1, i2, mp, B)) flag = 1;
          if (!flag) break;
          k--;
        } else {
          break;
        }
      }
      vpii priority;
      rep(i2, M) {
        if (isPuttableAdjacent(i, k, i2, adjacentMp, B)) {
          // 優先度最高
          priority.emplace_back(1000, i2);
          rep(j, B[i2].size()) {
            if (leaderMp.count(B[i2][j]) &&
                leaderMp[B[i2][j]] == B[i2].back()) {
              leaderMp[B[i2][j]] = leaderMp[B[i][k]];
            }
          }
          break;
        } else if (isPuttable(i, k, i2, mp, B)) {
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
        operation1(i, k, i2, B, ans, score);
      } else {
        // 詰んだ。仕方ないので適当なところに突っ込む
        rep(i3, M) {
          if (i3 == i) continue;
          if (B[i3].size() == 1 ||
              mp.count(B[i3][(int)B[i3].size() - 2]) == 0 ||
              B[i3][(int)B[i3].size() - 2] < B[i][k]) {
            operation1(i3, (int)B[i3].size() - 1, i, B, ans, score);
            operation1(i, (int)B[i].size() - 2, i3, B, ans, score);
            puttedNum[i3]++;
            break;
          }
          assert(i3 != M - 1);
        }
      }
    }

    // 昇順になるよう戻すパート
    while (sorted.size() && sorted.back() >= now) {
      if (poppedSet.count(sorted.back())) {
        sorted.pop_back();
        continue;
      }
      int oldNow = now;
      topCheck(B, ans, now);
      if (oldNow != now) continue;

      // リーダーの更新
      rep(i2, M) {
        for (int j = (int)B[i2].size() - 1; j >= 0; j--) {
          if (leaderMp.count(B[i2][j]) == 0) break;
          if (leaderMp[B[i2][j]] > now) break;
          if (j == (int)B[i2].size() - 1) {
            leaderMp[B[i2][j]] = B[i2][j];
          } else {
            leaderMp[B[i2][j]] = leaderMp[B[i2][j + 1]];
          }
        }
      }

      rep(i2, M) {
        int k = (int)B[i2].size() - 1;
        if (i2 != i && B[i2].size() &&
            B[i2].back() == leaderMp[sorted.back()]) {
          if (sortedTowerSet.count(i2)) {
            while (k >= 1 && B[i2][k - 1] == adjacentMp[B[i2][k]])
              k--;  // 隣接昇順
            // 戻さなくていい山なら戻さない
            if (k == 0 ||
                (mp.count(B[i2][k - 1]) == 0 && B[i2][k - 1] > B[i2][k])) {
              sorted.pop_back();
              for (int j = k; j < (int)B[i2].size(); j++)
                poppedSet.insert(B[i2][j]);
              break;
            } else {
              // 戻す. 下を巻き混む必要がない
              for (int j = k; j < (int)B[i2].size(); j++)
                poppedSet.insert(B[i2][j]);
              operation1(i2, k, i, B, ans, score);
              sorted.pop_back();
              break;
            }
          } else {
            // 昇順に下を巻き込めるなら巻き込んでから戻す
            k = (int)B[i2].size() - 1;
            while (k != 0 && B[i2][k - 1] > B[i2][k] &&
                   (B[i].empty() || B[i2][k - 1] < B[i].back()))
              k--;
            for (int j = k; j < (int)B[i2].size(); j++)
              poppedSet.insert(B[i2][j]);
            operation1(i2, k, i, B, ans, score);
            topCheck(B, ans, now);
            // assert(poppedSet.count(sorted.back()));
            sorted.pop_back();

            // 間に挟めるなら挟んじゃう（最適でないこともある）
            int idx = 0;
            while (true) {
              idx = -1;
              int count = 0;
              int bottomNum = 0;
              // if ((int)randXor() % 10 < p[2]) break;
              rep(i3, M) {
                if (B[i3].empty()) continue;
                if (sortedTowerSet.count(i3)) continue;
                // if (willRemove(i3)) continue;
                if ((sorted.empty() || B[i3].back() > sorted.back()) &&
                    (B[i].empty() || B[i].back() > B[i3].back())) {
                  k = (int)B[i3].size() - 1;
                  // 昇順に下を巻き込めるなら巻き込む
                  while (k != 0 && B[i3][k - 1] > B[i3][k] &&
                         (B[i].empty() || B[i3][k - 1] < B[i].back()))
                    k--;

                  if (count < (int)B[i3].size() - k) {
                    idx = i3;
                    count = (int)B[i3].size() - k;
                    bottomNum = B[i3][k];
                  } else if (count == (int)B[i3].size() - k &&
                             bottomNum < B[i3][k]) {
                    idx = i3;
                    count = (int)B[i3].size() - k;
                    bottomNum = B[i3][k];
                  }
                }
              }
              if (idx == -1) break;
              k = (int)B[idx].size() - count;
              operation1(idx, k, i, B, ans, score);
              topCheck(B, ans, now);
            }
            break;
          }
        }
        // if (i2 == M - 1) debug(B, adjacentMp, leaderMp, poppedSet, sorted);
        assert(i2 != M - 1);  // どこかで見つかるはず
      }
    }
    sortedTowerSet.insert(i);
  }

  // 操作2をする
  topCheck(B, ans, now);

  // 最適解を更新
  if (now != 201) debug(now, B);
  assert(now == 201);
  rep(i, M) assert(B[i].size() == 0);
  if (chmin(bestScore, score)) swap(bestAns, ans);
  return score;
}

int main() {
  /* input */
  cin >> N >> M;
  vvi OB(M, vi(N / M));
  rep(i, M) rep(j, N / M) cin >> OB[i][j];
  vi p(5, 5);  // 乱択用の確率

  vvi B = OB;

  // どの順でタワーをソートするか。初期値は最小値昇順
  vi C;
  {
    vi rev(N);
    rep(i, M) rep(j, N / M) rev[B[i][j] - 1] = i;
    set<int> st;
    rep(i, N) if (st.count(rev[i]) == 0) st.insert(rev[i]), C.push_back(rev[i]);
  }
  int prevScore = solve(B, C, p);
  // 初期解

  // 時間計測
  auto startClock = system_clock::now();
  // const static double START_TEMP = 4000;  // 開始時の温度
  // const static double END_TEMP = 100;     // 終了時の温度
  const static double END_TIME = 20.95;  // 終了時間（秒）
  double time = 0.0;                     // 経過時間（秒）
  int loopCount = 0;
  do {
    // if (loopCount % 1000 == 0) {
    //   debug(bestScore, p, C);
    // }
    loopCount++;
    // 進捗。開始時が0.0で、終了時が1.0
    // const double progressRatio = time / END_TIME;
    // const double temp = START_TEMP + (END_TEMP - START_TEMP) *
    // progressRatio;

    // int kind = randXor() % 4;
    // int pprev = -1;

    int i = randXor() % M, j = randXor() % M;
    swap(C[i], C[j]);
    if (i == j) i = randXor() % M;
    if (i == j) i = randXor() % M;
    // if (kind == 3) {
    //   // swapする
    // } else {
    //   pprev = p[kind];
    //   if (p[kind] == 0 || (p[kind] != 10 && randXor() % 2)) {
    //     p[kind]++;
    //   } else {
    //     p[kind]--;
    //   }
    // }

    B = OB;
    int score = solve(B, C, p);

    if (prevScore < score) {
      // ok
    } else {
      // 戻す
      if (randXor() % 5 == 0) {
        swap(C[i], C[j]);
        // if (kind == 3) {
        // } else {
        //   p[kind] = pprev;
        // }
      }
    }
    prevScore = score;

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