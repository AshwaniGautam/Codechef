#include<bits/stdc++.h>

using namespace std;

struct node{

    int value, zeroes;

};

int N, Q, weight[100010], starting[100010], ending[100010], tour[100010],pos ;
char que   ;
node ST[375000] ;
vector<int> tree[100010]    ;

inline void build(int low, int high, int pos){

    if(low == high){
        ST[pos].value = weight[tour[low]] ;
        if(ST[pos].value == 0)
            ST[pos].zeroes = 1    ;
      //  cout << low << " " << ST[pos].value << " " << ST[pos].zeroes << " " << pos << endl;
        return ;
    }
    int mid = (low + high) / 2  ;
    build(low, mid, 2*pos+1)    ;
    build(mid+1, high, 2*pos+2) ;
    ST[pos].zeroes = ST[2*pos+1].zeroes + ST[2*pos+2].zeroes    ;

}

inline void update(int idx, int low, int high, int pos, int val){

    if(idx < low || idx > high)
        return ;
    if(low == high){
        ST[pos].value = val ;
        if(ST[pos].value == 0)
            ST[pos].zeroes = 1  ;
        else
            ST[pos].zeroes = 0  ;
        return ;
    }
    int mid = (low + high) / 2  ;
    update(idx, low, mid, 2*pos+1, val) ;
    update(idx, mid+1, high, 2*pos+2, val)   ;
    ST[pos].zeroes = ST[2*pos+1].zeroes + ST[2*pos+2].zeroes    ;
}

inline int query(int i, int j, int low, int high, int pos){

    if(j < low || i > high)
        return 0 ;
    if(i <= low && high <= j)
        return ST[pos].zeroes   ;
    int mid = (low + high) / 2  ;
    return query(i, j, low, mid, 2*pos+1) + query(i, j, mid+1, high, 2*pos+2)   ;
}

inline void ETT(int v, int pv){

    tour[pos] = v   ;
    starting[v] = pos++    ;

    for(auto i : tree[v])
        if(i != pv)
            ETT(i, v)   ;

    ending[v] = pos - 1;
}

int main(){

    cin.sync_with_stdio(0)  ;
    cin >> N >> Q   ;

    for(int i = 0; i < N-1; i++){
        int u, v    ;
        cin >> u >> v   ;
        tree[u].push_back(v)    ;
        tree[v].push_back(u)    ;
    }

    for(int i = 1; i <= N;  i++)
        cin >> weight[i]    ;

    ETT(1, 0)   ;

    for(int i = 1; i <= N; i++)
        cout << starting[i] << " "  ;
    cout << endl;
    for(int i = 1; i <= N; i++)
        cout << ending[i] << " "    ;
    cout << endl;


    build(0, N-1, 0)    ;

    for(int i = 0; i < Q; i++){

        cin >> que  ;
        if(que == 'U'){
            int u, v    ;
            cin >> u >> v   ;
            update(starting[u], 0, N-1, 0, v)    ;
        }
        else{
            int v   ;
            cin >> v    ;
            cout << query(starting[v], ending[v], 0, N-1, 0) << "\n" ;
        }

    }

    return 0    ;
}
