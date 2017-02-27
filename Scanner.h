#include <stdio.h>
#define IDSIZE    1
#define BUFSIZE 250

class Scanner{
	
	

static int col;
static int lineno;
static char line[BUFSIZE]; //line buffer
	public:
		Scanner();
		void scan(FILE *fp);
		int get_token(char ch[]);
	private:
		int get_char(char ch[]);
};