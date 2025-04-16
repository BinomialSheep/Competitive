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

struct Interval {
  int L, R, idx;
};

int hoyo(int N, int M, vi L, vi R) {
  vector<Interval> intervals(M);
  rep(i, M) {
    intervals[i].L = L[i] + 1;
    intervals[i].R = R[i] + 1;
    intervals[i].idx = i;  // 後で出力時にどの操作を選んだかを復元するため
  }

  // ---- Step1: コスト1で達成可能か？ ----
  //     [1..N] を覆う区間があれば OK
  {
    for (int i = 0; i < M; i++) {
      if (intervals[i].L == 1 && intervals[i].R == N) {
        // これ1回操作1にすれば全部1になる
        // 出力 (コスト=1)
        cout << 1 << "\n";
        // i番目のみ操作1, 他0
        vector<int> ans(M, 0);
        ans[i] = 1;
        for (int j = 0; j < M; j++) {
          cout << ans[j];
          if (j + 1 < M) cout << " ";
        }
        cout << "\n";
        return 0;
      }
    }
  }

  // ---- 以下コスト2でできるかを順にチェックする ----
  //    見つかれば出力して終了

  // ---- (1) A ∪ B = [1..N] (両方操作1) ----
  //  - たとえば「L=1 の区間」の中で最も R が大きいものをAとし、
  //    そこから先を最後まで覆える区間B(R=N)があればOK というチェック例。
  {
    // まず L=1 かつ R が最大のものを探す
    int bestIdx = -1;  // その区間の idx
    int maxR = -1;     // その区間の R
    for (int i = 0; i < M; i++) {
      if (intervals[i].L == 1 && intervals[i].R > maxR) {
        maxR = intervals[i].R;
        bestIdx = i;
      }
    }
    // bestIdx != -1 のとき → A = intervals[bestIdx] が [1..maxR] を覆う
    if (bestIdx != -1 && maxR < N) {
      // まだ全部は覆っていないので、後半部分 [maxR+1 .. N]
      // を覆う区間があるか確認 具体的には L <= maxR+1 かつ R = N
      // という区間があれば良い
      for (int j = 0; j < M; j++) {
        if (j == bestIdx) continue;
        if (intervals[j].L <= maxR + 1 && intervals[j].R == N) {
          // 2つの操作で [1..N] をカバーできる
          // -> 両方操作1, コスト2
          cout << 2 << "\n";
          vector<int> ans(M, 0);
          ans[bestIdx] = 1;  // 操作1
          ans[j] = 1;        // 操作1
          for (int k = 0; k < M; k++) {
            cout << ans[k];
            if (k + 1 < M) cout << " ";
          }
          cout << "\n";
          return 0;
        }
      }
    }
  }

  // ---- (2) A ∩ B = ∅ => A^c ∪ B^c = [1..N] (両方操作2) ----
  //  - 交わらない2区間があれば、その補集合の和集合は全体になる
  //  - 交わらない条件: R_A < L_B or R_B < L_A
  //  - 下の例では「R 昇順ソート」を使って「suffixの最小L」を比較
  {
    auto intervals2 = intervals;
    // R 昇順にソート
    sort(intervals2.begin(), intervals2.end(),
         [](auto& a, auto& b) { return a.R < b.R; });
    // suffixMinL[i]: intervals2[i..] の中で最小の L
    vector<int> suffixMinL(M + 1, INT_MAX);
    for (int i = M - 1; i >= 0; i--) {
      suffixMinL[i] = min(suffixMinL[i + 1], intervals2[i].L);
    }
    // 走査: intervals2[i] と交わらない区間が i+1 以降にあるか？
    for (int i = 0; i < M - 1; i++) {
      int curR = intervals2[i].R;
      // 後ろにある区間のうち最小の L
      int candidateL = suffixMinL[i + 1];
      if (candidateL > curR) {
        // すなわち intervals2[i] の R より L が大きい区間が存在する =>
        // 交わらない 実際にどれか1つその区間を探す
        for (int j = i + 1; j < M; j++) {
          if (intervals2[j].L > curR) {
            // i, j が交わらない
            // -> 両方操作2
            cout << 2 << "\n";
            vector<int> ans(M, 0);
            ans[intervals2[i].idx] = 2;
            ans[intervals2[j].idx] = 2;
            for (int k = 0; k < M; k++) {
              cout << ans[k];
              if (k + 1 < M) cout << " ";
            }
            cout << "\n";
            return 0;
          }
        }
      }
    }
  }

  // ---- (3)(4) 包含関係: A ⊂ B or B ⊂ A ----
  //      => A ∪ B^c = [1..N] あるいは B ∪ A^c = [1..N]
  //      => (片方操作1, 片方操作2) でカバー
  // ソートで「L 昇順、L 同じなら R 降順」にしてチェックする例を2回行う:
  //   - 1回目の走査で「A ⊂ B」を見つける
  //   - 2回目の走査で「B ⊂
  //   A」を見つける（ソート順変えてもよいが、ここでは2回ほぼ同じ処理）
  {
    auto intervals2 = intervals;
    // (3) A ⊂ B  → A∪B^c=[1..N]
    //     ソート: L 昇順, L 同値なら R 降順
    sort(intervals2.begin(), intervals2.end(), [](auto& a, auto& b) {
      if (a.L == b.L) return a.R > b.R;  // L同じならR大きい方を先に
      return a.L < b.L;
    });
    // maxR: これまで見た中で最大のR
    // maxR_idx: その区間のidx
    int maxR = -1;
    int maxR_idx = -1;
    for (int i = 0; i < M; i++) {
      int curL = intervals2[i].L;  // ソートにより, すでに past.L <= curL
      int curR = intervals2[i].R;
      int curIdx = intervals2[i].idx;

      // 過去に出てきた区間( maxR_idx ) のR が今の curR より大きければ
      // その過去区間は「L_past <= L_cur」(ソートによる) かつ「R_past >= curR」
      // つまり intervals2[i] が含まれている → (A ⊂ B)
      if (maxR >= curR && maxR_idx != -1) {
        // 包含元 = intervals2[ maxR_idx ]
        // 包含先 = intervals2[i]
        // => (A, B)=(含まれる区間, 包含する区間)
        // => Aを操作1, Bを操作2にして A ∪ B^c = [1..N]
        //  (A⊂B なら B^c が「A の外側」も含んで全域をカバー可能)
        cout << 2 << "\n";
        vector<int> ans(M, 0);
        // A = curIdx → 操作1
        ans[curIdx] = 1;
        // B = maxR_idx → 操作2
        ans[maxR_idx] = 2;
        for (int k = 0; k < M; k++) {
          cout << ans[k];
          if (k + 1 < M) cout << " ";
        }
        cout << "\n";
        return 0;
      }
      // maxR を更新
      if (curR > maxR) {
        maxR = curR;
        maxR_idx = curIdx;
      }
    }
  }

  {
    // (4) B ⊂ A → B∪A^c=[1..N]  (片方1,片方2)
    //   今度は R 昇順, R 同値なら L 降順 とか、あるいは
    //   L 降順のまま逆向きにたどってもいいですが、
    //   ここでは簡単のため「R 昇順, R同じならL降順」でソートし直す例
    auto intervals2 = intervals;
    sort(intervals2.begin(), intervals2.end(), [](auto& a, auto& b) {
      if (a.R == b.R) return a.L < b.L;  // R同じならLが小さい方を先
      return a.R < b.R;
    });
    // minL: これまで見た中で最小の L
    // minL_idx: その区間の idx
    // いま見ている区間(大きいR)が過去の区間(小さいR)を含むかどうか → (B ⊂ A)
    //   B: Rが小さいほう, A: Rが大きいほう
    //   R_B <= R_A （ソート上自明に Bが先）
    //   L_A <= L_B   が必要
    int minL = INT_MAX;
    int minL_idx = -1;
    for (int i = 0; i < M; i++) {
      int curR = intervals2[i].R;
      int curL = intervals2[i].L;
      int curIdx = intervals2[i].idx;

      // いま見てる区間を「A」(Rが大きい側) とみる
      // 過去に出てきた区間を「B」(Rが小さい側) とみると
      // B ⊂ A の条件: L_A <= L_B and R_B <= R_A(今のソート順でR_B <=
      // R_Aは自動OK) だから (過去の区間のL) >= (今の区間のL) ならダメ
      //          (過去の区間のL) >= L_A → Bが左にあるか同じか
      // 実際は「BのL >= AのL」 => BがAに含まれる となる
      // ここはややややこしいですが例として実装
      // minL = これまでの中で最小の L(B)
      // AのL(curL) <= BのL(minL) なら B ⊂ A(=今の)
      if (minL_idx != -1) {
        // 過去に区間がある
        if (curL <= minL) {
          // 今見ている区間(A)のL <= 過去区間(B)のL なら Bが含まれている
          // B = intervals2[minL_idx], A = intervals2[i]
          cout << 2 << "\n";
          vector<int> ans(M, 0);
          // B => 操作1, A => 操作2  (B ⊂ A  -> B∪A^c=[1..N])
          ans[intervals2[minL_idx].idx] = 1;
          ans[curIdx] = 2;
          for (int k = 0; k < M; k++) {
            cout << ans[k];
            if (k + 1 < M) cout << " ";
          }
          cout << "\n";
          return 0;
        }
      }

      // minL を更新
      if (curL < minL) {
        minL = curL;
        minL_idx = i;  // i 番目のintervals2に入ってる
      }
    }
  }

  // ---- ここまで来たらコスト2でも不可能 ----
  cout << -1 << "\n";
  return 0;
}

