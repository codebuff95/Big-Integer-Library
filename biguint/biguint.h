// High precision very long unsigned integer array implementation.
#include<iostream>
#include<string>
#define MAXSIZE 100
using namespace std;
typedef unsigned int uint;
class BigUInt{
	public:
		//Variables
		char value[MAXSIZE];
		//Object constructors
		BigUInt();
		BigUInt(int);
		BigUInt(string);
		BigUInt(const BigUInt&);
		//Mathematical
		void add(BigUInt);
		//Custom comparators
		static bool less(BigUInt a, BigUInt b);
		static bool greater(BigUInt a, BigUInt b);
		static bool less_obj(BigUInt*, BigUInt*);
		//Overloaded operators
		BigUInt operator+(BigUInt &);
		bool operator==(BigUInt &);
		bool operator>(BigUInt &);
		bool operator<(BigUInt &);
		bool operator<=(BigUInt &);
		bool operator>=(BigUInt &);
		void operator=(string);
		//Miscellaneous
		void out(ostream&);
};

/*---------------------------*/
/* Object Constructors Start*/
/*-------------------------*/

BigUInt::BigUInt(){
	value[0] = '0';
	value[1] = '\0';
}
BigUInt::BigUInt(int n){
	int i = 0;
	do{
		value[i++] = '0' + (n % 10);
		n = n / 10;
	}while(n);
	value[i] = '\0';
}
BigUInt::BigUInt(string s){
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
BigUInt::BigUInt(const BigUInt &b){ //Default copy constructor would've sufficed too.
	uint i;
	for(i = 0; b.value[i] != '\0'; i++){
		value[i] = b.value[i];
	}
	value[i] = '\0';
}

/*-------------------------*/
/* Object Constructors End*/
/*-----------------------*/

/*-------------------------------*/
/* Mathematical Functions Start */
/*-----------------------------*/

void BigUInt::add(BigUInt b){
	uint i;
	int oldcarry = 0,newcarry;
	for(i = 0; value[i] != '\0' && b.value[i] != '\0'; i++){
		newcarry = (value[i] + b.value[i] + oldcarry - '0' - '0')/10;
		value[i] = ((value[i] + b.value[i] + oldcarry - '0' - '0') % 10) + '0';
		oldcarry = newcarry;
	}	
	if(b.value[i] == '\0' && value[i] == '\0'){
		if(oldcarry == 0) return;
		value[i] = '0' + oldcarry;
		value[i+1] = '\0';
	}
	else if(b.value[i] == '\0'){
		if(oldcarry == 0) return;
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

/*-----------------------------*/
/* Mathematical Functions End */
/*---------------------------*/

/*---------------------------*/
/* Custom Comparators Start */
/*-------------------------*/
bool BigUInt::less(BigUInt a, BigUInt b){
	return a < b;
}
bool BigUInt::greater(BigUInt a, BigUInt b){
	return a > b;
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

/*-------------------------*/
/* Custom Comparators End */
/*-----------------------*/

/*------------------------------*/
/* Overloading Operators Start */
/*----------------------------*/

BigUInt BigUInt::operator+(BigUInt &b){
	BigUInt newobj(b);
	newobj.add(*this);
	return newobj;
}
bool BigUInt::operator==(BigUInt &b){
	int blen,alen;
	for(blen = 0; b.value[blen] != '\0'; blen++);
	blen--;
	for(alen = 0; this->value[alen] != '\0'; alen++);
	alen--;
	
	if(blen != alen) return false;
	
	for(;alen>=0;alen--){
		if(this->value[alen] != b.value[alen]) return false;
	}
	return true;
}
bool BigUInt::operator>(BigUInt &b){
	int blen,alen;
	for(blen = 0; b.value[blen] != '\0'; blen++);
	blen--;
	for(alen = 0; this->value[alen] != '\0'; alen++);
	alen--;
	
	if(blen > alen) return false;
	if(blen < alen) return true;
	
	for(;alen>=0;alen--){
		if(this->value[alen] > b.value[alen]) return true;
		if(this->value[alen] < b.value[alen]) return false;
	}
	return false;
}
bool BigUInt::operator>=(BigUInt &b){
	int blen,alen;
	for(blen = 0; b.value[blen] != '\0'; blen++);
	blen--;
	for(alen = 0; this->value[alen] != '\0'; alen++);
	alen--;
	
	if(blen > alen) return false;
	if(blen < alen) return true;
	
	for(;alen>=0;alen--){
		if(this->value[alen] > b.value[alen]) return true;
		if(this->value[alen] < b.value[alen]) return false;
	}
	return true;
}
bool BigUInt::operator<(BigUInt &b){
	int blen,alen;
	for(blen = 0; b.value[blen] != '\0'; blen++);
	blen--;
	for(alen = 0; this->value[alen] != '\0'; alen++);
	alen--;
	
	if(blen < alen) return false;
	if(blen > alen) return true;
	
	for(;alen>=0;alen--){
		if(this->value[alen] < b.value[alen]) return true;
		if(this->value[alen] > b.value[alen]) return false;
	}
	return false;
}
bool BigUInt::operator<=(BigUInt &b){
	int blen,alen;
	for(blen = 0; b.value[blen] != '\0'; blen++);
	blen--;
	for(alen = 0; this->value[alen] != '\0'; alen++);
	alen--;
	
	if(blen < alen) return false;
	if(blen > alen) return true;
	
	for(;alen>=0;alen--){
		if(this->value[alen] < b.value[alen]) return true;
		if(this->value[alen] > b.value[alen]) return false;
	}
	return true;
}
void BigUInt::operator=(string c){
	int len;
	for(len = 0; c[len] != '\0' && len <= MAXSIZE; len++);
	len--;
	for(int i = 0, j = len; i <= len; i++, j--){
		this->value[i] = c[j];
	}
	this->value[len+1] = '\0';
}
/*----------------------------*/
/* Overloading Operators End */
/*--------------------------*/

/*--------------------------------*/
/* Miscellaneous Functions Start */
/*------------------------------*/

void BigUInt::out(ostream &stream){
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

/*------------------------------*/
/* Miscellaneous Functions End */
/*----------------------------*/
