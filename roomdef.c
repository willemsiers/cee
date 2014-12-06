/*
 *	This file defines:
 *		structs for Option and Action
 *		add- function for Action and Option
 *		get for Action, get for Message(from Option)
*
 *	NOTE: these functions assume a global `room` var to get and set properties on 
*/

//OPTION DEFINITION
struct Option{
	char* query;
	char* response;
	struct Option* next;
};

struct Option* options;

//ROOM DEFINITION
struct Room{
	struct Option* options;
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
	struct Action* next;
};

struct Action* actions;


void addAction(char* query, void (*fupo)(union ActionArg), union ActionArg defArg){
	struct Action* action = (struct Action*) malloc(sizeof(struct Action)); //new action
	action->query = query;
	action->fupo = fupo;
	action->defArg = defArg;
	action->next = room->actions;
	room->actions = action;
};

void addOption(char* query, char* response){
	struct Option* option = (struct Option*) malloc(sizeof(struct Option)); //new option
	option->query = query;
	option->response = response;
	option->next = room->options;
	room->options = option;
}

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

char* getMessage(char* query){
	struct Option* option = room->options;
	while(option->next != NULL){ //when (*option).next is null it's the dummy (root) node
		if(strcmp(option->query, query) == 0){
			return option->response;
		}
		option = option->next;
	}
	return "Not Found!";
}