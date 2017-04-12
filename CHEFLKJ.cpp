#include<bits/stdc++.h>

using namespace std;

struct node{

    int domin   ;
    unordered_map<int, int> occ ;
} ST[375000];


int N, Q, found    ;
int arr[100002] ;
vector <int> soln   ;

inline void combine(int pos, int len){

    if(ST[pos].occ[ST[2*pos+1].domin] > (len / 2))
        ST[pos].domin = ST[2*pos+1].domin ;

    else if(ST[pos].occ[ST[2*pos+2].domin] > (len / 2))
            ST[pos].domin = ST[2*pos+2].domin   ;
    else
        ST[pos].domin = -1  ;
}

inline void build(int low, int high, int pos){

    if(low == high){
        ST[pos].domin = arr[low];
        ST[pos].occ[arr[low]] = 1;
        return ;
    }

    int mid = (low + high) / 2  ;
    build(low, mid, 2*pos+1)    ;
    build(mid+1, high, 2*pos+2) ;

    for(auto i : ST[2*pos+1].occ)
        ST[pos].occ[i.first] += i.second    ;
    for(auto i : ST[2*pos+2].occ)
        ST[pos].occ[i.first] += i.second    ;

    combine(pos, high - low + 1)    ;
}

inline void update(int idx, int low, int high, int pos, int value, int old){

    if(idx < low || idx > high)
        return ;
    if(low == high){
        ST[pos].occ.clear() ;
        ST[pos].domin = value   ;
        ST[pos].occ[value] = 1  ;
        arr[low] = value ;
        return ;
    }


    int mid = (low + high) / 2  ;
    update(idx, low, mid, 2*pos+1, value, old)  ;
    update(idx, mid+1, high, 2*pos+2, value, old)   ;

    ST[pos].occ[old] -= 1   ;
    ST[pos].occ[value] += 1 ;

    combine(pos, high - low + 1)    ;
}

inline void query(int i, int j, int low, int high, int pos){

    if(j < low || i > high)
        return ;

    if(i <= low && high <= j){
        soln.push_back(pos) ;
        return  ;
    }
    int mid = (low + high) / 2  ;
    query(i, j, low, mid, 2*pos+1)  ;
    query(i, j, mid+1, high, 2*pos+2)   ;
}


int main(){

    cin.sync_with_stdio(0)  ;
    cin >> N >> Q   ;

    for(int i = 0; i < N; i++)
        cin >> arr[i]   ;

    build(0, N-1, 0)    ;

    for(int i = 0; i < Q; i++){

        int type, u, v  ;
        cin >> type >> u >> v   ;

        if(type == 1){
            u-- ;
            update(u, 0, N-1, 0, v, arr[u]) ;
        }

        else{

            v-- ; u--;
            int len = v - u + 1  ;
            found = 0   ;
            soln.clear()    ;
            query(u, v, 0, N-1, 0)  ;
            for(int i = 0; i < soln.size(); i++){
                int Count = 0   ;
                for(int j = 0; j < soln.size(); j++)
                    Count += ST[soln[j]].occ[ST[soln[i]].domin] ;

                if(Count > (len / 2)){
                    found = 1   ;
                    cout << "Yes\n" ;
                    break ;
                }
            }
            if(!found)
                cout << "No\n"  ;
        }
    }
    return  0;
}
