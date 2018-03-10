#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
#include <memory.h>
#include <sstream>
#include <ctime>
using namespace std;

class buy_stock{
    public:
        buy_stock(int bid=0, int cli=0, int pri=0, int num=0){
            bidID = bid;
            clientID = cli;
            price = pri;
            number = num;
        }
        void cancel(){number = 0;}
        void deal(int num){number -= num;}
        bool finish(){return !number;}
        int get_price(){return price;}
        int get_num(){return number;}
        int get_clientID(){return clientID;}
        int get_bidID(){return bidID;}
    private:
        int bidID;
        int clientID;
        int price;
        int number;
};

class sell_stock{
    public:
        sell_stock(int bid=0, int cli=0, int pri=0, int num=0){
            bidID = bid;
            clientID = cli;
            price = pri;
            number = num;
        }
        void cancel(){number = 0;}
        void deal(int num){number -= num;}
        bool finish(){return !number;}
        int get_price(){return price;}
        int get_num(){return number;}
        int get_clientID(){return clientID;}
        int get_bidID(){return bidID;}
    private:
        int bidID;
        int clientID;
        int price;
        int number;
};

bool buy_cmp(buy_stock a, buy_stock b){
    if(a.get_price() == b.get_price())
        return a.get_bidID() > b.get_bidID();
    else
        return a.get_price() < b.get_price();
}
bool sell_cmp(sell_stock a, sell_stock b){
    if(a.get_price() == b.get_price())
        return a.get_bidID() > b.get_bidID();
    else
        return a.get_price() > b.get_price();
}

int maxdeal(int a, int b){return a<=b? a:b;}

int main()
{
    vector<buy_stock> buy;
    vector<sell_stock> sell;
    make_heap(buy.begin(), buy.end(), buy_cmp);
    make_heap(sell.begin(), sell.end(), sell_cmp);
    string strin;
    int deals = 0;
        int b, c, a, p, n;
    while(scanf("%d %d %d %d %d", &b, &c, &a, &p, &n) != EOF){
        buy_stock buy_temp(b, c, p, n);
        sell_stock sell_temp(b, c, p, n);
        switch(a){
            case 0:
                buy.push_back(buy_temp);
                push_heap(buy.begin(), buy.end(), buy_cmp);
                break ;
            case 1:
                sell.push_back(sell_temp);
                push_heap(sell.begin(), sell.end(), sell_cmp);
                break ;
            case 2:
                for(int j=0; j<buy.size(); j++){
                    if(buy[j].get_bidID() == p){
                        buy[j].cancel();
                        break ;
                    }
                }
                for(int j=0; j<sell.size(); j++){
                    if(sell[j].get_bidID() == p){
                        sell[j].cancel();
                        break ;
                    }
                }
                break ;
        }
        while(buy.size() && buy[0].finish()){
            pop_heap(buy.begin(), buy.end(), buy_cmp);
            buy.pop_back();
        }
        while(sell.size() && sell[0].finish()){
            pop_heap(sell.begin(), sell.end(), sell_cmp);
            sell.pop_back();
        }
        while(buy.size() && sell.size() && buy[0].get_price() >= sell[0].get_price()){
            int dealnum = maxdeal(buy[0].get_num(), sell[0].get_num());
            printf("%d\t%d\t%d\t%d\t%d\n", deals, buy[0].get_clientID(), sell[0].get_clientID(), sell[0].get_price(), dealnum);
            buy[0].deal(dealnum);
            sell[0].deal(dealnum);
            while(buy.size() && buy[0].finish()){
                pop_heap(buy.begin(), buy.end(), buy_cmp);
                buy.pop_back();
            }
            while(sell.size() && sell[0].finish()){
                pop_heap(sell.begin(), sell.end(), sell_cmp);
                sell.pop_back();
            }
            deals++;
        }
    }
    return 0;
}
