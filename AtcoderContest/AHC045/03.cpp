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
// #include <atcoder/all>
// using namespace atcoder;

constexpr int N = 800;
int rest_Q = 400;
int M, L, W;
vector<int> input_group_size_list;

class City {
 public:
  int idx_, lx_, rx_, ly_, ry_;

  double x_, y_;

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
}

class QQuery {
 public:
  vector<int> city_idxes_;
  vector<pair<int, int>> edges_;

  QQuery() {}

  void inquire() {
    assert(rest_Q);
    assert(2 <= (int)city_idxes_.size() && (int)city_idxes_.size() <= L);
    rest_Q--;
    cout << "? " << city_idxes_.size() << " ";
    rep(i, city_idxes_.size()) { cout << city_idxes_[i] << " "; }
    cout << endl;
    //
    rep(i, (int)city_idxes_.size() - 1) {
      int a, b;
      cin >> a >> b;
      edges_.emplace_back(a, b);
    }
  }
};

class AQuery {
 public:
  vector<int> city_idxes_;
  vector<pair<int, int>> edges_;

  AQuery() {}

  void start_answer() { cout << "!" << endl; }

  void answer() {
    rep(i, city_idxes_.size()) { cout << city_idxes_[i] << " "; }
    cout << "\n";
    rep(i, edges_.size()) {
      //
      cout << edges_[i].first << " " << edges_[i].second << "\n";
    }
    cout << flush;
  }
};

// 入出力確認
void first_submit() {
  vector<AQuery> ans_list;

  int idx = 0;
  for (auto& g : input_group_size_list) {
    AQuery aq;
    rep(i, g) {
      aq.city_idxes_.push_back(idx);
      idx++;
    }
    // 2個ずらして3個訊く
    for (int i = 0; i < g;) {
      QQuery qq;

      rep(i2, 3) {
        if (i + i2 == g) break;
        qq.city_idxes_.push_back(aq.city_idxes_[i + i2]);
      }
      debug(qq.city_idxes_);

      int sz = (int)qq.city_idxes_.size();
      if (sz == 1) {
        // 何もしなくていい
      } else if (sz == 2) {
        aq.edges_.emplace_back(qq.city_idxes_[0], qq.city_idxes_[1]);
      } else {
        qq.inquire();
        for (auto p : qq.edges_) aq.edges_.push_back(p);
      }
      i += 2;
    }

    ans_list.push_back(aq);
  }

  ans_list[0].start_answer();
  for (auto& ans : ans_list) {
    ans.answer();
  }
}

/*
グループの代表点を求める。
*/
vector<int> list_representative_point() {
  vector<int> ret;

  auto calc_dist = [&](int idx, double x, double y) {
    return hypot(city_list[idx].x_ - x, city_list[idx].y_ - y);
  };

  int mx_idx = 0;
  double mx_dist = 0;
  vector<double> dist(N, 1e9);
  double last_x = 0, last_y = 0;

  rep(gi, M) {
    mx_dist = 0;

    rep(i, N) {
      chmin(dist[i], calc_dist(i, last_x, last_y));
      if (chmax(mx_dist, dist[i])) mx_idx = i;
    }

    ret.push_back(mx_idx);
    last_x = city_list[mx_idx].x_, last_y = city_list[mx_idx].y_;
  }
  return ret;
}

