/*							___
 *	Global state vars below \!/
 */							 
struct Room* room; //AKA currentRoom
int powerful = 0; //used in actions.c (action_microwave)
int trapdoor = 0;
int gate_locked = 1;
int follow_state = 0;


#ifdef Release
    #define room_listing_path "data/rooms.dat"
    #define ROOM_FILE_EXTENSIONS  ".dat"
    #define ROOM_FILE_ROOT "data/"
#else
    #define room_listing_path "room_listing.txt"
    #define ROOM_FILE_EXTENSIONS ".txt"
    #define ROOM_FILE_ROOT ""
#endif

#define ROBO_NAME "House Robot 3000"
#define VOICE_CMD "housebot"
#define BUF_SIZE 600
#define BUF_SIZE_QUERY 32
#define BUF_SIZE_HIDDEN 6
#define BUF_SIZE_ACTION 32
#define BUF_SIZE_ARG 600
#define EXIT_WIN 4
#define EXIT_OTHER 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.c"
#include "roomdef.c"
#include "actions.c"

int start(){
    printf("(Hint) Remeber you can type \"options\" at any time.\n");
    //story
    printf("You wake up. \"What happened? And what is wrong with the thermostat...\"\n");
    char* query = malloc(BUF_SIZE);
    int exitStatus = 0;

    // temp buffers for splitting up action input
    char* spl_action = (char*) malloc(BUF_SIZE);
    char* spl_actionArg = (char*) malloc(BUF_SIZE);

    while(exitStatus == 0){
        setTerminalColor(COL_INPUT);
        printf(">");
        query = fgets(query, BUF_SIZE, stdin); //query is pointer to query
        setTerminalColor(COL_STORY);

        if (query == 0)	{ //? check man?
            return 99;
        }

        remNewline(query);

        if(strcmp(query, "bye") == 0){ //exit program
            exitStatus = 1;
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
                exitStatus = (*fupo)(arg);
            }
        }else{
            printf("Huh?\n");
        }

    }
    return exitStatus;
}

