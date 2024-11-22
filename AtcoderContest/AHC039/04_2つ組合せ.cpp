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

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

class TimeKeeper {
 private:
  chrono::high_resolution_clock::time_point start_time_;
  int64_t time_threshold_;

 public:
  // 時間制限をミリ秒単位で指定してインスタンスをつくる。
  TimeKeeper(const int64_t& time_threshold)
      : start_time_(chrono::high_resolution_clock::now()),
        time_threshold_(time_threshold) {}

  // インスタンス生成した時から指定した時間制限を超過したか判定する。
  bool isTimeOver() const {
    auto diff = chrono::high_resolution_clock::now() - this->start_time_;
    return chrono::duration_cast<chrono::milliseconds>(diff).count() >=
           time_threshold_;
  }

  int64_t getTime() const {
    auto diff = chrono::high_resolution_clock::now() - this->start_time_;
    return chrono::duration_cast<chrono::milliseconds>(diff).count();
  }
};

int input_N;
vector<int> input_saba_X(5000), input_saba_Y(5000);
vector<int> input_iwashi_X(5000), input_iwashi_Y(5000);

map<int, vector<int>> iwashi_XY_map;
map<int, vector<int>> saba_XY_map;

void process_input() {
  cin >> input_N;
  rep(i, input_N) cin >> input_saba_X[i] >> input_saba_Y[i];
  rep(i, input_N) cin >> input_iwashi_X[i] >> input_iwashi_Y[i];
}

void init_XY_map() {
  rep(i, input_N) {
    saba_XY_map[input_saba_X[i]].emplace_back(input_saba_Y[i]);
    iwashi_XY_map[input_iwashi_X[i]].emplace_back(input_iwashi_Y[i]);
  }
  for (auto& [k, vec] : saba_XY_map) sort(all(vec));
  for (auto& [k, vec] : iwashi_XY_map) sort(all(vec));
}

class Point {
 public:
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
};

// オペレーターの定義
bool operator<(const Point& a, const Point& b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

Point operator-(const Point& a, const Point& b) {
  return Point(a.x - b.x, a.y - b.y);
}

int cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }

// 多角形の面積を計算（符号付き）
double polygonArea(const std::vector<Point>& polygon) {
  double area = 0;
  int n = polygon.size();
  for (int i = 0; i < n; ++i) {
    const Point& p1 = polygon[i];
    const Point& p2 = polygon[(i + 1) % n];
    area += (p1.x * p2.y - p2.x * p1.y);
  }
  return area / 2.0;
}

// 修正された凸包計算関数
std::vector<Point> convexHull(std::vector<Point> P) {
  int n = P.size();
  if (n <= 1) return P;  // 点が1つ以下の場合、そのまま返す
  std::vector<Point> H;
  H.reserve(2 * n);
  // 座標でソート
  std::sort(P.begin(), P.end(), [](const Point& a, const Point& b) {
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
  });
  // 下側凸包
  for (int i = 0; i < n; ++i) {
    while (H.size() >= 2 && cross(H[H.size() - 1] - H[H.size() - 2],
                                  P[i] - H[H.size() - 2]) <= 0)
      H.pop_back();
    H.push_back(P[i]);
  }
  // 上側凸包
  size_t t = H.size() + 1;
  for (int i = n - 2; i >= 0; --i) {
    while (H.size() >= t && cross(H[H.size() - 1] - H[H.size() - 2],
                                  P[i] - H[H.size() - 2]) <= 0)
      H.pop_back();
    H.push_back(P[i]);
  }
  H.pop_back();  // 最初の点を重複して追加しているので削除
  return H;
}

const int CONTAINED = 0;
const int SEPARETED = 1;
const int ADJACENT = 2;
const int INTERSECT = 3;
class Square {
 public:
  int _x1, _x2, _y1, _y2;
  int _cnt_saba, _cnt_iwashi;

  Square(int x1, int y1, int x2, int y2, int saba, int iwashi) {
    _x1 = min(x1, x2);
    _x2 = max(x1, x2);
    _y1 = min(y1, y2);
    _y2 = max(y1, y2);
    _cnt_saba = saba;
    _cnt_iwashi = iwashi;
  }

