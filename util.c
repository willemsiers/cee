/*
*	Utility Functions
*/


//Replace \n with \0
void remNewline(char* str){
	char* MAX = str + 300;
	for(; *str != '\0' && str != MAX; str++){
		if(*str == '\n'){
			*str = '\0';
			return;
		}
	}
}

//Replace @ with \n
void unescapeNewline(char* str){
	char* MAX = str + 300;
	for(; *str != '\0' && str != MAX; str++){
		if(*str == '@'){
			*str = '\n';
		}
	}
}
