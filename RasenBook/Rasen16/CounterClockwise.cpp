#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INTFY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

/* 幾何学的オブジェクトのまとめ */

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

  // 直行判定（Θが90度か-90度 ⇔ cosΘが0なので内積を利用）
  static bool isOrthogonal(Point p1, Point p2) {
    return equal(dot(p1, p2), 0.0);
  }
  // 直行判定（直線A, Bを通る点が2点ずつ与えられた場合）
  static bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
    return isOrthogonal(a1 - a2, b1 - b2);
  }
  // 平行判定（Θが0度か180度の時 ⇔ sinΘが0なので外積を利用）
  static bool isParallel(Point p1, Point p2) {
    return equal(cross(p1, p2), 0.0);
  }
  // 平行判定（直線A, Bを通る点が2点ずつ与えられた場合）
  static bool isParallel(Point a1, Point a2, Point b1, Point b2) {
    return isParallel(a1 - a2, b1 - b2);
  }
  // 射影（点pからベクトル(p2-p1)に垂線を引いた時の交点x）
  static Point project(Point p1, Point p2, Point p) {
    Point base = p2 - p1;
    // rは比率。|x-p1|/|p2-p1|。詳しくは螺旋本16.3
    double r = dot(p - p1, base) / base.norm();
    return p1 + base * r;
  }
  // 反射（ベクトル(p2-p1)を対称軸とした点pと線対称の点x）
  static Point reflect(Point p1, Point p2, Point p) {
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
    return (ccw(a, b, c) * ccw(a, b, d) <= 0 &&
            ccw(c, d, a) * ccw(c, d, b) <= 0);
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

//線分と直線
struct Segment {
  Point p1, p2;
  // 直行判定
  static bool isOrthogonal(Segment s1, Segment s2) {
    return equal(Point::cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
  }
  // 平行判定
  static bool isParallel(Segment s1, Segment s2) {
    return equal(Point::cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
  }
  // 射影
  static Point project(Segment s, Point p) {
    Vector base = s.p2 - s.p1;
    double r = Point::dot(p - s.p1, base) / Point::norm(base);
    return s.p1 + base * r;
  }
  // 反射
  static Point reflect(Segment s, Point p) {
    return p + (project(s, p) - p) * 2;
  }
  // 線分と点の距離
  static double getDistanceSP(Segment s, Point p) {
    return Point::getDistanceSP(s.p1, s.p2, p);
  }
  // 線分と線分の距離
  static double getDistanceSS(Segment s1, Segment s2) {
    return Point::getDistanceSS(s1.p1, s1.p2, s2.p1, s2.p2);
  }
};
typedef Segment Line;

int main() {
  int x0, y0, x1, y1;
  cin >> x0 >> y0 >> x1 >> y1;
  Point p0(x0, y0), p1(x1, y1);
  int q;
  cin >> q;
  vector<int> ans(q);

  const int COUNTER_CLOCKWISE = 1;  // a, b, cが半時計回り
  const int CLOCKWISE = -1;         // a, b, cが時計回り
  const int ONLINE_BACK = 2;        // c, a, bの順で同一直線上
  const int ONLINE_FRONT = -2;      // a, b, cの順で同一直線上
  const int ON_SEGMENT = 0;         // a, c, bの順で直線上

  rep(i, q) {
    int x2, y2;
    cin >> x2 >> y2;
    Point p2(x2, y2);

    ans[i] = Point::ccw(p0, p1, p2);
  }

  rep(i, q) {
    string output;
    if (ans[i] == COUNTER_CLOCKWISE)
      output = "COUNTER_CLOCKWISE";
    else if (ans[i] == CLOCKWISE)
      output = "CLOCKWISE";
    else if (ans[i] == ONLINE_BACK)
      output = "ONLINE_BACK";
    else if (ans[i] == ONLINE_FRONT)
      output = "ONLINE_FRONT";
    else
      output = "ON_SEGMENT";
    cout << output << endl;
  }

  return 0;
}