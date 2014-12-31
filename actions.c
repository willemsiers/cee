/* *	Actions that can be called from the script */ 
const int WALL_WIDTH = 6;

const int BASEMENT_WALL_WIDTH = 9;

const int BASEMENT_WALL_OFFSET = 0;
const int BASEMENT_WALL_LEFT_WIDTH = 32;


char* BASEMENT_WALL_TEXT[] = { "7270855/0", "Ꮵ ⒣ٍ\223ܔ\210⒔ٍ\223ܔ\210⒔",
"Ꮯڕ\215ߌ\233Ꮠ  ߒ\227ڔ\235 ",
"Ꮸ ⒦ٍ\231ܔ\210⒚ٍ\231  ",
"drd[ qe`k",
"7270855/0",};

char* BASEMENT_WALL_LEFT[] = { 
    "88888888888888888888888888888888",
    "  R͍̯̮͘e̡̠M͍̩͡e̯̺̣̕ͅM͔̬̩̣̕ͅB̤̲͓̜͓͍E̳̭̜̳̩R̩ MANual Page 39       ",
    "    Ć̷̻͍̖͍͙̘O̮̙͇̮̹͡N̵̞̜̻̹͉̭̜T͏̬͚R̥͉̰͙̞Ǫ̴͓͈̼̝͈̰̙̱̲L̵͇̗̹ ̨̬̬̪͘O̼̖̯͢͠F̴̧̪̝͓̠̝͓ ̱͍̖̯̺̣̱͝T̶̢̺͉͖͔̥̘̩H̡̠̻͍̕E̳͕͇͍͕͈͢͡͞     ͖̙̣̺̳    exec:",
    "      C̝̱̣̙O͔͕̯̣̟M̧̰̯͙P̜̞͍̦͓̫ͅƯ̳͍͓̞T͇̪̼E̱̤̭̮̜ͅR̗̼͟ ͍̣͍̮̯̘ͅC̷̙O͉̹̦͉UL͙̼̲̺͉̰̩D̦ ͓̰̪̟̯̥̩͟N̖̰O͠T̸͓ͅ        ", 
    "     B̖͇̱̬͕̤̬͉E͓͙̰̥̮ ̲̫̹̠̩̯́ͅŖ̱͇̩̤E̻̞͓̤G̴̛̗̗̜̣̪ͅA̧̛̺͚̻̤̩̥̤I̗̟̻͞N̰̪͔̹͈͙̯̼E͈̠͠Ḑ̞̳͟͝.               ",
    "88888888888888888888888888888888"
};

char* basement_wall_text[6];

const char* WALL_TEXT = 
    "ulaMna"
    "e4 Pga"
    "OKCULN"
    "na Oep"
    "e .gta";

char* wall_text;

int loadActions(){
    wall_text = (char*)malloc(strlen(WALL_TEXT)+1); 
    strcpy(wall_text, WALL_TEXT);
     
    //allocate string array
    int j;
    for(j = 0; j<6; j++){
        basement_wall_text[j] = (char*)malloc(strlen(BASEMENT_WALL_TEXT[j]));
        strcpy(basement_wall_text[j], BASEMENT_WALL_TEXT[j]); 
    }
}

void respond(union ActionArg text){
    printf("%s\n", text.text);
}

void action_go(union ActionArg room_arg){
    struct Room* arg_room = (struct Room*)room_arg.room;
    if(arg_room->on_enter != NULL){
        if(!arg_room->on_enter()){
            printf("You remain in the same room.\n");
            return;
        }
    }   
    room = arg_room; 
    printf("You went to room: %p\n",room);
}

void action_say(union ActionArg text){
    printf("You say: %s\n", text.text);
}

void action_use(union ActionArg text){
    printf("Using %s\n",text.text);
}

