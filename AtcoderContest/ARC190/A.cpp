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

void hoyo(int N, int M, vi L, vi R) {
  vector<Interval> intervals(M);
  rep(i, M) {
    intervals[i].L = L[i] + 1;
    intervals[i].R = R[i] + 1;
    intervals[i].idx = i;  // 後で出力時にどの操作を選んだかを復元するため
  }

  // まずは 1 区間で [1..N] を覆えるかチェック
  {
    // L=1, R=N の区間があれば、それを操作1、他全部操作0でOK
    for (int i = 0; i < M; i++) {
      if (intervals[i].L == 1 && intervals[i].R == N) {
        // 出力
        cout << 1 << "\n";  // コスト1
        // i番目の操作を1に、他を0に
        // 順番は入力順に合わせる必要があるので、配列を用意
        vector<int> ans(M, 0);
        ans[i] = 1;
        for (int j = 0; j < M; j++) {
          cout << ans[j];
          if (j + 1 < M) cout << " ";
        }
        cout << "\n";
        return;
      }
    }
  }

  // ここからコスト2 で実現できるかのチェックをする
  // どのペアが使えるか分かったら、実際にどちらを操作1・2に割り当てるかを決めて出力

  //=======================
  // (例1) A ∪ B = [1..N] の判定 (両方操作1)
  //=======================
  {
    // 「L=1 で最大の R を持つ区間」をまず探す (それを A とする)
    // それがカバーする部分の右端を Rmax として、
    // 「L <= Rmax+1 でかつ R=N の区間」があれば 2区間で [1..N] を覆える
    int bestIdx = -1;
    int maxR = -1;
    for (int i = 0; i < M; i++) {
      if (intervals[i].L == 1 && intervals[i].R > maxR) {
        maxR = intervals[i].R;
        bestIdx = i;
      }
    }
    if (bestIdx != -1) {
      // A: intervals[bestIdx] が [1..maxR] を覆う
      // ここで maxR が N に達してたら既に上で検出されているはずなので、
      // ここでは maxR < N のはず
      // 次に、L <= maxR+1 かつ R = N の区間 B を探す
      for (int j = 0; j < M; j++) {
        if (j == bestIdx) continue;
        if (intervals[j].L <= maxR + 1 && intervals[j].R == N) {
          // 見つかった -> コスト2 両方操作1
          cout << 2 << "\n";
          vector<int> ans(M, 0);
          ans[bestIdx] = 1;  // 操作1
          ans[j] = 1;        // 操作1
          for (int k = 0; k < M; k++) {
            cout << ans[k];
            if (k + 1 < M) cout << " ";
          }
          cout << "\n";
          return;
        }
      }
    }
  }

  //=======================
  // (例2) A ∩ B = ∅ の判定 (両方操作2)
  //=======================
  //  区間が重ならなければ、補集合同士の和集合は [1..N] となる
  {
    // R が小さい順にソートし、走査しながら「後ろに L が自分の R
    // より大きい区間」が存在するかを探す 例として実装
    auto intervals2 = intervals;
    sort(intervals2.begin(), intervals2.end(), [](auto& a, auto& b) {
      return a.R < b.R;  // R 昇順
    });
    // suffix の中で一番小さいL を管理して、「その L > 今の
    // R」になれば交わらない という探し方をする
    vector<int> suffixMinL(M + 1, INT_MAX);
    for (int i = M - 1; i >= 0; i--) {
      suffixMinL[i] = min(suffixMinL[i + 1], intervals2[i].L);
    }
    for (int i = 0; i < M - 1; i++) {
      int curR = intervals2[i].R;
      // 後ろの区間の中で一番小さい L
      int candidateL = suffixMinL[i + 1];
      if (candidateL > curR) {
        // 見つかった
        // intervals2[i] と交わらない区間がどこかにある
        // まずは具体的に、その区間を線形に探してもいいし、
        // 二分探索で見つけても良い（ここでは線形で書いてしまう）
        for (int j = i + 1; j < M; j++) {
          if (intervals2[j].L > curR) {
            // i, j が交わらないペア
            // コスト2, 両方操作2
            cout << 2 << "\n";
            // 出力用に整形
            vector<int> ans(M, 0);
            ans[intervals2[i].idx] = 2;
            ans[intervals2[j].idx] = 2;
            for (int k = 0; k < M; k++) {
              cout << ans[k];
              if (k + 1 < M) cout << " ";
            }
            cout << "\n";
            return;
          }
        }
      }
    }
  }

  //=======================
  // (例3) 包含関係の判定 (A ⊂ B など)
  //=======================
  {
    // A ⊂ B なら A ∪ B^c = [1..N] (A 操作1, B 操作2) となる
    // A ⊂ B : L_B <= L_A かつ R_A <= R_B
    // ここでは「L 昇順, L が同じなら R 降順」にソートし、
    // 走査しながら "今まで見た中で R が最大のもの"
    // を管理すれば、それが包含元候補になる
    auto intervals2 = intervals;
    sort(intervals2.begin(), intervals2.end(), [](auto& a, auto& b) {
      if (a.L == b.L) return a.R > b.R;  // L 同じなら R 大きい順
      return a.L < b.L;                  // L 昇順
    });
    int maxR = -1;
    int maxR_idx = -1;  // R 最大だった区間の元の idx
    for (int i = 0; i < M; i++) {
      int curL = intervals2[i].L;
      int curR = intervals2[i].R;
      int curIdx = intervals2[i].idx;
      // 今見ている区間が、過去最大Rを持つ区間に含まれていないか？をチェック
      //   過去最大区間: Lx <= curL (確実; ソート順で先に出る方が L は小さい or
      //   同じ)
      //                 Rx >= curR ?  なら含む
      if (maxR >= curR) {
        // つまり intervals2[i].区間 は intervals2[ maxR_idx ]
        // の区間に含まれている → 包含元を B, 包含される方を A とすれば B^c + A
        // = [1..N] が成り立つ
        //   (B^c は操作2, A は操作1)
        cout << 2 << "\n";
        vector<int> ans(M, 0);
        // B^c = 操作2, A = 操作1
        ans[maxR_idx] = 2;  // B
        ans[curIdx] = 1;    // A
        for (int k = 0; k < M; k++) {
          cout << ans[k];
          if (k + 1 < M) cout << " ";
        }
        cout << "\n";
        return;
      }
      // maxR を更新
      if (curR > maxR) {
        maxR = curR;
        maxR_idx = curIdx;
      }
    }
    // 今度は逆に B ⊂ A も同様にすれば良いですが、
    // 実は同じソート基準で同じループをもう一回回せばOK(あるいは L逆順 など)
    // ここでは簡単のため同じのをもう一回書きます:
    // (実際には A⊂B と B⊂A の判定は同じように書けるのでまとめられます)
    // ただしソート順を変えて "R 昇順, R 同じなら L 降順" にしてチェック でもOK
  }

  // どれにも該当しない → -1
  cout << -1 << "\n";
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

    hoyo(N, M, L, R);

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