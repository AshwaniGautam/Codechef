#include<bits/stdc++.h>
#define MAX 100000000000000000LL

using namespace std	;

vector <int> adj[100002]	;
vector<pair<int, int> > tickets[100002]     ;
int N, M, Q     ;
long long int tree[375000], soln[100005]  ;


inline void build(int low, int high, int pos){

    if(low == high){

        tree[pos] = MAX   ;
        return ;
    }
    int mid = (low + high) / 2  ;
    build(low, mid, 2*pos+1)    ;
    build(mid+1, high, 2*pos+2) ;
    tree[pos] = MAX   ;
}

inline void update(int idx, int low, int high, int pos, long long int value){

    if(idx < low || idx > high)
        return ;

    if(low == high){
        tree[pos] = value     ;
        return ;
    }
    int mid = (low + high) / 2  ;
    update(idx, low, mid, 2*pos+1, value)  ;
    update(idx, mid+1, high, 2*pos+2, value)   ;
    tree[pos] = min(tree[2*pos+1], tree[2*pos+2]) ;

}
inline long long int query(int i, int j, int low, int high, int pos){

    if(j < low || i > high)
        return MAX  ;
    if(i <= low && high <= j)
        return tree[pos]  ;

    int mid = (low + high) / 2  ;
    return min(query(i, j, low, mid, 2*pos+1), query(i, j, mid+1, high, 2*pos+2))   ;

}

inline void dfs(int v, int pv, int h){

    update(h, 0, N-1, 0, soln[v])   ;
    for(auto i : adj[v]){

        if(i == pv)
            continue;
        for(auto j : tickets[i])
            soln[i] = min(1LL * soln[i], query(max(h - j.first + 1, 0), h, 0, N-1, 0) + j.second) ;
        dfs(i, v, h+1)  ;

    }
    update(h, 0, N-1, 0, MAX)   ;
}

int main(){
    int a, b, city, travel, cost ;
    cin >> N >> M ;
	for (int i = 0; i < N-1; i++){
		cin >> a >> b	;
		adj[b].push_back(a)	;
	}

	for (int i = 0; i < M; i++){
        cin >> city >> travel >> cost ;
        tickets[city].push_back(make_pair(travel, cost))    ;
	}

    build(0, N-1, 0)  ;

    for(int i = 1; i <= N; i++)
        soln[i] = MAX   ;

    soln[1] = 0     ;
    dfs(1, 0, 0)   ;

    cin >> Q    ;
    for(int i = 1;  i <= Q; i++){
        int u ;
        cin >> u ;
        cout << soln[u] << "\n"    ;
    }
	return 0	;
}
