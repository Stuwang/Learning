#include <iostream>

using namespace std;

int sortn(int *start,int *end , int n ){
	int * cur = start + n ;
RES:
	int * s= start,* e  = end -1 ;
	int tmp = *s;
	while( s < e ){
		while(s < e && *e >= tmp )
			e--;
		*s = *e;
		while( s < e && *s < tmp )
			s++;
		*e = *s;
	}
	*s = tmp;

	if( s == cur ){
		return *cur;
	}else{
		if( s < cur ){
			start = s + 1 ;
		}else{
			end = s;
		}
		goto RES;
	}
};

int main(){
	
	int a[] = {
		6 ,2 ,1 ,4 ,5 ,10,3 ,50,12,23,
		34,21,34,80,34,70,45,31,11,14
	};


	int i = sortn(a,a+20,9);

	for(int m=0;m<20;m++){
		cout << m+1 << ":" << a[m] << endl ;
	}
	cout << endl;

	cout << i << endl;
}
