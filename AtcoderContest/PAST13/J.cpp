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

// 点とベクトル
class Point {
 public:
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}

  /* --- メンバ関数 --- */
  // ベクトルの大きさ
  double norm() { return x * x + y * y; }
  double abs() { return sqrt(norm()); }

  /* --- クラス関数 --- */
  // ベクトルの大きさ
  static double norm(Point p) { return p.x * p.x + p.y * p.y; }
  static double abs(Point p) { return sqrt(norm(p)); }
  // ベクトルの内積
  static double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
  // ベクトルの外積
  static double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

  // ベクトルの直行判定
  static bool isOrthogonal(Point p1, Point p2) {
    // Θが90度か-90度 ⇔ cosΘが0なので内積を利用
    return equal(dot(p1, p2), 0.0);
  }
  // 2直線を通る4点の直行判定
  static bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
    return isOrthogonal(a1 - a2, b1 - b2);
  }
  // ベクトルの平行判定
  static bool isParallel(Point p1, Point p2) {
    // Θが0度か180度の時 ⇔ sinΘが0なので外積を利用
    return equal(cross(p1, p2), 0.0);
  }
  // 2直線を通る4点の平行判定
  static bool isParallel(Point a1, Point a2, Point b1, Point b2) {
    return isParallel(a1 - a2, b1 - b2);
  }
  // 射影
  static Point project(Point p1, Point p2, Point p) {
    // 射影とは、点pからベクトル(p2-p1)に垂線を引いた時の交点x
    Point base = p2 - p1;
    // rは比率。|x-p1|/|p2-p1|。詳しくは螺旋本16.3
    double r = dot(p - p1, base) / base.norm();
    return p1 + base * r;
  }
  // 反射
  static Point reflect(Point p1, Point p2, Point p) {
    // 反射とは、ベクトル(p2-p1)を対称軸とした点pと線対称の点x
    // pからp1p2への射影へのベクトルを2倍すればいい
    return p + (project(p1, p2, p) - p) * 2.0;
  }
  // 点と点の距離
  static double getDistance(Point a, Point b) { return abs(a - b); }
  // 点pと直線abの距離
  static double getDistanceLP(Point a, Point b, Point p) {
    return abs(cross(b - a, p - a) / abs(b - a));
  }
  // 点pと線分abの距離(Sはsegment)
  static double getDistanceSP(Point a, Point b, Point p) {
    // 線分と端点-点pの為す角が90度を超えたら端点と点の距離を返す
    if (dot(b - a, p - a) < 0.0) return abs(p - a);
    if (dot(a - b, p - b) < 0.0) return abs(p - b);
    // そうでなければ線との距離を返す
    return getDistanceLP(a, b, p);
  }
  // 線分abと線分cdの距離
  static double getDistanceSS(Point a, Point b, Point c, Point d) {
    // 線分が交差してたら距離0
    if (intersect(a, b, c, d)) return 0.0;
    // 線分abと点c, 線分abと点d, 線分cdと点a, 線分cdと点bのmin
    return min(min(getDistanceSP(a, b, c), getDistanceSP(a, b, d)),
               min(getDistanceSP(c, d, a), getDistanceSP(c, d, b)));
  }
  // ベクトルabとacの位置判定（Counter-ClockWise)
  static int ccw(Point a, Point b, Point c) {
    const int COUNTER_CLOCKWISE = 1;  // a, b, cが半時計回り
    const int CLOCKWISE = -1;         // a, b, cが時計回り
    const int ONLINE_BACK = 2;        // c, a, bの順で同一直線上
    const int ONLINE_FRONT = -2;      // a, b, cの順で同一直線上
    const int ON_SEGMENT = 0;         // a, c, bの順で直線上
    Point ab = b - a;
    Point ac = c - a;
    if (cross(ab, ac) > EPS) return COUNTER_CLOCKWISE;
    if (cross(ab, ac) < -EPS) return CLOCKWISE;
    if (dot(ab, ac) < -EPS) return ONLINE_BACK;
    if (ab.norm() < ac.norm()) return ONLINE_FRONT;
    return ON_SEGMENT;
  }

  // 線分abと線分cdの交差判定
  static bool intersect(Point a, Point b, Point c, Point d) {
    // 点c,dが線分abの逆側（含線上)かつ点a,bが線分cdの逆側（含線上)なら交差
    debug(ccw(a, b, c), ccw(a, b, d), ccw(c, d, a), ccw(c, d, b));
    return (ccw(a, b, c) * ccw(a, b, d) <= 0 &&
            ccw(c, d, a) * ccw(c, d, b) <= 0);
  }
  // 線分の交点
  static Point getCrossPoint(Point a1, Point a2, Point b1, Point b2) {
    // 外積と図形的考察によって交点を境とした比率を求めている（螺旋本16.8）
    Point base = b2 - b1;
    double d1 = abs(cross(base, a1 - b1));
    double d2 = abs(cross(base, a2 - b1));
    double t = d1 / (d1 + d2);
    return a1 + (a2 - a1) * t;
  }

  // 線分の回転（ベクトルabを、座標aを中心に回転させる）ラジアン
  static Point rotate(Point a, Point b, double rad) {
    double xx = b.x - a.x;
    double yy = b.y - a.y;
    double px = xx * cos(rad) - yy * sin(rad) + a.x;
    double py = xx * sin(rad) + yy * cos(rad) + a.y;
    return Point(px, py);
  }
  // 線分の90度左回転（ベクトルabを、座標aを中心に回転させる）
  static Point rotate90(Point a, Point b) {
    double xx = b.x - a.x;
    double yy = b.y - a.y;
    double px = -yy + a.x;
    double py = xx + a.y;
    return Point(px, py);
  }

  /* --- 演算子のオーバーロード --- */
  // ベクトルの基本演算
  Point operator+(Point p) { return Point(x + p.x, y + p.y); }
  Point operator-(Point p) { return Point(x - p.x, y - p.y); }
  Point operator*(double k) { return Point(x * k, y * k); }
  Point operator/(double k) { return Point(x / k, y / k); }

  // 点の不等式（ここではx座標の大きさ。x座標が等しければy座標の大きさ）
  bool operator<(const Point& p) const { return x != p.x ? x < p.x : y < p.y; }
  // 点の等式
  bool operator==(const Point& p) const {
    // fabsは小数点用の絶対値計算
    // EPSはマクロで定義した1e-10。小数点の誤差を考慮
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};
typedef Point Vector;

