#include <bits/stdc++.h>
using namespace std;

// 便利マクロ
#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(v) (v).begin(), (v).end()

constexpr int input_N = 100;
constexpr int input_L = 500000;
vector<int> input_T(input_N);

class Employee {
 public:
  int id_, target_;
  int a_, b_;
  // デバッグ用の変数(本質的には不要)
  int actial_count_ = 0;
  int predict_count_ = 0;

  Employee() {}
  Employee(int id, int target) : id_(id), target_(target) {}
};

// 入力を受け取る
void exec_input() {
  int tmpN, tmpL;
  cin >> tmpN >> tmpL;  // 問題文上は固定だが一応読み込み
  rep(i, input_N) cin >> input_T[i];
}

// (a_i, b_i) を出力
void exec_output(vector<Employee> &employee_list) {
  // id_ が 0,1,2,... の順になるようソート
  sort(all(employee_list), [](auto &a, auto &b) { return a.id_ < b.id_; });

  // 各行: a_i b_i
  rep(i, input_N) {
    cout << employee_list[i].a_ << " " << employee_list[i].b_ << "\n";
  }
  cout << flush;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // 1) 入力
  exec_input();

  // 2) Employee配列を準備
  vector<Employee> employees;
  employees.reserve(input_N);
  rep(i, input_N) { employees.emplace_back(i, input_T[i]); }

  //--------------------------------------------------------------------------
  // 3) 各社員 i の「入ってくる辺の本数」k_i を計算 (合計200本)
  //    k_i = floor(T_i / 2500) + 調整
  //--------------------------------------------------------------------------
  vector<int> k(input_N);
  vector<double> frac(input_N);  // 小数部分を保持
  long long sumK = 0;

  // まず k_i = floor(T_i / 2500)
  rep(i, input_N) {
    double val = double(employees[i].target_) / 2500.0;
    int base = (int)floor(val);
    k[i] = base;
    frac[i] = val - base;  // 小数部
    sumK += base;
  }

  // 合計が 200 本になるように微調整
  {
    int diff = 200 - sumK;
    // 小数部分が大きい順/小さい順にソートするための index リスト
    vector<int> idx(input_N);
    iota(all(idx), 0);

    if (diff > 0) {
      // remainder(小数部) が大きい人から順に +1
      sort(all(idx), [&](int a, int b) { return frac[a] > frac[b]; });
      rep(i, diff) { k[idx[i]]++; }
    } else if (diff < 0) {
      diff = -diff;
      // remainder が小さい人から順に -1
      sort(all(idx), [&](int a, int b) { return frac[a] < frac[b]; });
      rep(i, diff) { k[idx[i]]--; }
    }
    // これで sum(k[i]) == 200 は保証される
  }

  //--------------------------------------------------------------------------
  // 4) k_i 個の「スロット」を社員 i ごとに用意 → slots に i を詰める
  //    ( slots.size() == 200 )
  //--------------------------------------------------------------------------
  vector<int> slots;
  slots.reserve(200);
  rep(i, input_N) {
    rep(cnt, k[i]) { slots.push_back(i); }
  }
  // ここで slots は「サイズ 200」のベクタ。内容は社員ID。

  // slots をシャッフル
  {
    random_device rd;
    mt19937 g(rd());
    shuffle(all(slots), g);
  }

  //--------------------------------------------------------------------------
  // 5) 社員 j が 2 本ずつ辺 (a_j, b_j) を出す
  //    → slots から 2 コずつ割り当てる
  //--------------------------------------------------------------------------
  // 今回は j=0..99 の順に取り出すサンプル
  // ( j の順もランダムにしたければここでシャッフルしても可 )
  rep(j, input_N) {
    // slots の index: 2*j, 2*j+1
    int idxA = 2 * j;
    int idxB = 2 * j + 1;
    employees[j].a_ = slots[idxA];
    employees[j].b_ = slots[idxB];
  }

  //--------------------------------------------------------------------------
  // 6) 出力
  //--------------------------------------------------------------------------
  exec_output(employees);

  return 0;
}
