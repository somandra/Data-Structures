#include <iostream>
#include <string>
#include <vector>

using std::string;

#define MAXCHAR 256

typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

// size_t PolyHash(const string& s){
//     static const size_t multiplier = 256;
//     static const size_t prime = 101;
//     unsigned long long hash = 0;
//     for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
//         hash = (hash * multiplier + s[i]) % prime;
//     return hash;
// }

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}

// std::vector<int> PreComputeHash(const string& t,size_t len_t, size_t len_p){
//     static const size_t multiplier = 256;
//     static const size_t prime = 101;
//     unsigned long long int n = len_t-len_p+1;
//     std::vector<int> H(n);
//     string s = t.substr(len_t-len_p);
//     H[len_t-len_p] = PolyHash(s);
//     unsigned long long y = 1;
//     for (size_t i = 1; i <=len_p; i++)
//     {
//         y = (((y*multiplier)%prime)+prime)%prime;
//     }
//     std::cout<<y<<"\n";
//     for (int i = len_t-len_p-1; i >=0; i--)
//     {
//         H[i] = (multiplier*H[i+1]+t[i]-y*t[i+len_p-1])%prime;
//         std::cout<<H[i+1]<<" "<<t[i]<<" "<<H[i]<<" "<<t[i+len_p]<<"\n";
//     }

//     return H;
// }

// std::vector<int> RabinKarp(const Data& input){
//     const string& p = input.pattern, t = input.text;
//     std::vector<int> result;
//     size_t pHash = PolyHash(p);
//     //std::cout<<pHash<<" "<<p.length()<<"\n";
//     std::vector<int> H = PreComputeHash(t,t.length(),p.length());
//     for(int i=0;i<=t.length()-p.length(); i++){
//         //size_t tHash = PolyHash(t.substr(i,p.length()));
//         //std::cout<<tHash<<" "<<t.substr(i,p.length())<<"\n";
//         std::cout<<pHash<<" "<<H[i]<<"\n";
//         if(pHash!=H[i]){
//             continue;
//         }
//         if(t.substr(i,p.length()).compare(p)==0){
//             result.push_back(i);
//         }
//     }
//     return result;
// }


std::vector<int> RabinKarp(const Data& input) {
    string pattern = input.pattern;
    string mainString = input.text;
    int prime = 101;
   int patLen = pattern.size();
   int strLen = mainString.size();
   int charIndex, pattHash = 0, strHash = 0, h = 1;
   std::vector<int> result;

   for(int i = 0; i<patLen-1; i++) {
      h = (h*MAXCHAR) % prime;    //calculating h = {d^(M-1)} mod prime
   }
   
   for(int i = 0; i<patLen; i++) {
      pattHash = (MAXCHAR*pattHash + pattern[i]) % prime;    //pattern hash value
      strHash = (MAXCHAR*strHash + mainString[i]) % prime;   //hash for first window
   }
   
   for(int i = 0; i<=(strLen-patLen); i++) {
      if(pattHash == strHash) {      //when hash values are same check for matching
         for(charIndex = 0; charIndex < patLen; charIndex++) {
            if(mainString[i+charIndex] != pattern[charIndex])
               break;
         }

         if(charIndex == patLen) {    //the pattern is found
            result.push_back(i);
         }
      }

      if(i < (strLen-patLen)) {    //find hash value for next window
         strHash = (MAXCHAR*(strHash - mainString[i]*h) + mainString[i+patLen])%prime;
         if(strHash < 0) {
            strHash += prime;    //when hash value is negative, make it positive
         }
      }
   }
   return result;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    //print_occurrences(get_occurrences(read_input()));
    print_occurrences(RabinKarp(read_input()));

    return 0;
}
