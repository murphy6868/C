#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
#include <memory.h>
#include <sstream>
using namespace std;

int n;
void stack_output(vector<int> num, vector<int> in, vector<int> out){
    if(out.size() == n){
        for(int j=0; j<n; j++)
            printf("%d ", out[j]);
        printf("\n");
        return ;
    }
    if(num.size()){
        int temp = num.back();
        num.pop_back();
        in.push_back(temp);
        stack_output(num, in, out);
        temp = in.back();
        in.pop_back();
        num.push_back(temp);
    }
    if(in.size()){
        int temp = in.back();
        in.pop_back();
        out.push_back(temp);
        stack_output(num, in, out);
    }
}

int main()
{
    scanf("%d", &n);
    vector<int> num, in, out;
    for(int j=n; j>0; j--){
        num.push_back(j);
    }
    stack_output(num, in, out);
    return 0;
}
