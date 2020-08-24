#include <bits/stdc++.h>
using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<string> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    int size;
    vector<vector<string>> v;
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) { size = bucket_count;v.resize(size);}   
    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
    }

    void processQuery_Hashing(const Query& query) {
        if (query.type == "check") {
            for (size_t i = 0; i < v[query.ind].size(); i++)
            {
                cout<<v[query.ind][i]<<" ";
            }
            std::cout << "\n";
        } else {
            long long index = hash_func(query.s);
            if (query.type == "find"){
                if (!v[index].empty())
                {
                    for (size_t i = 0; i < v[query.ind].size(); i++)
                    {
                        if(v[index][i] == query.s){
                            writeSearchResult(true);
                            break;
                        }
                    }  
                }
                else
                {
                    writeSearchResult(false);
                }  
            }
            else if (query.type == "add") {
                if (!v[index].empty())
                {
                    bool flag = false;
                    for (size_t i = 0; i < v[query.ind].size(); i++)
                    {
                        if(v[index][i] == query.s){
                            flag = true;
                        }
                    } 
                    if(!flag) v[index].insert(v[index].begin(), query.s); 
                }
                else
                {
                    v[index][0] = query.s;
                }
                
                
               
            } else if (query.type == "del") {
                if (!v[index].empty())
                {
                    for (size_t i = 0; i < v[query.ind].size(); i++)
                    {
                        if(v[index][i] == query.s)
                            v[index].erase(v[index].begin()+index-1);
                            break;
                        }
                    }
                    if (v[index].size()==0)
                    {
                        v[index].clear();
                    }
                      
                }
            }
        }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            //processQuery(readQuery());
            processQuery_Hashing(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
