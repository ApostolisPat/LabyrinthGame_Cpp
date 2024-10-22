#include "makeMap.h"

int makeMap::createMap(std::string pathToMap){
//Read the map file
	//map.txt
	std::ifstream file(pathToMap);
	
	//Check if file exists
	if(!file.is_open()){
		printw("Error opening the file.");
		getch();
		endwin();
		return 1;
	}
	
	//Read each line of the file
	std::string line;
	while(std::getline(file,line)){
		printw("%s\n",line.c_str());
	}	
	
	//Close the file 
	file.close();
	return 0;
}

std::vector<int> makeMap::initializeConditions(){
	//Create the player character,ruby and pc-character
	int randx;
	int randy;
	std::vector<int> positions;
	int currTile;
	int done = 0;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	for(int i=0;i<3;i++){
		randy = std::rand()%18+1;	 //create random number between 1 and 20 for y
		randx = std::rand()%39+1; //create random number between 1 and 40 for x
		currTile = mvinch(randy,randx) & A_CHARTEXT; //Check UP
		if(currTile=='.'){
			positions.push_back(randx);
			positions.push_back(randy);
		}
		else	i--;
	}
	return positions;
}