struct Solver {
  void solve() {
    /* input */
    INT(N, M);
    vi L(M), R(M);
    rep(i, M) cin >> L[i] >> R[i];
    rep(i, M) L[i]--, R[i]--;

    /* solve */

    auto naive = [&]() {
      int minCost = 1e9;
      vector<int> ansVec;

      auto isAll1 = [](vi vec) {
        for (auto v : vec)
          if (v == 0) return false;
        return true;
      };

      auto dfs = [&](auto rec, int idx, int cost, vi& vec, vi& opeVec) -> void {
        if (idx == M) {
          if (isAll1(vec) && chmin(minCost, cost)) {
            ansVec = opeVec;
          }
          return;
        }

        // op0
        opeVec[idx] = 0;
        rec(rec, idx + 1, cost, vec, opeVec);

        // op1
        vi vec1 = vec;
        opeVec[idx] = 1;
        rep(i, N) if (L[idx] <= i && i <= R[idx]) vec1[i] = 1;
        rec(rec, idx + 1, cost + 1, vec1, opeVec);
        // op2L
        vi vec2 = vec;
        opeVec[idx] = 2;
        rep(i, N) if (!(L[idx] <= i && i <= R[idx])) vec2[i] = 1;
        rec(rec, idx + 1, cost + 1, vec2, opeVec);
      };

      vector<int> vec(N);
      vector<int> oPeVec(M);
      dfs(dfs, 0, 0, vec, oPeVec);

      return make_pair(minCost, ansVec);
    };

    // auto p = naive();
    // debug(p);

    auto check_1 = [&]() {
      rep(i, M) {
        if (L[i] == 0 && R[i] == N - 1) return i;
      }
      return -1;
    };
    {
      int res = check_1();
      if (res != -1) {
        int K = 1;
        vector<int> ans(M);
        ans[res] = 1;
        out(K);
        out(ans);
        return;
      }
    }

    // R, 元のidx
    set<pair<int, int>> st;
    // rep(i, M) st.insert(make_pair(R[i], i));

    // Lごとに作る
    map<int, vector<pair<int, int>>> mp;
    rep(i, M) mp[L[i]].emplace_back(R[i], i);

    rep(i, M) {
      // if (L[i] == 0) mp[R[i] + 1].emplace_back(N - 1, i);
      // if (R[i] == N - 1) mp[0].emplace_back(L[i] - 1, i);
      mp[0].emplace_back(L[i] - 1, i);
      mp[R[i] + 1].emplace_back(N - 1, i);
    }

    map<int, vector<pair<int, int>>> query;
    rep(i, M) { query[L[i]].emplace_back(R[i], i); }
    rep(i, M) {
      if (L[i] == 0) query[R[i] + 1].emplace_back(N - 1, i);
      if (R[i] == N - 1) query[0].emplace_back(L[i] - 1, i);
      // query[0].emplace_back(L[i] - 1, i);
      // query[R[i] + 1].emplace_back(N - 1, i);
    }

    // debug(st, mp, query);

    pair<int, int> ansPair = make_pair(-1, -1);

    rep(left, N) {
      for (auto [r, idx] : mp[left]) {
        st.insert(make_pair(r, idx));
      }
      for (auto [r, idx] : query[left]) {
        // debug(r, idx, st);
        // L以下かつR以上かつ自分自身以外を探す
        auto it = st.lower_bound(make_pair(r, 0));
        while (it != st.end() && it->second == idx) it++;
        if (it != st.end()) {
          ansPair = make_pair(it->second, idx);
        }
      }
    }
    debug(ansPair);

    if (ansPair.first == -1) {
      // hoyo(N, M, L, R);
      if (M == 2) {
        out(-1);
        return;
      }
      vector<pair<int, int>> vec;
      vec.emplace_back(L[0], 0);
      vec.emplace_back(L[1], 1);
      vec.emplace_back(L[2], 2);
      sort(all(vec));

      vi ans(M);
      ans[vec[0].second] = 1, ans[vec[1].second] = 2, ans[vec[2].second] = 1;

      out(3);
      out(ans);
      return;
    }

    vector<int> ans(M);
    int ok = 0;

    auto f = [&](int op, int l, int r, vi& vec) {
      if (op == 1) {
        rep(i, N) if (l <= i && i <= r) vec[i] = 1;
      } else {
        rep(i, N) if (!(l <= i && i <= r)) vec[i] = 1;
      }
    };
    auto g = [&](vi& vec) {
      for (auto v : vec)
        if (v == 0) return false;
      return true;
    };

    for (int i = 1; i <= 2; i++) {
      for (int j = 1; j <= 2; j++) {
        vi vec(N);
        f(i, L[ansPair.first], R[ansPair.first], vec);
        f(j, L[ansPair.second], R[ansPair.second], vec);

        debug(i, j, vec);

        if (g(vec)) {
          ok = 1;
          ans[ansPair.first] = i;
          ans[ansPair.second] = j;
        }

        if (ok) break;
      }
      if (ok) break;
    }
    if (!ok) {
      assert(false);
    }
    if (!ok) {
      out(-1);
      return;
    }

    out(2);
    out(ans);

    /* output */
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