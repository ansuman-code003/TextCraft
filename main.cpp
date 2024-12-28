#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

struct termios orig_state;

void enableRawMode();
void disableRawMode();

int main(){
	enableRawMode();
	char c;
	while( read(STDIN_FILENO, &c, 1) == 1 && c !='q');
	return 0;
}

void enableRawMode(){
	tcgetattr(STDIN_FILENO, &orig_state);
	atexit(disableRawMode);
	
	struct termios raw = orig_state;
	raw.c_lflag &= ~(ECHO | ICANON);
	
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

	
}

void disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_state);
}
