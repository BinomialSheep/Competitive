#include <bits/stdc++.h>
using namespace std;

void print(vector<string> vec) {
  for (auto v : vec) cout << v << " ";
  cout << endl;
}
void print(vector<int> vec) {
  for (auto v : vec) cout << v << " ";
  cout << endl;
}

vector<string> counting_sort(vector<string> A, int d) {
  // B := ソート結果を格納する配列
  vector<string> B(A.size());
  // C := 補助領域
  vector<int> C(26);

  for (int i = 0; i < (int)A.size(); i++) {
    C[A[i][d] - 'A']++;
  }
  // C[i] = 配列Aのうち、値がちょうどiである要素の個数
  print(C);
  // 累積和を取る
  for (int i = 1; i < 26; i++) {
    C[i] += C[i - 1];
  }
  // C[i] = 配列Aのうち、値がi以下である要素の個数
  print(C);

  // Aの最後から順に、AをBにコピーする
  for (int i = (int)A.size() - 1; i >= 0; i--) {
    B[C[A[i][d] - 'A'] - 1] = A[i];
    C[A[i][d] - 'A']--;
  }

  return B;
}

vector<string> radix_sort(vector<string> A, int n, int d) {
  for (int i = 0; i < d; i++) {
    // 下の桁から行う
    int idx = d - i - 1;
    A = counting_sort(A, idx);
    printf("下%d桁までソート後\n", i);
    print(A);
  }

  return A;
}

int main() {
  vector<string> input = {"COW", "DOG", "SEA", "RUG", "ROW", "MOB",
                          "BOX", "TAB", "BAR", "EAR", "TAR", "DIG",
                          "BIG", "TEA", "NOW", "FOX"};
  vector<string> output = radix_sort(input, (int)input.size(), 3);
  cout << "ソート前" << endl;
  print(input);
  cout << "ソート後" << endl;
  print(output);

  return 0;
}