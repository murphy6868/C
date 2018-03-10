#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
    int total = 73209277;
struct data{
    int usid;
    int item;
    int resu;
    int time;
};
data a[73209277];
struct usid_item{
    int usid;
    int item;
    int resu;
};
usid_item b[73209277];
struct gtimes{
    int usid;
    int tota;
    int acce;
};
int c[2421058][2];
int get_time_sta(int time_num, int start, int enddd)
{
    if(a[start].time == time_num)
        return start;
    int mid;
    while(start <= enddd) {
        mid = start + (enddd - start) / 2;
        if(a[mid].time < time_num)
            start = mid+1;
        else if(a[mid].time > time_num)
            enddd = mid - 1;
        else{
            mid--;
            while(a[mid].time == time_num)
                mid--;
            return mid+1;
        }
    }
}
int get_time_end(int time_num, int start, int enddd)
{
    if(a[enddd].time == time_num)
        return enddd;
    int mid;
    while(start <= enddd) {
        mid = start + (enddd - start) / 2;
        if(a[mid].time < time_num)
            start = mid+1;
        else if(a[mid].time > time_num)
            enddd = mid - 1;
        else{
            mid++;
            while(a[mid].time == time_num)
                mid++;
            return mid-1;
        }
    }
}

int get_item_sta(int item_num, int start, int enddd)
{
    if(b[start].item == item_num)
        return start;
    int mid;
    while(start <= enddd) {
        mid = start + (enddd - start) / 2;
        if(b[mid].item < item_num)
            start = mid+1;
        else if(b[mid].item > item_num)
            enddd = mid - 1;
        else{
            mid--;
            while(b[mid].item == item_num)
                mid--;
            return mid+1;
        }
    }
    printf("878787\n");
    return 878787;
}

void accept(int u, int i, int t)
{
    int k = get_time_sta(t, 0, total-1);
    while(a[k].time == t) {
        if(a[k].usid == u && a[k].item == i)
        {
            printf("%d\n", a[k].resu);
            return ;
        }
        k++;
    }
}

void items(int u1, int u2)
{
    int EMPTY = 1;
    int given_u1 = 0;
    int given_u2 = 0;
    int item = b[0].item;
    for(int j=0; j<total; j++) {
        if(b[j].item != item)
        {
            item = b[j].item;
            u1 = 0;
            u2 = 0;
        }
        if(b[j].usid == u1){
            given_u1 = 1;
            if(given_u2){
                printf("%d\n", item);
                EMPTY = 0;
                given_u1 = given_u2 = 0;
                while(b[j].item == item)
                    j++;
                item = b[j].item;
                j--;
            }
        }else if(b[j].usid == u2){
            given_u2 = 1;
            if(given_u1){
                printf("%d\n", item);
                EMPTY = 0;
                given_u1 = given_u2 = 0;
                while(b[j].item == item)
                    j++;
                item = b[j].item;
                j--;
            }
        }
    }
    if(EMPTY)
        printf("EMPTY\n");
}

int users(int i1, int i2, int t1, int t2)
{
    int start = get_time_sta(t1, 0, total-1);
    int enddd = get_time_end(t2, 0, total-1);
    vector<int> usid_i1;
    vector<int> usid_i2;
    for(int j=start; j<=enddd; j++) {
        if(a[j].item == i1 && usid_i1.end() == find(usid_i1.begin(), usid_i1.end(), a[j].usid))
            usid_i1.push_back(a[j].usid);
        else if(a[j].item == i2)
            usid_i2.push_back(a[j].usid);
    }
    sort(usid_i1.begin(), usid_i1.end());
    int sizeof_users = usid_i1.size();
    int EMPTY = 1;
    for(int j=0; j<sizeof_users; j++)
        if(usid_i2.end() != find(usid_i2.begin(), usid_i2.end(), usid_i1[j])) {
            printf("%d\n", usid_i1[j]);
            EMPTY = 0;
        }
    if(EMPTY)
        printf("EMPTY\n");
}

