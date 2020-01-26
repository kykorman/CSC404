//This program bruteforces the shortest solution for the missionaries/cannibals problem
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int n, cap;
long shortestSolution = INT_MAX;

void printVector(vector <vector <int> > v){
	shortestSolution = v.size();
	for(int i=0; i<v.size()-1; i++)
		printf("(%d, %d, %d, %d) -> ", v[i][1], v[i][2], v[i][3], v[i][4]);

	printf("(%d, %d, %d, %d)\n", v[v.size()-1][1], v[v.size()-1][2], v[v.size()-1][3], v[v.size()-1][4]);
}


void solver(vector <vector <int> > v){
	int endV = v.size()-1;
	vector <vector <int> > tmp; 

	int LHSc = v[endV][2], LHSm=v[endV][1], ISc = v[endV][4], ISm = v[endV][3], RHSc = n - LHSc - ISc, RHSm = n - LHSm - ISm;
	//Left Hand Side Cannibals, Left Hand Side Missionaries, island version of either, etc.


	// Comment this out if you want to see all solutions. Takes forever though.
	if(v.size() >= shortestSolution)return;


	//Terminate if looping
	for(int i=0; i<v.size()-1; i++)
		for(int k=i+1; k<v.size(); k++)
			if(v[i]==v[k])
				return;


	//If invalid state, terminate branch
	//This is way easier to do than having more if statements and massive conditions for 2nd parameter of for loop
	//I discovered this fact way too late after burning a lot of time

	if( (LHSm !=0 && LHSc > LHSm) || (RHSm != 0 && RHSc > RHSm) || (ISm != 0 && ISc > ISm) || (LHSm + RHSm + ISm > n) || (LHSc + RHSc + ISc > n) || LHSc < 0 || LHSm < 0 || RHSc < 0 || RHSm < 0 || ISc < 0 || ISm < 0) return;

	if(v[endV][0] == 0){ //We're on left side
//printf("LHS: "); printVector(v);
		for(int i=0; i<=cap; i++)
			for(int k=0;k+i<=cap; k++)
				if(i+k>0){
					vector <int> tmp2;
					//Go to island
					tmp = v;

					tmp2.push_back(1);	
					tmp2.push_back(v[endV][1]-i);
					tmp2.push_back(v[endV][2]-k);

					tmp2.push_back(v[endV][3]+i);
					tmp2.push_back(v[endV][4]+k);
					tmp.push_back(tmp2);
					solver(tmp);

					//Go to right side
					tmp2.clear();
					tmp.clear();

					tmp = v;

					tmp2.push_back(2);	
					tmp2.push_back(v[endV][1]-i);
					tmp2.push_back(v[endV][2]-k);

					tmp2.push_back(v[endV][3]);
					tmp2.push_back(v[endV][4]);
					tmp.push_back(tmp2);
					solver(tmp);



				}
	}else if(v[endV][0] == 2){ //right side
//printf("RHS: "); printVector(v);
		if(v[endV][1]==0 && v[endV][2]==0 && ISc == 0 && ISm == 0){
			printVector(v);
			return;
		}
		for(int i=0; i<=cap; i++)
			for(int k=0;k+i<=cap; k++)
				if(i+k>0){
			
					vector <int> tmp2;
					//Go to island
					tmp = v;

					tmp2.push_back(1);	
					tmp2.push_back(v[endV][1]);
					tmp2.push_back(v[endV][2]);

					tmp2.push_back(v[endV][3]+i);
					tmp2.push_back(v[endV][4]+k);
					tmp.push_back(tmp2);
					solver(tmp);

					//Go to left side
					tmp2.clear();
					tmp.clear();

					tmp = v;

					tmp2.push_back(0);
					tmp2.push_back(v[endV][1]+i);
					tmp2.push_back(v[endV][2]+k);

					tmp2.push_back(v[endV][3]);
					tmp2.push_back(v[endV][4]);
					tmp.push_back(tmp2);
					solver(tmp);

				}
	}else{ //On the island, sipping tiki drinks
//printf("ISL: "); printVector(v);
		for(int i=0; i<=cap; i++)
			for(int k=0;k+i<=cap; k++)
				if(i+k>0){
			
					vector <int> tmp2;
					//Go to right side

					tmp = v;

					tmp2.push_back(2);	
					tmp2.push_back(v[endV][1]);
					tmp2.push_back(v[endV][2]);

					tmp2.push_back(v[endV][3]-i);
					tmp2.push_back(v[endV][4]-k);
					tmp.push_back(tmp2);
					solver(tmp);


					//Go to left side
					tmp2.clear();
					tmp.clear();
					tmp = v;

					tmp2.push_back(0);	
					tmp2.push_back(v[endV][1]+i);
					tmp2.push_back(v[endV][2]+k);

					tmp2.push_back(v[endV][3]-i);
					tmp2.push_back(v[endV][4]-k);
					tmp.push_back(tmp2);
					solver(tmp);				}


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

	tmp.push_back(0);
	tmp.push_back(0);

	v.push_back(tmp);

	solver(v);

	return 0;
}
