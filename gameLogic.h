#include <ncurses.h>
#include <string>
#include <ctime>
#include <array>
#include <iostream>

class gameLogic{
	private:
		int playerX,playerY;
		int pcX,pcY;
		int rubyX,rubyY;
	public:
		gameLogic(int playerX,int playerY,int pcX,int pcY,int rubyX,int rubyY); //Constructor
		int getInfo(int entInf);// Get x or y of an entity.0=playerX,1=playerY,2=pcX etc.
		void setInfo(int entInf,int val); //Set x or y of an entity. same rules as getInfo
		void movePlayer(int buttonPressed); //Controls the user-character		
		void movePcCharacter(int *direction); //Controls the pc-character
		void moveRuby(int *stepGoal,int *step); //Controls ruby movement
		int checkTiles(int *direction); //Checks for neighbouring free tiles. 
		bool checkIfEnd(); //Checks if game-ending conditions have been fulfilled
		void printPositions(); //Displays player,pc-character and ruby positions
};
