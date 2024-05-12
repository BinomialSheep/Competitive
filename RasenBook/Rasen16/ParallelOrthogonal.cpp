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

// 点とベクトル
class Point {
 public:
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  // ベクトルの基本演算
  Point operator+(Point &p) { return Point(x + p.x, y + p.y); }
  Point operator-(Point &p) { return Point(x - p.x, y - p.y); }
  Point operator*(double k) { return Point(x * k, y * k); }
  Point operator/(double k) { return Point(x / k, y / k); }
  // ベクトルの大きさ
  double norm() { return x * x + y * y; }
  double abs() { return sqrt(norm()); }
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

  // 点の不等式（ここではx座標の大きさ。x座標が等しければy座標の大きさ）
  bool operator<(const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
  // 点の等式
  bool operator==(const Point &p) const {
    // fabsは小数点用の絶対値計算
    // EPSはマクロで定義した1e-10。小数点の誤差を考慮
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};
//線分と直線
struct Segment {
  Point p1, p2;

  // 直行判定
  bool isOrthogonal(Segment s1, Segment s2) {
    return equal(Point::cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
  }

  // 平行判定
  bool isParallel(Segment s1, Segment s2) {
    return equal(Point::cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
  }
};

int main() {
  int q;
  cin >> q;
  int xi0, yi0, xi1, yi1, xi2, yi2, xi3, yi3;
  vector<int> ans(q);
  rep(i, q) {
    cin >> xi0 >> yi0 >> xi1 >> yi1 >> xi2 >> yi2 >> xi3 >> yi3;
    Point p0(xi0, yi0);
    Point p1(xi1, yi1);
    Point p2(xi2, yi2);
    Point p3(xi3, yi3);

    if (Point::isParallel(p0, p1, p2, p3)) {
      ans[i] = 2;
    } else if (Point::isOrthogonal(p0, p1, p2, p3)) {
      ans[i] = 1;
    } else {
      ans[i] = 0;
    }
  }

  rep(i, q) cout << ans[i] << endl;

  return 0;
}