/*
制約を満たすグループを作る。
*/
vector<vector<int>> divide_groups(vector<int>& representative_points) {
  auto calc_dist = [&](int i1, int i2) -> int {
    return (int)((city_list[i1].x_ - city_list[i2].x_) *
                     (city_list[i1].x_ - city_list[i2].x_) +
                 (city_list[i1].y_ - city_list[i2].y_) *
                     (city_list[i1].y_ - city_list[i2].y_));
  };

  // repsentative_pointsごとのグループサイズを決定する
  vector<int> group_size_list(M);
  {
    // (cnt, idx)
    vector<pair<int, int>> vec;
    rep(i, M) vec.emplace_back(0, i);
    rep(i, N) {
      int idx = 0;
      int d = 1e9;
      rep(j, M) {
        // if(vec[j].first == mx) continue;
        if (chmin(d, calc_dist(i, representative_points[j]))) idx = j;
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

  atcoder::mcf_graph<int, int> graph(N + M + 2);
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
      int d = calc_dist(i, representative_points[j]);
      graph.add_edge(i, j + N, 1, d);
    }
  }
  // 各グループの個数 -> tareget
  rep(i, M) graph.add_edge(i + N, TARGET, group_size_list[i], 0);

  // 実行
  auto result = graph.flow(SOURCE, TARGET);
  // debug(result);
  auto edges = graph.edges();

  // グループidxと、グループに所属する各頂点のリスト
  map<int, vector<int>> mp;
  rep(i, edges.size()) {
    if (edges[i].from < N && edges[i].flow) {
      mp[edges[i].to - N].push_back(edges[i].from);
    }
    // if (edges[i].flow) {
    //   if (edges[i].from < N)
    //     cerr << "都市：";
    //   else if (edges[i].from < N + M)
    //     cerr << "代表点：";
    //   debug(edges[i].from, edges[i].to, edges[i].cap, edges[i].cost,
    //         edges[i].flow);
    // }
  }
  // for (auto [k, v] : mp) {
  //   debug(k, v.size(), v);
  // }

  vector<vector<int>> ret(M);

  for (auto&& [idx, vec] : mp) {
    for (auto&& v : vec) {
      if (rep2idx.count(v)) assert(v == representative_points[idx]);
      ret[idx].push_back(v);
    }
  }

  // debug(ret);
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

vector<Tree> initial_ans(vector<vector<int>>& groups) {
  vector<Tree> ret;
  atcoder::dsu uf(N);

  auto calc_dist = [&](int i1, int i2) -> int {
    return (int)((city_list[i1].x_ - city_list[i2].x_) *
                     (city_list[i1].x_ - city_list[i2].x_) +
                 (city_list[i1].y_ - city_list[i2].y_) *
                     (city_list[i1].y_ - city_list[i2].y_));
  };

  for (auto& group : groups) {
    vector<Edge> edges;

    rep(i, group.size()) rep(j, i) {
      edges.emplace_back(group[j], group[i], calc_dist(group[j], group[i]));
    }
    sort(all(edges));

    Tree tree;
    tree.vertices = group;

    for (auto&& e : edges) {
      if (uf.same(e.source, e.target)) continue;
      uf.merge(e.source, e.target);

      tree.graph[e.source].push_back(e.target);
      tree.graph[e.target].push_back(e.source);

      if (uf.size(e.source) == (int)group.size()) break;
    }

    debug(tree.vertices, tree.graph);
    ret.push_back(tree);
  }

  return ret;
}

void update_ans(vector<Tree>& tree_list) {
  for (auto&& tree : tree_list) {
    if (tree.vertices.size() < 3) continue;

    if ((int)tree.vertices.size() <= L) {
      QQuery qq;
      qq.city_idxes_ = tree.vertices;
      qq.inquire();
      debug(qq.city_idxes_, qq.edges_);

      tree.graph.clear();
      assert(tree.graph.size() == 0);
      for (auto [v, u] : qq.edges_) {
        tree.graph[v].push_back(u);
        tree.graph[u].push_back(v);
      }
    }

    if (rest_Q == 0) break;
  }
}

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

    // debug(tree.vertices, edges);
    assert(tree.vertices.size() == edges.size() + 1);
    cnt += (int)tree.vertices.size();
    // debug(cnt);
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
  exec_input();
  // TODO：占いの一部を使って座標更新する

  // グループの代表点を求める
  vector<int> representative_points = list_representative_point();
  // グループを作る
  vector<vector<int>> groups = divide_groups(representative_points);

  // グループ内でMSTする
  vector<Tree> tree_list = initial_ans(groups);

  // 占いクエリを使ってグループ内のMSTの精度を高める
  update_ans(tree_list);

  // 回答順
  vector<int> ans_idexes(M);
  {
    map<int, vector<int>> mp;
    rep(i, M) mp[input_group_size_list[i]].push_back(i);
    rep(i, M) {
      int sz = (int)tree_list[i].vertices.size();
      ans_idexes[mp[sz].back()] = i;
      mp[sz].pop_back();
    }
  }

  // 回答出力
  print_ans(tree_list, ans_idexes);

  // first_submit();
}