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
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvi = vector<vector<vector<int>>>;
using pii = pair<int, int>;

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
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

#define YESNO(yes, no)                          \
  void yes(bool i = 1) { out(i ? #yes : #no); } \
  void no() { out(#no); }
YESNO(first, second)
YESNO(First, Second)
YESNO(Yes, No)
YESNO(YES, NO)
YESNO(possible, impossible)
YESNO(POSSIBLE, IMPOSSIBLE)
#pragma endregion header
// #include <atcoder/all>
// using namespace atcoder;

template <typename T>
class dynamic_connectivity {
  class euler_tour_tree {
   public:
    struct node;
    using np = node*;
    using lint = long long;
    struct node {
      np ch[2] = {nullptr, nullptr};
      np p = nullptr;
      int l, r, sz;
      T val = et, sum = et;
      bool exact;
      bool child_exact;
      bool edge_connected = 0;
      bool child_edge_connected = 0;
      node() {}
      node(int l, int r)
          : l(l), r(r), sz(l == r), exact(l < r), child_exact(l < r) {}
      bool is_root() { return !p; }
    };
    vector<unordered_map<int, np>> ptr;
    np get_node(int l, int r) {
      if (ptr[l].find(r) == ptr[l].end()) ptr[l][r] = new node(l, r);
      return ptr[l][r];
    }
    np root(np t) {
      if (!t) return t;
      while (t->p) t = t->p;
      return t;
    }
    bool same(np s, np t) {
      if (s) splay(s);
      if (t) splay(t);
      return root(s) == root(t);
    }
    np reroot(np t) {
      auto s = split(t);
      return merge(s.second, s.first);
    }
    pair<np, np> split(np s) {
      splay(s);
      np t = s->ch[0];
      if (t) t->p = nullptr;
      s->ch[0] = nullptr;
      return {t, update(s)};
    }
    pair<np, np> split2(np s) {
      splay(s);
      np t = s->ch[0];
      np u = s->ch[1];
      if (t) t->p = nullptr;
      s->ch[0] = nullptr;
      if (u) u->p = nullptr;
      s->ch[1] = nullptr;
      return {t, u};
    }
    tuple<np, np, np> split(np s, np t) {
      auto u = split2(s);
      if (same(u.first, t)) {
        auto r = split2(t);
        return make_tuple(r.first, r.second, u.second);
      } else {
        auto r = split2(t);
        return make_tuple(u.first, r.first, r.second);
      }
    }
    template <typename First, typename... Rest>
    np merge(First s, Rest... t) {
      return merge(s, merge(t...));
    }
    np merge(np s, np t) {
      if (!s) return t;
      if (!t) return s;
      while (s->ch[1]) s = s->ch[1];
      splay(s);
      s->ch[1] = t;
      if (t) t->p = s;
      return update(s);
    }
    int size(np t) { return t ? t->sz : 0; }
    np update(np t) {
      t->sum = et;
      if (t->ch[0]) t->sum = fn(t->sum, t->ch[0]->sum);
      if (t->l == t->r) t->sum = fn(t->sum, t->val);
      if (t->ch[1]) t->sum = fn(t->sum, t->ch[1]->sum);
      t->sz = size(t->ch[0]) + (t->l == t->r) + size(t->ch[1]);
      t->child_edge_connected =
          (t->ch[0] ? t->ch[0]->child_edge_connected : 0) |
          (t->edge_connected) | (t->ch[1] ? t->ch[1]->child_edge_connected : 0);
      t->child_exact = (t->ch[0] ? t->ch[0]->child_exact : 0) | (t->exact) |
                       (t->ch[1] ? t->ch[1]->child_exact : 0);
      return t;
    }
    void push(np t) {
      // 遅延評価予定
    }
    void rot(np t, bool b) {
      np x = t->p, y = x->p;
      if ((x->ch[1 - b] = t->ch[b])) t->ch[b]->p = x;
      t->ch[b] = x, x->p = t;
      update(x);
      update(t);
      if ((t->p = y)) {
        if (y->ch[0] == x) y->ch[0] = t;
        if (y->ch[1] == x) y->ch[1] = t;
        update(y);
      }
    }
    void splay(np t) {
      push(t);
      while (!t->is_root()) {
        np q = t->p;
        if (q->is_root()) {
          push(q), push(t);
          rot(t, q->ch[0] == t);
        } else {
          np r = q->p;
          push(r), push(q), push(t);
          bool b = r->ch[0] == q;
          if (q->ch[1 - b] == t)
            rot(q, b), rot(t, b);
          else
            rot(t, 1 - b), rot(t, b);
        }
      }
    }

   public:
    euler_tour_tree() {}
    euler_tour_tree(int sz) {
      ptr.resize(sz);
      for (int i = 0; i < sz; i++) ptr[i][i] = new node(i, i);
    }
    int size(int s) {
      np t = get_node(s, s);
      splay(t);
      return t->sz;
    }
    bool same(int s, int t) { return same(get_node(s, s), get_node(t, t)); }
    void set_size(int sz) {
      ptr.resize(sz);
      for (int i = 0; i < sz; i++) ptr[i][i] = new node(i, i);
    }
    void update(int s, T x) {
      np t = get_node(s, s);
      splay(t);
      t->val = fn(t->val, x);
      update(t);
    }
    void edge_update(int s, auto g) {
      np t = get_node(s, s);
      splay(t);
      function<void(np)> dfs = [&](np t) {
        assert(t);
        if (t->l < t->r && t->exact) {
          splay(t);
          t->exact = 0;
          update(t);
          g(t->l, t->r);
          return;
        }
        if (t->ch[0] && t->ch[0]->child_exact)
          dfs(t->ch[0]);
        else
          dfs(t->ch[1]);
      };
      while (t && t->child_exact) {
        dfs(t);
        splay(t);
      }
    }
    bool try_reconnect(int s, auto f) {
      np t = get_node(s, s);
      splay(t);
      function<bool(np)> dfs = [&](np t) -> bool {
        assert(t);
        if (t->edge_connected) {
          splay(t);
          return f(t->l);
        }
        if (t->ch[0] && t->ch[0]->child_edge_connected)
          return dfs(t->ch[0]);
        else
          return dfs(t->ch[1]);
      };
      while (t->child_edge_connected) {
        if (dfs(t)) return 1;
        splay(t);
      }
      return 0;
    }
    void edge_connected_update(int s, bool b) {
      np t = get_node(s, s);
      splay(t);
      t->edge_connected = b;
      update(t);
    }
    bool link(int l, int r) {
      if (same(l, r)) return 0;
      merge(reroot(get_node(l, l)), get_node(l, r), reroot(get_node(r, r)),
            get_node(r, l));
      return 1;
    }
    bool cut(int l, int r) {
      if (ptr[l].find(r) == ptr[l].end()) return 0;
      np s, t, u;
      tie(s, t, u) = split(get_node(l, r), get_node(r, l));
      merge(s, u);
      np p = ptr[l][r];
      np q = ptr[r][l];
      ptr[l].erase(r);
      ptr[r].erase(l);
      delete p;
      delete q;
      return 1;
    }
    T get_sum(int p, int v) {
      cut(p, v);
      np t = get_node(v, v);
      splay(t);
      T res = t->sum;
      link(p, v);
      return res;
    }
    T get_sum(int s) {
      np t = get_node(s, s);
      splay(t);
      return t->sum;
    }
  };
  int dep = 1;
  vector<euler_tour_tree> ett;
  vector<vector<unordered_set<int>>> edges;
  int sz;

 public:
  dynamic_connectivity(int sz) : sz(sz) {
    ett.emplace_back(sz);
    edges.emplace_back(sz);
  }
  bool link(int s, int t) {
    if (s == t) return 0;
    if (ett[0].link(s, t)) return 1;
    edges[0][s].insert(t);
    edges[0][t].insert(s);
    if (edges[0][s].size() == 1) ett[0].edge_connected_update(s, 1);
    if (edges[0][t].size() == 1) ett[0].edge_connected_update(t, 1);
    return 0;
  }
  bool same(int s, int t) { return ett[0].same(s, t); }
  int size(int s) { return ett[0].size(s); }
  vector<int> get_vertex(int s) { return ett[0].vertex_list(s); }
  void update(int s, T x) { ett[0].update(s, x); }
  T get_sum(int s) { return ett[0].get_sum(s); }
  bool cut(int s, int t) {
    if (s == t) return 0;
    for (int i = 0; i < dep; i++) {
      edges[i][s].erase(t);
      edges[i][t].erase(s);
      if (edges[i][s].size() == 0) ett[i].edge_connected_update(s, 0);
      if (edges[i][t].size() == 0) ett[i].edge_connected_update(t, 0);
    }
    for (int i = dep - 1; i >= 0; i--) {
      if (ett[i].cut(s, t)) {
        if (dep - 1 == i) {
          dep++;
          ett.emplace_back(sz);
          edges.emplace_back(sz);
        }
        return !try_reconnect(s, t, i);
      }
    }
    return 0;
  }
  bool try_reconnect(int s, int t, int k) {
    for (int i = 0; i < k; i++) {
      ett[i].cut(s, t);
    }
    for (int i = k; i >= 0; i--) {
      if (ett[i].size(s) > ett[i].size(t)) swap(s, t);
      auto g = [&](int s, int t) { ett[i + 1].link(s, t); };
      ett[i].edge_update(s, g);
      auto f = [&](int x) -> bool {
        for (auto itr = edges[i][x].begin(); itr != edges[i][x].end();) {
          auto y = *itr;
          itr = edges[i][x].erase(itr);
          edges[i][y].erase(x);
          if (edges[i][x].size() == 0) ett[i].edge_connected_update(x, 0);
          if (edges[i][y].size() == 0) ett[i].edge_connected_update(y, 0);
          if (ett[i].same(x, y)) {
            edges[i + 1][x].insert(y);
            edges[i + 1][y].insert(x);
            if (edges[i + 1][x].size() == 1)
              ett[i + 1].edge_connected_update(x, 1);
            if (edges[i + 1][y].size() == 1)
              ett[i + 1].edge_connected_update(y, 1);
          } else {
            for (int j = 0; j <= i; j++) {
              ett[j].link(x, y);
            }
            return 1;
          }
        }
        return 0;
      };
      if (ett[i].try_reconnect(s, f)) return 1;
    }
    return 0;
  }
  constexpr static T et = T();
  constexpr static T fn(T s, T t) { return s + t; }
};

struct Solver {
  void solve() {
    /* input */
    INT(N, M);

    vector<vector<pair<int, int>>> G(N);
    map<pair<int, char>, int> mp;
    rep(i, M) {
      INT(A, B);
      --A, --B;
      char C;
      cin >> C;
      G[A].emplace_back(B, C);
      G[B].emplace_back(A, C);
      mp[make_pair(A, B)] = i + 1;
      mp[make_pair(B, A)] = i + 1;
    }

    // debug(G);

    STR(S);

    /* solve */
    set<int> st2;
    dynamic_connectivity<int> dc(N);
    vi ans;
    vi flag(N);
    auto dfs = [&](auto rec, int v) -> bool {
      if ((int)st2.size() == N) return true;

      // if ((int)dc.size() == N) return false;
      if (st2.count(v) == 0) {
        for (auto [u, c] : G[v]) {
          if (S[v] != c) continue;
          if (dc.same(v, u)) continue;
          dc.link(v, u);

          int f1 = 0, f2 = 0;
          if (S[v] == c && !st2.count(v)) f1 = 1, st2.insert(v);
          if (S[u] == c && !st2.count(u)) f2 = 1, st2.insert(u);
          bool res = rec(rec, u);
          if (res) {
            ans.push_back(mp[make_pair(v, u)]);
            return true;
          }
          if (f1) st2.erase(v);
          if (f2) st2.erase(u);
          dc.cut(v, u);
        }
      }

      int next = v + 1;
      while (next < N) {
        if (flag[next] == 0) {
          flag[next] = 1;
          bool res = rec(rec, next);
          flag[next] = 1;
          if (res) {
            return true;
          }
        }
        next++;
      }

      return false;
    };
    int isYes = dfs(dfs, 0);
    Yes(isYes);

    rep(v, N) {
      for (auto [u, c] : G[v]) {
        if (!dc.same(v, u)) {
          ans.push_back(mp[make_pair(v, u)]);
          dc.link(v, u);
        }
      }
    }

    if (isYes) out(ans);

    /* output */
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}