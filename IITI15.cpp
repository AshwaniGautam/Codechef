    #include <bits/stdc++.h>

    using namespace std ;

    struct node{
        int left, right, idx    ;
    }   ;

    int N, Q, MAXN = 20001 ; ;
    int  BLOCK_SIZE ;
    node queries[20002]    ;
    long long int answers[20001] ;
    int ST[80000] ;
    int arr[20001] ;

    set<int> myset   ;
    unordered_map<int, int> mymap   ;

    inline bool cmp(node A, node B){

        if(A.left / BLOCK_SIZE != B.left / BLOCK_SIZE)
            return A.left / BLOCK_SIZE < B.left / BLOCK_SIZE    ;
        return A.right < B.right;
    }

    inline void update(int i, int low, int high, int pos, int value) {

        if (i < low || i > high)
            return ;
        if(low == high){
            ST[pos] += value   ;
            return  ;
        }
        int mid = (low + high) / 2  ;
        update(i, low, mid, 2*pos+1, value) ;
        update(i, mid+1, high, 2*pos+2, value)  ;
        ST[pos] = ST[2*pos+1] + ST[2*pos+2] ;

    }

    inline long long int query(int i, int j, int low, int high, int pos){

        if(j < low || i > high)
            return 0    ;
        if (i<=low && high <=j)
            return ST[pos]  ;
        int mid = (low+high) / 2    ;
        return(query(i, j, low, mid, 2*pos+1)+query(i, j, mid+1, high, 2*pos+2)   );
    }

    int main(){
        cin.sync_with_stdio(false)  ;
        cin >> N;
        BLOCK_SIZE = static_cast<int>(sqrt(N));

        for(int i = 0; i < N; i++){
            cin >> arr[i]   ;
            myset.insert(arr[i]);
        }

        int j = 1;
        for(auto iter : myset){
            mymap[iter] = j;
            j++;
        }

        for (int i = 0; i < N; i++)
            arr[i] = mymap[arr[i]] ;

        cin >> Q    ;
        for(int i = 0; i < Q; i++){
            int u, v    ;
            cin >> u >> v   ;
            u-- ;v--;
            queries[i].left = u ;
            queries[i].right = v    ;
            queries[i].idx = i  ;
        }

        sort(queries, queries + Q, cmp) ;

        int m_left = 0, m_right = -1 ;
        long long int curr_answer = 0 ;

        for(int i = 0; i < Q; i++){

            int left = queries[i].left   ;
            int right = queries[i].right   ;

            while(m_right < right){

                m_right++ ;
                long long int inv = query(arr[m_right]+1, MAXN, 0, MAXN, 0)  ;
                update(arr[m_right], 0, MAXN, 0, 1)  ;
                curr_answer += inv ;

            }
            while(m_right > right){

                long long int inv = query(arr[m_right]+1, MAXN, 0, MAXN, 0)  ;
                update(arr[m_right], 0, MAXN, 0, -1)  ;
                curr_answer -= inv  ;
                m_right--   ;

            }
            while(m_left < left){
                long long int inv = query(0, arr[m_left]-1, 0, MAXN, 0)    ;
                update(arr[m_left], 0, MAXN, 0, -1)  ;
                m_left++ ;
                curr_answer -= inv   ;

            }
            while(m_left > left){

                m_left--;
                long long int inv = query(0, arr[m_left]-1, 0, MAXN, 0)    ;
                update(arr[m_left], 0, MAXN, 0, 1)  ;
                curr_answer += inv   ;

            }

            answers[queries[i].idx] = curr_answer    ;
        }
        for(int i = 0; i < Q; i++)
            cout << answers[i] << "\n"  ;
        return 0    ;
    }
