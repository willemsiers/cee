#ifndef ROOMDEF_C
#include <string.h>
#define ROOMDEF_C
/*
 *	This file defines:
 *		structs Action and Room
 *		add- function for Action
 *		get for Action
*
 *	NOTE: these functions assume a global `room` var to get and set properties on 
*/

//ROOM DEFINITION
struct Room{
	struct Action* actions;
    int (*on_enter)();
	// No 'linkedlist' features. If Action needs a different room use pointer.
};

typedef union ActionArg ActionArg;
union ActionArg {
	char* text;
	struct Room* room;
};

typedef int (* FuncSig)(union ActionArg* defArg); //type for returning a void function with a string argument  

//ACTION DEFINITION
struct Action
{	char* query;
	int (*fupo)(union ActionArg*);
	union ActionArg* defArg;
	int hidden;
	struct Action* next;
};

struct Action* actions;

void addAction(char* query, int (*fupo)(union ActionArg*), union ActionArg* defArg, int hidden){
    struct Action* action = (struct Action*) malloc(sizeof(struct Action)); //new action

    action->query = (char*)malloc(sizeof(char) * (strlen(query) + 1));
	strcpy(action->query, query);
    action->fupo = fupo;
    action->defArg = defArg;
    action->hidden = hidden;
    action->next = NULL;

    struct Action* actionsTail = room->actions;
    //is first action of room?
    if(actionsTail->fupo == NULL){
        room->actions = action;
    }else{
        //add to end of list`
        while(actionsTail ->next != NULL){
            actionsTail = actionsTail->next;
        }
        actionsTail->next = action;
    }
};

struct Action* getAction(char* query){
	struct Action* action = room->actions;
	while(action != NULL){
		if(strcmp(action->query, query) == 0){
			break;
		}
		action = action->next;
	}
	if(action == NULL)
	{
		//printf("Action not found! %s\n",query);
	}
	return action;
}

void setOnEnter(int (*fupo)()){
    room->on_enter = fupo;
}

#endif
