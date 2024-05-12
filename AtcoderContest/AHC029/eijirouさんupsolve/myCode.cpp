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

#define ull unsigned long long int
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#ifdef ONLINE_JUDGE
constexpr double time_limit = 1.95;
#else
constexpr double time_limit = 2.95;
// constexpr double time_limit = 0.1;
#endif  // ONLINE_JUDGE

/* 定数 */
constexpr int max_turn = 1000;
constexpr int max_investments = 20;

constexpr int nd_size = 1024;
constexpr double initial_frequencies = 1.0;

int investment_turn_threshold_0 = 0.88 * max_turn;
int investment_turn_threshold_1 = 0.96 * max_turn;
int last_phase_threshold = 0.98 * max_turn;
double remaining_penalty = 0.6;
double work_coefficient = 1.1;
double v_rate = 0.98;
double regular_work_card_profit = 0.9;
double hard_work_card_profit = 0.6;

double card_evaluation_coefficient = 0.8;
double project_evaluation_coefficient = 0.7;
double project_remaining_evaluation = 0.3;
double investments_coefficient = 425.0;
double saving_evaluation_coefficient = 20.0;
double cancel_card_correction = 0.4;
double state_evaluation_exp = 0.95;

int max_simulation_turns = 10;    // プレイアウトのターン数
int max_play_out_candidates = 7;  // プレイアウトの候補

// プロジェクトの隠しパラメータ推定の初期値
vector<int> initial_frequencies_list = {21, 11, 11, 6, 4};

template <class T>
inline int argmin(const vector<T>& data) {
  assert(!data.empty());
  return (int)distance(data.begin(), min_element(data.begin(), data.end()));
}

template <class T>
inline int argmax(const vector<T>& data) {
  assert(!data.empty());
  return (int)distance(data.begin(), max_element(data.begin(), data.end()));
}

class Xorshift {
 public:
  Xorshift(uint32_t seed) : x_(seed) { assert(seed); }

  uint32_t randrange(uint32_t stop) {
    // [0, stop)
    assert(stop > 0);
    next();
    return x_ % stop;
  }

  uint32_t randrange(uint32_t start, uint32_t stop) {
    // [start, stop)
    assert(start < stop);
    next();
    return start + x_ % (stop - start);
  }

  uint32_t randint(uint32_t a, uint32_t b) {
    // [a, b]
    assert(a <= b);
    return randrange(a, b + 1);
  }

  double random() {
    // [0.0, 1.0]
    next();
    return static_cast<double>(x_) * (1.0 / static_cast<double>(UINT32_MAX));
  }

  double uniform(double a, double b) {
    // [a, b] or [b, a]
    return a + (b - a) * random();
  }

 private:
  void next() {
    x_ ^= x_ << 13;
    x_ ^= x_ >> 17;
    x_ ^= x_ << 5;
  }

  uint32_t x_;
};

class Timer {
 public:
  Timer() {
    begin();
    elapsed_time_ = 0.0;
  }

  void begin() { start_time_ = chrono::system_clock::now(); }

  double get_time() {
    chrono::system_clock::time_point end_time = chrono::system_clock::now();
    elapsed_time_ = (double)chrono::duration_cast<std::chrono::nanoseconds>(
                        end_time - start_time_)
                        .count();
    elapsed_time_ *= 1e-9;  // nanoseconds -> seconds
    return elapsed_time_;
  }

  double get_last_time() const { return elapsed_time_; }

  bool yet(double time_limit) { return get_time() < time_limit; }

  double progress(double time_limit) { return get_time() / time_limit; }

 private:
  chrono::system_clock::time_point start_time_;
  double elapsed_time_;
};

enum struct CardType {
  RegularWork,
  HardWork,
  Cancel,
  Restructuring,
  Investment
};

struct Card {
  CardType t;
  ll w;
  Card() {}
  Card(CardType t_, ll w_) : t(t_), w(w_) {}
};

struct Project {
  ll h, v;
  Project() {}
  Project(ll h_, ll v_) : h(h_), v(v_) {}

  bool work(ll w) {
    h -= w;
    return h <= 0;
  }
};

struct State {
  int turn;
  vector<Card> cards;
  vector<Project> projects;
  ll money;
  int l;
  int empty_card_position;
  vector<int> empty_project_positions;
  int investments;

