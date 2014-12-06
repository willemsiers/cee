/*
*	Utility Functions
*/


//Replace \n with \0
void remNewline(char* str){
	char* MAX = str + 100;
	for(; *str != '\0' && str != MAX; str++){
		if(*str == '\n'){
			*str = '\0';
			return;
		}
	}
}