A few rooms (~3) with a few (simple) puzzles (5)
In the end you find a note that contains something you must say to the robot to release you
Then you won the game
Credits roll...


Break out of the tomb of the robot mummy
He/she/it has kidnapped you (the creator) and it has now gone into sleep mode
The walls are aware...

First room with robot
look>respond>You are in a grey coloured chamber. In the middle lies %robot_name. There is also a door [door].
door>actions_go>room2_switches.txt
say>say_to_robot>dummy

Second room with switches
look>respond>You are in a blue room with three switches [examine]. There is a door to the robot [return] and a locked door to the outside world [flee].
examine>actions_switches_view>dummy
set>actions_switch_set>dummy
return>actions_go>room1_robot
flee>actions_go_flee>dummy


Encounter robot/machine
    >can talk to it [say]
    >saying 'exec' executes commands, per manual: instruction is 1 word long
    >exec HCF gets rejected, exec asdf HCF destroys the facility
        >timer starts. time to run for the exit. if too late you lose, otherwise you win.

Robot manual lies somewhere, lots of pages ripped out
    >has instruction manual, you can say them to the robot (prepened by 'exec')
    >instructions are in CAPS
    >OPENDOOR
    >
    >HCF (ripped out)
    
    Manual:
        >instruction length (e.g. 2)
        >instruction listing

Shifting letters puzzle:
 
 ╦ ╦╔═╗╔═╗ 
 ╠═╣║  ╠╣  
 ╩ ╩╚═╝╚   
INSTRUCTION


const char* WALL_TEXT = 
"Manual"
"Page 4"
"UNLOCK"
"Open a"
"gate. ";

reverse code: /*/(0--'(

const char* WALL_TEXT_LEFT = 
"R͍̯̮͘e̡̠M͍̩͡e̯̺̣̕ͅM͔̬̩̣̕ͅB̤̲͓̜͓͍E̳̭̜̳̩R̩ MANual Page 39\n" 
"  \"Ć̷̻͍̖͍͙̘O̮̙͇̮̹͡N̵̞̜̻̹͉̭̜T͏̬͚R̥͉̰͙̞Ǫ̴͓͈̼̝͈̰̙̱̲L̵͇̗̹ ̨̬̬̪͘O̼̖̯͢͠F̴̧̪̝͓̠̝͓ ̱͍̖̯̺̣̱͝T̶̢̺͉͖͔̥̘̩H̡̠̻͍̕E̳͕͇͍͕͈͢͡͞ ͖̙̣̺̳\n" 
"    C̝̱̣̙O͔͕̯̣̟M̧̰̯͙P̜̞͍̦͓̫ͅƯ̳͍͓̞T͇̪̼E̱̤̭̮̜ͅR̗̼͟ ͍̣͍̮̯̘ͅC̷̙O͉̹̦͉UL͙̼̲̺͉̰̩D̦ ͓̰̪̟̯̥̩͟N̖̰O͠T̸͓ͅ\n" 
"    B̖͇̱̬͕̤̬͉E͓͙̰̥̮ ̲̫̹̠̩̯́ͅŖ̱͇̩̤E̻̞͓̤G̴̛̗̗̜̣̪ͅA̧̛̺͚̻̤̩̥̤I̗̟̻͞N̰̪͔̹͈͙̯̼E͈̠͠Ḑ̞̳͟͝.\" \\n";