  State() {}

  State(const vector<Card>& cards_, const vector<Project>& projects_)
      : turn(0),
        cards(cards_),
        projects(projects_),
        money(0),
        l(0),
        empty_card_position(-1) {
    investments = 0;
    for (const Card& card : cards)
      if (card.t == CardType::Investment) ++investments;
  }

  void use_card(int c, int m) {
    empty_project_positions.clear();
    empty_card_position = c;

    const Card& card = cards[c];
    switch (card.t) {
      case CardType::RegularWork:
        work(m, (int)card.w);
        break;
      case CardType::HardWork:
        for (size_t i = 0; i < projects.size(); ++i) {
          work((int)i, (int)card.w);
        }
        break;
      case CardType::Cancel:
        empty_project_positions.push_back(m);
        break;
      case CardType::Restructuring:
        empty_project_positions.resize(projects.size());
        iota(empty_project_positions.begin(), empty_project_positions.end(), 0);
        break;
      case CardType::Investment:
        ++l;
        break;
    }
  }

  void work(int m, int w) {
    if (projects[m].work(w)) {
      money += projects[m].v;
      empty_project_positions.push_back(m);
    }
  }

  void refill_card(const Card& card, ll p) {
    money -= p;
    cards[empty_card_position] = card;
    if (card.t == CardType::Investment) {
      ++investments;
    }
    ++turn;
  }
};

struct IO2 {
  bool online_judge;

  int n, m, k;
  vector<Card> initial_cards;
  vector<Project> initial_projects;

  vector<Project> future_projects;
  vector<vector<pair<Card, ll>>> future_cards;
  int completed_projects;

  void input() {
    online_judge = true;

    int t;
    cin >> n >> m >> k >> t;
    assert(t == max_turn);

    initial_cards.resize(n);
    rep(i, n) {
      INT(t2);
      LL(w);
      initial_cards[i] = Card(static_cast<CardType>(t2), w);
    }
    initial_projects.resize(m);
    rep(i, m) {
      LL(h, v);
      initial_projects[i] = Project(h, v);
    }
  }

  void use_card(State& state, int c, int i) {
    assert(0 <= c && c < n);
    assert(0 <= i && i < m);
    cout << c << " " << i << endl;
    state.use_card(c, i);
  }

  void update_projects(State& state) {
    if (online_judge) {
      for (int i = 0; i < m; ++i) {
        ll h, v;
        cin >> h >> v;
        state.projects[i] = Project(h, v);
      }
    } else {
      for (int i : state.empty_project_positions) {
        Project project = future_projects[completed_projects++];
        project.h <<= state.l;
        project.v <<= state.l;
        state.projects[i] = project;
      }
    }
  }

  void input_money(const State& state) {
    if (online_judge) {
      ll money;
      cin >> money;
      assert(money == state.money);
    }
  }

  vector<pair<Card, ll>> get_candidate_cards(const State& state) {
    if (online_judge) {
      vector<pair<Card, ll>> ret(k);
      for (int i = 0; i < k; ++i) {
        int t;
        ll w, p;
        cin >> t >> w >> p;
        ret[i] = {Card(static_cast<CardType>(t), w), p};
      }
      return ret;
    } else {
      vector<pair<Card, ll>> ret = future_cards[state.turn];
      for (int i = 0; i < k; ++i) {
        ret[i].first.w <<= state.l;
        ret[i].second <<= state.l;
      }
      return ret;
    }
  }

  void refill_card(State& state, const vector<pair<Card, ll>>& candidate_cards,
                   int r) {
    assert(0 <= r && r < k);
    auto [card, p] = candidate_cards[r];
    assert(state.money >= p);
    cout << r << endl;
    state.refill_card(card, p);
  }
};

struct InputGenerator {
  Xorshift rng;
  array<double, nd_size> nd;
  int sum_frequencies;
  array<int, 5> frequencies;

  InputGenerator() : rng(1) {
    frequencies[0] = (int)(initial_frequencies * initial_frequencies_list[0]);
    frequencies[1] = (int)(initial_frequencies * initial_frequencies_list[1]);
    frequencies[2] = (int)(initial_frequencies * initial_frequencies_list[2]);
    frequencies[3] = (int)(initial_frequencies * initial_frequencies_list[3]);
    frequencies[4] = (int)(initial_frequencies * initial_frequencies_list[4]);
    sum_frequencies = accumulate(frequencies.begin(), frequencies.end(), 0);
    init_nd();
  }

