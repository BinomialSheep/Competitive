#include <bits/stdc++.h>
using namespace std;

static const int N = 100;
static const int L = 500000;
vector<int> Tval(N);

//------------------[ Employee構造体 ]------------------
class Employee {
 public:
  int id_;
  int target_;  // T_i
  int a_, b_;   // (a_x, b_x)

  Employee() {}
  Employee(int i, int t) : id_(i), target_(t), a_(0), b_(0) {}
};

//------------------[ 入出力 ]------------------
void exec_input() {
  int N_, L_;
  cin >> N_ >> L_;  // ここでは固定で N=100, L=500000
  for (int i = 0; i < N; i++) {
    cin >> Tval[i];
  }
}

void exec_output(const vector<Employee> &emps) {
  auto sorted_emps = emps;
  sort(sorted_emps.begin(), sorted_emps.end(),
       [](auto &a, auto &b) { return a.id_ < b.id_; });
  for (int i = 0; i < N; i++) {
    cout << sorted_emps[i].a_ << " " << sorted_emps[i].b_ << "\n";
  }
  cout << flush;
}

//-----------------------------------------------------
// (a_x, b_x) が決まっているとき、フロー近似で各社員の訪問回数 X を求める
//   1. 初期 X を (T_i の比率 * L) などで設定
//   2. X -> X' の反復 (iter_count回)
//   3. 最後に総和を L にスケーリング
//-----------------------------------------------------
vector<double> compute_distribution(const vector<Employee> &emps,
                                    int iter_count) {
  // 初期 X を T_i 比率で分配
  double sumT = 0.0;
  for (auto &v : Tval) sumT += v;
  vector<double> X(N);
  if (sumT < 1e-9) {
    // 全員 0目標の特殊ケース -> 均等
    for (int i = 0; i < N; i++) X[i] = (double)L / N;
  } else {
    for (int i = 0; i < N; i++) {
      X[i] = (double)Tval[i] / sumT * L;
    }
  }
  // 反復
  for (int it = 0; it < iter_count; it++) {
    vector<double> Xnew(N, 0.0);
    for (int x = 0; x < N; x++) {
      double half = X[x] * 0.5;
      Xnew[emps[x].a_] += half;
      Xnew[emps[x].b_] += half;
    }
    // スケーリング
    double s = 0.0;
    for (auto &val : Xnew) s += val;
    if (s < 1e-9) {
      // フローが消滅するような特殊ケース -> 均等に再割り当て
      for (int i = 0; i < N; i++) {
        Xnew[i] = (double)L / N;
      }
    } else {
      double scale = (double)L / s;
      for (auto &val : Xnew) val *= scale;
    }
    X = Xnew;
  }
  return X;
}

// 誤差計算: sum of |X_i - T_i|
double calc_cost(const vector<double> &X) {
  double cost = 0.0;
  for (int i = 0; i < N; i++) {
    cost += fabs(X[i] - (double)Tval[i]);
  }
  return cost;
}

//-----------------------------------------------------
// [1] 貪欲割り当て (ratio = T_i/(X_i+eps) が大きい社員を優先)
//     - 同じ社員を2回選ばないようにする
//-----------------------------------------------------
void assign_edges_greedy(const vector<double> &X, vector<Employee> &emps) {
  // ratio 計算
  vector<double> ratio(N);
  for (int i = 0; i < N; i++) {
    ratio[i] = (double)Tval[i] / max(1e-9, X[i]);
  }
  // 各 x について
  //   ratio の大きい社員を上位2名  (ただし重複しないように)
  //   N=100ならソートでもOK
  for (int x = 0; x < N; x++) {
    vector<int> idx(N);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(),
         [&](int a, int b) { return ratio[a] > ratio[b]; });
    // 上位2名の社員が被らないように割り当て
    int bestA = idx[0], bestB = idx[1];
    if (bestA == bestB) {
      // 念のための補正(めったに発生しないはずだが)
      bestB = (bestB + 1) % N;
    }
    emps[x].a_ = bestA;
    emps[x].b_ = bestB;
  }
}

//-----------------------------------------------------
// [近傍操作の例]
//   (A) SingleNodeRandom : 1ノードの (a_x, b_x) を完全ランダム変更
//   (B) SwapEdges        : ランダムに2ノード x,y を選んで (a_x,b_x) と
//   (a_y,b_y) を交換 (C) GreedyReassignSubset : ノードの一部(例:
//   10～20個)を貪欲に再割り当て
//-----------------------------------------------------
void neighbor_single_node_random(vector<Employee> &emps, mt19937 &rng) {
  uniform_int_distribution<int> distN(0, N - 1);
  int x = distN(rng);
  int newA = distN(rng);
  int newB = distN(rng);
  emps[x].a_ = newA;
  emps[x].b_ = newB;
}

void neighbor_swap_edges(vector<Employee> &emps, mt19937 &rng) {
  uniform_int_distribution<int> distN(0, N - 1);
  int x = distN(rng);
  int y = distN(rng);
  if (x == y) return;
  // swap (a_x, b_x) <-> (a_y, b_y)
  swap(emps[x].a_, emps[y].a_);
  swap(emps[x].b_, emps[y].b_);
}

