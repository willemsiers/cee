/*
 *	Actions that can be called from the script
*/

void on_go(union ActionArg room_arg){
	room = (struct Room*)room_arg.room;
	printf("Went to room: %p\n",room);
}

void on_say(union ActionArg text){
	printf("You say: %s\n", text.text);
}

void on_use(union ActionArg text){
	printf("Using %s\n",text.text);
}

void print_options(union ActionArg text){
		// struct Action* action = room->actions;
		struct Option* option = room->options;
		printf("You can do the following things: \n");
		while(option != NULL && option->query != NULL){
			if(option->hidden != 0){
				printf("Option\t%s\n",option->query);
			}
			option = option->next;
		}

		// while(action != NULL){
		// 	if(action->hidden == 0){
		// 		printf("Action\t%s\n",action->query);
		// 	}
		// 	action = action->next;
		// }
}