  void init_nd() {
    mt19937 engine(0);
    normal_distribution<> dist(0.0, 1.0);
    for (int i = 0; i < nd_size; ++i) {
      nd[i] = dist(engine);
    }
  }

  double gauss(double mu, double sigma) {
    return mu + sigma * nd[rng.randrange(nd_size)];
  }

  void update(const vector<pair<Card, ll>>& candidate_cards) {
    sum_frequencies += (int)candidate_cards.size();
    for (const auto& [card, _] : candidate_cards) {  // This is a bug !
      ++frequencies[static_cast<int>(card.t)];
    }
  }

  CardType generate_card_type() {
    int x = rng.randrange(sum_frequencies);
    rep(i, 4) {
      if (x < frequencies[i]) return static_cast<CardType>(i);
      x -= frequencies[i];
    }
    return CardType::Investment;
  }

  vector<pair<Card, ll>> generate_cards(int k, ll m) {
    vector<pair<Card, ll>> ret(k);
    ret[0] = {Card(CardType::RegularWork, 1), 0};
    for (int i = 1; i < k; ++i) {
      CardType t = generate_card_type();
      switch (t) {
        case CardType::RegularWork: {
          ll w_dash = rng.randint(1, 50);
          ll w = w_dash;
          ll p = clamp(lround(gauss((double)w_dash, (double)w_dash / 3.0)), 1l,
                       10000l);
          ret[i] = {Card(t, w), p};
          break;
        }
        case CardType::HardWork: {
          ll w_dash = rng.randint(1, 50);
          ll w = w_dash;
          ll p = clamp(lround(gauss((double)w_dash * (double)m,
                                    (double)w_dash * (double)m / 3.0)),
                       1l, 10000l);
          ret[i] = {Card(t, w), p};
          break;
        }
        case CardType::Cancel:
          ret[i] = {Card(t, 0), rng.randint(0, 10)};
          break;
        case CardType::Restructuring:
          ret[i] = {Card(t, 0), rng.randint(0, 10)};
          break;
        case CardType::Investment:
          ret[i] = {Card(t, 0), rng.randint(200, 1000)};
          break;
      }
    }
    return ret;
  }

  Project generate_project() {
    double b = rng.uniform(2.0, 8.0);
    ll h = lround(pow(2, b));
    ll v = lround(pow(2, clamp(gauss(b, 0.5), 0.0, 10.0)));
    return Project(h, v);
  }
};

const array<double, 257> make_pow_array(double c1, double c2, double c3) {
  array<double, 257> ret;
  for (int i = 0; i < 257; ++i) {
    ret[i] = c3 / (1.0 + c1 * pow(1 + i, c2));
  }
  return ret;
}

static const array<double, 257> pow_array_5_4 =
    make_pow_array(0.5, 0.4, work_coefficient);
const array<double, 257> pow_array_3_4 = make_pow_array(0.3, 0.4, 1.0);

inline double calculate_profit(ll w, const Project& project, int l, ll money) {
  if (project.h <= w) {
    return work_coefficient * (double)project.v;
  }
  double profit = static_cast<double>(project.v * w) / (double)project.h;
  ll i = max(0ll, project.h - w - money) >> l;
  assert(i < 257);
  return profit * pow_array_5_4[i];
}

inline bool is_superior_card(const Card& card, ll p,
                             const vector<pair<Card, ll>>& candidate_cards) {
  for (auto [card2, p2] : candidate_cards) {
    if (card2.t == card.t && p2 < p && card2.w >= card.w) {
      return false;
    }
  }
  return true;
}

inline bool can_buy_card(const State& state, const Card& card, ll p,
                         const vector<pair<Card, ll>>& candidate_cards) {
  if (p > state.money) {
    return false;
  } else if (card.t != CardType::Investment) {
    return is_superior_card(card, p, candidate_cards);
  } else if (state.investments >= max_investments) {
    return false;
  } else if (state.turn <= investment_turn_threshold_0) {
    return is_superior_card(card, p, candidate_cards);
  } else if (state.turn >= investment_turn_threshold_1) {
    return false;
  } else {
    double max_investment_rate =
        static_cast<double>(investment_turn_threshold_1 - state.turn) /
        (investment_turn_threshold_1 - investment_turn_threshold_0);
    if ((double)p > (double)state.money * max_investment_rate) {
      return false;
    }
    return is_superior_card(card, p, candidate_cards);
  }
}

