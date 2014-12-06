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