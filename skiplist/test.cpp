#include <iostream>
#include <stack>
#include <vector>

#include "skiplist.h"

using namespace std;

int main(){
	typedef yuan::skiplist<int,int>  mylist;
	mylist s ;

	std::vector<vector<int> > v;
	int help[mylist::MAX_HEIGHT];
	for(int i=0;i<mylist::MAX_HEIGHT;i++){
		help[i] = 1;
		v.push_back(std::vector<int>());
	}

	for( int i=0 ; i< 1*1000*1000 ; i++ ){
		int m = 1 + rand() % 200;
		s.Insert(m,i);
	}
	
	cout << "aaaaaaaaaaaaaaa" << endl;
	for(mylist::iterator i  =s.begin() ; i != s.end() ; i++  ){
		// cout<< i.ptr->height  << "  "
		// 	<< "key " << i.key() 
		// 	<< " value " << i.value() << endl;
		int height = i.ptr->height ;
		for (int m = 0; m < height; ++m)
		{
			v[m].push_back(help[m]);
			help[m] = 1;
		}
		for(int m= height;m<mylist::MAX_HEIGHT;m++){
			help[m] ++;
		}
	};

	cout << "bbbbbbbbbbbbbbb" << endl;
	for(int i=0;i<mylist::MAX_HEIGHT;i++){
		int sum = 0;
		for(int j=0;j<v[i].size();j++){
			sum += v[i][j];
		}
		if(v[i].size())
			cout << "height " << i << " avg " << sum/v[i].size() << endl;
	}

	// cout << "FindLessThan 4 " << s.FindLessThan(4)->key << endl;
	// cout << "FindGreaterOrEqual 5 " << s.FindGreaterOrEqual(4,NULL)->key << endl;
	// cout << "FindLast " << s.FindLast()->key << endl;
}