inline double get_last_penalty(int turn) {
  if (turn <= last_phase_threshold) {
    return 1.0;
  } else {
    return static_cast<double>(max_turn - turn) /
           (max_turn - last_phase_threshold);
  }
}

inline double get_regular_work_card_profit(double last_penalty, ll w) {
  return last_penalty * regular_work_card_profit * (double)w;
}

inline double get_hard_work_card_profit(double last_penalty, ll w, size_t m) {
  return last_penalty * hard_work_card_profit * (double)m * (double)w;
}

inline double get_cancel_card_profit(double last_penalty, int l) {
  return last_penalty * (1 << l);
}

inline double get_restructuring_card_profit(double last_penalty, int l) {
  return last_penalty * (1 << l);
}

inline double get_card_profit(const Card& card, double last_penalty,
                              const State& state) {
  switch (card.t) {
    case CardType::RegularWork:
      return get_regular_work_card_profit(last_penalty, card.w);
    case CardType::HardWork:
      return get_hard_work_card_profit(last_penalty, card.w,
                                       state.projects.size());
    case CardType::Cancel:
      return get_cancel_card_profit(last_penalty, state.l);
    case CardType::Restructuring:
      return get_restructuring_card_profit(last_penalty, state.l);
    case CardType::Investment:
      return 0.0;
  }
  assert(false);
}

inline tuple<double, int, int> evaluate_card(State& state, const Card& argCard,
                                             ll p) {
  state.cards[state.empty_card_position] = argCard;

  double last_penalty = get_last_penalty(state.turn);
  ll money = state.money - p;
  double max_profit = -numeric_limits<double>::infinity();
  int best_c = -1;
  int best_m = -1;

  bool regular_done = false;
  bool cancel_done = false;
  bool restructuring_done = false;
  bool investment_done = false;

  for (size_t c = 0; c < state.cards.size(); ++c) {
    const Card& card = state.cards[c];
    switch (card.t) {
      case CardType::RegularWork: {
        if (card.w == (1 << state.l)) {
          if (regular_done) {
            break;
          }
          regular_done = true;
        }
        double regular_work_card_profit2 =
            get_regular_work_card_profit(last_penalty, card.w);
        for (size_t m = 0; m < state.projects.size(); ++m) {
          double profit =
              calculate_profit(card.w, state.projects[m], state.l, money) -
              regular_work_card_profit2;
          if (profit > max_profit) {
            max_profit = profit;
            best_c = (int)c;
            best_m = (int)m;
          }
        }
        break;
      }
      case CardType::HardWork: {
        double profit = 0.0;
        for (const Project& project : state.projects) {
          profit += calculate_profit(card.w, project, state.l, money);
        }
        profit -= get_hard_work_card_profit(last_penalty, card.w,
                                            state.projects.size());
        if (profit > max_profit) {
          max_profit = profit;
          best_c = (int)c;
          best_m = 0;
        }
        break;
      }
      case CardType::Cancel: {
        if (cancel_done) {
          break;
        }
        cancel_done = true;
        double cancel_card_profit =
            get_cancel_card_profit(last_penalty, state.l);
        for (size_t m = 0; m < state.projects.size(); ++m) {
          const Project& project = state.projects[m];
          double profit =
              (double)project.h -
              (v_rate * (double)project.v + (1.0 - v_rate) * (32 << state.l)) -
              cancel_card_profit;
          if (profit > max_profit) {
            max_profit = profit;
            best_c = (int)c;
            best_m = (int)m;
          }
        }
        break;
      }
      case CardType::Restructuring: {
        if (restructuring_done) {
          break;
        }
        restructuring_done = true;
        double profit = 0.0;
        for (const Project& project : state.projects) {
          profit += (double)project.h - (v_rate * (double)project.v +
                                         (1.0 - v_rate) * (32 << state.l));
        }
        profit -= get_cancel_card_profit(last_penalty, state.l);
        if (profit > max_profit) {
          max_profit = profit;
          best_c = (int)c;
          best_m = 0;
        }
        break;
      }
      case CardType::Investment: {
        if (investment_done) {
          break;
        }
        investment_done = true;
        assert(state.l < max_investments);
        max_profit = 1e18;
        best_c = (int)c;
        best_m = 0;
        break;
      }
    }
  }
  max_profit += get_card_profit(argCard, last_penalty, state) - (double)p;
  return {max_profit, best_c, best_m};
}

