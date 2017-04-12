#include <stdio.h>
#include <iostream>
#include <string.h>
# define INF 1ll << 60 			//lulz
#define N 100099

using namespace std;

int array[N]	;

struct node{

	int two_power	;
	int five_power	;
	int sol			;
	int lazy_two	;
	int lazy_five	;
	int Left;

};

struct fact
{
	int two 	;
	int five 	;
};

node ST[350000]	;
fact array_fact[N]	;

int power(int n, int mult){

	int total = 0	;
	while(!(n % mult)){
		total ++	;
		n /= mult			;	
	}

	return total	;		
}

void combine(int pos, int low, int high){

	ST[pos].two_power  = ST[2*pos+1].two_power  + ST[2*pos+2].two_power		;
	ST[pos].five_power = ST[2*pos+1].five_power + ST[2*pos+2].five_power	;
	ST[pos].Left = -1 	;

}

void factorial(){

	for (int i = 2; i < N; i++){

		array_fact[i].two  = array_fact[i-1].two  + power(i, 2)	;
		array_fact[i].five = array_fact[i-1].five + power(i, 5)	;

	}

}

void build(int i, int j, int pos, int low, int high){

	if(j < low || i > high)
		return 	;	

	if (low == high){

		ST[pos].two_power  = power(array[low], 2)	;
		ST[pos].five_power = power(array[low], 5)	;
		ST[pos].Left = -1 	;
		return ;
	}

	int mid = (low + high) / 2			;
	build(i, j, 2*pos + 1, low, mid)	;
	build(i, j, 2*pos + 2, mid+1, high)	;

	combine(pos, low, high)	;
}

void pushdown_reset(int low, int high, int pos, int two, int five){

	ST[pos].two_power = array_fact[high - ST[pos].Left + 1].two  - array_fact[low - ST[pos].Left].two  + two  * (high - low + 1)	;
	ST[pos].five_power= array_fact[high - ST[pos].Left + 1].five - array_fact[low - ST[pos].Left].five + five * (high - low + 1)	;


	if (low != high){

		ST[2*pos+1].Left  = ST[pos].Left ;
		ST[2*pos+2].Left  = ST[pos].Left ;
		
		ST[2*pos+1].lazy_two  = two		;
		ST[2*pos+1].lazy_five = five	;
		ST[2*pos+2].lazy_two  = two		;
		ST[2*pos+2].lazy_five = five 	;
	}

	ST[pos].Left = -1;
	ST[pos].lazy_two = ST[pos].lazy_five = 0	;

}

void pushdown_multiply(int low, int high, int pos, int two, int five){

	ST[pos].two_power  += two  * (high - low + 1)	;
	ST[pos].five_power += five * (high - low + 1)	;

	if (low != high){

		int mid = (low + high) / 2;

		if (ST[2*pos+1].Left > -1)
			pushdown_reset(low, mid, 2*pos+1, ST[2*pos+1].lazy_two, ST[2*pos+1].lazy_five)	;

		if(ST[2*pos+2].Left > -1)
			pushdown_reset(mid+1, high, 2*pos+2, ST[2*pos+2].lazy_two, ST[2*pos+2].lazy_five)	;

		ST[2*pos+1].lazy_two  += two 	;
		ST[2*pos+1].lazy_five += five	;
		ST[2*pos+2].lazy_two  += two 	;
		ST[2*pos+2].lazy_five += five 	;

	}

	ST[pos].lazy_two = ST[pos].lazy_five = 0	;
	ST[pos].Left = -1;	
}

void update_multiply(int i, int j, int low, int high, int pos, int two, int five){

	if (ST[pos].Left > -1)
		pushdown_reset(low, high, pos, ST[pos].lazy_two, ST[pos].lazy_five)	;

	if (ST[pos].lazy_two || ST[pos].lazy_five)
		pushdown_multiply(low, high, pos, ST[pos].lazy_two, ST[pos].lazy_five)	;

	if (j < low || i > high)
		return	;

	if (i <= low && high <= j){
		
		pushdown_multiply(low, high, pos, two, five)	;
		return 	;

	}

	int mid = (low + high) / 2						;
	update_multiply(i, j, low, mid, 2*pos+1, two, five)		;
	update_multiply(i, j, mid+1, high, 2*pos+2, two, five)	;

	combine(pos, low, high)	;

}

void update_reset(int i, int j, int low, int high ,int pos, int two, int five){


	if (ST[pos].Left > -1)
		pushdown_reset(low, high, pos, ST[pos].lazy_two, ST[pos].lazy_five)	;

	if (ST[pos].lazy_two || ST[pos].lazy_five)
		pushdown_multiply(low, high, pos, ST[pos].lazy_two, ST[pos].lazy_five)	;

	if (j < low || i > high)
		return ;
	if(i <= low && high <= j){

		ST[pos].Left = i;
		pushdown_reset(low, high, pos, two, five) 		;		
		return ;

	}

	int mid = (low+high) / 2	;
	update_reset(i, j, low, mid, 2*pos+1, two, five)	;
	update_reset(i, j, mid+1, high, 2*pos+2, two, five)	;

	combine(pos, low, high);
}

void query(int i, int j , int low, int high, int pos, node &T){

	if (ST[pos].Left > -1)
		pushdown_reset(low, high, pos, ST[pos].lazy_two, ST[pos].lazy_five)	;

	if (ST[pos].lazy_two || ST[pos].lazy_five)
		pushdown_multiply(low, high, pos, ST[pos].lazy_two, ST[pos].lazy_five)	;


	if(j < low || i > high){

		T.two_power  = 0	;
		T.five_power = 0	;
		T.sol = INF	;
		return ;

	}

	if (i <= low && high <= j){
		
		T.two_power  = ST[pos].two_power;
		T.five_power = ST[pos].five_power;
		T.sol = min(T.two_power, T.five_power)	;
		return ;

	}

	int mid = (low + high) / 2					;
	node Left, Right							;
	query(i, j, low, mid, 2*pos+1, Left)		;
	query(i, j, mid+1, high, 2*pos+2, Right)	;

	T.two_power  = Left.two_power  + Right.two_power	;
	T.five_power = Left.five_power + Right.five_power	;
	T.sol = min(T.two_power, T.five_power)				;
	
}


 int main(){

	ios_base::sync_with_stdio(false);   cin.tie(0)  ;
 	int t, L, R, type, X 	;
 	factorial()	;
 	scanf("%d", &t)	;

 	while(t--){

 		int n, q	;
 		long long int summation = 0 ;
 		scanf("%d %d", &n, &q)	;

 		memset(ST, 0, sizeof(ST));
 		memset(array, 0, sizeof(array));

 		for (int i = 0; i < n; i++)
 			scanf("%d", &array[i])	;

 		build(0, n-1, 0, 0, n-1)	;

 		for (int i = 0; i < q; i++){

 			scanf("%d %d %d", &type, &L, &R)	;
 			if (type == 1){

 				scanf("%d", &X)	;
 				update_multiply(L-1, R-1, 0, n-1, 0, power(X, 2), power(X, 5))	;

 			}
  			else if(type == 2){

 				scanf("%d", &X)	;
 				update_reset(L-1, R-1, 0, n-1, 0, power(X, 2), power(X, 5))	;

 			}

 			else{

 				node ans	;
 				query(L-1, R-1, 0, n-1, 0, ans)	;
 				summation += ans.sol	;

 			}
 		}
 		printf("%lld\n", summation)	;
 	}
 	return 0	;
 }