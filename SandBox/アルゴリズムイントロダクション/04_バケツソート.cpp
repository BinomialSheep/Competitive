#include <bits/stdc++.h>
using namespace std;

void print(vector<int> vec) {
  for (auto v : vec) cout << v << " ";
  cout << endl;
}
void print(vector<vector<int>> vec) {
  for (int i = 0; i < (int)vec.size(); i++) {
    cout << i << ": ";
    for (auto v : vec[i]) cout << v << " ";
    cout << endl;
  }
}

vector<int> backet_sort(vector<int> A, int n) {
  vector<vector<int>> B(n);

  // 1桁目でバケツに入れる
  for (int i = 0; i < n; i++) {
    B[A[i] / 10].push_back(A[i]);
  }
  cout << "バケツに入れた後" << endl;
  print(B);

  // バケツの各区間をソートする
  for (int i = 0; i < n; i++) {
    stable_sort(B[i].begin(), B[i].end());
  }
  cout << "各区間のソート後" << endl;
  print(B);

  vector<int> ret;

  for (int i = 0; i < n; i++) {
    for (auto v : B[i]) ret.push_back(v);
  }

  return ret;
}

int main() {
  vector<int> input = {79, 13, 16, 64, 39, 20, 89, 53, 71, 42};
  vector<int> output = backet_sort(input, (int)input.size());
  cout << "ソート前" << endl;
  print(input);
  cout << "ソート後" << endl;
  print(output);

  return 0;
}