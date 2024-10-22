#include "gameLogic.h"

gameLogic::gameLogic(int playerX_,int playerY_,int pcX_,int pcY_,int rubyX_,int rubyY_)
	:playerX(playerX_)
	,playerY(playerY_)
	,pcX(pcX_)
	,pcY(pcY_)
	,rubyX(rubyX_)
	,rubyY(rubyY_)
	{}

int gameLogic::getInfo(int entInf){
	if(entInf==0) return playerX;
	else if(entInf==1) return playerY;
	else if(entInf==2) return pcX;
	else if(entInf==3) return pcY;
	else if(entInf==4) return rubyX;
	else if(entInf==5) return rubyY;
	else return -1;
}

void gameLogic::setInfo(int entInf,int val){
	if(entInf==0) playerX = val;
	else if(entInf==1) playerY = val;
	else if(entInf==2) pcX = val;
	else if(entInf==3) pcY = val;
	else if(entInf==4) rubyX = val;
	else if(entInf==5) rubyY = val;
}

void gameLogic::moveRuby(int *stepGoal,int *step){
	int randx,randy;
	int currTile;
	bool set;//Used for checking if ruby has found a position
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	if(*step==*stepGoal){
		//create new step Goal
		*stepGoal = std::rand()%100+50;
		//create ruby positions
		mvprintw(getInfo(5),getInfo(4),"."); //Clear the ruby's current position
		while(set==false){
			randx = std::rand()%39+1;
			randy = std::rand()%18+1;
			currTile = mvinch(randy,randx) & A_CHARTEXT; //Check ruby
			if(currTile=='.'){
				setInfo(4,randx);
				setInfo(5,randy);
				set=true;
			}
		}
		*step=0;
	}
	std::string text = "Ruby will change positions in: " + std::to_string(*stepGoal-*step) +  " steps.";
	mvprintw(30,0,"%s",text.c_str()); 
		
	mvprintw(getInfo(5),getInfo(4),"@"); //Draw the ruby
	refresh();
}

void gameLogic::movePlayer(int buttonPressed){
	int next_tile=0;
	bool moved=false;
	switch(buttonPressed){
			case KEY_UP: //key up
				next_tile = mvinch(playerY-1,playerX) & A_CHARTEXT; //Reads next tile
				if(next_tile!='*'){
					playerY--;
					mvprintw(playerY+1,playerX,"."); //Clear the previous tile before moving on
					refresh();
					moved=true;
				}
				break;
			case KEY_DOWN: //key down
				next_tile = mvinch(playerY+1,playerX) & A_CHARTEXT;//Reads next tile
				if(next_tile!='*'){
					playerY++;
					mvprintw(playerY-1,playerX,"."); //Clear the previous tile before moving on
					refresh();
					moved=true;
				}
				break;
			case KEY_RIGHT: //key right
				next_tile = mvinch(playerY,playerX+1) & A_CHARTEXT;//Reads next tile
				if(next_tile!='*'){
					playerX++;
					mvprintw(playerY,playerX-1,"."); //Clear the previous tile before moving on
					refresh();
					moved=true;
				}							
				break;
			case KEY_LEFT: //key left
				next_tile = mvinch(playerY,playerX-1) & A_CHARTEXT;//Reads next tile
				if(next_tile!='*'){
					playerX--;
					mvprintw(playerY,playerX+1,"."); //Clear the previous tile before moving on
					refresh();
					moved=true;
				}
				break;
				
		}
	attron(COLOR_PAIR(1));
	mvprintw(playerY,playerX,"#");
	attroff(COLOR_PAIR(1));
	refresh();
	
	if(moved==false){
		buttonPressed = getch();
		movePlayer(buttonPressed);
	} 
}

