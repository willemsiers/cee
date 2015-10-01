#ifndef CEE_UTILS_C
#define CEE_UTILS_C

#include <ctype.h>
/*
*	Utility Functions
*/

#define COL_INPUT 1
#define COL_STORY 2
#define COL_END 3
#define COL_DEFAULT 4 //enviromens dependent

#ifdef _WIN32
#define CLEAR_CONSOLE "cls"
#include <windows.h>
#include <wincon.h>
void setTerminalColor(int colMode){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD wAttributes;
    if(colMode == COL_INPUT){
        wAttributes = FOREGROUND_GREEN;
    }
    else if(colMode == COL_STORY){
        wAttributes = 0x0003; //CYAN
    }
    else if(colMode == COL_END){
        wAttributes =0x0006;//yellow
    }
    else if(colMode == COL_DEFAULT){
        wAttributes = FOREGROUND_GREEN;//should be white or defualt, but couldn't find it in wincon.h
    }

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, wAttributes);
}

#elif __unix
#define CLEAR_CONSOLE "clear"
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

int nocase_strcmp(char const *s1, char const *s2)
{
	for (;; s1++, s2++) {
		int d = tolower(*s1) - tolower(*s2);
		if (d != 0 || !*s1)
			return d;
	}
}

#endif
