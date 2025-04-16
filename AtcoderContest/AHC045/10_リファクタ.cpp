#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()

// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}
#include <atcoder/all>
// using namespace atcoder;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

//-------------------------------//
//  乱数、時間管理                //
//-------------------------------//

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
// 0以上1未満の小数をとる乱数
static double rand01() { return (randXor() + 0.5) * (1.0 / UINT_MAX); }

class TimeKeeper {
 private:
  chrono::high_resolution_clock::time_point start_time_;
  int64_t time_threshold_;

 public:
  // 時間制限をミリ秒単位で指定してインスタンスをつくる。
  TimeKeeper(const int64_t& time_threshold)
      : start_time_(chrono::high_resolution_clock::now()),
        time_threshold_(time_threshold) {}

  // インスタンス生成時から指定した時間制限を超過したか判定する。
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

//-------------------------------//
//  グローバル定数・入力           //
//-------------------------------//

constexpr int N = 800;
int rest_Q = 400;
int M, L, W;
vector<int> input_group_size_list;

//-------------------------------//
//  都市                         //
//-------------------------------//

// 都市クラス
class City {
 public:
  int idx_;
  double lx_, rx_, ly_, ry_;
  // 推定結果
  double x_, y_;
  // ローカル実行用
  double actual_x_ = -1, actual_y_ = -1;

  City() {}
  City(int idx, int lx, int rx, int ly, int ry)
      : idx_(idx), lx_(lx), rx_(rx), ly_(ly), ry_(ry) {
    x_ = (lx_ + rx_) / 2.;
    y_ = (ly_ + ry_) / 2.;
  }

  void debug_print() { debug(lx_, rx_, ly_, ry_, x_, y_); }

  bool operator<(const City& another) const {
    if (int(2 * x_) == int(2 * another.x_)) return y_ < another.y_;
    return x_ < another.x_;
  };
};
vector<City> city_list;

// 都市を管理する神クラス
class CityManager {
 public:
  static double calc_dist(int idx, double x, double y) {
    return hypot(city_list[idx].x_ - x, city_list[idx].y_ - y);
  };
  static double calc_dist(int i1, int i2) {
    return hypot(city_list[i1].x_ - city_list[i2].x_,
                 city_list[i1].y_ - city_list[i2].y_);
  }

  // 真の座標との予測誤差を返す（ローカル実行用）
  static double calc_prediction_error() {
    // 本番では使用不可
    if (city_list[0].actual_x_ < 0) return 0.0;
    double ret = 0;
    rep(i, N) {
      double d = calc_dist(i, city_list[i].actual_x_, city_list[i].actual_y_);
      // city_list[i].debug_print();
      // debug(city_list[i].actual_x_, city_list[i].actual_y_, d);
      ret += d;
    }
    return ret;
  }
};

//-------------------------------//
//  クエリ管理クラス              //
//-------------------------------//
class QueryManager {
 public:
  static vector<pair<int, int>> ask(const vector<int>& city_indices) {
    assert(rest_Q);
    assert(2U <= city_indices.size() && (int)city_indices.size() <= L);
    rest_Q--;

    // "? k city_1 city_2 ... city_k"
    cout << "? " << city_indices.size();
    for (auto v : city_indices) cout << " " << v;
    cout << endl;

    // 都市数 - 1 個の辺入力を受け取る
    vector<pair<int, int>> edges;
    edges.resize(city_indices.size() - 1);
    rep(i, (int)edges.size()) { cin >> edges[i].first >> edges[i].second; }
    return edges;
  }
};

// グループの代表点を求める。
vector<int> list_representative_point() {
  vector<int> ret;

  int mx_idx = 0;
  double mx_dist = 0;
  vector<double> dist(N, 1e9);
  double last_x = 0, last_y = 0;

  rep(gi, M) {
    mx_dist = 0;

    rep(i, N) {
      chmin(dist[i], CityManager::calc_dist(i, last_x, last_y));
      if (chmax(mx_dist, dist[i])) mx_idx = i;
    }

    ret.push_back(mx_idx);
    last_x = city_list[mx_idx].x_, last_y = city_list[mx_idx].y_;
  }
  return ret;
}

// 制約を満たすグループを作る。
vector<vector<int>> divide_groups(vector<int>& representative_points) {
  // repsentative_pointsごとのグループサイズを決定する
  vector<int> group_size_list(M);
  {
    // (cnt, idx)
    vector<pair<int, int>> vec;
    rep(i, M) vec.emplace_back(0, i);
    rep(i, N) {
      int idx = 0;
      double d = 1e9;
      rep(j, M) {
        // if(vec[j].first == mx) continue;
        if (chmin(d, CityManager::calc_dist(i, representative_points[j])))
          idx = j;
      }
      vec[idx].first++;
    }
    sort(all(vec));
    // group_size側
    vector<pair<int, int>> vec2;
    rep(i, M) vec2.emplace_back(input_group_size_list[i], i);
    sort(all(vec2));

    rep(i, M) {
      group_size_list[vec[i].second] = input_group_size_list[vec2[i].second];
    }
  }
  // 代表点の頂点から代表点配列のidxへのmap
  unordered_map<int, int> rep2idx;
  rep(i, M) rep2idx[representative_points[i]] = i;

  atcoder::mcf_graph<int, ll> graph(N + M + 2);
  const int SOURCE = N + M, TARGET = N + M + 1;

  // source -> 都市
  rep(i, N) graph.add_edge(SOURCE, i, 1, 0);
  // 都市 -> グループの代表点
  rep(i, N) {
    if (rep2idx.count(i)) {
      graph.add_edge(i, rep2idx[i] + N, 1, 0);
      continue;
    }
    rep(j, M) {
      int d = (int)CityManager::calc_dist(i, representative_points[j]);
      graph.add_edge(i, j + N, 1, d);
    }
  }
  // 各グループの個数 -> tareget
  rep(i, M) graph.add_edge(i + N, TARGET, group_size_list[i], 0);

  // 実行
  graph.flow(SOURCE, TARGET);
  auto edges = graph.edges();

  // グループidxと、グループに所属する各頂点のリスト
  map<int, vector<int>> mp;
  rep(i, edges.size()) {
    if (edges[i].from < N && edges[i].flow) {
      mp[edges[i].to - N].push_back(edges[i].from);
    }
  }

  vector<vector<int>> ret(M);
  for (auto&& [idx, vec] : mp) {
    for (auto&& v : vec) {
      ret[idx].push_back(v);
    }
  }
  return ret;
}

class Edge {
 public:
  int source, target, cost;
  Edge(int s = 0, int t = 0, int c = 0) : source(s), target(t), cost(c) {}
  bool operator<(Edge& e) { return cost < e.cost; }
};

class Tree {
 public:
  // 双方向に持つとしよう
  map<int, vector<int>> graph;
  vector<int> vertices;