inline vector<tuple<double, int, int>> evaluate_card_with_candidates(
    State& state, const Card& argCard, ll p) {
  state.cards[state.empty_card_position] = argCard;

  double last_penalty = get_last_penalty(state.turn);
  ll money = state.money - p;

  vector<tuple<double, int, int>> ret(state.cards.size());
  double fixed_profit =
      get_card_profit(argCard, last_penalty, state) - (double)p;

  bool regular_done = false;
  bool cancel_done = false;
  bool restructuring_done = false;
  bool investment_done = false;

  for (size_t c = 0; c < state.cards.size(); ++c) {
    const Card& card = state.cards[c];
    double max_profit = -numeric_limits<double>::infinity();
    int best_m = 0;
    switch (card.t) {
      case CardType::RegularWork: {
        if (card.w == (1 << state.l)) {
          if (regular_done) {
            break;
          }
          regular_done = true;
        }
        for (size_t m = 0; m < state.projects.size(); ++m) {
          double profit =
              calculate_profit(card.w, state.projects[m], state.l, money);
          profit -= get_regular_work_card_profit(last_penalty, card.w);
          if (profit > max_profit) {
            max_profit = profit;
            best_m = (int)m;
          }
        }
        break;
      }
      case CardType::HardWork: {
        double profit = 0.0;
        for (size_t m = 0; m < state.projects.size(); ++m) {
          profit += calculate_profit(card.w, state.projects[m], state.l, money);
        }
        profit -= get_hard_work_card_profit(last_penalty, card.w,
                                            state.projects.size());
        if (profit > max_profit) {
          max_profit = profit;
          best_m = 0;
        }
        break;
      }
      case CardType::Cancel: {
        if (cancel_done) {
          break;
        }
        cancel_done = true;
        for (size_t m = 0; m < state.projects.size(); ++m) {
          const Project& project = state.projects[m];
          double profit =
              (double)project.h -
              (v_rate * (double)project.v + (1.0 - v_rate) * (32 << state.l));
          profit -= get_cancel_card_profit(last_penalty, state.l);
          if (profit > max_profit) {
            max_profit = profit;
            best_m = (int)m;
          }
        }
        break;
      }
      case CardType::Restructuring: {
        if (restructuring_done) {
          break;
        }
        restructuring_done = true;
        double profit = 0.0;
        for (size_t m = 0; m < state.projects.size(); ++m) {
          const Project& project = state.projects[m];
          profit += (double)project.h - (v_rate * (double)project.v +
                                         (1.0 - v_rate) * (32 << state.l));
        }
        profit -= get_cancel_card_profit(last_penalty, state.l);
        if (profit > max_profit) {
          max_profit = profit;
          best_m = 0;
        }
        break;
      }
      case CardType::Investment: {
        if (investment_done) {
          break;
        }
        investment_done = true;
        assert(state.l < max_investments);
        max_profit = 1e18;
        best_m = 0;
        break;
      }
    }
    ret[c] = {max_profit + fixed_profit, c, best_m};
  }
  sort(ret.begin(), ret.end(),
       [](const tuple<double, int, int>& a, const tuple<double, int, int>& b) {
         return get<0>(a) > get<0>(b);
       });
  return ret;
}

inline tuple<int, int, int> greedy(
    State& state, const vector<pair<Card, ll>>& candidate_cards) {
  int r = 0;
  int c = 0;
  int m = 0;
  double max_profit = -numeric_limits<double>::infinity();
  for (size_t i = 0; i < candidate_cards.size(); ++i) {
    const auto& [card, p] = candidate_cards[i];
    if (!can_buy_card(state, card, p, candidate_cards)) {
      continue;
    }
    auto [profit, ci, mi] = evaluate_card(state, card, p);
    if (profit > max_profit) {
      r = (int)i;
      c = ci;
      m = mi;
      max_profit = profit;
    }
  }
  return {r, c, m};
}

