#include "Scanner.h"
#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;


int main(){
	FILE * myinput;
	char l[BUFSIZE];
	if((myinput = fopen("myluafile.lua", "r")) == NULL){
		cout << "Error opening file";
	}
	else{
		Scanner s;
		s.scan(myinput);
	}
	
	fclose(myinput);
}