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

    double marray[1000];
    double narray[100];
    double table[100][1000];
double mini(double a, double b)
{
    return  a<b? a: b;
}
double abss(double a)
{
    return a>0? a: -a;
}

int main()
{
    int m;
    int n;

    scanf("%d", &m);
    for(int j=0; j<m; j++)
        scanf("%lf", &marray[j]);
    scanf("%d", &n);
    for(int j=0; j<n; j++)
        scanf("%lf", &narray[j]);

    table[0][0] = abss(marray[0] - narray[0]);
    for(int i=1; i<n; i++)
        table[i][i] = abss(marray[i] - narray[i]) + table[i-1][i-1];
    for(int k=1; k<m; k++)
        table[0][k] = abss(narray[0] - marray[k]) + table[0][k-1];
    for(int j=1; j<n; j++)
        for(int k=j+1; k<m; k++){
            table[j][k] = mini(table[j-1][k-1], table[j][k-1]) +
            abss(marray[k] - narray[j]);
        }
    int minpos = 0;
    for(int h=1; h<n; h++)
        if(table[minpos][m-1] > table[h][m-1])
            minpos = h;
    printf("%f\n", table[minpos][m-1]);
    int a = minpos, b = m-1;
    int path[99];
    int len = 0;
    while(a != 0){
        if(table[a][b] - table[a-1][b-1] != abss(marray[b] - narray[a]))
            b--;
        else{
            path[len] = b;
            a--;
            b--;
            len++;
        }
    }
    printf("0 ");
    for(int h=len-1; h>=0; h--)
        printf("%d ", path[h]);
    return 0;
}
