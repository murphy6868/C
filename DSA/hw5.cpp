#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory.h>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<string>> ht;

int hashCode(string key)
{
    int code = key[0] * 97;
    for(int i=0 ; i<key.length() ; i++){
        code *= 101;
        code += key[i]*53;
        code %= 500000;
    }
    return code;
}

int inTable(string s)
{
    int index = hashCode(s);
    int l = ht[index].size();
    if(l == 0)return 0;
    for(int j=0; j<l; j++)
        if(ht[index][j] == s)return 1;
    return 0;
}

void Insert(string s, vector<string> &ed)
{
    int len = s.length();
    for(int j=0; j<=len; j++){
        s.insert(j, "0");
        for(int k='a'; k<='z'; k++){
            s[j] = k;
            ed.push_back(s);
        }
        s.erase(j, 1);
    }
}
void Delete(string s, vector<string> &ed)
{
    string t = s;
    int len = s.length();
    for(int j=0; j<len; j++){
        s.erase(j, 1);
        ed.push_back(s);
        s = t;
    }
}
void Substitute(string s, vector<string> &ed)
{
    string t = s;
    int len = s.length();
    for(int j=0; j<len; j++){
        char origin = s[j];
        for(int k='a'; k<='z'; k++){
            if(k == origin) continue ;
            s[j] = k;
            ed.push_back(s);
        }
        s = t;
    }
}
void Transpose(string s, vector<string> &ed)
{
    string t = s;
    int len = s.length();
    for(int j=0; j<len-1; j++){
        char ta = t[j];
        char tb = t[j+1];
        if(ta == tb) continue ;
        t[j] = tb;
        t[j+1] = ta;
        ed.push_back(t);
        t = s;
    }
}


int main(void)
{
    //FILE* fp = fopen("cmudict-0.7b.txt", "rb");
    FILE* fp = fopen("/tmp2/dsa2016_hw5/cmudict-0.7b", "rb");
    assert(fp != NULL);
    ht.resize(500000, vector<string>(0));
    char in[99];
    int trash = 126;
    while(trash--)
        fgets(in, 99, fp);

    int n = 133781;
    int num = 1;
    string last;
    while(n--){
        fgets(in, 99, fp);
        int pos = 0;
        string now;
        while((in[pos] >= 'A' && in[pos] <= 'Z') || in[pos] == '\'' || in[pos] == '.' || in[pos] == '-' || in[pos] == '_'){
            now += tolower(in[pos]);
            pos++;
        }
        if(now == last) continue ;
        ht[hashCode(now)].push_back(now);
        last = now;
        num++;
    }fclose(fp);

    char testcase[99];
    while(fgets(testcase, 99, stdin) != NULL){
        istringstream iss(testcase);
        string tcase;
        iss >> tcase;
        printf("%s ==>", tcase.c_str());
        if(inTable(tcase)){
            printf(" OK\n");
        }else{
            vector<string> ed;
            Insert(tcase, ed);
            Delete(tcase, ed);
            Substitute(tcase, ed);
            Transpose(tcase, ed);

                sort(ed.begin(), ed.end());
                vector<string>::iterator it = unique(ed.begin(), ed.end());
                ed.resize(distance(ed.begin(), it));

            int num_ed1 = ed.size();
            for(int h=0; h<num_ed1; h++){
                Insert(ed[h], ed);
                Delete(ed[h], ed);
                Substitute(ed[h], ed);
                Transpose(ed[h], ed);
            }

            vector<string> ans;
            int num_ed2 = ed.size();
            for(int h=0; h<num_ed2; h++)
                if(inTable(ed[h]))
                    ans.push_back(ed[h]);
            if(ans.size() == 0){
                printf(" NONE\n");
            }else{
                sort(ans.begin(), ans.end());
                vector<string>::iterator it = unique(ans.begin(), ans.end());
                ans.resize(distance(ans.begin(), it));
                int num_ans = ans.size();
                for(int h=0; h<num_ans; h++)
                        printf(" %s", ans[h].c_str());
                printf("\n");
            }
        }
    }
    return 0;
}