  static int check_square_reration(Square sq1, Square sq2) {
    // 内包判定
    if (sq2._x1 <= sq1._x1 && sq1._x2 <= sq2._x2 && sq2._y1 <= sq1._y1 &&
        sq1._y2 <= sq2._y2) {
      return CONTAINED;
    }
    if (sq1._x1 <= sq2._x1 && sq2._x2 <= sq1._x2 && sq1._y1 <= sq2._y1 &&
        sq2._y2 <= sq1._y2) {
      return CONTAINED;
    }

    // 交差判定
    if (sq1._x1 < sq2._x2 && sq2._x1 < sq1._x2 && sq1._y1 < sq2._y2 &&
        sq2._y1 < sq1._y2) {
      return INTERSECT;
    }

    // 隣接判定
    if ((sq1._x1 == sq2._x2 || sq2._x1 == sq1._x2) &&
        (sq1._y1 < sq2._y2 && sq2._y1 < sq1._y2)) {
      return ADJACENT;
    }
    if ((sq1._y1 == sq2._y2 || sq2._y1 == sq1._y2) &&
        (sq1._x1 < sq2._x2 && sq2._x1 < sq1._x2)) {
      return ADJACENT;
    }

    // 離れている判定
    return SEPARETED;
  }
  vector<Point> getCorners() const {
    return {Point(_x1, _y1), Point(_x1, _y2), Point(_x2, _y1), Point(_x2, _y2)};
  }

  void print() const {
    // デバッグ用出力
    debug(_x1, _x2, _y1, _y2, _cnt_saba, _cnt_iwashi);
  }

  // スコア昇順ソート
  bool operator<(const Square& another) const {
    return _cnt_saba - _cnt_iwashi < another._cnt_saba - another._cnt_iwashi;
  }
  bool operator>(const Square& another) const {
    return _cnt_saba - _cnt_iwashi > another._cnt_saba - another._cnt_iwashi;
  }
};

// 交差した長方形の外周を時計回りに出力する
std::vector<Point> getClockwiseOutline(const Square& sq1, const Square& sq2) {
  std::set<Point> points;

  // 両方の長方形の頂点をセットに追加
  for (const auto& corner : sq1.getCorners()) points.insert(corner);
  for (const auto& corner : sq2.getCorners()) points.insert(corner);

  // 交差部分の座標も追加
  int ix1 = std::max(sq1._x1, sq2._x1);
  int iy1 = std::max(sq1._y1, sq2._y1);
  int ix2 = std::min(sq1._x2, sq2._x2);
  int iy2 = std::min(sq1._y2, sq2._y2);

  if (ix1 < ix2 && iy1 < iy2) {  // 交差領域が存在する場合のみ
    points.insert(Point(ix1, iy1));
    points.insert(Point(ix1, iy2));
    points.insert(Point(ix2, iy1));
    points.insert(Point(ix2, iy2));
  }

  // 点をベクトルに変換
  std::vector<Point> pointVec(points.begin(), points.end());

  // 凸包を計算
  auto hull = convexHull(pointVec);

  // 時計回りにするために面積をチェック
  double area = polygonArea(hull);
  if (area > 0) {
    // 反時計回りなので逆順にする
    std::reverse(hull.begin(), hull.end());
  }

  return hull;
}

int count_saba(int x1, int x2, int y1, int y2) {
  int saba = 0;
  auto saba_it = saba_XY_map.lower_bound(x1);
  while (saba_it != saba_XY_map.end()) {
    if (saba_it->first > x2) break;
    for (auto v : saba_it->second) {
      if (y2 < v) break;
      if (y1 <= v) saba++;
    }
    saba_it++;
  }
  return saba;
}
int count_iwashi(int x1, int x2, int y1, int y2) {
  int iwashi = 0;
  auto iwashi_it = iwashi_XY_map.lower_bound(x1);
  while (iwashi_it != iwashi_XY_map.end()) {
    if (iwashi_it->first > x2) break;
    for (auto v : iwashi_it->second) {
      if (y2 < v) break;
      if (y1 <= v) iwashi++;
    }
    iwashi_it++;
  }
  return iwashi;
}

