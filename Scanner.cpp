#include "Scanner.h"
#include "lua_symbols.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdlib>


#define EOL '\n'

using namespace std;
char Scanner::line[BUFSIZE];
int Scanner::col = 0;
int Scanner::lineno = 0;

Scanner::Scanner(){
	
}

void Scanner::scan(FILE *fp){
	cout << "Beginning lexical analysis..." << endl;
	while(fgets(line, BUFSIZE, fp)){
			get_token(line);
		}
	cout << "Reached end of file.  " << lineno << " lines scanned without error." << endl;
}

Scanner::get_token(char ch[]){
	bool flag = true;
	int state = 0;
	int c;
	int d;
	while(1){
		c = get_char(ch);
		flag = true;
		if(c == EOL||c == EOF || c == 0){
			col = 0;
			lineno++;
			break;
		}
		else{
			while(flag){
				switch(state){
					case 0:
						if(tolower(c) < 123 && tolower(c) > 96){
							state = 1;
							
						}	
						else if(c <= 58 && c >= 48){
							state = 2;
							
						}
						else if(c == '+'){
							cout << "lexeme: " << static_cast<char>(c) << " " << "token: " << ADD << endl;
							flag = false;
						}
						else if(c == '-'){
							cout << "lexeme: " << static_cast<char>(c) << " " << "token: " << SUB << endl;
							flag = false;
						}
						else if(c == '*'){
							cout << "lexeme: " << static_cast<char>(c) << " " << "token: " << MUL << endl;
							flag = false;
						}
						else if(c == '/'){
							cout << "lexeme: " << static_cast<char>(c) << " " << "token: " << DIV << endl;
							flag = false;
						}
						else if(c == '='){
							state = 4;
						}
						else if(c == '<' || c == '>'){
							state = 3;
						}
						else if(c == '~'){
							state = 5;
						}
						else if(c == 0){
							cout << "Reached end of file.  " << lineno << " lines scanned without error." << endl;
							flag = false;
							break;
							}
						else if(c == 32 || c == EOL){
							flag = false;
							break;
						}
						else{
							cout << "Illegal token at line " << lineno << " column " << col << endl;
							cout << "Terminating lexical analysis..." << endl;
							exit(1);
						}
						break;
						
					case 1:
						c = get_char(ch);
						if(c != 32 && c != EOL && c != 0){
							cout << "Error: Illegal identifier at line " << lineno << " column " << col << endl;
							exit(1);
						}
						col = col - 2;
						c = get_char(ch);
						cout << "lexeme: " << static_cast<char>(c) << " " << "token: " << ID << endl;
						state = 0;
						flag = false;
						break;
					case 2:
						d = 0;
						d = get_char(ch);
						if(d <=58 && d >= 48){	
							c = (c-48);
							while(d <=58 && d >= 48){
								c = c * 10;
								c = c + (d-48);
								d = get_char(ch);
							}
						}
						else{
							c = c-48;
						}
						if(d!= 32 && d != EOL && d != 0){
							cout << "Illegal token at line " << lineno << " column " << col << endl;
							exit(1);
						}
						else{
							cout << "lexeme: " << c << " token: " << INTLIT << endl;
							state = 0;
							flag = false;
							break;
						}
					case 3:
						d = 0;
						d = get_char(ch);
						if(d != 32 && d != EOL && d != 0 && d != '='){
							cout << "Error: Illegal token at line " << lineno << " column " << col << endl;
							exit(1);
						}
						else{
							if(c == '<'){
								if(d == '='){
									cout << "lexeme: " << static_cast<char>(c) << 
										static_cast<char>(d) << " token: " << LEQ << endl;
								}
								else{
									cout << "lexeme: " << static_cast<char>(c) << " token: " << LETHAN << endl;
								}
							}
							else if(c == '>'){
								if(d == '='){
									cout << "lexeme: " << static_cast<char>(c) << 
										static_cast<char>(d) << " token: " << GEQ << endl;
								}
								else{
									cout << "lexeme: " << static_cast<char>(c) << " token: " << GRTHAN << endl;
								}
							}
								
							state = 0;
							flag = false;
							break;
						}
					case 4:
						d = 0;
						d = get_char(ch);
						if(d != 32 && d != EOL && d != 0 && d != '='){
							cout << "Error: Illegal token at line " << lineno << " column " << col << endl;
							exit(1);
						}
						else{
							if(d == '='){
								cout << "lexeme: " << static_cast<char>(c) << 
										static_cast<char>(d) << " token: " << EQUAL << endl;
							}
							else{
								cout << "lexeme: " << static_cast<char>(c) << " token: " << ASSIGN << endl;
							}
							state = 0;
							flag = false;
							break;
						}
					case 5:
						d = 0;
						d = get_char(ch);
						if(d != '='){
							cout << "Error: Illegal token at line " << lineno << " column " << col << endl;
							exit(1);
						}
						else{
							cout << "lexeme: " << static_cast<char>(c) << 
										static_cast<char>(d) << " token: " << NEQUAL << endl;
						}
						state = 0;
						flag = false;
						break;
				}
			}
			
		}
		
	}
}


Scanner::get_char(char ch[]){
		return ch[col++];
		
	
	
}