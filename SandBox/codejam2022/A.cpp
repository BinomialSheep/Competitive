#include <iostream>
using namespace std;

void printFirstBorder(int c) {
  cout << "..";
  for (int i = 1; i < c; i++) {
    cout << '+' << '-';
  }
  cout << '+' << endl;
}

void printBorder(int c) {
  for (int i = 0; i < c; i++) {
    cout << '+' << '-';
  }
  cout << '+' << endl;
}

void printFirstCell(int c) {
  cout << "..";
  for (int i = 1; i < c; i++) {
    cout << '|' << '.';
  }
  cout << '|' << endl;
}

void printCell(int c) {
  for (int i = 0; i < c; i++) {
    cout << '|' << '.';
  }
  cout << '|' << endl;
}

int main() {
  /* input */
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int r, c;
    cin >> r >> c;
    cout << "Case #" << i + 1 << ":" << endl;
    printFirstBorder(c);
    printFirstCell(c);
    for (int j = 1; j < r; j++) {
      printBorder(c);
      printCell(c);
    }
    printBorder(c);
  }

  /* solve */

  /* output */

  return 0;
}