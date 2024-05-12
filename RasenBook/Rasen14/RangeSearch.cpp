#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

class Node {
 public:
  int location;
  int p, l, r;
  Node() {}
};

class Point {
 public:
  int id, x, y;
  Point() {}
  Point(int id, int x, int y) : id(id), x(x), y(y) {}
  bool operator<(const Point &p) const {
    return id < p.id;
  }  //　演算子のオーバーロード

  void print() {
    printf("%d\n", id);  // coutだと間に合わない
  }
};

static const int MAX = 1001000;
static const int NIL = -1;

int N;
Point P[MAX];
Node T[MAX];
int np;

bool lessX(const Point &p1, const Point &p2) { return p1.x < p2.x; }
bool lessY(const Point &p1, const Point &p2) { return p1.y < p2.y; }

int makeKDTree(int l, int r, int depth) {
  if (!(l < r)) return NIL;
  int mid = (l + r) / 2;
  int t = np++;
  // 深さに応じてX軸ソートとy軸ソートを切り替える
  // P+rは&(P[r])
  depth % 2 == 0 ? sort(P + l, P + r, lessX) : sort(P + l, P + r, lessY);
  T[t].location = mid;
  T[t].l = makeKDTree(l, mid, depth + 1);
  T[t].r = makeKDTree(mid + 1, r, depth + 1);

  return t;
}

void find(int v, int sx, int tx, int sy, int ty, int depth,
          vector<Point> &ans) {
  int x = P[T[v].location].x;
  int y = P[T[v].location].y;

  if (sx <= x && x <= tx && sy <= y && y <= ty) ans.push_back(P[T[v].location]);

  if (depth % 2 == 0) {
    if (T[v].l != NIL && sx <= x) find(T[v].l, sx, tx, sy, ty, depth + 1, ans);
    if (T[v].r != NIL && x <= tx) find(T[v].r, sx, tx, sy, ty, depth + 1, ans);
  } else {
    if (T[v].l != NIL && sy <= y) find(T[v].l, sx, tx, sy, ty, depth + 1, ans);
    if (T[v].r != NIL && y <= ty) find(T[v].r, sx, tx, sy, ty, depth + 1, ans);
  }
}

int main() {
  int N;
  scanf("%d", &N);
  int x, y;
  rep(i, N) {
    scanf("%d %d", &x, &y);
    P[i] = Point(i, x, y);
    T[i].l = T[i].r = T[i].p = NIL;
  }
  np = 0;
  int root = makeKDTree(0, N, 0);

  // rep(i, N) { cout << P[i].id << " " << P[i].x << " " << P[i].y << endl; }

  int q;
  scanf("%d", &q);
  int sxi, txi, syi, tyi;
  vector<Point> ans;
  rep(i, q) {
    scanf("%d %d %d %d", &sxi, &txi, &syi, &tyi);
    ans.clear();
    // sxi << x << txi かつ syi << y << tyi
    //を満たす点の番号を、番号の昇順に出力する
    find(root, sxi, txi, syi, tyi, 0, ans);
    sort(ans.begin(), ans.end());
    rep(j, ans.size()) ans[j].print();
    printf("\n");
  }

  return 0;
}