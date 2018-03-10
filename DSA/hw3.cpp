#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
#include <memory.h>
#include <sstream>
using namespace std;
int p[30][30];
int R, C, N;

int r[30][15];
int c[30][15];
int rn[30];
int cn[30];

int rp[30];
int cp[30];
int rs[30];
int cs[30];

void prb(int row)
{
    int total_len = rn[row] - 1;
    for(int j=0; j<rn[row]; j++)
        total_len += r[row][j];
    int bigger = C - total_len + 1;
    int now = 0;
    for(int j=0; j<rn[row]; j++){
        now += r[row][j];
        if(r[row][j] >= bigger)
        {
            int k = now - 1;
            int n = r[row][j] - bigger + 1;
            while(n--){
                p[row][k] = 1;
                k--;
            }
        }
        now++;
    }
}
void pcb(int col)
{
    int total_len = cn[col] - 1;
    for(int j=0; j<cn[col]; j++)
        total_len += c[col][j];
    int bigger = R - total_len + 1;
    int now = 0;
    for(int j=0; j<cn[col]; j++){
        now += c[col][j];
        if(c[col][j] >= bigger)
        {
            int k = now - 1;
            int n = c[col][j] - bigger + 1;
            while(n--){
                p[k][col] = 1;
                k--;
            }
        }
        now++;
    }
}

int check_r(int row, int col)
{
    if(col == C-1 && rp[row] != rs[row])return 0;
    int temp[15];
    memset(temp, 0, 60);
    int section = 0;
    int newsec = 0;
    for(int j=0; j<=col; j++){
        while(j <= col && p[row][j] != 1)j++;
        while(j <= col && p[row][j] == 1){
            newsec = 1;
            temp[section]++;
            j++;
        }
        if(newsec)
            section++;
        newsec = 0;
    }
    if(col == C-1){
        for(int h=0; h<rn[row]; h++)
            if(temp[h] != r[row][h])
                return 0;
    }else if(p[row][col] == -1){
        for(int h=0; h<section; h++)
            if(r[row][h] != temp[h])
                return 0;
    }else if(p[row][col] == 1){
        for(int h=0; h<section-1; h++)
            if(r[row][h] != temp[h])
                return 0;
        if(temp[section-1] > r[row][section-1])
            return 0;
    }
    return 1;
}
int check_c(int row, int col)
{
    if(row == R-1 && cp[col] != cs[col])return 0;
    int temp[15];
    memset(temp, 0, 60);
    int section = 0;
    int newsec = 0;
    for(int j=0; j<=row; j++){
        while(j <= row && p[j][col] != 1)j++;
        while(j <= row && p[j][col] == 1){
            newsec = 1;
            temp[section]++;
            j++;
        }
        if(newsec)
            section++;
        newsec = 0;
    }
    if(row == R-1){
        for(int h=0; h<cn[col]; h++)
            if(temp[h] != c[col][h])
                return 0;
    }else if(p[row][col] == -1){
        for(int h=0; h<section; h++)
            if(c[col][h] != temp[h])
                return 0;
    }else if(p[row][col] == 1){
        for(int h=0; h<section-1; h++)
            if(c[col][h] != temp[h])
                return 0;
        if(temp[section-1] > c[col][section-1])
            return 0;
    }
    return 1;
}

void pp(int n)
{
    printf("%d\n",n);
    for(int j=0; j<R; j++)
    {
        for(int k=0; k<C; k++)
            if(p[j][k] == 1)
                printf("#");
            else if(p[j][k] == -1)
                printf(".");
            else
                printf("0");
        printf("\n");
    }
    printf("\n");
}

