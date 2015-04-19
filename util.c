/*
*	Utility Functions
*/

#define COL_INPUT 1
#define COL_STORY 2
#define COL_END 3
#define COL_DEFAULT 4 //enviromens dependent

#ifdef _WIN32
void setTerminalColor(int colMode){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD wAtributes;
    if(colMode == COL_INPUT){
        wAttribute = FOREGROUND_GREEN;
    }
    else if(colMode == COL_STORY){
        wAttribute = FOREGROUND_CYAN;
    }
    else if(colMode == COL_END){
        wAttribute = FOREGROUND_YELLOW;
    }
    else if(colMode == COL_DEFAULT){
        wAttribute = FOREGROUND_WHITE;
    }

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}

#elif __unix
void setTerminalColor(int colMode){
    if(colMode == COL_INPUT){
        printf("\x1B[32m");
    }
    else if(colMode == COL_STORY){
        printf("\x1B[36m");
    }
    else if(colMode == COL_END){
        printf("\x1B[33m");
    }
    else if(colMode == COL_DEFAULT){
        printf("\e[1;37m");
    }
}
#endif

//Replace \n with \0
void replaceTxtWithDat(char* str){
	char* MAX = str + 300;
	for(; *str != '.' && str != MAX; str++);
    str++;
    *str = 'd';
    str++;
    *str = 'a';
    str++;
    *str = 't';
}

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
	char* MAX = str + 800;
	for(; *str != '\0' && str != MAX; str++){
		if(*str == '@'){
			*str = '\n';
		}
	}
}
