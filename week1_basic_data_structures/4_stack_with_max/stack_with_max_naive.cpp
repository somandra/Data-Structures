#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;

  public:

    void Push(int value) {
        stack.push_back(value);
    }

    int Pop() {
        assert(stack.size());
        int top = stack[stack.size()-1];
        stack.pop_back();
        return top;
    }

    int Max() const {
        if(stack.size()==0){
            return -1;
        }
        assert(stack.size());
        return stack[stack.size()-1];
        //return *max_element(stack.begin(), stack.end());
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;
    StackWithMax stack1;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
            //cout<<stack1.Max()<<"\n";
            if(std::stoi(value)>=stack1.Max()){
                //cout<<"Changing Max"<<"\n";
                stack1.Push(std::stoi(value));
            } else {
                stack1.Push(stack1.Max());
            }
        }
        else if (query == "pop") {
            int top = stack.Pop();
            int top1 = stack1.Pop();
        }
        else if (query == "max") {
            cout << stack1.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}