  Tree() {}
};

class Dag {
 public:
  map<pair<int, int>, set<pair<int, int>>> from_;
  map<pair<int, int>, set<pair<int, int>>> to_;
  Dag() {}

  void add_edge(int from_v, int from_u, int to_v, int to_u) {
    if (from_v > from_u) swap(from_v, from_u);
    if (to_v > to_u) swap(to_v, to_u);
    auto fp = make_pair(from_v, from_u);
    auto tp = make_pair(to_v, to_u);
    to_[fp].insert(tp);
    from_[tp].insert(fp);
  }
  // 同じ距離の循環参照を解消
  // TODO：制約をマージすると効率がいい
  void resolve() {
    for (auto&& [p, st] : to_) {
      for (auto p2 : st) {
        if (to_[p2].count(p)) {
          to_[p2].erase(p);
          from_[p].erase(p2);
        }
      }
    }
  }
};

vector<Tree> build_ans(Dag dag, vector<vector<int>>& groups) {
  vector<Tree> ans(M);
  // 頂点番号からグループのidxを引くやつ
  vector<int> v_to_group_idx(N);
  rep(gi, groups.size()) {
    for (auto v : groups[gi]) {
      v_to_group_idx[v] = gi;
      ans[gi].vertices.push_back(v);
    }
  }
  // 連結成分のdsu
  atcoder::dsu uf(N);

  // dist, edge
  using P = pair<double, pair<int, int>>;
  priority_queue<P, vector<P>, greater<P>> pq;
  rep(i, N) rep(j, i) {
    if (!dag.from_.count(make_pair(j, i))) {
      pq.emplace(CityManager::calc_dist(j, i), make_pair(j, i));
    }
  }
  while (pq.size()) {
    auto [d, p] = pq.top();
    pq.pop();
    // debug(d, p);

    for (auto p2 : dag.to_[p]) {
      dag.from_[p2].erase(p);
      if (dag.from_[p2].size() == 0) {
        pq.emplace(CityManager::calc_dist(p2.first, p2.second), p2);
      }
    }

    auto [a, b] = p;
    // 異なるクラスタは繋がない
    if (v_to_group_idx[a] != v_to_group_idx[b]) continue;
    // もう繋がってるなら繋がない
    if (uf.same(a, b)) continue;
    // 繋ぐ！
    ans[v_to_group_idx[a]].graph[a].push_back(b);
    ans[v_to_group_idx[a]].graph[b].push_back(a);
    uf.merge(a, b);
  }

  return ans;
}

// 座標推定を行うクラス
class CoordinateEstimater {
 public:
  Dag dag;
  // 座標推定に使っていい回数
  const int PARAM_QUERY = 400;