void neighbor_greedy_reassign_subset(vector<Employee> &emps, mt19937 &rng) {
  // まず現在のXを計算
  //   大きめのiter_count(例:5～10回) でもN=100なら許容範囲
  vector<double> X = compute_distribution(emps, 5);

  // ランダムにsubsetを選び、その部分だけ貪欲割り当て
  // subsetサイズは適宜調整(例:10～20程度)
  uniform_int_distribution<int> distN(0, N - 1);
  int subset_size = 10;  // 調整余地
  vector<int> chosen;
  chosen.reserve(subset_size);
  for (int i = 0; i < subset_size; i++) {
    chosen.push_back(distN(rng));
  }
  // ratioを使うためにも、計算し直す
  vector<double> ratio(N);
  for (int i = 0; i < N; i++) {
    ratio[i] = (double)Tval[i] / max(1e-9, X[i]);
  }
  // subset 内の x だけ (a_x, b_x) を再割り当て
  for (auto x : chosen) {
    // ソートで上位2名
    vector<int> idx(N);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(),
         [&](int a, int b) { return ratio[a] > ratio[b]; });
    int bestA = idx[0], bestB = idx[1];
    if (bestA == bestB) {
      bestB = (bestB + 1) % N;
    }
    emps[x].a_ = bestA;
    emps[x].b_ = bestB;
  }
}

//------------------------------------------------------------------------------
// メイン
//------------------------------------------------------------------------------
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  exec_input();

  // 初期従業員リスト
  vector<Employee> employees(N);
  for (int i = 0; i < N; i++) {
    employees[i] = Employee(i, Tval[i]);
  }

  // 1) 初期: (a_x, b_x) を全て "一巡サイクル" にしておく
  for (int i = 0; i < N; i++) {
    employees[i].a_ = (i + 1) % N;
    employees[i].b_ = (i + 1) % N;
  }
  // 2) Xを計算し、少し貪欲で改善
  {
    vector<double> X = compute_distribution(employees, 5);
    assign_edges_greedy(X, employees);
  }
  // 3) さらにもう一度フロー近似して評価
  vector<double> Xcur = compute_distribution(employees, 5);
  double best_cost = calc_cost(Xcur);
  vector<Employee> best_emps = employees;
  vector<double> best_dist = Xcur;

  // ---- 焼きなまし or ローカル探索 ----
  auto start_time = chrono::steady_clock::now();
  double timelimit = 1.95;  // 2000ms
  mt19937 rng((unsigned)time(nullptr));

  double T0 = 3000.0;   // 初期温度: 大きめに
  double Tfinal = 0.1;  // 最終温度
  int iteration_count = 0;

  while (true) {
    iteration_count++;
    auto now_time = chrono::steady_clock::now();
    double elapsed = chrono::duration<double>(now_time - start_time).count();
    if (elapsed > timelimit) break;  // time out

    double progress = elapsed / timelimit;  // 0 -> 1
    double temperature = T0 * pow(Tfinal / T0, progress);

    // 近傍操作をランダムに選択
    int nbtype = rng() % 3;
    // 0: SingleNodeRandom
    // 1: SwapEdges
    // 2: GreedyReassignSubset
    vector<Employee> new_emps = employees;
    if (nbtype == 0) {
      neighbor_single_node_random(new_emps, rng);
    } else if (nbtype == 1) {
      neighbor_swap_edges(new_emps, rng);
    } else {
      neighbor_greedy_reassign_subset(new_emps, rng);
    }

    // 新しい割り当てに対して X' を計算 (少し回数減らして高速化)
    vector<double> new_X = compute_distribution(new_emps, 3);
    double new_cost = calc_cost(new_X);

    double diff = new_cost - best_cost;
    if (diff < 0) {
      // 改善
      employees = new_emps;
      Xcur = new_X;
      best_cost = new_cost;
      best_emps = new_emps;
      best_dist = new_X;
    } else {
      // 焼きなまし
      double prob = exp(-diff / temperature);
      if (((double)rng() / rng.max()) < prob) {
        employees = new_emps;
        Xcur = new_X;
      }
    }

    // 適宜、何かのタイミングで "全ノード貪欲再割り当て" を混ぜる手もあり
    // 例: progress が 0.3, 0.6, 0.9 を超えたタイミングなど
    //   if(iteration_count % 200 == 0){
    //       assign_edges_greedy(Xcur, employees);
    //       Xcur = compute_distribution(employees, 3);
    //       double cst = calc_cost(Xcur);
    //       if(cst < best_cost){
    //           best_cost = cst;
    //           best_emps = employees;
    //           best_dist = Xcur;
    //       }
    //   }
  }

  // 出力
  exec_output(best_emps);
  cerr << "DONE: best_cost=" << best_cost
       << ", iteration_count=" << iteration_count << endl;

  return 0;
}
