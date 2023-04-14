#include "console.h"

int terminal_position = 0;
char character_buffer[50] = {0};


/*method to clear the terminal screen*/
void clear_terminal(){
	for(int i=0; i<VGA_TOTAL_BYTES; i+=2){
		VGA_BUFFER[i] = 0;
		VGA_BUFFER[i+1] = 0X07;
	}
	update_cursor();
}

/*method to handle new line character i.e. move cursor to new line*/
void handle_newline_character(){
	terminal_position = terminal_position + VGA_BYTES_PER_ROW - (terminal_position % (VGA_BYTES_PER_ROW));
}

/*method to handle all the special character cases*/
void handle_special_character(char c){
	switch(c){
		case '\n':
		handle_newline_character();
		break;
		case ' ':
		terminal_position += 2;
		break;
		
	}
}

/*method to check whether the character is special or not*/
int is_special_character(char c) {
	if(c >= '0' && c <= '9'){
    		return  0;
	}else if(c >= 'A' && c <= 'Z'){
    		return  0;
    	}else if(c >= 'a' && c <= 'z'){
    		return  0;
    	}else{
    		return 1;
    	} 
}

/*method to print each character of string*/
void print_character(char c){
	//terminal_position = get_cursor_position();
	
	if(is_special_character(c)){
		handle_special_character(c);
	}else{
		VGA_BUFFER[terminal_position++] = c;
		VGA_BUFFER[terminal_position++] = 0X07;
	}
	update_cursor();
	return;
}

/*method to print the string*/
void print_string(char* str){
	for(int i=0; str[i] != '\0'; i++){
		print_character(str[i]);
	}
}

void print_line(char* str){
	print_string(str);
	print_character('\n');
}

/*method to update the cursor postion*/
void update_cursor(){
	uint16_t cursor_position = terminal_position >> 1;
	outb(VGA_INDEX_REGISTER, VGA_LOW_REGISTER);
	outb(VGA_DATA_REGISTER, (uint8_t)(cursor_position));
	
	outb(VGA_INDEX_REGISTER, VGA_HIGH_REGISTER);
	outb(VGA_DATA_REGISTER, (uint8_t)(cursor_position >> 8));
}
/*method to get the cursor position*/
uint16_t get_cursor_position(){
	uint16_t cursor_position = 0;
	outb(VGA_INDEX_REGISTER, VGA_LOW_REGISTER);
	cursor_position |= inb(VGA_DATA_REGISTER);
	outb(VGA_INDEX_REGISTER, VGA_HIGH_REGISTER);
	cursor_position |= ((uint16_t)inb(VGA_DATA_REGISTER)) << 8;
	return cursor_position;
}

void print_integer(int toPrint){
	char* buffer = character_buffer;
	char* str = itoa(buffer, toPrint);
	
	print_string(str);
}
