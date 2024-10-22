This is a labyrinth game with 2 players. One player is controlled by you (red), while the other is run by the program (green).  
Your goal is to get the gem before Green does, be quick!  

1. **General**  
    * ***Movement***  
       - Move by using the arrow keys to go up, down, left and right. You can exit the program anytime by pressing 'Esc'  
    * ***Screen Information***  
       On the screen you can see the labyrinth map, the two players and the gem.  
       Under the map you can see:  
         - Remaining steps until the gem moves again.  
         - Coordinates of player and gem (x,y)  

2. **Technical Information**   
   * ***Classes*** 
      * Main
      * GameLogic  
        - w/ Object Variables:   
          > 1. Int PlayerX,playerY  
          > 2. Int PcX,PcY  
          > 3. Int RubyX,RubyY  
      * MakeMap
        
   * ***Methods***
     *  GameLogic
        > 1. Int GetInfo(int)  
        > 2. Void SetInfo(int,int)  
        > 3. Void MovePlayer(int)  
        > 4. Void MovePcCharacter(int *)  
        > 5. Void MoveRuby(int *,int *)  
        > 6. Int checkTiles(int *)  
        > 7. Bool checkIfEnd()  
        > 8. Void printPositions()
     *  MakeMap
        > 1. Int createMap(string)
        > 2. Vector<int> initializeConditions()

3.  **How to run the game**  
          Run it in an IDE by using the command ``` run ARGS=<path> ```, where ARGS is the relative path of the .txt file that contains the map.  