int main() {
  const int64_t time_threshold = 800;
  const int64_t time_threshold_2 = 800;
  auto time_keeper = TimeKeeper(time_threshold);
  /* input */
  process_input();
  init_XY_map();

  int saba_min_x = 1e9, saba_max_x = 0, saba_min_y = 1e9, saba_max_y = 0;
  rep(i, input_N) {
    chmax(saba_max_x, input_saba_X[i]);
    chmax(saba_max_y, input_saba_Y[i]);
    chmin(saba_min_x, input_saba_X[i]);
    chmin(saba_min_y, input_saba_Y[i]);
  }
  int saba_range_x = saba_max_x - saba_min_x;
  int saba_range_y = saba_max_y - saba_min_y;

  /* solve */
  const int pq_size = 10;
  using P = Square;
  priority_queue<P, vector<P>, greater<P>> pq;

  int loop_count = 0;

  while (!time_keeper.isTimeOver()) {
    loop_count++;
    int x1 = randXor() % saba_range_x + saba_min_x;
    int x2 = randXor() % saba_range_x + saba_min_x;
    int y1 = randXor() % saba_range_y + saba_min_y;
    int y2 = randXor() % saba_range_y + saba_min_y;
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    //

    int saba = count_saba(x1, x2, y1, y2);
    int iwashi = count_iwashi(x1, x2, y1, y2);

    // 更新
    if (pq.size() < pq_size) {
      pq.emplace(Square(x1, y1, x2, y2, saba, iwashi));
    } else {
      int score = saba - iwashi;
      int score2 = pq.top()._cnt_saba - pq.top()._cnt_iwashi;
      if (score > score2) {
        pq.pop();
        pq.emplace(Square(x1, y1, x2, y2, saba, iwashi));
      }
    }
  }

  vector<Square> square_vec;

  while (pq.size()) {
    square_vec.emplace_back(pq.top());
    pq.top().print();
    pq.pop();
  }
  reverse(all(square_vec));
  int max_score = square_vec[0]._cnt_saba - square_vec[0]._cnt_iwashi;
  int best_x1 = square_vec[0]._x1;
  int best_x2 = square_vec[0]._x2;
  int best_y1 = square_vec[0]._y1;
  int best_y2 = square_vec[0]._y2;
  debug(loop_count, max_score);

  auto time_keeper_2 = TimeKeeper(time_threshold_2);
  int loop_count_2 = 0;
  while (!time_keeper_2.isTimeOver()) {
    loop_count_2++;
    //
    int x1 = best_x1;
    int x2 = best_x2;
    int y1 = best_y1;
    int y2 = best_y2;
    //
    int ty = randXor() % 4;
    int len = randXor() % 2000 - 1000;
    if (ty == 0) {
      x1 += len;
      chmax(x1, saba_min_x);
      chmin(x1, x2);
    } else if (ty == 1) {
      x2 += len;
      chmax(x2, x1);
      chmin(x2, saba_max_x);
    } else if (ty == 2) {
      y1 += len;
      chmax(y1, saba_min_y);
      chmin(y1, y2);
    } else if (ty == 3) {
      y2 += len;
      chmax(y2, y1);
      chmin(y2, saba_max_y);
    }

    if (chmax(max_score,
              count_saba(x1, x2, y1, y2) - count_iwashi(x1, x2, y1, y2))) {
      best_x1 = x1;
      best_x2 = x2;
      best_y1 = y1;
      best_y2 = y2;
    }
  }
  debug(loop_count_2, max_score);

  for (int i = 1; i < (int)square_vec.size(); i++) {
    if (Square::check_square_reration(square_vec[0], square_vec[i]) ==
        INTERSECT) {
      debug(i);
      auto outline = getClockwiseOutline(square_vec[0], square_vec[i]);
      out(outline.size());
      for (auto p : outline) {
        out(p.x, p.y);
      }

      break;
    }
  }

  /* output */
  // out(4);
  // out(best_x1, best_y1);
  // out(best_x2, best_y1);
  // out(best_x2, best_y2);
  // out(best_x1, best_y2);
}