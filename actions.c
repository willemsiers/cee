/*
 *	Actions that can be called from the script
*/

void actions_go(union ActionArg room_arg){
	room = (struct Room*)room_arg.room;
	printf("Went to room: %p\n",room);
}

void actions_say(union ActionArg text){
	printf("You say: %s\n", text.text);
}

void actions_use(union ActionArg text){
	printf("Using %s\n",text.text);
}

void print_actions(union ActionArg text){
		// struct Action* action = room->actions;
		struct Action* action = room->actions;
		printf("You can do the following things: \n");
		while(action != NULL && action->query != NULL){
			if(action->hidden != 0){
				printf("Action\t%s\n",action->query);
			}
			action = action->next;
		}
}

void respond(union ActionArg text){
	printf("respond: %s\n", text.text);
}