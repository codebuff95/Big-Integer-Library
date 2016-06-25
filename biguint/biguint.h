// High precision very long unsigned integer array implementation.
#include<iostream>
#include<string>
#define MAXSIZE 100
using namespace std;
typedef unsigned int uint;
class BigUInt{
	public:
		char value[MAXSIZE];
		BigUInt(){
			value[0] = '0';
			value[1] = '\0';
		}
		BigUInt(int n){
			int i = 0;
			do{
				value[i++] = '0' + (n % 10);
				n = n / 10;
			}while(n);
			value[i] = '\0';
		}
		BigUInt(string s){
			int i = 0,j = 0;
			//BigUInt(); ---> call one constructor from another.
			if(s[0] == '\0'){
				s[0] = '0';s[1] = '\0';
			}
			while(s[i] != '\0') i++;
			i--;
			while(i >= 0){
				value[j++] = s[i--];
			}
			value[j] = '\0';
		}
		void out(ostream& stream){
			int i = 0;
			while(value[i] != '\0') i++;
			/*if(!i){
				cout<<'0';
				return;
			}*/ //assuming there is always at least one character in value.
			do{
				stream<<value[--i];
			}while(i > 0);
		}
		void add(BigUInt);
		static bool less(BigUInt a, BigUInt b);
		static bool less_obj(BigUInt*, BigUInt*);
};
void BigUInt::add(BigUInt b){
	uint i;
	int oldcarry = 0,newcarry;
	for(i = 0; value[i] != '\0' && b.value[i] != '\0'; i++){
		newcarry = (value[i] + b.value[i] + oldcarry - '0' - '0')/10;
		value[i] = ((value[i] + b.value[i] + oldcarry - '0' - '0') % 10) + '0';
		oldcarry = newcarry;
	}
	if(oldcarry == 0) return;
	
	if(b.value[i] == '\0' && value[i] == '\0'){
		value[i] = '0' + oldcarry;
		value[i+1] = '\0';
	}
	else if(b.value[i] == '\0'){
		for(; value[i] != '\0'; i++){
			value[i] += oldcarry;
			if(value[i] > '9'){
				value[i] = '0';
			}
			else{
				return;
			}
		}
		value[i] = '1';
		value[i+1] = '\0';
	}
	else{
		for(; b.value[i] != '\0'; i++){
			value[i] = b.value[i] + oldcarry;
			if(value[i] > '9'){
				value[i] = '0';
			}
			else{
				oldcarry = 0;
			}
		}
		if(oldcarry){
			value[i] = '0' + oldcarry;
			value[i+1] = '\0';
		}
	}
	return;
}
bool BigUInt::less(BigUInt a, BigUInt b){
	int i = 0,j = 0;
	while(a.value[i] != '\0') i++;
	while(b.value[j] != '\0') j++;
	if(i > j){
		return false;
	}
	if(j > i){
		return true;
	}
	//both numbers are equal digits long.
	for(i--;i>=0;i--){
		if(a.value[i] > b.value[i]){
			return false;
		}
		if(a.value[i] < b.value[i]){
			return true;
		}
	}
	//both numbers are equal.
	return true; //for stable sort?
}
bool BigUInt::less_obj(BigUInt *a, BigUInt *b){
	int i = 0,j = 0;
	while(a->value[i] != '\0') i++;
	while(b->value[j] != '\0') j++;
	if(i > j){
		return false;
	}
	if(j > i){
		return true;
	}
	//both numbers are equal digits long.
	for(i--;i>=0;i--){
		if(a->value[i] > b->value[i]){
			return false;
		}
		if(a->value[i] < b->value[i]){
			return true;
		}
	}
	//both numbers are equal.
	return true; //for stable sort?
}