  void update_dag(vector<int>& ask_cities, vector<pair<int, int>>& edges) {
    map<int, vector<int>> tree;
    set<pair<int, int>> st;
    for (auto [v, u] : edges) {
      tree[v].push_back(u);
      tree[u].push_back(v);
      st.insert(make_pair(min(v, u), max(v, u)));
    }
    rep(i2, (int)ask_cities.size()) {
      rep(j2, i2) {
        int v = ask_cities[i2], u = ask_cities[j2];
        if (v > u) swap(v, u);
        if (st.count(make_pair(v, u))) continue;

        // dfsをしてvからuへの復元
        vector<int> vec;
        auto dfs = [&](auto rec, int start, int goal, int now,
                       int parent) -> bool {
          bool ret = false;
          for (auto next : tree[now]) {
            if (next == parent) continue;
            if (next == goal) {
              vec.push_back(next);
              ret = true;
            } else {
              ret = rec(rec, start, goal, next, now);
            }
            if (ret) break;
          }
          if (ret) vec.push_back(now);
          return ret;
        };
        dfs(dfs, v, u, v, -1);

        rep(k, (int)vec.size() - 1) { dag.add_edge(vec[k], vec[k + 1], v, u); }
      }
    }
  }

  void build_dag() {
    // クエリに含まれた回数
    // vector<int> cnt(N);
    rep(qi, PARAM_QUERY) {
      int idx = qi;
      // int min_cnt = 1e9;
      // rep(i, N) {
      //   if (chmin(min_cnt, cnt[i])) {
      //     idx = i;
      //     if (min_cnt == 0) break;
      //   }
      // }
      // 頂点iからもっとも距離が近いL個の座標に対してクエリを飛ばす
      vector<pair<double, int>> dist;
      rep(j, N) dist.emplace_back(CityManager::calc_dist(idx, j), j);
      sort(all(dist));
      vector<int> ask_cities;
      rep(k, L) {
        // cnt[dist[k].second]++;
        ask_cities.push_back(dist[k].second);
      }
      //
      auto edges = QueryManager::ask(ask_cities);
      update_dag(ask_cities, edges);
    }
    dag.resolve();
  }

  void exec() {
    // 制約を作る
    build_dag();

    auto dfs = [&](auto rec, pair<int, int> vp, pair<int, int> startp) -> void {
      auto [va, vb] = vp;
      auto [sa, sb] = startp;

      double dv = CityManager::calc_dist(va, vb);
      double ds = CityManager::calc_dist(sa, sb);
      // ds < dvのはずなのでこれは矛盾
      if (ds > dv) {
        // ペナルティを加える
        double pen = ds - dv;
        // vpは伸ばす、spは縮める
        {
          double ratio = (pen * 50 / 100) / dv;
          double dx = abs(city_list[vb].x_ - city_list[va].x_) * ratio;
          double dy = abs(city_list[vb].y_ - city_list[va].y_) * ratio;
          if (city_list[va].x_ < city_list[vb].x_) {
            city_list[va].x_ = max(city_list[va].lx_, city_list[va].x_ - dx);
            city_list[vb].x_ = min(city_list[vb].rx_, city_list[vb].x_ + dx);
          } else if (city_list[va].x_ > city_list[vb].x_) {
            city_list[vb].x_ = max(city_list[vb].lx_, city_list[vb].x_ - dx);
            city_list[va].x_ = min(city_list[va].rx_, city_list[va].x_ + dx);
          }
          if (city_list[va].y_ < city_list[vb].y_) {
            city_list[va].y_ = max(city_list[va].ly_, city_list[va].y_ - dy);
            city_list[vb].y_ = min(city_list[va].ry_, city_list[vb].y_ + dy);
          } else if (city_list[va].y_ > city_list[vb].y_) {
            city_list[vb].y_ = max(city_list[vb].ly_, city_list[vb].y_ - dy);
            city_list[va].y_ = min(city_list[va].ry_, city_list[va].y_ + dy);
          }
        }
        {
          double ratio = (pen * 50 / 100) / ds;
          double dx = abs(city_list[sb].x_ - city_list[sa].x_) * ratio;
          double dy = abs(city_list[sb].y_ - city_list[sa].y_) * ratio;
          if (city_list[sa].x_ < city_list[sb].x_) {
            city_list[sa].x_ = min(city_list[sa].rx_, city_list[sa].x_ + dx);
            city_list[sb].x_ = max(city_list[sb].lx_, city_list[sb].x_ - dx);
          } else if (city_list[sa].x_ > city_list[sb].x_) {
            city_list[sb].x_ = min(city_list[sb].rx_, city_list[sb].x_ + dx);
            city_list[sa].x_ = max(city_list[sa].lx_, city_list[sa].x_ - dx);
          }
          if (city_list[sa].y_ < city_list[sb].y_) {
            city_list[sa].y_ = min(city_list[sa].ry_, city_list[sa].y_ + dy);
            city_list[sb].y_ = max(city_list[sb].ly_, city_list[sb].y_ - dy);
          } else if (city_list[sa].y_ > city_list[sb].y_) {
            city_list[sb].y_ = min(city_list[sb].ry_, city_list[sb].y_ + dy);
            city_list[sa].y_ = max(city_list[sa].ly_, city_list[sa].y_ - dy);
          }
        }
        // double ndv = CityManager::calc_dist(va, vb);
        // double nds = CityManager::calc_dist(sa, sb);
        // double npen = nds - ndv;
        // debug(pen, npen);
      }

      for (auto&& up : dag.to_[vp]) {
        rec(rec, up, startp);
      }
    };

    auto sum_pen = [&]() {
      double sum = 0;
      auto dfs2 = [&](auto rec, pair<int, int> vp,
                      pair<int, int> startp) -> void {
        auto [va, vb] = vp;
        auto [sa, sb] = startp;

        double dv = CityManager::calc_dist(va, vb);
        double ds = CityManager::calc_dist(sa, sb);
        // ds < dvのはずなのでこれは矛盾
        if (ds > dv) {
          // ペナルティを加える
          sum += ds - dv;
        }
        for (auto&& up : dag.to_[vp]) {
          rec(rec, up, startp);
        }
      };

      for (auto&& [p, st] : dag.to_) {
        for (auto&& np : st) {
          dfs2(dfs, np, p);
        }
      }
      debug(sum);
    };

    int cnt = 0;
    auto tk2 = TimeKeeper(50000);
    sum_pen();
    double prediction_error = CityManager::calc_prediction_error();
    debug("修正前：", prediction_error);
    while (tk2.getTime() < 600) {
      for (auto&& [p, st] : dag.to_) {
        if (tk2.getTime() >= 600) break;
        cnt++;
        for (auto&& np : st) {
          dfs(dfs, np, p);
        }
      }
    }
    sum_pen();
    prediction_error = CityManager::calc_prediction_error();
    debug("修正後：", prediction_error);
    debug(cnt);
  }