void action_say_robot(union ActionArg text){
    char* cmd = malloc(100); //TODO dangerous
    char* input = malloc(100);
    strcpy(input, text.text);

    //fuck loops
    cmd = strtok(input, " ");
    if(cmd != NULL){
        {
            if(strcmp(cmd, "exec") == 0){
                cmd = strtok(NULL, " ");
                if(cmd != NULL){
                    if(strcmp(cmd, "HCF") == 0){
                        printf("Hahaha do you think I am that stupid?\n");
                    }
                    else if(strcmp(cmd, "open") == 0){
                        printf("I won't open the door :( \n");
                    }
                    else{
                        printf("%s: command not found *Brrrrrt*\n", cmd);
                        //check for roberflow
                        cmd = strtok(NULL, " ");
                        if(cmd != NULL){
                            if(strcmp(cmd, "HCF") == 0){
                                printf("The robot blows up and you die\n");
                                exit(EXIT_SUCCESS);
                            }else{
                                printf("*̡ͣ͆̇͑̊ͧ̒b́ͨ̅̎͜͡lͥ̅̆̏ͦ̎͠eͦ͢e̾̈́̀͞͏p̄̒͗̔ͬ̓ ̶ͨ̍ͥ̂ͪ̄̀b̢̢̿ͤ̚͞l̄͏̷ōͨ͛̾͆ͫ͊ͯ͜ȯ̈́͑͛͘pͮ̾ͮͧ̽̈ͤ̍͠ ̸̨ͦ̊͑̂͋ͩ̐̏̎̕K̷̢̈ͮ̃̔ͣͦ͟ķ̓̅ͧͭ̕g̸ͬ̾͒ͥ͛̂ͦ͗ͣǵͬ̌̀̿ͤͯ͜t̨̆̏̓ͧͪ́̆ͩ̏͞t̸̔̑̊̈ͯ̅ͭͧͨ̕tͮ̿̎ͯ̋̈ͯ͏̡*̔͛҉̧\n");
                            }
                        }
                    }
                }
            }else{
                printf("*quiet*\n");
            }
        }
    }
    }
    void print_actions(union ActionArg text){ // struct Action* action = room->actions;
        struct Action* action = room->actions;
        printf("You can do the following things: \n");
        while(action != NULL && action->query != NULL){
            if(action->hidden != 0){
                printf("Action\t%s\n",action->query);
            }
            action = action->next;
        }
    }

    void action_order_view(union ActionArg text){
        int i;
        int len = strlen(wall_text)+1;
        printf("012345\n");
        for(i = 0; i<len; i+=WALL_WIDTH){
            printf("%.*s\n", WALL_WIDTH, &wall_text[i]);
        }

    }


    void action_order_push(union ActionArg text){
        if(!(strlen(text.text) == 1 && isdigit(text.text[0]))){
            printf("There is no such button %s\n",text.text);
            return;
        }

        int button = atoi(text.text); //could fail if strange input? (input MUsT be in [1...9])
        if(button > 5 || button < 0){
            printf("There is no such button %s\n",text.text);
            return;
        }
        printf("btn:%d\n",button);
        int i, row, index_neigh;
        int len = strlen(wall_text);
        char temp;
        row = 0;
        for(i = button; i<len; i+=WALL_WIDTH){
            temp = wall_text[i];
            index_neigh = (i+1)%WALL_WIDTH+row*WALL_WIDTH;
            wall_text[i] = wall_text[index_neigh];
            wall_text[index_neigh] = temp;
            row ++;
        }

        //reuse ActionArg (lazy/bad?)
        text.text = "The text on the wall has changed...";
        respond(text);
        action_order_view(text);
    }

void action_microwave(union ActionArg text){
    int time = atoi(text.text);
    if(time != 0){
        printf("You microwave the hotdog %d seconds...\n", time);
        if(time == 71){
            printf("You succesfully cook the hotdog, yum! You feel a lot more POWERFUL!\n");
            powerful++;
        }else{
            printf("Hmmm... that hotdog doesn't look right. Luckily there are enough hotdogs here, but this time I must cook it for the correct amount of time.\n");
        }
    }else{
        printf("You must enter a time (seconds) to the microwave for it to start.\n");
    }
}

void action_go_flee(union ActionArg text){

}

void action_close_trapdoor(union ActionArg text){
    if(follow_state == 0){
        trapdoor = !trapdoor;
        if(!trapdoor){
            printf("You open the trapdoor. A little beam of light now enters the room\n");
        }else{
            printf("You close the trapdoor. There's no light left in the room.\nIt's as if your eyes suddenly got disabled.\n");
            printf("There's definitely some sound, it's very clear.\n");
        }
    }else{
        printf("The trapdoor is currently out of reach.\n");
    }
}

