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

random_device rd;
mt19937 gen(rd());

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
  int idx_;
  double lx_, rx_, ly_, ry_;
  // 重宝形の中心
  double mx_, my_;
  // 推定結果
  double x_, y_;

  // 受けている力
  double dx_, dy_;
  //
  double penalty_;

  City() {}
  City(int idx, int lx, int rx, int ly, int ry)
      : idx_(idx), lx_(lx), rx_(rx), ly_(ly), ry_(ry) {
    mx_ = x_ = (lx_ + rx_) / 2.;
    my_ = y_ = (ly_ + ry_) / 2.;
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

class Graph {
 public:
  map<pair<int, int>, set<pair<int, int>>> from_;
  map<pair<int, int>, set<pair<int, int>>> to_;
  Graph() {}

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

Graph build_dag(vector<vector<int>>& groups) {
  Graph dag;

  set<vector<int>> is_inquired;
  vector<int> is_completed(M);
  rep(i, M) if ((int)groups[i].size() < 3) is_completed[i] = 1;

  int is_update = 1;
  while (rest_Q && is_update) {
    is_update = 0;
    rep(i, M) {
      if (is_completed[i]) continue;
      if (rest_Q == 0) break;

      int sz = min(L, (int)groups[i].size());

      if (sz < (int)groups[i].size()) {
        shuffle(all(groups[i]), gen);
        vector<int> vec;
        rep(j, sz) vec.push_back(groups[i][j]);
        sort(all(vec));
        if (is_inquired.count(vec)) continue;
        is_inquired.insert(vec);
      }
      is_update = 1;
      QQuery qq;
      rep(j, sz) qq.city_idxes_.push_back(groups[i][j]);

      qq.inquire();

      map<int, vector<int>> tree;
      set<pair<int, int>> st;
      for (auto [v, u] : qq.edges_) {
        tree[v].push_back(u);
        tree[u].push_back(v);
        st.insert(make_pair(min(v, u), max(v, u)));
      }
      rep(i2, (int)qq.city_idxes_.size()) {
        rep(j2, i2) {
          int v = qq.city_idxes_[i2], u = qq.city_idxes_[j2];
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

          rep(k, (int)vec.size() - 1) {
            dag.add_edge(vec[k], vec[k + 1], v, u);
          }
        }
      }
    }
  }
  dag.resolve();
  return dag;
}

vector<Tree> build_ans(Graph dag, vector<vector<int>>& groups) {
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

  auto calc_dist = [&](int i, int j) {
    return (city_list[i].x_ - city_list[j].x_) *
               (city_list[i].x_ - city_list[j].x_) +
           (city_list[i].y_ - city_list[j].y_) *
               (city_list[i].y_ - city_list[j].y_);
  };

  // dist, edge
  using P = pair<int, pair<int, int>>;
  priority_queue<P, vector<P>, greater<P>> pq;
  rep(i, N) rep(j, i) {
    if (!dag.from_.count(make_pair(j, i))) {
      pq.emplace(calc_dist(j, i), make_pair(j, i));
    }
  }
  while (pq.size()) {
    auto [d, p] = pq.top();
    pq.pop();
    // debug(d, p);

    for (auto p2 : dag.to_[p]) {
      dag.from_[p2].erase(p);
      if (dag.from_[p2].size() == 0) {
        pq.emplace(calc_dist(p2.first, p2.second), p2);
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

// 座標推定を行うクラス
class CoordinateEstimater {
 public:
  Graph dag;
  // map<pair<int, int>, vector<pair<int, int>>> constraints;
  // 座標推定に使っていい回数
  const int PARAM_QUERY = 400;

  int calc_dist(int i1, int i2) {
    return (int)((city_list[i1].x_ - city_list[i2].x_) *
                     (city_list[i1].x_ - city_list[i2].x_) +
                 (city_list[i1].y_ - city_list[i2].y_) *
                     (city_list[i1].y_ - city_list[i2].y_));
  }
  double calc_dist_dbl(int i1, int i2) {
    return hypot(city_list[i1].x_ - city_list[i2].x_,
                 city_list[i1].y_ - city_list[i2].y_);
  }

  void update_dag(QQuery& qq) {
    map<int, vector<int>> tree;
    set<pair<int, int>> st;
    for (auto [v, u] : qq.edges_) {
      tree[v].push_back(u);
      tree[u].push_back(v);
      st.insert(make_pair(min(v, u), max(v, u)));
    }
    rep(i2, (int)qq.city_idxes_.size()) {
      rep(j2, i2) {
        int v = qq.city_idxes_[i2], u = qq.city_idxes_[j2];
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
    rep(i, PARAM_QUERY) {
      // 頂点iからもっとも距離が近いL個の座標に対してクエリを飛ばす
      vector<pair<int, int>> dist;
      rep(j, N) dist.emplace_back(calc_dist(i, j), j);
      sort(all(dist));
      QQuery qq;
      rep(k, L) qq.city_idxes_.push_back(dist[k].second);
      //
      qq.inquire();
      update_dag(qq);
    }
    dag.resolve();
  }

  // ある辺を含むようなものだけのdagに分割するイメージ
  // FIXME：行きがけに更新する必要がある
  // void build_constrains() {
  //   vector<map<pair<int, int>, int>> memo(
  //       N);  // numを目的としてcity_idxを訪れた時のメモ
  //   // p := 今の頂点, num := 着目している都市番号, from :=
  //   // 直近のnumを含む辺の相方
  //   auto dfs = [&](auto rec, pair<int, int> vp, int num) -> int {
  //     auto [a, b] = vp;
  //     if (memo[num].count(vp)) {
  //       if (memo[num][vp] != -1) }
  //     int ret = -1;

  //     for (auto&& up : dag.to_[vp]) {
  //       auto [a2, b2] = up;
  //       if (a2 == num) {
  //       } else if (b2 == num) {
  //       } else {
  //         rec(rec, up, num, from);
  //       }
  //     }

  //     if (vp.first == num) {
  //       return memo[num][vp] = vp.second;
  //     } else if (vp.second == num) {
  //       return memo[num][vp] = vp.first;
  //     } else {
  //       return memo[num][vp] = ret;
  //     }
  //   };

  //   for (auto&& [p, st] : dag.to_) {
  //     if (dag.from_.count(p)) continue;
  //     auto [a, b] = p;
  //     dfs(dfs, p, a, b);
  //     dfs(dfs, p, b, a);
  //   }
  // }

  void exec(TimeKeeper& time_keeper) {
    // 制約を作る
    build_dag();
    // TODO：DAGをDFSして、帰りがけに各頂点からの距離順の制約を作る

    //

    auto dfs = [&](auto rec, pair<int, int> vp, pair<int, int> startp) -> void {
      auto [va, vb] = vp;
      auto [sa, sb] = startp;

      double dv = calc_dist_dbl(va, vb);
      double ds = calc_dist_dbl(sa, sb);
      // ds < dvのはずなのでこれは矛盾
      if (ds > dv) {
        // ペナルティを加える
        double pen = ds - dv;
        city_list[va].penalty_ += pen;
        city_list[vb].penalty_ += pen;
        city_list[sa].penalty_ += pen;
        city_list[sb].penalty_ += pen;
        // vpは伸ばす、spは縮める
        {
          double ratio = (pen * 30 / 100) / dv;
          double dx = abs(city_list[vb].x_ - city_list[va].x_) * ratio;
          double dy = abs(city_list[vb].y_ - city_list[va].y_) * ratio;
          // debug(pen, dx, dy, city_list[va].x_, city_list[vb].x_,
          //       city_list[va].y_, city_list[vb].y_);
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
          // debug(city_list[va].x_, city_list[vb].x_, city_list[va].y_,
          //       city_list[vb].y_);
        }
        {
          double ratio = (pen * 30 / 100) / ds;
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
        double ndv = calc_dist_dbl(va, vb);
        double nds = calc_dist_dbl(sa, sb);
        double npen = nds - ndv;
        debug(pen, npen);
      }

      for (auto&& up : dag.to_[vp]) {
        rec(rec, up, startp);
      }
    };
    int cnt = 0;
    auto tk2 = TimeKeeper(2000);
    while (tk2.getTime() < 300) {
      for (auto&& [p, st] : dag.to_) {
        if (tk2.getTime() >= 300) break;
        cnt++;
        for (auto&& np : st) {
          dfs(dfs, np, p);
        }
      }
    }
    debug(cnt);
  }
};

int main() {
  const int time_threshold = 1990;
  auto time_keeper = TimeKeeper(time_threshold);

  exec_input();
  // TODO：占いの一部を使って座標更新する
  CoordinateEstimater estimater;
  estimater.exec(time_keeper);

  // グループの代表点を求める
  vector<int> representative_points = list_representative_point();
  // グループを作る
  vector<vector<int>> groups = divide_groups(representative_points);

  // Graph dag = build_dag(groups);

  vector<Tree> ans = build_ans(estimater.dag, groups);

  // グループ内でMSTする
  // vector<Tree> tree_list = initial_ans(groups);
  // 占いクエリを使ってグループ内のMSTの精度を高める
  // update_ans(tree_list);

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

  debug(rest_Q);

  // first_submit();
}