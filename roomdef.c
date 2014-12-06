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
	// No 'linkedlist' features. If Action needs a different room use pointer.
};

union ActionArg {
	char* text;
	struct Room* room;
};

typedef void (* FuncSig)(union ActionArg defArg); //type for returning a void function with a string argument  

//ACTION DEFINITION
struct Action
{	char* query;
	void (*fupo)(union ActionArg);
	union ActionArg defArg;
	int hidden;
	struct Action* next;
};

struct Action* actions;


void addAction(char* query, void (*fupo)(union ActionArg), union ActionArg defArg, int hidden){
	struct Action* action = (struct Action*) malloc(sizeof(struct Action)); //new action
	action->query = query;
	action->fupo = fupo;
	action->defArg = defArg;
	action->hidden = hidden;
	action->next = room->actions;
	room->actions = action;
};

struct Action* getAction(char* query){
	struct Action* action = room->actions;
	while(action->next != NULL){
		if(strcmp(action->query, query) == 0){
			return action;
		}
		action = action->next;
	}
	return NULL;
}