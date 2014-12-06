/*							___
*	Global state vars below \!/
*/							 
struct Room* room; //AKA currentRoom

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.c"
#include "roomdef.c"
#include "actions.c"

int start(){
	int BUF_SIZE = 100;
	char* query = malloc(BUF_SIZE);
	int status = 0;

	// temp buffers for splitting up action input
	char* spl_action = (char*) malloc(BUF_SIZE);
	char* spl_actionArg = (char*) malloc(BUF_SIZE);

	while(status == 0){
		printf(">");
		query = fgets(query, BUF_SIZE, stdin); //query is pointer to query

		if (query == 0)	{ //? check man?
			return 99;
		}

		remNewline(query);

		if(strcmp(query, "bye") == 0){ //exit program
			status = 1;
		}

		//Call getAction with the first part of the input
		// "everything except space followed by space (1) and the rest (2)"
		int read = sscanf(query, "%[^ ] %[^\n]\n", spl_action, spl_actionArg);
		//printf("read %d\taction%s\targ%s\t",read,spl_action,spl_actionArg);

		struct Action* action = getAction(spl_action);
		if(action != NULL){
			FuncSig fupo = action->fupo;
			if(read < 2){
				(*fupo)(action->defArg);
			}else{
				union ActionArg arg;
				arg.text = spl_actionArg;
				(*fupo)(arg);
			}
		}
		
		else{
			printf("msg:\t%s\n", getMessage(query));
		}	
	}
	return status;
}

int load(){
	int BUF_SIZE = 100;
	char* OPTION = "option";

	//temp vars (function scope) for gettings pointers of rooms as `Action` defArg
	struct Room* rooms[10];
	char roomNames[10][BUF_SIZE];
	int roomCnt = 0;

	FILE* file_room_listing = fopen("room_listing.txt", "r");

	char* buf_room_listing = (char*) malloc(BUF_SIZE);

	while(fgets(buf_room_listing, BUF_SIZE, file_room_listing) != NULL){
		remNewline(buf_room_listing);
		FILE* file_room = fopen(buf_room_listing, "r");

		//create new `Room`
		room = (struct Room*) malloc(sizeof(struct Room)); //set global var
		rooms[roomCnt] = room;
		strcpy(roomNames[roomCnt] , buf_room_listing);
		roomCnt++;

		//init linkedlist `options`
		room->options = (struct Option*) malloc(sizeof(struct Option));
		room->options->next = NULL;

		//init linkedlist `actions`
		room->actions = (struct Action*) malloc(sizeof(struct Action));
		room->actions->next = NULL;

		//shared buffers for each line that's read (no malloc needed) TODO: Can move outside outer while loop.
		char buf_mode[BUF_SIZE];
		char buf_line[BUF_SIZE];
	
		while(fgets(buf_line, BUF_SIZE, file_room) != NULL){
			remNewline(buf_line);

			//first allocate memory to let string contents live outside scope
			char* buf_query = (char*) malloc(BUF_SIZE);
			char* buf_arg3 = (char*) malloc(BUF_SIZE);
			char* buf_arg4 = (char*) malloc(BUF_SIZE);

			int read = sscanf(buf_line, "%100[^>] > %100[^>] > %100[^>] > %100[^\n]\n", buf_mode, buf_query, buf_arg3, buf_arg4);

			if(read <3){
				printf("Error parsing file *near* %s\n",buf_query);
				fclose(file_room);
				fclose(file_room_listing);
				return 1;
			}

			printf("%d\t%s\t%s\t\t%s\t\t\t%s\n",read,buf_mode,buf_query,buf_arg3,buf_arg4);
			
			if(strcmp(buf_mode, OPTION) == 0){
				addOption(buf_query, buf_arg3);
			}else{

				union ActionArg defArg;
				defArg.text = buf_arg3;

				if(strcmp(buf_query, "go") == 0){
					printf("go\n");
					addAction(buf_query, &on_go, defArg); //required arg
				}else if(strcmp(buf_query, "say") == 0){
					printf("say\n");
					addAction(buf_query, &on_say, defArg); //arg4 is user input, now it's just a dummy value
				}else if(strcmp(buf_query, "use") == 0){
					printf("use\n");
					addAction(buf_query, &on_use, defArg); //arg 4 is dummy
				}else{
					fclose(file_room);
					fclose(file_room_listing);
					printf("Error: action not found: %s\n",buf_query);
					return 2;
				}
			}
		}
		printf("(DEB) Last read option attempt was %s \n", buf_line);		

		fclose(file_room);
	}

	fclose(file_room_listing);

	//next replace all names (Strings) of rooms in `go` actions with Room*
	while(roomCnt --> 0){
		struct Action* action = rooms[roomCnt]->actions;
		while(action != NULL){
			if(action->fupo == &on_go){
				int i = 0;
				while(i<=12 && (strcmp(roomNames[i], action->defArg.text) != 0)){i++;};
				if(i == 12){ //ouch!!!
					printf("ERROR! room not found!\n"); 
				}
				printf("Replacing defArg %s to %p\n", action->defArg.text, rooms[i]);
				action->defArg.room = rooms[i];
			}
			action = action->next;
		}
	}
	
	addOption("hello","welcome!");
	addOption("help", "type some shit");
	addOption("bye","byebye!!");

	return 0;
}

int main(){
	// printf("%p %p %p",&on_go,&on_use,&on_say);
	// return 0;
	if(!load()){
		int exitStatus = start();
		printf("exit status: %d\n", exitStatus);
	}
	return 0;
}