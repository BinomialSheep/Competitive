#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int input_N, input_M, input_H;
vector<int> input_A(1000), input_x(1000), input_y(1000);
vector<vector<int>> input_G(1000);

void exec_input() {
  cin >> input_N >> input_M >> input_H;
  rep(i, 1000) cin >> input_A[i];
  rep(i, input_M) {
    int v, u;
    cin >> v >> u;
    input_G[v].push_back(u);
    input_G[u].push_back(v);
  }
  rep(i, input_N) { cin >> input_x[i] >> input_y[i]; }
}

int calc_score(vector<int>& v_height) {
  int ret = 1;
  rep(i, 1000) { ret += input_A[i] * (v_height[i] + 1); }
  return ret;
}

// 見栄えのいい頂点順
vector<int> nice_look(1000);
void sort_nice_look() {
  vector<pair<int, int>> ps;
  rep(i, 1000) ps.emplace_back(input_A[i], i);
  sort(ps.rbegin(), ps.rend());
  rep(i, 1000) nice_look[i] = ps[i].second;
}

int main() {
  exec_input();
  sort_nice_look();

  // 今のv_heightからBFSして全体をvalidな高さにできるか判定する
  auto is_valid = [&](int h, vector<int> v_height_copy) -> bool {
    vector<int> used(input_N);

    // BFSする
    queue<int> q;
    rep(i, input_N) if (v_height_copy[i] == h) q.push(i);
    while (q.size()) {
      auto v = q.front();
      q.pop();

      for (auto u : input_G[v]) {
        if (v_height_copy[u] != -1) continue;
        v_height_copy[u] = v_height_copy[v] + 1;
        if (v_height_copy[u] < input_H) q.push(u);
      }
    }

    rep(i, input_N) {
      if (v_height_copy[i] == -1) return false;
    }
    return true;
  };

  // 高さhとする頂点を決める
  // 見栄えのいい頂点から順に、高さhにしなくてもvalidな解になるなら高さhにしない
  auto f = [&](int h, vector<int>& v_height) {
    rep(i, input_N) {
      // 高さh-1に隣接する高さ未定の頂点を一旦全て高さhと置く
      if (v_height[i] != -1) continue;
      for (auto u : input_G[i]) {
        if (v_height[u] == h - 1) v_height[i] = h;
      }
    }
    if (h == input_H) return;

    rep(i, input_N) {
      // 見栄えのいい頂点順に処理する
      int v = nice_look[i];
      if (v_height[v] != h) continue;
      // 取り除いてみる
      v_height[v] = -1;
      // 取り除いたらvalidな解にならないなら高さhとする
      if (!is_valid(h, v_height)) {
        v_height[v] = h;
      }
    }
  };

  vector<int> v_height(input_N, -1);
  // 高さ0から10まで順に決める
  for (int i = 0; i <= input_H; i++) {
    f(i, v_height);
  }

  // 高さの復元
  vector<int> ans_p(input_N);
  rep(i, input_N) {
    if (v_height[i] == 0) {
      ans_p[i] = -1;
    } else {
      for (auto u : input_G[i]) {
        if (v_height[u] == v_height[i] - 1) {
          ans_p[i] = u;
          break;
        }
      }
    }
  }

  cerr << calc_score(v_height) << endl;
  rep(i, input_N) cout << ans_p[i] << endl;
}