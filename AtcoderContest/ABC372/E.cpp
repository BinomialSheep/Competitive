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
#include <atcoder/all>
using namespace atcoder;

template <class VAL>
struct RBST {
  VAL SUM_UNITY = 0;  // to be set

  unsigned int randInt() {
    static unsigned int tx = 123456789, ty = 362436069, tz = 521288629,
                        tw = 88675123;
    unsigned int tt = (tx ^ (tx << 11));
    tx = ty;
    ty = tz;
    tz = tw;
    return (tw = (tw ^ (tw >> 19)) ^ (tt ^ (tt >> 8)));
  }

  struct NODE {
    NODE *left, *right;
    VAL val;   // the value of the node
    int size;  // the size of the subtree
    VAL sum;   // the value-sum of the subtree

    NODE() : val(SUM_UNITY), size(1), sum(SUM_UNITY) { left = right = NULL; }

    NODE(VAL v) : val(v), size(1), sum(v) { left = right = NULL; }

    /* additional update */
    inline void update() {}

    /* additional lazy-propagation */
    inline void push() {
      /* ex: reverse */
      /*
      if (this->rev) {
      swap(this->left, this->right);
      if (this->left) this->left->rev ^= true;
      if (this->right) this->right->rev ^= true;
      this->rev = false;
      }
      */
    }
  };

  ///////////////////////
  // root
  ///////////////////////

  NODE* root;
  RBST() : root(NULL) {}
  RBST(NODE* node) : root(node) {}

  ///////////////////////
  // basic operations
  ///////////////////////

  /* size */
  inline int size(NODE* node) { return !node ? 0 : node->size; }
  inline int size() { return this->size(this->root); }

  /* sum */
  inline VAL sum(NODE* node) { return !node ? SUM_UNITY : node->sum; }
  inline VAL sum() { return this->sum(this->root); }

  /* update, push */
  inline NODE* update(NODE* node) {
    node->size = size(node->left) + size(node->right) + 1;
    node->sum = sum(node->left) + sum(node->right) + node->val;
    node->update();
    return node;
  }

  inline void push(NODE* node) {
    if (!node) return;
    node->push();
  }

  /* lower_bound */
  inline int lowerBound(NODE* node, VAL val) {
    push(node);
    if (!node) return 0;
    if (val <= node->val)
      return lowerBound(node->left, val);
    else
      return size(node->left) + lowerBound(node->right, val) + 1;
  }
  inline int lowerBound(VAL val) { return this->lowerBound(this->root, val); }

  /* upper_bound */
  inline int upperBound(NODE* node, VAL val) {
    push(node);
    if (!node) return 0;
    if (val >= node->val)
      return size(node->left) + upperBound(node->right, val) + 1;
    else
      return upperBound(node->left, val);
  }
  inline int upperBound(VAL val) { return this->upperBound(this->root, val); }

  /* count */
  inline int count(VAL val) { return upperBound(val) - lowerBound(val); }

  /* get --- k: 0-index */
  inline VAL get(NODE* node, int k) {
    push(node);
    if (!node) return -1;
    if (k == size(node->left)) return node->val;
    if (k < size(node->left))
      return get(node->left, k);
    else
      return get(node->right, k - size(node->left) - 1);
  }
  inline VAL get(int k) { return get(this->root, k); }

  ///////////////////////
  // merge-split
  ///////////////////////

  NODE* merge(NODE* left, NODE* right) {
    push(left);
    push(right);
    if (!left || !right) {
      if (left)
        return left;
      else
        return right;
    }
    if (randInt() % (left->size + right->size) < left->size) {
      left->right = merge(left->right, right);
      return update(left);
    } else {
      right->left = merge(left, right->left);
      return update(right);
    }
  }
  void merge(RBST add) { this->root = this->merge(this->root, add.root); }
  pair<NODE*, NODE*> split(NODE* node, int k) {  // [0, k), [k, n)
    push(node);
    if (!node) return make_pair(node, node);
    if (k <= size(node->left)) {
      pair<NODE*, NODE*> sub = split(node->left, k);
      node->left = sub.second;
      return make_pair(sub.first, update(node));
    } else {
      pair<NODE*, NODE*> sub = split(node->right, k - size(node->left) - 1);
      node->right = sub.first;
      return make_pair(update(node), sub.second);
    }
  }
  RBST split(int k) {
    pair<NODE*, NODE*> sub = split(this->root, k);
    this->root = sub.first;
    return RBST(sub.second);
  }

  ///////////////////////
  // insert-erase
  ///////////////////////

  void insert(const VAL val) {
    pair<NODE*, NODE*> sub = this->split(this->root, this->lowerBound(val));
    this->root = this->merge(this->merge(sub.first, new NODE(val)), sub.second);
  }

  void erase(const VAL val) {
    if (!this->count(val)) return;
    pair<NODE*, NODE*> sub = this->split(this->root, this->lowerBound(val));
    this->root = this->merge(sub.first, this->split(sub.second, 1).second);
  }

  ///////////////////////
  // debug
  ///////////////////////

  void print(NODE* node) {
    if (!node) return;
    push(node);
    print(node->left);
    cout << node->val << " ";
    print(node->right);
  }
  void print() {
    cout << "{";
    print(this->root);
    cout << "}" << endl;
  }
};

int main() {
  /* input */
  INT(N, Q);
  /* solve */

  vector<RBST<int>> S(N);

  vector<set<int>> sets(N);
  vector<int> leader(N);
  rep(i, N) leader[i] = i;
  rep(i, N) sets[i].insert(i);
  rep(i, N) S[i].insert(i);

  rep(qi, Q) {
    INT(ty);
    if (ty == 1) {
      INT(u, v);
      --u, --v;
      while (u != leader[u]) u = leader[u];
      while (v != leader[v]) v = leader[v];
      if (u == v) continue;
      if (sets[u].size() > sets[v].size()) swap(u, v);
      leader[u] = v;
      for (auto i : sets[u]) {
        sets[v].insert(i);
        S[v].insert(i);
      }
      sets[u].clear();
    } else {
      INT(v, K);
      --v;
      while (v != leader[v]) v = leader[v];
      // debug(qi, v, K);
      assert(sets[v].size() == S[v].size());

      if (S[v].size() < K) {
        out(-1);
      } else {
        K = S[v].size() - K;
        // debug("小さい方から", K, S[v].size());
        out(S[v].get(K) + 1);
      }
    }
    // debug(qi, sets);
  }
}
