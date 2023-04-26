#include "console.h"

int terminal_position = 0;
char character_buffer[50] = {0};
char command_buffer[2][300] = {0};
char charbuffer[300] = {'\0'};
int isExit = 0;
Color terminal_font_color = LIGHT_GRAY;

/*method to clear the terminal screen*/
void clear_terminal(){
	for(int i=0; i<VGA_TOTAL_BYTES; i+=2){
		VGA_BUFFER[i] = 0;
		VGA_BUFFER[i+1] = terminal_font_color;
	}
	terminal_position = 0;
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
		default:
		VGA_BUFFER[terminal_position++] = c;
		VGA_BUFFER[terminal_position++] = terminal_font_color;
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
	if(terminal_position >= VGA_TOTAL_BYTES)
		shift_terminal_up();
	
	if(is_special_character(c)){
		handle_special_character(c);
	}else{
		VGA_BUFFER[terminal_position++] = c;
		VGA_BUFFER[terminal_position++] = terminal_font_color;
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
/*method to print integer*/
void print_integer(int toPrint){
	char* new_buffer = character_buffer;
	char* str = itoa(new_buffer, toPrint);
	
	print_string(str);
}

/*method to print the output prompt part to begin the command*/
void output_prompt(){
	print_string("~>");
}

/*method to read the command from terminal*/
void read_command(){
	int typing = 1;
	unsigned char byte;
        while (typing) {
                while (byte = scan()) {
                        if (byte == ENTER){
                        	divide_command();
                        	handle_command();
                        	clear_array(command_buffer[1]);
                        	//clear_array(command_buffer[2]);
                        	clear_array(charbuffer);
                        	
                        	typing = 0;
                        }else{
                        	print_character(charmap[byte]);
                        	append(charbuffer, charmap[byte]);
                        }
                }
        }
}

/*method to check whether the command is valid or not, if valid perform specific function*/
void handle_command(){
	if(strcmp(command_buffer[1], "exit") == 0){
		print_string("\nExiting the terminal...\n");
		isExit = 1;
	}
	else if(strcmp(command_buffer[1], "clear") == 0){
		clear_terminal();		
	}
	else if(strcmp(command_buffer[1], "help") == 0){
		print_string(help_list);		
	}
	else if(strcmp(command_buffer[1], "set-terminal-font-color") == 0){
		set_terminal_font_color();
		print_string("\n");
	}
	else{
		print_string("\nCommand not found: ");
		print_string(command_buffer[1]);
		print_string("\n");
	}
}

/*method to set the terminal font color to appropriate color value*/
void set_terminal_font_color(){
	if(strcmp(command_buffer[2], "black") == 0){
		terminal_font_color = BLACK;
	}
	else if(strcmp(command_buffer[2], "blue") == 0){
		terminal_font_color = BLUE;
	}
	else if(strcmp(command_buffer[2], "green") == 0){
		terminal_font_color = GREEN;
	}
	else if(strcmp(command_buffer[2], "cyan") == 0){
		terminal_font_color = CYAN;
	}
	else if(strcmp(command_buffer[2], "red") == 0){
		terminal_font_color = RED;
	}
	else if(strcmp(command_buffer[2], "magenta") == 0){
		terminal_font_color = MAGENTA;
	}
	else if(strcmp(command_buffer[2], "brown") == 0){
		terminal_font_color = BROWN;
	}
	else if(strcmp(command_buffer[2], "lightgray") == 0){
		terminal_font_color = LIGHT_GRAY;
	}
	else if(strcmp(command_buffer[2], "darkgray") == 0){
		terminal_font_color = DARK_GRAY;
	}
	else if(strcmp(command_buffer[2], "lightblue") == 0){
		terminal_font_color = LIGHT_BLUE;
	}
	else if(strcmp(command_buffer[2], "lightgreen") == 0){
		terminal_font_color = LIGHT_GREEN;
	}
	else if(strcmp(command_buffer[2], "lightcyan") == 0){
		terminal_font_color = LIGHT_CYAN;
	}
	else if(strcmp(command_buffer[2], "lightred") == 0){
		terminal_font_color = LIGHT_RED;
	}
	else if(strcmp(command_buffer[2], "lightmagenta") == 0){
		terminal_font_color = LIGHT_MAGENTA;
	}
	else if(strcmp(command_buffer[2], "yellow") == 0){
		terminal_font_color = YELLOW;
	}
	else if(strcmp(command_buffer[2], "white") == 0){
		terminal_font_color = WHITE;
	}
	else{
		print_string("\nNo Color FOUND...\n");
	}
}

/*method to shift the terminal up*/
void shift_terminal_up()
{
    copy_content((char *) (offset(0,1) + VGA_BUFFER), (char *) (offset(0,0) + VGA_BUFFER), VGA_WIDTH * (VGA_HEIGHT - 1) * 2);

    for(int column = 0; column < VGA_WIDTH; column++)
    {
        terminal_position = offset(column, VGA_HEIGHT - 1);
        print_character(0);
    }
    terminal_position = offset(0, VGA_HEIGHT-1);
}

/*---- utility method ------*/
/*methd to separate the command and option part*/
void divide_command(){
	char delim = ' ';
	static char* input = 0;
	input = charbuffer;
	
	int i = 0, j = 0;
	for (; input[i] != '\0' && input[i] != ' '; i++){				
		command_buffer[1][i] = input[i];
	}
    	command_buffer[1][i] = '\0';
    	if(input[i] != '\0' && input[i+1] != ' '){
       		i++;
        	for(; input[i] != '\0' && input[i] != ' '; i++)
        	{
            		command_buffer[2][j] = input[i];
            		j++;
        	}
        	command_buffer[2][j] = '\0';
    	}
}

void copy_content(char * src, char * dest, int numbytes)
{  
    for(int i = 0; i < numbytes; i++)
    {
        *(dest + i) = *(src + i);
    }
}

int offset( int col, int row)
{
    return 2 * (row * VGA_WIDTH + col);
}
