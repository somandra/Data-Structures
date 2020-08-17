#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;
using std::floor;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int LeftChild(int i){
    return 2*i+1;
  }

  int RightChild(int i){
    return 2*(i+1);
  }

  int Parent(int i){
    return (i-1)/2;
  }

  void ShiftDown(int i){
    int minIndex = i;
    int l = LeftChild(i);
    if (l<data_.size() && data_[l]<data_[minIndex]){
      minIndex = l;
    }
    int r = RightChild(i);
    if (r<data_.size() && data_[r]<data_[minIndex]){
      minIndex = r;
    }

    if(i!=minIndex){
      swap(data_[i], data_[minIndex]);
      swaps_.push_back(make_pair(i,minIndex));
      ShiftDown(minIndex);
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    // for (int i = 0; i < data_.size(); ++i)
    //   for (int j = i + 1; j < data_.size(); ++j) {
    //     if (data_[i] > data_[j]) {
    //       swap(data_[i], data_[j]);
    //       swaps_.push_back(make_pair(i, j));
    //     }
    //   }

    int size = data_.size();
    for(int i=size/2;i>=0;i--){
      ShiftDown(i);
    }

  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