int gameLogic::checkTiles(int *direction){//Check surrounding tiles for unblocked paths
	int next_tile1=0,next_tile2=0,next_tile3=0,next_tile4=0; //These hold the values of the surrounding tiles
	std::array<int,4> unblockedPaths{0,0,0,0}; //{UP,DOWN,LEFT,RIGHT}. If any tiles are free, then its corresponding position will be 1.The way back is always 0.
	std::array<int,4> compareArr {0,0,0,0}; //This array will be compared with unblockedPaths.If both are {0,0,0,0}(meaning there are no free paths), then the pc-character must go backwards
	bool found=false;
	
	std::string text;
	//int times=0;
	
	if(*direction==1){//If we are going up
		//Check the surrounding tiles.(The tile we came from is always going to be 0.
		next_tile1 = mvinch(pcY-1,pcX) & A_CHARTEXT; //Check UP
		if(next_tile1!='*') unblockedPaths[0]=1;
		next_tile3 = mvinch(pcY,pcX-1) & A_CHARTEXT; //Check LEFT
		if(next_tile3!='*') unblockedPaths[2]=1;
		next_tile4 = mvinch(pcY,pcX+1) & A_CHARTEXT; //Check RIGHT
		if(next_tile4!='*') unblockedPaths[3]=1;
		if(unblockedPaths==compareArr) {//If there are no free paths around the character,it means it is blocked and has to go backwards.
			*direction=2;//go down
			int moveAllowed=1; //Direction found, exit the while loop in movePcCharacter
			return moveAllowed;
		
		}
		else if(!(unblockedPaths==compareArr)){//If there are free paths
			while(!found){//Run until it decides on a path
				
				std::srand(static_cast<unsigned int>(std::time(nullptr)));
				int index = std::rand()%4;
				while(unblockedPaths[index]!=1){ //If the array position of the index is not 1,just increment by 1,and modulo by 4 to go to the next position.
					index++;
					index=index%4;
				}
				if(unblockedPaths[index]==1){
					*direction = index+1;//index is between 0-3. Switch case checks for 1-4. So index+1 to return the correct value.
					found=true;
					int moveAllowed=1;
					return moveAllowed;
				}
				
			}
		}
	}
	
	//The code is pretty much the same as above for the other directions.
	
	else if(*direction==2){//if we are going down
		next_tile2 = mvinch(pcY+1,pcX) & A_CHARTEXT; //Check DOWN
		if(next_tile2!='*') unblockedPaths[1]=1;
		next_tile3 = mvinch(pcY,pcX-1) & A_CHARTEXT; //Check LEFT
		if(next_tile3!='*') unblockedPaths[2]=1;
		next_tile4 = mvinch(pcY,pcX+1) & A_CHARTEXT; //Check RIGHT
		if(next_tile4!='*') unblockedPaths[3]=1;
		if(unblockedPaths==compareArr){
			*direction=1;
			int moveAllowed=1;
			return moveAllowed;
		}
		else if(!(unblockedPaths==compareArr)){//Run as long as we haven't found an unblocked path
			while(!found){
				
				std::srand(static_cast<unsigned int>(std::time(nullptr)));
				int index = std::rand()%4;
				while(unblockedPaths[index]!=1){ //If the array position of the index is not 1,just increment by 1,and modulo by 4 to go to the next position.
					index++;
					index=index%4;
				}
				if(unblockedPaths[index]==1){
					*direction = index+1;
					int moveAllowed=1;
					return moveAllowed;
				}
			}
			
		}
	}
	else if(*direction==3){//If we are going left
		next_tile1 = mvinch(pcY-1,pcX) & A_CHARTEXT; //Check UP
		if(next_tile1!='*') unblockedPaths[0]=1;
		next_tile2 = mvinch(pcY+1,pcX) & A_CHARTEXT; //Check DOWN
		if(next_tile2!='*') unblockedPaths[1]=1;
		next_tile3 = mvinch(pcY,pcX-1) & A_CHARTEXT; //Check LEFT	
		if(next_tile3!='*') unblockedPaths[2]=1;
		if(unblockedPaths==compareArr){
			*direction = 4;
			int moveAllowed=1;
			return moveAllowed;
		}
		else if(!(unblockedPaths==compareArr)){//Run as long as we haven't found an unblocked path
			while(!found){

				std::srand(static_cast<unsigned int>(std::time(nullptr)));
				int index = std::rand()%4;
				while(unblockedPaths[index]!=1){ //If the array position of the index is not 1,just increment by 1,and modulo by 4 to go to the next position.
					index++;
					index=index%4;
				}
				if(unblockedPaths[index]==1){
					*direction = index+1;
					found=true;
					int moveAllowed=1;
					return moveAllowed;
				}
			}
			
		}
	}
	else if(*direction==4){//If we are going right
		next_tile1 = mvinch(pcY-1,pcX) & A_CHARTEXT; //Check UP
		if(next_tile1!='*') unblockedPaths[0]=1;
		next_tile2 = mvinch(pcY+1,pcX) & A_CHARTEXT; //Check DOWN
		if(next_tile2!='*') unblockedPaths[1]=1;
		next_tile4 = mvinch(pcY,pcX+1) & A_CHARTEXT; //Check RIGHT
		if(next_tile4!='*') unblockedPaths[3]=1;
		if(unblockedPaths==compareArr){ 
			*direction=3;
			int moveAllowed=1;
			return moveAllowed;
		}
		else if(!(unblockedPaths==compareArr)){//Run as long as we haven't found an unblocked path
			while(!found){
				
				std::srand(static_cast<unsigned int>(std::time(nullptr)));
				int index = std::rand()%4;
				while(unblockedPaths[index]!=1){ //If the array position of the index is not 1,just increment by 1,and modulo by 4 to go to the next position.
					index++;
					index=index%4;
				}
				if(unblockedPaths[index]==1){
					*direction = index+1;
				
					found=true;
					int moveAllowed=1;
					return moveAllowed;
				}
			}
			
		}
	}
}

