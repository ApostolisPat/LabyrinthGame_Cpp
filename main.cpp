#include <ncurses.h>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include "gameLogic.h"
#include "makeMap.h"
int main(int argc,char* argv[]){
	if(argc<2){
		std::cout << "Please input correct path.Use:" << std::endl;
		std::cout << "make run ARGS=<path>" << std::endl;
		std::cout << "or" << std::endl;
		std::cout << "./labirynth ARGS=<path>" << std::endl;
		
		return 1;
	}
	
	std::string pathToMap = argv[1];
	


	initscr(); //Initialize the ncurses window
	if(has_colors() == FALSE){
		endwin();
		std::cout << "You terminal does not support color" << std::endl;
		exit(1);
	}
	
	keypad(stdscr,TRUE);
	cbreak(); //Disable line buffering
	noecho(); //Don't print input characters
	
	start_color();
	init_pair(1,COLOR_RED,COLOR_WHITE); //Color for player
	init_pair(2,COLOR_GREEN,COLOR_WHITE); //Color for pc-character
	
	
	//Read the map file and create the map
	makeMap map;
	map.createMap(pathToMap);

	//Initialize the positions of the player,the pc-character and the ruby
	std::vector<int> positions;
	positions = map.initializeConditions();
	
	//Create the game object.
	gameLogic game(positions[0],positions[1],positions[2],positions[3],positions[4],positions[5]);//Create the game object (Player Xcoord,Player Ycoord,Pc Xcoord,Pc Ycoord,Ruby Xcoord,Ruby Ycoord)
	
	int dir=1; //Start with a random direction for movePcCharacter().
	int move=0; //This is used to hold the player's input for movement.
	
	
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int stepGoal = std::rand()%100+50;
	int step = 0;
	
	
	bool run = true; //run=false when user presses 'Esc'
	
	while(run){
		
		game.moveRuby(&stepGoal,&step);//Move the ruby when needed
		move = getch();//Read the player's movement
		if(move==27){ //If the user presses Esc,the program exits.
			break;
		}
		game.movePlayer(move);//Move the player
		
		//If you want to check pc-character's behaviour, comment 'game.movePlayer() above.
		game.movePcCharacter(&dir);//Move the pc-character
		

		if(game.checkIfEnd()) run=false; //If checkIfEnd return true, set 'run' variable to false
		
		game.printPositions();
		refresh();
		step++;
	}
	endwin();//Close the ncurses window
	std::cout << "GAME OVER!" << std::endl;
	return 0;
	
}
