//Driver for operator overloading.
#include "biguint.h"
#include<iostream>
int main(){
	BigUInt a,b,c;
	a = "1234";
	b = 1234;
	c = 12345;
	cout<< (a == b) << endl;
	cout<< (a >= c) << endl;
	cout<< (a <= c) << endl;
	cout<< (a >= b) <<endl;
}
