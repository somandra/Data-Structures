#include<bits/stdc++.h>

using namespace std;

void max_sliding_window_naive(vector<int> const & A, int w) {

    deque<int> Qi(w);

    int i;
    for ( i = 0; i < w; i++)
    {
        while ((!Qi.empty()) && A[i] >= A[Qi.back()]) Qi.pop_back();
        Qi.push_back(i); 
    }

    for (; i < A.size(); ++i)
    {
        cout<<A[Qi.front()]<<" ";
         // Remove the elements which are out of this window 
        while ((!Qi.empty()) && Qi.front() <= i - w) 
            Qi.pop_front();
        // Remove all elements smaller than the currently 
        // being added element (remove useless elements) 
        while ((!Qi.empty()) && A[i] >= A[Qi.back()]) 
            Qi.pop_back(); 
  
        // Add current element at the rear of Qi 
        Qi.push_back(i); 
    }

    cout<<A[Qi.front()];
    
    


    // for (size_t i = 0; i < A.size() - w + 1; ++i) {
    //     int window_max = A.at(i);
    //     for (size_t j = i + 1; j < i + w; ++j)
    //         window_max = max(window_max, A.at(j));

    //     cout << window_max << " ";
    // }

    return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
