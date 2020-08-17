#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;


class MinHeap{
    
  public:

  int num_workers_;
  vector< pair<int, int> > data_;

  void init(int num_workers_){
    for (int i = 0; i < num_workers_; i++)
    {
      data_.push_back(make_pair(i,0));
    }
  }

  void ChangePriority(int i,int p){
    int old_p = data_[i].second;
    data_[i] = make_pair(data_[i].first, p);
    if (p < old_p){
      ShiftUp(i);
    }
    else{
      ShiftDown(i);
    }
    ShiftDown(i);
  }

  void BuildHeap(){
    for (int i = num_workers_/2; i >= 0; i--)
    {
      ShiftDown(i);
    }
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

  bool CompareWorker(pair<int, int> w1,pair<int, int> w2){
    if(w1.second!=w2.second){
      return w1.second<w2.second;
    }
    else
    {
      return w1.first<w2.first;
    }
    
  }

  void ShiftUp(int i){
    while (i>0 && CompareWorker(data_[i], data_[Parent(i)]))
    {
      swap(data_[i],data_[Parent(i)]);
      i = Parent(i);
    }
    
  }

  void ShiftDown(int i){
    int minIndex = i;
    int l = LeftChild(i);
    if (l<data_.size() && CompareWorker(data_[l],data_[minIndex])){
      minIndex = l;
    }
    int r = RightChild(i);
    if (r<data_.size() && CompareWorker(data_[r],data_[minIndex])){
      minIndex = r;
    }

    if(i!=minIndex){
      swap(data_[i], data_[minIndex]);
      data_.push_back(make_pair(i,minIndex));
      ShiftDown(minIndex);
    }
  }



};

class JobQueue: public MinHeap {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    // vector<long long> next_free_time(num_workers_, 0);
    // for (int i = 0; i < jobs_.size(); ++i) {
    //   int duration = jobs_[i];
    //   int next_worker = 0;
    //   for (int j = 0; j < num_workers_; ++j) {
    //     if (next_free_time[j] < next_free_time[next_worker])
    //       next_worker = j;
    //   }
    //   assigned_workers_[i] = next_worker;
    //   start_times_[i] = next_free_time[next_worker];
    //   next_free_time[next_worker] += duration;
    // }
    MinHeap min_heap = MinHeap();
    min_heap.init(num_workers_);
    for (int i = 0; i < jobs_.size(); i++)
    {
      assigned_workers_[i] = min_heap.data_[0].first;
      start_times_[i] = min_heap.data_[0].second;
      min_heap.ChangePriority(0,min_heap.data_[0].second+jobs_[i]);
    }
    
    
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue = JobQueue();
  job_queue.Solve();
  return 0;
}
