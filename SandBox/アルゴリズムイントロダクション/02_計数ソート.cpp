#include <bits/stdc++.h>
using namespace std;

void print(vector<int> vec) {
  for (auto v : vec) cout << v << " ";
  cout << endl;
}

/**
 * 長さnで、要素が0以上k以下であるような配列Aを計数ソートする
 */
vector<int> counting_sort(vector<int> A, int n, int k) {
  // B := ソート結果を格納する配列
  vector<int> B(n);
  // C := 補助領域
  vector<int> C(k + 1);

  for (int i = 0; i < n; i++) {
    C[A[i]]++;
  }
  // C[i] = 配列Aのうち、値がちょうどiである要素の個数
  print(C);
  // 累積和を取る
  for (int i = 1; i <= k; i++) {
    C[i] += C[i - 1];
  }
  // C[i] = 配列Aのうち、値がi以下である要素の個数
  print(C);

  // Aの最後から順に、AをBにコピーする
  for (int i = n - 1; i >= 0; i--) {
    B[C[A[i]] - 1] = A[i];
    C[A[i]]--;
  }

  return B;
}

/**
 * 長さnで、要素が0以上k以下であるような配列Aを計数ソートする
 */
vector<int> counting_sort_2(vector<int> A, int n, int k) {
  // B := ソート結果を格納する配列
  vector<int> B(n);
  // C := 補助領域
  vector<int> C(k + 1);
  vector<int> D(k + 1);

  // 各要素の個数を数える
  for (int i = 0; i < n; i++) {
    C[A[i]]++;
  }
  // 累積和を取る
  for (int i = 1; i <= k; i++) {
    C[i] += C[i - 1];
  }

  // 終端でなく始端のindexが分かるように直す（ついでに0-indexedになる）
  for (int i = k; i >= 1; i--) C[i] = C[i - 1];
  C[0] = 0;
  print(C);

  // Aの最後から順に、AをBにコピーする
  for (int i = 0; i < n; i++) {
    B[C[A[i]]] = A[i];
    C[A[i]]++;
  }

  return B;
}

int main() {
  vector<int> input = {2, 5, 3, 0, 2, 3, 0, 3};
  //   vector<int> input = {6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
  vector<int> output = counting_sort_2(input, (int)input.size(), 5);
  cout << "ソート前" << endl;
  print(input);
  cout << "ソート後" << endl;
  print(output);

  return 0;
}