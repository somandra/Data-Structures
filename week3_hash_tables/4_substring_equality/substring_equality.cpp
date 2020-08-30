#include <bits/stdc++.h>

using namespace std;
#define m 1000000009
#define p 263


int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	vector<long long> p_pow (s.length());
	p_pow[0] = 1;
	for(size_t i=1; i<p_pow.size(); ++i){
    	p_pow[i] = (m + (p_pow[i-1] * p) % m) % m;
	}
	vector<long long> h (s.length());
	for (size_t i=0; i<s.length(); ++i){
		h[i] = (m + (s[i] - 'a' + 1) * p_pow[i] % m) % m;
		if(i){
			h[i] = (m + (h[i] + h[i-1]) % m) % m;
		}
	}
	vector<string> result;
	for (int i = 0; i < q; i++) {
		int a,b,len;
		cin >> a >> b >> len;
		if(a == b){      // just avoid extra calculation, saves little time
			result.push_back("Yes");
		}else{
			long long h1 = h[a+len-1] % m;
			if(a){
				h1 = (m + (h1 - h[a-1]) % m) % m;
			}
			long long h2 = h[b+len-1] % m;
			if(b){
				h2 = (m + (h2 - h[b-1]) % m) % m;
			}
			if (a < b && h1 * p_pow[b-a] % m == h2 % m || a > b && h1 % m == h2 * p_pow[a-b] % m){
				//cout << "Yes" << endl;
				result.push_back("Yes");
			}else{
				// cout << "No" << endl;
				result.push_back("No");
			}
		}
	}
	for (size_t i = 0; i < result.size(); i++)
	{
		cout<<result[i]<<"\n";
	}
	
}
