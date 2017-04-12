#include <bits/stdc++.h>
#define gc getchar_unlocked
using namespace std;

struct node{

    int left, right, K, idx ;

}   ;

int N, Q, BLOCK_SIZE;
int arr[200002], answers[200002], above[200000];
node queries[200002]    ;
unordered_map<int, int> frequency;

inline void add(int x){

    above[frequency[x]] ++;
    frequency[x]++  ;

}

inline void remove(int x){

    frequency[x]--   ;
    above[frequency[x]]--   ;

}

inline bool cmp(node x, node y){

    int x_block = x.left / BLOCK_SIZE   ;
    int y_block = y.left / BLOCK_SIZE   ;
    if(x_block != y_block)
        return x_block < y_block    ;
    return x.right < y.right   ;
}


int main(){

    cin.sync_with_stdio(false);
    int t;
    cin >> t    ;

    while(t--){

        frequency.clear();
        memset(above, 0, sizeof(above)) ;
        cin >> N >> Q   ;
        BLOCK_SIZE = static_cast<int>(sqrt(N))  ;
        for(int i = 0; i < N; i++)
            cin >> arr[i]   ;

        for(int i = 0; i < Q; i++){
            int L, R, K ;
            cin >> L >> R >> K ;
            L-- ; R-- ;
            queries[i].left = L ;
            queries[i].right = R    ;
            queries[i].K = K    ;
            queries[i].idx = i  ;
        }

        sort(queries, queries + Q, cmp) ;

        int m_left = queries[0].left    ;
        int m_right = m_left-1    ;

        for(int i = 0; i < Q; i++){

            int left = queries[i].left     ;
            int right = queries[i].right    ;

            while(m_right < right){

                m_right++   ;
                add(arr[m_right])   ;
            }
            while(m_right > right){


                remove(arr[m_right])    ;
                m_right--   ;

            }
            while(m_left < left){

                remove(arr[m_left]) ;
                m_left++    ;
            }

            while(m_left > left){
                m_left--    ;
                add(arr[m_left])    ;
            }

            answers[queries[i].idx] = above[0] - above[queries[i].K];
        }
    for(int i = 0; i < Q; i++)
        cout << answers[i] << "\n"  ;
    }

}
