#include"biguint.h"
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
	int n;
	vector<BigUInt *> myvec;
	BigUInt *mybig;
	string s;
	cout<<"Enter number of elements: ";
	cin>>n;
	for(int i = 0; i < n; i++){
		cout<<"Enter value of BigUInt "<<i+1<<": ";
		cin>>s;
		mybig = new BigUInt(s);
		myvec.push_back(mybig);
	}
	cout<<"The vector is: "<<endl;
	for(int i = 0; i < n; i++){
		myvec[i]->out(std::cout);
		cout<<" ";
	}
	cout<<endl;
	sort(myvec.begin(), myvec.end(), BigUInt::less_obj);
	for(int i = 0; i < n; i++){
		myvec[i]->out(std::cout);
		cout<<" ";
	}
	
	BigUInt newobj("123456"),new2obj(4321);
	BigUInt myobj = newobj + new2obj;
	cout<<"addition is: ";myobj.out(cout);
	myobj = newobj;
}
