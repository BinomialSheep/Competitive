#include <bits/stdc++.h>

using namespace std;


class Point {
  public:
    double x;
    double y;
    Point(double a, double b){
      this->x = a;
      this->y = b;
    }
};

double th = M_PI * 60.0 / 180.0; // 度からラジアンに変換

queue<Point> pointQue;

void kochCurve(int n, int dipth, Point p1, Point p2){
  // 再帰の深さがnに達したら終わり
  if(n == dipth) return;

  // 与えられた線分(p1, p2)を3等分する
  Point s((2*p1.x+p2.x)/3, (2*p1.y + p2.y)/3);
  Point t((p1.x+2*p2.x)/3, (p1.y + 2*p2.y)/3);

  // 線分を3等分する2点s, tを頂点とする正三角形(s, u, t)を作成する
  double ux = (t.x - s.x) * cos(th) - (t.y - s.y) * sin(th) + s.x;
  double uy = (t.x - s.x) * sin(th) + (t.y - s.y) * cos(th) + s.y;
  Point u(ux, uy);

  // 線分(p1,s), (s,u), (u, t), (t, p2)に対して再帰的に同じ操作を繰り返す
  kochCurve(n, dipth+1, p1, s);
  pointQue.push(s);
  kochCurve(n, dipth+1, s, u);
  pointQue.push(u);
  kochCurve(n, dipth+1, u, t);
  pointQue.push(t);
  kochCurve(n, dipth+1, t, p2);
}



int main() {
  int n;
  scanf("%d", &n);

  Point p1(0, 0);
  Point p2(100, 0);

  pointQue.push(p1);
  kochCurve(n, 0, p1, p2);
  pointQue.push(p2);

  while(!pointQue.empty()){
    Point p = pointQue.front();
    pointQue.pop();
    printf("%f %f\n", p.x, p.y);
  }


  return 0;
}