inline double get_money_profit(ll money, int l) {
  ll fixed_money = money >> l;
  if (fixed_money <= 200) {
    return 0.0;
  }
  double rate =
      fixed_money < 1000 ? ((double)fixed_money - 200.0) / 800.0 : 1.0;
  return saving_evaluation_coefficient * rate * (1 << l);
}

double evaluate_state(const State& state) {
  if (state.turn >= max_turn - 1) {
    return (double)state.money;
  }
  double last_penalty = get_last_penalty(state.turn);

  double card_evaluation = 0.0;
  bool have_cancel_card = false;
  for (const Card& card : state.cards) {  // This is a bug !
    card_evaluation += get_card_profit(card, last_penalty, state);
    if (card.t == CardType::Cancel || card.t == CardType::Restructuring) {
      have_cancel_card = true;
    }
  }
  card_evaluation *= card_evaluation_coefficient;

  double project_evaluation = 0.0;
  for (const Project& project : state.projects) {
    ll i = max(0ll, project.h - state.money) >> state.l;
    assert(i < 257);
    if (project.h > project.v && have_cancel_card) {
      project_evaluation += cancel_card_correction *
                            (double)(project.v - project.h) * pow_array_3_4[i];
    } else {
      project_evaluation += (double)(project.v - project.h) * pow_array_3_4[i];
    }
  }
  project_evaluation *= project_evaluation_coefficient;

  double investments_evaluation = investments_coefficient * (1 << state.l);

  double evaluation = (double)state.money + card_evaluation +
                      project_evaluation + investments_evaluation +
                      get_money_profit(state.money, state.l);

  return pow(max(0.0, evaluation), state_evaluation_exp);
}

double play_out(State state, const Card& card0, ll p0, int c0, int m0,
                int simulation_turns, const vector<Project>& future_projects,
                const vector<vector<pair<Card, ll>>>& future_cards) {
  assert(static_cast<int>(future_cards.size()) == simulation_turns);

  int future_projects_index = 0;
  for (int t = 0; t < simulation_turns; ++t) {
    if (t == 0) {
      state.refill_card(card0, p0);
      state.use_card(c0, m0);
    } else {
      vector<pair<Card, ll>> candidate_cards = future_cards[t];
      for (size_t i = 0; i < candidate_cards.size(); ++i) {
        candidate_cards[i].first.w <<= state.l;
        candidate_cards[i].second <<= state.l;
      }
      auto [r, c, m] = greedy(state, candidate_cards);
      state.refill_card(candidate_cards[r].first, candidate_cards[r].second);
      state.use_card(c, m);
    }
    for (int i : state.empty_project_positions) {
      Project project = future_projects[future_projects_index++];
      project.h <<= state.l;
      project.v <<= state.l;
      state.projects[i] = project;
    }
  }
  return evaluate_state(state);
}

struct Solver {
  Timer timer;
  IO2 io;
  State state;
  InputGenerator input_generator;
  vector<vector<Project>> future_projects;

  Solver() {
    io.input();
    initialize_state();
  }

  void initialize_state() {
    state = State(io.initial_cards, io.initial_projects);
  }

  void solve() {
    // first turn
    auto [c0, m0] = choose_card_in_first_turn();
    io.use_card(state, c0, m0);
    io.update_projects(state);
    io.input_money(state);

    // main section
    while (state.turn < max_turn - 1) {
      vector<pair<Card, ll>> candidate_cards = io.get_candidate_cards(state);
      input_generator.update(candidate_cards);
      auto [r, c, m] = decide_action(candidate_cards);
      io.refill_card(state, candidate_cards, r);
      io.use_card(state, c, m);
      io.update_projects(state);
      io.input_money(state);
    }
    // last turn
    vector<pair<Card, ll>> candidate_cards = io.get_candidate_cards(state);
    io.refill_card(state, candidate_cards, 0);
  }

  pair<int, int> choose_card_in_first_turn() {
    state.empty_card_position = 0;
    vector<pair<Card, ll>> candidate_cards = {{state.cards[0], 0}};
    auto [_, c, m] = decide_action(candidate_cards);
    return {c, m};
  }