void ratio_(int i, int thereshould)
{
    int k = get_item_sta(i, 0, total);
    int ac = 0;
    int to = 0;
    while(b[k].item == i) {
        if(c[b[k].usid][0] > thereshould)
        {
            to ++;
            if(b[k].resu == 1)
                ac ++;
        }
        k++;
    }
    printf("%d/%d\n", ac, to);
}

void findtime_item(int i, const vector<int>& uss)
{
    int EMPTY = 1;
    for(int j=0; j<total; j++) {
        if(a[j].item != i)
            continue ;
        if(find(uss.begin(), uss.end(), a[j].usid) != uss.end())
        {
            printf("%d\n", a[j].time);
            EMPTY = 0;
            int ttt = a[j].time;
            while(a[j].time == ttt)
                j++;
            j--;
        }
    }
    if(EMPTY)
        printf("EMPTY\n");
}

void read_data(FILE *fp, data &in)
{
    in.usid = in.item = in.time = 0;
    char c = fgetc(fp);
    do{
        in.usid = in.usid*10 + c-'0';
        c = fgetc(fp);
    }while(!isspace(c));
    while(isspace(c)){
        c = fgetc(fp);
    }
    do{
        in.item = in.item*10 + c-'0';
        c = fgetc(fp);
    }while(!isspace(c));
    while(isspace(c)){
        c = fgetc(fp);
    }
        if(c == '-'){
            in.resu = -1;
            c = fgetc(fp);            c = fgetc(fp);

        }else{
            in.resu = 1;
            c = fgetc(fp);
        }
    while(isspace(c)){
        c = fgetc(fp);
    }
    do{
        in.time = in.time*10 + c-'0';
        c = fgetc(fp);
    }while(c != '\n');
}

int cmp_item(const void *d1,const void *d2)
{
    usid_item *data1 = (usid_item*)d1;
    usid_item *data2 = (usid_item*)d2;
    if(data1->item < data2->item)
        return -1;
    else if(data1->item > data2->item)
        return 1;
    else
        return 0;
}

int main()
{
       //    FILE *fp = fopen("rec_log_train.txt", "rb"); // /tmp2/KDDCUP2012/track1/rec_log_train.txt
          FILE *fp = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt", "rb"); // /tmp2/KDDCUP2012/track1/rec_log_train.txt
        for(int j=0; j<total; j++){
            read_data(fp, a[j]);
            b[j].usid = a[j].usid;
            b[j].item = a[j].item;
            b[j].resu = a[j].resu;
            int k = j-1;
            while(k >= 0 && a[j].time == a[k].time){
                if(a[j].usid == a[k].usid&&
                   a[j].item == a[k].item&&
                   a[j].resu == a[k].resu)
                {
                    j--;
                    total--;
                    break ;
                }
                k--;
            }
        }
        for(int j=0; j<total; j++) {
            c[a[j].usid][0] = c[a[j].usid][1] = 0;
        }
        for(int j=0; j<total; j++) {
            c[a[j].usid][0]++;
            if(a[j].resu==1)
                c[a[j].usid][1]++;
        }
        qsort(b, total, sizeof(usid_item), cmp_item);
    int n = 0;
    scanf("%d", &n);
    char query[16];
    while(n--) {
        scanf("%s", query);
        switch(query[0]) {
            case 'a':
                int u, i, t;
                scanf("%d %d %d", &u, &i, &t);
                accept(u, i, t);
                break ;
            case 'i':
                int u1, u2;
                scanf("%d %d", &u1, &u2);
                items(u1, u2);
                break ;
            case 'u':
                int i1, i2, t1, t2;
                scanf("%d %d %d %d", &i1, &i2, &t1, &t2);
                users(i1, i2, t1, t2);
                break ;
            case 'r':
                int ii, thereshould;
                scanf("%d %d", &ii, &thereshould);
                ratio_(ii, thereshould);
                break ;
            case 'f':
                vector<int> uss;
                int iii;
                int uuu;
                scanf("%d", &iii);
                while(scanf("%d", &uuu) == 1)
                    uss.push_back(uuu);
                findtime_item(iii, uss);
                break ;
        }
    }
    return 0;
}
