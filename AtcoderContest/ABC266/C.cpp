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
// #include <atcoder/all>
// using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

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

  /* --- 演算子のオーバーロード --- */
  // ベクトルの基本演算
  Point operator+(Point p) { return Point(x + p.x, y + p.y); }
  Point operator-(Point p) { return Point(x - p.x, y - p.y); }
  Point operator*(double k) { return Point(x * k, y * k); }
  Point operator/(double k) { return Point(x / k, y / k); }

  // 点の不等式（ここではx座標の大きさ。x座標が等しければy座標の大きさ）
  bool operator<(const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
  // 点の等式
  bool operator==(const Point &p) const {
    // fabsは小数点用の絶対値計算
    // EPSはマクロで定義した1e-10。小数点の誤差を考慮
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};
typedef Point Vector;

struct Solver {
  void solve() {
    /* input */
    vvi ps(4, vi(2));
    rep(i, 4) rep(j, 2) cin >> ps[i][j];

    /* solve */
    Point A(ps[0][0], ps[0][1]);
    Point B(ps[1][0], ps[1][1]);
    Point C(ps[2][0], ps[2][1]);
    Point D(ps[3][0], ps[3][1]);

    /* output */
    cout << (Point::intersect(A, C, B, D) ? "Yes" : "No") << endl;
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