int load(){
    //temp vars (function scope) for gettings pointers of rooms as `Action` defArg
    struct Room* rooms[4];
    char roomNames[10][BUF_SIZE];
    int roomCnt = 0;

    FILE* file_room_listing = fopen(room_listing_path, "r");

    char* buf_room_listing = (char*) malloc(BUF_SIZE);

    while(fgets(buf_room_listing, BUF_SIZE, file_room_listing) != NULL){
        remNewline(buf_room_listing);
#ifdef Release
        replaceTxtWithDat(buf_room_listing);
        char* corrected_path = (char*)malloc(BUF_SIZE);
        strcpy(corrected_path, "data/");
        strcat(corrected_path, buf_room_listing);
        buf_room_listing = corrected_path;
#endif
        FILE* file_room = fopen(buf_room_listing, "r");

        //create new `Room`
        room = (struct Room*) malloc(sizeof(struct Room)); //set global var
        rooms[roomCnt] = room;
        strcpy(roomNames[roomCnt] , buf_room_listing);
        roomCnt++;

        //init on_enter to NULL
        setOnEnter(NULL);
        //room->on_enter = (int (*)()) malloc(sizeof(int (*)())); OLD

        //init linkedlist `actions`
        room->actions = (struct Action*) malloc(sizeof(struct Action));
        room->actions->next = NULL;
        room->actions->fupo = NULL;

        //shared buffers for each line that's read (no malloc needed) TODO: Can move outside outer while loop.
        char buf_line[BUF_SIZE];
        char buf_func[BUF_SIZE];

        while(fgets(buf_line, BUF_SIZE, file_room) != NULL){
            remNewline(buf_line);

            //first allocate memory to let string contents live outside scope
            char* buf_query = (char*) malloc(BUF_SIZE_QUERY);
            char* buf_arg = (char*) malloc(BUF_SIZE_ARG);
            char buf_hidden[BUF_SIZE_HIDDEN] = "000000";

            int read = sscanf(buf_line, "%32[^>\t]\t>\t%32[^>\t]\t>\t%600[^>]>\t%6[^\n]\n", buf_query, buf_func, buf_arg, buf_hidden);

            if(read <2){
                printf("Error parsing file *near* %s\n",buf_query);
                fclose(file_room);
                fclose(file_room_listing);
                return 1;
            }

            int (*fupo)(union ActionArg) = NULL;
            int (*fupo_enter)() = NULL;
            //comments are incorrect
            if(strcmp(buf_func, "action_go") == 0){
                fupo = &action_go;
            }else if(strcmp(buf_func, "action_say") == 0){
                fupo = &action_say;
            }else if(strcmp(buf_func, "action_order_view") == 0){
                fupo = &action_order_view;
            }else if(strcmp(buf_func, "action_order_push") == 0){
                fupo = &action_order_push;
            }else if(strcmp(buf_func, "action_say_robot") == 0){
                fupo = &action_say_robot;
            }else if(strcmp(buf_func, "action_microwave") == 0){
                fupo = &action_microwave;
            }else if(strcmp(buf_func, "action_close_trapdoor") == 0){
                fupo = &action_close_trapdoor;
            }else if(strcmp(buf_func, "action_listen") == 0){
                fupo = &action_listen;
            }else if(strcmp(buf_func, "action_follow_left") == 0){
                fupo = &action_follow_left;
            }else if(strcmp(buf_func, "action_follow_right") == 0){
                fupo = &action_follow_right;
            }else if(strcmp(buf_func, "action_follow_return") == 0){
                fupo = &action_follow_return;
            }else if(strcmp(buf_func, "action_look_basement") == 0){
                fupo = &action_look_basement;
            }else if(strcmp(buf_func, "action_basement_button") == 0){
                fupo = &action_basement_button;
            }else if(strcmp(buf_func, "action_basement_check") == 0){
                fupo = &action_basement_check;
            }else if(strcmp(buf_func, "action_basement_type") == 0){
                fupo = &action_basement_type;
            }else if(strcmp(buf_func, "on_enter_basement") == 0){
                fupo_enter = &on_enter_basement;
            }else if(strcmp(buf_func, "on_enter_microwave") == 0){
                fupo_enter = &on_enter_microwave;
            }else if(strcmp(buf_func, "on_enter_robot") == 0){
                fupo_enter = &on_enter_robot;
            }else if(strcmp(buf_func, "respond") == 0){
                fupo = &respond;
            }else{
                fclose(file_room);
                fclose(file_room_listing);
                printf("Error: action not found: %s\n",buf_func);
                return 2;
            }

            union ActionArg defArg = {};
            unescapeNewline(buf_arg);
            if(fupo != &action_go){
                defArg.text = buf_arg;
            }else{
                defArg.text = (char*)malloc(80);
                strcpy(defArg.text, ROOM_FILE_ROOT);
                strcat(defArg.text, buf_arg);
                strcat(defArg.text, ROOM_FILE_EXTENSIONS);
            }

            int hidden = strcmp(buf_hidden, "hidden");

            //on_enter callbacks
            if(strcmp(buf_query, "on_enter") == 0){
                setOnEnter(fupo_enter);
            }else{
                addAction(buf_query, fupo, defArg, hidden);
            }

        }
        //add some globally available actions here
        union ActionArg dummy;
        addAction("options", &print_actions, dummy, 0);

        //printf("(DEB) Last read line was %s \n", buf_line);		

        fclose(file_room);
    }

    fclose(file_room_listing);

    //next replace all names (Strings) of rooms in `go` actions with Room*
    while(roomCnt --> 0){
        struct Action* action = rooms[roomCnt]->actions;
        while(action != NULL){
            if(action->fupo == &action_go){
                int i = 0;
                while(i<=6 && (strcmp(roomNames[i], action->defArg.text) != 0)){i++;};
                if(i == 6){ //ouch!!!
                    printf("ERROR! room not found!\n"); 
                }
                //printf("Replacing defArg %s to %p\n", action->defArg.text, rooms[i]);
                action->defArg.room = rooms[i];
            }
            action = action->next;
        }
    }

    int loadActionsStatus = loadActions();

    return 0;
}

int main(){
    printf("Loading game...\n");
    int loadStatus = load();
    if(!loadStatus){
        printf("Game loaded!\n\n\n");
        printf("Welcome.\nType \"options\" if you are stuck.\nPress Ctrl-C to exit.\nPress enter to start...\n");

        char enter_input = 0;
        while (enter_input  != '\r' && enter_input != '\n') { enter_input = getchar(); }
        printf("\033[2J\033[1;1H"); //clear terminal

        int exitStatus = start();
        if(exitStatus == EXIT_WIN){
            setTerminalColor(COL_END);
            printf("\n***\nCONGRATULATIONS, YOU BEAT THE ROBOT!\n***\n");
            printf("Programming: Willem Siers\n");
        }
        printf("Thank you for playing.\n");
        setTerminalColor(COL_DEFAULT);
    }else{
        printf("Error during loading. Status code: %d\n", loadStatus);
    }
    return 0;
}
