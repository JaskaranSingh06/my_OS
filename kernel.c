#include "console.h"
#include "keyboard.h"

void main(){

	clear_terminal();
	
	//print_integer(get_cursor_position());
	
        while (1) {
               	output_prompt();
		read_command();
		if(isExit)
			break;

        }

	return ;
}