struct Solver {
  void solve() {
    /* input */
    INT(N, K);
    INT(xs, ys, xt, yt);
    vi P(N), Q(N), R(N), W(N);
    rep(i, N) cin >> P[i] >> Q[i] >> R[i] >> W[i];

    /* solve */
    // 交差判定
    Point s(xs, ys);
    Point t(xt, yt);
    vi ws;
    rep(i, N) {
      double A = P[i];
      double B = Q[i];
      double C = R[i];
      // 通る点 TODO AかBが0の場合
      int flag = 0;
      if (A == 0) {
        double CB = C / B;
        if (ys == CB || yt == CB || (ys > CB && yt < CB) ||
            (ys < CB && yt > CB))
          flag = 1;
      } else if (B == 0) {
        double CA = C / A;
        if (xs == CA || xt == CA || (xs > CA && xt < CA) ||
            (xs < CA && xt > CA))
          flag = 1;
      } else {
        Point p;
        Point q;
        if (C == 0) {
          p = Point(0, 0);
          q = Point(B, A);
        } else {
          p = Point(0, C / B);
          q = Point(C / A, 0);
        }

        debug(p.x, p.y, q.x, q.y, Point::intersect(p, q, s, t));
        flag = Point::ccw(p, q, s) * Point::ccw(p, q, t) <= 0;
      }

      if (flag) {
        ws.push_back(W[i]);
      } else {
        ws.push_back(0);
      }
      debug(i, ws.back());
    }

    // 交差しないのを優先
    // 交差するなら安いのから貪欲
    sort(all(ws));
    ll ans = 0;
    rep(i, K) ans += ws[i];
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