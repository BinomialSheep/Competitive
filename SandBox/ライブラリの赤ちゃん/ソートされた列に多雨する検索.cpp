#include <algorithm>
#include <cassert>
#include <vector>

/*
ひつじにっきのテーマ
https://scrapbox.io/kemuniku/%E3%82%BD%E3%83%BC%E3%83%88%E3%81%95%E3%82%8C%E3%81%9F%E5%88%97%E3%81%AB%E5%AF%BE%E3%81%99%E3%82%8B%E6%A4%9C%E7%B4%A2
*/

template <typename T>
class SortedSearchSheep {
 public:
  std::vector<T> sortedVec;

  SortedSearchSheep(const std::vector<T>& vec) : sortedVec(vec) {
    std::sort(sortedVec.begin(), sortedVec.end());
  }

  typename std::vector<T>::iterator end() { return sortedVec.end(); }

  // i未満の最大の要素
  typename std::vector<T>::iterator maxElementLessThan(const T& i) {
    auto it = std::lower_bound(sortedVec.begin(), sortedVec.end(), i);
    if (it == sortedVec.begin()) {
      return sortedVec.end();
    }
    return --it;
  }

  // i以下の最大の要素
  typename std::vector<T>::iterator maxElementLessThanOrEqual(const T& i) {
    auto it = std::upper_bound(sortedVec.begin(), sortedVec.end(), i);
    if (it == sortedVec.begin()) {
      return sortedVec.end();
    }
    return --it;
  }

  // iより大きい最小の要素
  typename std::vector<T>::iterator minElementGreaterThan(const T& i) {
    return std::upper_bound(sortedVec.begin(), sortedVec.end(), i);
  }

  // i以上の最小の要素
  typename std::vector<T>::iterator minElementGreaterThanOrEqual(const T& i) {
    return std::lower_bound(sortedVec.begin(), sortedVec.end(), i);
  }

  // イテレータまでの要素の個数（仕切りのイメージ）
  size_t countElements(typename std::vector<T>::iterator it) {
    return std::distance(sortedVec.begin(), it);
  }
};

int main() {
  std::vector vec1 = {0, 0, 1, 1, 2, 2, 4, 4, 5, 5};

  SortedSearchSheep sss = (vec1);

  assert(*(sss.maxElementLessThan(1)) == 0);
  assert(*(sss.maxElementLessThanOrEqual(2)) == 2);
  assert(*(sss.maxElementLessThanOrEqual(3)) == 2);
  assert(*(sss.minElementGreaterThan(4)) == 5);
  assert(*(sss.minElementGreaterThanOrEqual(5)) == 5);

  assert(sss.maxElementLessThan(0) == sss.end());
  assert((sss.maxElementLessThanOrEqual(-1)) == sss.end());
  assert((sss.minElementGreaterThan(5)) == sss.end());
  assert((sss.minElementGreaterThanOrEqual(6)) == sss.end());

  // 実用的にはプラス1することが多い
  assert(sss.countElements((sss.maxElementLessThan(1))) + 1 == 2);
  assert(sss.countElements((sss.maxElementLessThanOrEqual(2))) == 5);
  assert(sss.countElements((sss.maxElementLessThanOrEqual(3))) == 5);
  assert(sss.countElements((sss.minElementGreaterThan(4))) == 8);
  assert(sss.countElements((sss.minElementGreaterThanOrEqual(5))) == 8);
  // 上を取る時はサイズから引くが、これも実用的にはマイナス1したくなる
  assert((int)sss.sortedVec.size() -
             sss.countElements((sss.maxElementLessThan(1))) - 1 ==
         8);
  assert(std::distance(sss.maxElementLessThan(1), sss.sortedVec.end()) ==
         (int)sss.sortedVec.size() -
             (int)sss.countElements((sss.maxElementLessThan(1))));
}