void gameLogic::movePcCharacter(int *direction){
	
	int moveAllowed=0;	
	while(moveAllowed==0){
		moveAllowed = checkTiles(direction);	
	}
	
	
	switch(*direction){
		case 1://move UP
			pcY--;//move UP
			attron(COLOR_PAIR(2));
			mvprintw(pcY,pcX,"#");//Draw pc-controlled character
			attroff(COLOR_PAIR(2));
			mvprintw(pcY+1,pcX,"."); //Clear the previous tile 
			break;
		case 2://move DOWN
			pcY++;//move DOWN
			attron(COLOR_PAIR(2));
			mvprintw(pcY,pcX,"#");//Draw pc-controlled character
			attroff(COLOR_PAIR(2));
			mvprintw(pcY-1,pcX,"."); //Clear the previous tile 			
			break;
		case 3://move LEFT 
			pcX--;//move LEFT
			attron(COLOR_PAIR(2));
			mvprintw(pcY,pcX,"#");//Draw pc-controlled character
			attroff(COLOR_PAIR(2));
			mvprintw(pcY,pcX+1,"."); //Clear the previous tile
			break;
		case 4://move RIGHT
			pcX++;//move RIGHT
			attron(COLOR_PAIR(2));
			mvprintw(pcY,pcX,"#");//Draw pc-controlled character
			attroff(COLOR_PAIR(2));
			mvprintw(pcY,pcX-1,"."); //Clear the previous tile before moving on
			break;
		
	}
	refresh();
}

bool gameLogic::checkIfEnd(){
		//Check for game ending conditions
		if((getInfo(0)==getInfo(4) && getInfo(1)==getInfo(5))||(getInfo(2)==getInfo(4) && getInfo(3)==getInfo(5))){
			return true;
		}
		return false;
}


void gameLogic::printPositions(){
	std::string text;
	text = "Player=(" + std::to_string(getInfo(0)) +  "," + std::to_string(getInfo(1)) + ")";
	mvprintw(32,0,"%s",text.c_str()); 
	text = "PC=(" + std::to_string(getInfo(2)) +  "," + std::to_string(getInfo(3)) + ")";
	mvprintw(33,0,"%s",text.c_str()); 
	text = "Ruby=(" + std::to_string(getInfo(4)) +  "," + std::to_string(getInfo(5)) + ")";
	mvprintw(34,0,"%s",text.c_str()); 
}




