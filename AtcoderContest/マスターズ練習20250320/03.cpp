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

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()

// #include <atcoder/all>
// using namespace atcoder;

int N, M;
double eps, delta;
int input_sx, input_sy;
vector<pair<int, int>> input_p;
vector<pair<int, int>> input_l, input_r;

void exec_input() {
  cin >> N >> M >> eps >> delta;
  cin >> input_sx >> input_sy;
  input_p.resize(N);
  input_l.resize(M), input_r.resize(M);
  rep(i, N) { cin >> input_p[i].first >> input_p[i].second; }
  rep(i, M) cin >> input_l[i].first >> input_l[i].second >> input_r[i].first >>
      input_r[i].second;
}

class Action {
 public:
  char type_;
  ll x_, y_;
  Action() {}
  Action(char type, ll x, ll y) : type_(type), x_(x), y_(y) {
    assert(type == 'A' || type == 'S');
  }

  void print() { cout << type_ << " " << x_ << " " << y_ << endl; }
};

// ユークリッド距離を計算
double distance(int x1, int y1, int x2, int y2) {
  return hypot(x2 - x1, y2 - y1);
}

// 目的地の訪問順を決める（最近傍法）
vector<pair<int, int>> calc_route() {
  vector<pair<int, int>> route;
  vector<bool> visited(input_p.size(), false);

  int cx = input_sx, cy = input_sy;  // 現在地
  for (size_t i = 0; i < input_p.size(); i++) {
    int nearest_idx = -1;
    double min_dist = 1e9;
    for (size_t j = 0; j < input_p.size(); j++) {
      if (!visited[j]) {
        double d = distance(cx, cy, input_p[j].first, input_p[j].second);
        if (d < min_dist) {
          min_dist = d;
          nearest_idx = (int)j;
        }
      }
    }

    if (nearest_idx != -1) {
      visited[nearest_idx] = true;
      route.push_back(input_p[nearest_idx]);
      cx = input_p[nearest_idx].first;
      cy = input_p[nearest_idx].second;
    }
  }
  return route;
}

/**
 * 目標座標に全速力で近づく
 */
pair<int, int> calc_acceleration(int now_x, int now_y, int target_x,
                                 int target_y, int now_vx, int now_vy) {
  // 現在位置から目標までの距離
  int dx = target_x - now_x;
  int dy = target_y - now_y;

  // 理想的な加速度
  int ax = dx - now_vx;
  int ay = dy - now_vy;

  // 加速度の大きさの2乗
  ll acc_sq = (ll)ax * ax + (ll)ay * ay;
  const ll max_acc_sq = 500 * 500;

  // 加速度が制限を超えている場合、縮小する
  if (acc_sq > max_acc_sq && acc_sq != 0) {
    double acc = sqrt(acc_sq);
    double scale = 500.0 / acc;
    ax = static_cast<int>((int)ax * scale);
    ay = static_cast<int>((int)ay * scale);
  }
  //  加速度を適用した後の新しい速度
  int new_vx = now_vx + ax;
  int new_vy = now_vy + ay;

  // 各軸の速度が絶対値hoyoを超えないように補正

  int hoyo = 4000;
  if (new_vx > hoyo) {
    ax = hoyo - now_vx;
  } else if (new_vx < -hoyo) {
    ax = -hoyo - now_vx;
  }

  if (new_vy > hoyo) {
    ay = hoyo - now_vy;
  } else if (new_vy < -hoyo) {
    ay = -hoyo - now_vy;
  }
  assert(ax * ax + ay * ay <= 500 * 500);
  return make_pair(ax, ay);
}

void solve_A() {
  vector<pair<int, int>> route = calc_route();

  map<pair<int, int>, int> visited;

  debug(route);
  int turn = 0;
  // 今の座標
  int now_x = input_sx, now_y = input_sy;
  // 今の速度ベクトル
  int now_vx = 0, now_vy = 0;

  for (auto [target_x, target_y] : route) {
    if (visited[make_pair(target_x, target_y)]) continue;
    debug(now_x, now_y, target_x, target_y);
    int flag = false;
    int search_dist = 0;  // どちらの方向にサーチするか
    while (!flag) {
      turn++;
      if (turn > 5000) return;

      auto [ax, ay] =
          calc_acceleration(now_x, now_y, target_x, target_y, now_vx, now_vy);
      Action action('A', ax, ay);

      if (now_x == target_x && now_y == target_y) {
        // 測定する
        int search_x = 0, search_y = 1;
        action = Action('S', search_x, search_y);
      }
      debug(action.type_, action.x_, action.y_);

      // 出力
      action.print();
      // 入力受け取り
      double dist = 0;
      if (action.type_ == 'S') cin >> dist;
      debug(dist);
      int c, h;
      cin >> c >> h;
      debug(c, h);
      rep(i, h) {
        int idx;
        cin >> idx;
        visited[input_p[idx]] = true;
        if (visited[make_pair(target_x, target_y)]) flag = 1;
      }

      // 想定の速度と位置の更新
      if (action.type_ == 'A') {
        now_vx += ax, now_vy += ay;
        now_x += now_vx, now_y += now_vy;
      } else {
        // 予定の距離
        double predict_dist = distance(0, now_x, 0, now_y);
        // dist倍する
        if (predict_dist < -1e9) {
          continue;
        } else {
          now_x = (dist / predict_dist) * now_x;
          now_y = (dist / predict_dist) * now_y;
        }

        search_dist ^= 1;
      }
      debug(now_x, now_y, target_x, target_y, now_vx, now_vy, ax, ay);
    }
  }
}

int main() {
  exec_input();
  solve_A();
}