  /* r, c, mを返す
     r:= 何番目のカードを手札に加えるか
     c:= 手札のうち何番目の方針カードを使用するか
     m:= カードの効果を適用するプロジェクトの番号
   */
  tuple<int, int, int> decide_action(
      const vector<pair<Card, ll>>& candidate_cards) {
    vector<tuple<double, int, int, int>> candidates;

    if (state.turn == 0) {
      for (auto [profit, c, m] :
           evaluate_card_with_candidates(state, state.cards[0], 0)) {
        candidates.push_back({profit, 0, c, m});
      }
    } else {
      for (size_t i = 0; i < candidate_cards.size(); ++i) {
        const auto& [card, p] = candidate_cards[i];
        if (!can_buy_card(state, card, p, candidate_cards)) {
          continue;
        }
        for (auto [profit, c, m] :
             evaluate_card_with_candidates(state, card, p)) {
          candidates.push_back({profit, i, c, m});
        }
      }
    }
    assert(!candidates.empty());
    sort(candidates.rbegin(), candidates.rend());

    if (candidates.size() > max_play_out_candidates) {
      candidates.resize(max_play_out_candidates);
    }

    if (candidates.size() == 1) {
      auto [_, r, c, m] = candidates[0];
      return {r, c, m};
    }
    // Monte Carlo Method
    double time_now = timer.get_time();
    double remaining_time = time_limit - time_now;
    double usable_time = remaining_time / (max_turn - state.turn);
    double local_time_limit = time_now + usable_time;
    int original_candidates_size = (int)candidates.size();

    vector<double> sum_evaluation(candidates.size(), 0.0);
    int seed = 0;
    while (timer.yet(local_time_limit) && candidates.size() >= 2) {
      if (static_cast<int>(future_projects.size()) == seed) {
        vector<Project> projects(max_simulation_turns * state.projects.size());
        for (size_t i = 0; i < projects.size(); ++i) {
          projects[i] = input_generator.generate_project();
        }
        future_projects.emplace_back(projects);
      }
      int simulation_turn =
          min(max_simulation_turns, max_turn - state.turn - 1);
      vector<vector<pair<Card, ll>>> future_cards(simulation_turn);
      for (int t = 0; t < simulation_turn; ++t) {
        future_cards[t] = input_generator.generate_cards(
            (int)candidate_cards.size(), state.projects.size());
      }
      for (size_t i = 0; i < sum_evaluation.size(); ++i) {
        auto [_, r, c, m] = candidates[i];
        auto [card0, p0] = candidate_cards[r];
        sum_evaluation[i] += play_out(state, card0, p0, c, m, simulation_turn,
                                      future_projects[seed], future_cards);
      }
      if (timer.get_last_time() > time_now + usable_time *
                                                 (original_candidates_size -
                                                  (int)candidates.size() + 2) /
                                                 original_candidates_size) {
        int worst = argmin(sum_evaluation);
        candidates.erase(candidates.begin() + worst);
        sum_evaluation.erase(sum_evaluation.begin() + worst);
      }
      ++seed;
    }
    int best = argmax(sum_evaluation);
    auto [_, r, c, m] = candidates[best];
    return {r, c, m};
  }

  ll score() const { return state.money; }
};

/*
int investment_turn_threshold_0 = 0.88 * max_turn;
int investment_turn_threshold_1 = 0.96 * max_turn;
int last_phase_threshold = 0.98 * max_turn;
double remaining_penalty = 0.6;
double work_coefficient = 1.1;
double v_rate = 0.98;
double regular_work_card_profit = 0.9;
double hard_work_card_profit = 0.6;

double card_evaluation_coefficient = 0.8;
double project_evaluation_coefficient = 0.7;
double project_remaining_evaluation = 0.3;
double investments_coefficient = 425.0;
double saving_evaluation_coefficient = 20.0;
double cancel_card_correction = 0.4;
double state_evaluation_exp = 0.95;

int max_simulation_turns = 10;    // プレイアウトのターン数
int max_play_out_candidates = 7;  // プレイアウトの候補
*/

int main(int argc, char* argv[]) {
  if (argc == 3) {
    investment_turn_threshold_0 = atof(argv[1]) * max_turn;
    investment_turn_threshold_1 = atof(argv[2]) * max_turn;
    // last_phase_threshold = atof(argv[3]) * max_turn;
    // remaining_penalty = atof(argv[4]);
    // work_coefficient = atof(argv[5]);
  }
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solver solver;
  solver.solve();
}