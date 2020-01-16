//This program should generate all non-looping solutions to the missionaries/cannibals problem
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, cap;

void printVector(vector <vector <int> > v){
	for(int i=0; i<v.size()-1; i++)
		printf("(%d, %d) -> ", v[i][1], v[i][2]);

	printf("(%d, %d)\n", v[v.size()-1][1], v[v.size()-1][2]);
}


void solver(vector <vector <int> > v){
	int endV = v.size()-1;
	vector <vector <int> > tmp; 

	int LHSc = v[endV][2], LHSm=v[endV][1], RHSc = n - v[endV][2], RHSm = n - v[endV][1];
	//Left Hand Side Cannibals, Left Hand Side Missionaries, etc.

	//Terminate if looping
	for(int i=0; i<v.size()-1; i++)
		for(int k=i+1; k<v.size(); k++)
			if(v[i]==v[k])
				return;


	//If invalid state, terminate branch
	//This is way easier to do than having more if statements and massive conditions for 2nd parameter of for loop
	//I discovered this fact way too late after burning a lot of time

	if( (LHSm !=0 && LHSc > LHSm) || (RHSm != 0 && RHSc > RHSm) ) return;

	if(v[endV][0] == 0){ //We're on left side
		for(int i=0; i<=cap && i<=LHSm; i++)
			for(int k=0;(i==0 && k<=cap && k<=LHSc) || (k<=LHSc && k<=i && k+i<=cap); k++)
				if(i+k>0){
					vector <int> tmp2;

					tmp = v;

					tmp2.push_back(1);	
					tmp2.push_back(v[endV][1]-i);
					tmp2.push_back(v[endV][2]-k);

					tmp.push_back(tmp2);
					solver(tmp);
				}
	}else{ //right side
		if(v[endV][1]==0 && v[endV][2]==0){
			printVector(v);
			return;
		}
		for(int i=0; i<=cap && i<=RHSm; i++)
			for(int k=0;(i==0 && k<=cap && k<=RHSc) || (k<=RHSc && k<=i && k+i<=cap ); k++)
				if(i+k>0){
					vector <int> tmp2;

					tmp = v;

					tmp2.push_back(0);	
					tmp2.push_back(v[endV][1]+i);
					tmp2.push_back(v[endV][2]+k);

					tmp.push_back(tmp2);
					solver(tmp);
				}
	}

}

int main(){
	vector <vector <int> > v;
	vector <int> tmp;

	cout<<"Enter number of missionaries/cannibals: ";
	cin>>n;

	cout<<"Enter capacity of boat: ";
	cin>>cap;

	tmp.push_back(0);
	tmp.push_back(n);
	tmp.push_back(n);

	v.push_back(tmp);

	solver(v);

	return 0;
}