void dfs(int n)
{
    if(n == N){
        for(int j=0; j<R; j++)
        {
            for(int k=0; k<C; k++)
                if(p[j][k] == 1)
                    printf("#");
                else
                    printf(".");
            printf("\n");
        }
        exit(0);
    }
    int row = n/C;
    int col = n%C;
    if(p[row][col] != 0){
        //if(rp[row] <= rs[row] && cp[col] <= cs[col])
            if(check_r(row, col) && check_c(row, col))
                dfs(n+1);
        return ;
    }
    if(n%2 == 0){
        p[row][col] = 1;
        rp[row]++;
        cp[col]++;
        if(rp[row] <= rs[row] && cp[col] <= cs[col])
            if(check_r(row, col) && check_c(row, col))
                dfs(n+1);
        p[row][col] = -1;
        rp[row]--;
        cp[col]--;
        //if(rp[row] <= rs[row] && cp[col] <= cs[col])
            if(check_r(row, col) && check_c(row, col))
                dfs(n+1);
        p[row][col] = 0;
    }else{
        p[row][col] = -1;
        //if(rp[row] <= rs[row] && cp[col] <= cs[col])
            if(check_r(row, col) && check_c(row, col))
                dfs(n+1);
        p[row][col] = 1;
        rp[row]++;
        cp[col]++;
        if(rp[row] <= rs[row] && cp[col] <= cs[col])
            if(check_r(row, col) && check_c(row, col))
                dfs(n+1);
        p[row][col] = 0;
        rp[row]--;
        cp[col]--;
    }
    return ;
}


int main()
{
    string strin;
    getline(cin, strin);
    istringstream sso(strin);
    sso >> R >> C;
    N = R*C;
    memset(p, 0, 3600);
    memset(r, 0, 1800);
    memset(c, 0, 1800);
    memset(rs, 0, 120);
    memset(cs, 0, 120);

    for(int j=0; j<R; j++){
        getline(cin, strin);
        istringstream sso(strin);
        int k = 0;
        while(sso >> r[j][k]){
            rs[j] += r[j][k];
            k++;
        }
        rn[j] = k;
    }
    for(int j=0; j<C; j++){
        getline(cin, strin);
        istringstream sso(strin);
        int k = 0;
        while(sso >> c[j][k]){
            cs[j] += c[j][k];
            k++;
        }
        cn[j] = k;
    }

    for(int j=0; j<R; j++)
        prb(j);
    for(int j=0; j<C; j++)
        pcb(j);


    for(int j=0; j<R; j++){
        if(p[j][0] == 1){
            int cpos = 0;
            int len = r[j][0];
            while(len--){
                p[j][cpos] = 1;
                cpos++;
            }
            if(cpos == C)continue;
            p[j][cpos] = -1;
            cpos++;
            if(cpos == C)continue;
            if(p[j][cpos] == 1){
                len = r[j][1];
                while(len--){
                    p[j][cpos] = 1;
                    cpos++;
                }
                if(cpos < C)
                    p[j][cpos] = -1;
            }
        }
        if(p[j][C-1] == 1){
            int cpos = C-1;
            int len = r[j][rn[j]-1];
            while(len--){
                p[j][cpos] = 1;
                cpos--;
            }
            if(cpos == -1)continue;
            p[j][cpos] = -1;
            cpos--;
            if(cpos == -1)continue;
            if(p[j][cpos] == 1){
                len = r[j][rn[j]-2];
                while(len--){
                    p[j][cpos] = 1;
                    cpos--;
                }
                if(cpos >= 0)
                    p[j][cpos] = -1;
            }
        }
    }
    for(int j=0; j<C; j++){
        if(p[0][j] == 1){
            int cpos = 0;
            int len = c[j][0];
            while(len--){
                p[cpos][j] = 1;
                cpos++;
            }
            if(cpos == R)continue;
            p[cpos][j] = -1;
            cpos++;
            if(cpos == R)continue;
            if(p[cpos][j] == 1){
                len = c[j][1];
                while(len--){
                    p[cpos][j] = 1;
                    cpos++;
                }
                if(cpos < R)
                    p[cpos][j] = -1;
            }
        }
        if(p[R-1][j] == 1){
            int cpos = R-1;
            int len = c[j][cn[j]-1];
            while(len--){
                p[cpos][j] = 1;
                cpos--;
            }
            if(cpos == -1)continue;
            p[cpos][j] = -1;
            cpos--;
            if(cpos == -1)continue;
            if(p[cpos][j] == 1){
                len = c[j][cn[j]-2];
                while(len--){
                    p[cpos][j] = 1;
                    cpos--;
                }
                if(cpos >= 0)
                    p[cpos][j] = -1;
            }
        }
    }
//b bound
        memset(rp, 0, 120);
        memset(cp, 0, 120);
        for(int j=0; j<R; j++)
            for(int k=0; k<C; k++)
                if(p[j][k] == 1){
                    rp[j]++;
                    cp[k]++;
                }
        dfs(0);
        printf("NO SOL");
        return 0;
}