void action_listen(union ActionArg text){
    if(!trapdoor){
        printf("*tap tap tap...*\nYou hear something, but you can not really determine what it is, or where it's coming from.\n");
        return;
    }
    if(follow_state == 0){
        printf("*tap tap tok*\nThe sound is coming from the right [right] but there also some sort of growling sound to the left [left].\n");
    }else if(follow_state == 1){
        printf("*Tap TAp TOK*\nIt's coming from far away, but it's louder. Go left [left] or right [right].\n");
    }else if(follow_state == 2){
        printf("*TAP taP TAP!*\n It's very loud, I must be near. Go left [left] or right [right].\n");
    }else if(follow_state == 3){
        printf("*TAP TAP TAP TAP TAP TAP TAP TAP TAP\n...\n..\n.*\n\nIt got quiet.\n");
    }
}

void action_follow_left(union ActionArg text){
    if(trapdoor){
        if(follow_state == 0){
            printf("You walk about 10 meters through the darkness. The sound is louder than before [listen].\n");
            follow_state = 1;
        }
        else if(follow_state == 1){
            printf("You walk further and the sound becomes softer. Suddenly you feel like you're back at the start. Maybe try a different route.\n");
            follow_state = 0;
        }else if(follow_state == 2){
            printf("You walk further and the sound is now very loud [listen].\n");
            follow_state = 3;
        }
    }
}

void action_follow_right(union ActionArg text){
    if(trapdoor){
        if(follow_state == 0){
            printf("There seems to be a wall here. Let's go back and try to find a different route.\n");
        }
        else if(follow_state == 1){
            printf("You walk a long way through what feels like a long narrow pathway. The sound gets louder and louder, you know you are very near.\n");
            follow_state = 2;
        }else if(follow_state == 2){
            printf("You walk a long way through what feels like a long narrow pathway. Suddenly you feel like you're back at the start. Maybe try a different route.\n");
            follow_state = 0;
        }
    }
}

    void action_basement_check(union ActionArg text){
        if(follow_state != 3){
            return;
        }
        int row;
        for(row = 0; row < 6; row++){
           printf("%s%s",BASEMENT_WALL_LEFT[row], basement_wall_text[row]);
           if(row % 5 == 0){
               printf("888888\n");
           }else{
               printf("\n");
           }
        }
    }

    void action_look_basement(union ActionArg text){
        if(trapdoor){
            if(follow_state == 3){
                printf("All I can see is a little glowing button [push].\n");
            }else{
                printf("You can not see a thing.\n");
            }
        }else{
            printf("It's dark here, I don't see much except for the trapdoor [trapdoor] and the ladder [ladder].\n");
        }
    }

    void action_basement_button(union ActionArg text){
        if(follow_state == 3){
            printf("Upon pressing the light a spotlight shines on the wall on the other side of the room [examine]. Someone has written on it. It's hard to read, and the last part even seems to be encrypted. There also is a small keypad on the wall [type]. It expects 9 numbers to be entered.\n"); 
        }
    }

    int on_enter_basement(){
        if(powerful){
            printf("You use your hulk-like strength to lift the trapdoor. As it opens you see something flash by very quickly, it's gone now.\n");
            printf("There's a ladder that goes down. It's very dark, but you go anyway.\n");
            follow_state = 0;
            trapdoor = 0;
        }else{
            printf("You try to open the trapdoor, but as soon as you open it slightly it slams back closed, with great force. It's almost as if someone was pulling it shut...\n");
            printf("I guess I will try again later when I feel a bit more POWERFUL!\n");
        }
        return powerful;
    }

    int on_enter_robot(){
        if(trapdoor){
            printf("You can't find the ladder, it's too dark in here.\n");
        }
        return !trapdoor;
    }

  void action_basement_type(union ActionArg text){
      if(follow_state != 3){
          return;
      }

      int in_len = strlen(text.text);
  
      int row, col;
      for(row = 0; row < 6; row++){
          for(col = 0; col < 9*10; col++){  //dealing with unicode, just break on \0
              char orig_char = BASEMENT_WALL_TEXT[row][col]; 
              if(orig_char != '\0' && orig_char != '\n' && orig_char != '\t' && orig_char != ' '){
                  char input_at_index = text.text[col%in_len]; 
                  int offset = (int)input_at_index - (int)'0';
                  char new_char = (char)((int)orig_char + offset);
                  if(new_char != '\n' && new_char != '\t' && new_char != ' '){
                      basement_wall_text[row][col] = new_char;
                  }else{
                      basement_wall_text[row][col] = orig_char;
                  }
              }else{
                  basement_wall_text[row][col] = orig_char;
                  if(orig_char == '\0'){
                      break;
                  }
              }
          }
      }
  
      //reuse ActionArg (lazy/bad?)
      text.text = "The text on the wall has changed...";
      respond(text);
      action_basement_check(text);
  }
