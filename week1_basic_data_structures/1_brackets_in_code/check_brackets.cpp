#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;


struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    int flag = 0;

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_brackets_stack.push(Bracket(next,position));
            
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(opening_brackets_stack.empty()){
                flag = position+1;
                break;
            }
            Bracket top = opening_brackets_stack.top();
            if(!top.Matchc(next)){
                flag = position+1;
                break;
            }
            opening_brackets_stack.pop();
        }
    }

    if(flag){
        cout<<flag;
    }
    else{
        if(opening_brackets_stack.empty()) cout<<"Success"<<"\n";
        else{
            cout<<opening_brackets_stack.top().position+1<<" ";
        }
    }

    // Printing answer, write your code here

    return 0;
}