  // 推定値を真の値で置き換える（制度測定用）
  void cheat() {
    rep(i, N) {
      city_list[i].x_ = city_list[i].actual_x_;
      city_list[i].y_ = city_list[i].actual_y_;
    }
  }
};

// 入力
void exec_input() {
  int _;
  cin >> _ >> M >> _ >> L >> W;
  rep(i, M) {
    int g;
    cin >> g;
    input_group_size_list.push_back(g);
  }
  rep(i, N) {
    int lx, rx, ly, ry;
    cin >> lx >> rx >> ly >> ry;
    city_list.emplace_back(i, lx, rx, ly, ry);
  }
  // 真の座標はローカル実行の時だけ読み込める
#ifdef LOCAL
  rep(i, N) { cin >> city_list[i].actual_x_ >> city_list[i].actual_y_; }
#endif
}

// 最終出力
void print_ans(vector<Tree>& ans, vector<int>& ans_idexes) {
  cout << "!" << endl;

  int cnt = 0;
  set<int> st;

  rep(qi, M) {
    Tree& tree = ans[ans_idexes[qi]];
    set<pair<int, int>> edges;
    for (auto [v, us] : tree.graph) {
      for (auto u : us) edges.insert(make_pair(min(v, u), max(v, u)));
    }

    assert(tree.vertices.size() == edges.size() + 1);
    cnt += (int)tree.vertices.size();
    for (auto v : tree.vertices) st.insert(v);
    assert(cnt == (int)st.size());

    rep(i, tree.vertices.size()) {
      cout << tree.vertices[i];
      if (i == (int)tree.vertices.size() - 1) {
        cout << endl;
      } else {
        cout << " ";
      }
    }
    for (auto [fst, scd] : edges) {
      cout << fst << " " << scd << endl;
    }
  }
}

int main() {
  const int time_threshold = 1950;
  auto time_keeper = TimeKeeper(time_threshold);
  exec_input();

  // 占いの一部を使って座標更新する
  CoordinateEstimater estimater;
  estimater.exec();

  // estimater.cheat();

  // グループの代表点を求める
  vector<int> representative_points = list_representative_point();
  // グループを作る
  vector<vector<int>> groups = divide_groups(representative_points);

  // dagに基づいて初期解を作る
  vector<Tree> ans = build_ans(estimater.dag, groups);

  // 回答順
  vector<int> ans_idexes(M);
  {
    map<int, vector<int>> mp;
    rep(i, M) mp[input_group_size_list[i]].push_back(i);
    rep(i, M) {
      int sz = (int)groups[i].size();
      ans_idexes[mp[sz].back()] = i;
      mp[sz].pop_back();
    }
  }
  // 回答出力
  print_ans(ans, ans_idexes);
}