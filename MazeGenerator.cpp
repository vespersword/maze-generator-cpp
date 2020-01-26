#include <iostream>
#include <conio.h>
#include <ctime>
#include <string>
#include <windows.h>
#include <stack>
#define size 7
using namespace std;

struct cell{
	bool visited;
	bool tW;
	bool bW;
	bool lW;
	bool rW;
	string display;
};

void initialise(cell maze[size][size]);
void reset();
void draw(cell maze[size][size]);
void genMaze(cell maze[size][size],int &startX,int &startY,int &goalX,int &goalY);
	
/*int main(){
		cell maze[size][size];
		int startX=0;int startY=0;int goalX=0;int goalY=0;
		bool k=false;
		while(k==false){
			system("cls");
			initialise(maze);
			genMaze(maze,startX,startY,goalX,goalY);
			char input;
			cout<<"Create new maze? (y/n) :";
			cin>>input;
			if((input!="y")&&(input!="Y")&&(input!="n")&&(input!="N")){
				cout<<"Invalid input."<<endl;
			}
			else if(a=="n"||a=="N"){
				k=true;
				cout<<"Finished.";
			}
		}
		getch();
	}
}
*/

int main() {
        cell Level[size][size];
        int startX=0;
        int startY=0;
        int goalX=0;
        int goalY=0;
        bool k=false;
 
        while(!k) {
                system("cls");
                initialise(Level);
                draw(Level);
                genMaze(Level,startX,startY,goalX,goalY);
                //SaveMaze(Level);
 
                char input;
                cout << "Create a new Maze? (Y)/(N): ";
                cin >> input;
 
                if((input != 'n') && (input != 'N') && (input != 'y') && (input != 'Y'))
                        cout << "Invalid option" << endl;
                else if((input == 'n') || (input == 'N')) {
                        k=true;
                        cout << "Good bye!" << endl;
                }
        }
 
        getch();
        return 0;
}

void reset(){
	HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void draw(cell maze[size][size]){
	for(int i=0;i<size;i++){
		cout<<endl;
		for(int j=0;j<size;j++){
			cout<<maze[i][j].display<<" ";
		}
	}
}


/*void initialise(cell maze[size][size]){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			maze[i][j].display="*";
			maze[i][j].tW=true;
			maze[i][j].bW=true;
			maze[i][j].lW=true;
			maze[i][j].rW=true;
			maze[i][j].visited=false;
		}
	}
	for(int i=1;i<size-1;i++){
		for(int j=1;j<size-1;j++){
			maze[1][j].tW = false;
            maze[size-2][j].bW = false;
            maze[i][1].lW = false;
            maze[i][size-2].rW = false;
		}
	}              
}*/

void initialise(cell Level[][size]) {
        for(int i=0; i<size; i++) {
                for(int j=0; j<size; j++) {
                        Level[i][j].display = '*';
                        Level[i][j].visited = false;
                        Level[i][j].tW = true;
                        Level[i][j].bW = true;
                        Level[i][j].lW = true;
                        Level[i][j].rW = true;
                }
        }
        for(int i=1; i<size-1; i++) {
                for(int j=1; j<size-1; j++) {
                        // Border Cells have fewer accessible walls
                        Level[1][j].tW = false;
                        Level[size-2][j].bW = false;
                        Level[i][1].lW = false;
                        Level[i][size-2].rW = false;
                }
        }
}

void genMaze(cell maze[size][size],int &startX,int &startY,int &goalX,int &goalY){
	srand((unsigned)time(NULL));
	int r=0;
	int percent;
	stack<int> btrackX,btrackY;
	int rX=((2*rand())+1)%(size-1);
	int rY=((2*rand())+1)%(size-1);
	int totalCells= ((size-1)/2)*((size-1)/2);
	int visitedCells=1;
	maze[rX][rY].display="P";
	maze[rX][rY].visited=true;
	while(visitedCells<totalCells){
		if(((maze[rX-2][rX].visited==false) && (maze[rX][rY].lW==true && maze[rX-2][rY].rW==true)) ||
            ((maze[rX+2][rY].visited==false) && (maze[rX][rY].rW==true && maze[rX+2][rY].lW==true)) ||
            ((maze[rX][rY-2].visited==false) && (maze[rX][rY].bW==true && maze[rX][rY-2].tW==true)) ||
            ((maze[rX][rY+2].visited==false) && (maze[rX][rY].tW==true && maze[rX][rY+2].bW==true))){
            	r=(rand()%4)+1;
				if((r==1) && (rX>1)) {
                    if(maze[rX-2][rY].visited == false) {        // If not visited
                        maze[rX-1][rY].display = ' ';        // Delete display
                        maze[rX-1][rY].visited = true;       // Mark cell as visited
                        maze[rX][rY].lW = false;       // Knock down wall
 
                        btrackY.push(rY);                      // Push X for back track
                        btrackX.push(rX);                      // Push Y for back track
 
                        rX -= 2;                                   // Move to next cell
                        maze[rX][rY].visited = true;         // Mark cell moved to as visited
                        maze[rX][rY].display = ' ';          // Update path
                        maze[rX][rY].rW = false;       // Knock down wall
                        visitedCells++;                                 // Increase visitedCells counter
                        }
                        else continue;
                        }
 
                else if((r==2) && (rX<size-2)) {
                    if(maze[rX+2][rY].visited == false) {        // If not visited
                        maze[rX+1][rY].display = ' ';        // Delete display
                        maze[rX+1][rY].visited = true;       // Mark cell as visited
                        maze[rX][rY].rW = false;       // Knock down wall
 
                        btrackY.push(rY);                      // Push X for back track
                        btrackX.push(rX);                      // Push Y for back track
 
                        rX += 2;                                   // Move to next cell
                        maze[rX][rY].visited = true;         // Mark cell moved to as visited
                        maze[rX][rY].display = ' ';          // Update path
                        maze[rX][rY].lW = false;       // Knock down wall
                        visitedCells++;                                 // Increase visitedCells counter
                        }
                        else continue;
                        }
 
                        // GO LEFT
                else if((r==3) && (rY>1)) {
                    if(maze[rX][rY-2].visited == false) {        // If not visited
                        maze[rX][rY-1].display = ' ';        // Delete display
                        maze[rX][rY-1].visited = true;       // Mark cell as visited
                        maze[rX][rY].bW = false;      // Knock down wall
 
                        btrackY.push(rY);                      // Push X for back track
                        btrackX.push(rX);                      // Push Y for back track
 
                        rY -= 2;                                   // Move to next cell
                        maze[rX][rY].visited = true;         // Mark cell moved to as visited
                        maze[rX][rY].display = ' ';          // Update path
                        maze[rX][rY].tW = false;     // Knock down wall
                        visitedCells++;                                 // Increase visitedCells counter
                        }
                        else continue;
                        }
 
                        // GO RIGHT
                else if((r==4) && (rY<size-2)) {
                    if(maze[rX][rY+2].visited == false) {        // If not visited
                        maze[rX][rY+1].display = ' ';        // Delete display
                        maze[rX][rY+1].visited = true;       // Mark cell as visited
                        maze[rX][rY].tW = false;     // Knock down wall

                        btrackY.push(rY);                      // Push X for back track
                        btrackX.push(rX);                      // Push Y for back track
 
                        rY += 2;                                   // Move to next cell
                        maze[rX][rY].visited = true;         // Mark cell moved to as visited
                        maze[rX][rY].display = ' ';          // Update path
                        maze[rX][rY].bW = false;      // Knock down wall
                        visitedCells++;                                 // Increase visitedCells counter
                        }
                        else continue;
                        }
                        percent = (visitedCells*100/totalCells*100)/100;                // Progress in percentage
                        cout << endl << "       Generating a Random Maze... " << percent << "%" << endl;
				}
				else{
					rX=btrackX.top();
					btrackX.pop();
					rY=btrackY.top();
					btrackY.pop();
				}
				reset();
				draw(maze);
			}
			goalX=rX;
			goalY=rY;
			maze[rX][rY].display="E";
			system("cls");
			reset();
			draw(maze);
			cout<<endl<<"Maze generated.";
	}
	
/*
void genMaze(cell Level[][size], int &posX, int &posY, int &goalX, int &goalY) {
        srand((unsigned)time(NULL));                                                                            // Pick random start cell
        int random = 0;
        int rY = ((2*rand())+1)%(size-1);                                          // Generate a random odd number between 1 and SIZE
        int rX = ((2*rand())+1)%(size-1);                                          // Generate a random odd number between 1 and SIZE
        posX = rY;                                                                 // Save player's initial X position
        posY = rX;                                                                 // Save player's initial Y position
        int visitedCells = 1;
        int totalCells = ((size-1)/2)*((size-1)/2);
        int percent = 0;
        stack<int> back_trackX, back_trackY;                                            // Stack is used to trace the reverse path
 
        Level[rX][rY].display = 'S';                                          // Set S as the start cell
        Level[rX][rY].visited = true;                                         // Set start cell as visited;
 
        while(visitedCells < totalCells)
        {
                if(((Level[rX-2][rY].visited == false) && (Level[rX][rY].lW == true && Level[rX-2][rY].rW == true)) ||
                   ((Level[rX+2][rY].visited == false) && (Level[rX][rY].rW == true && Level[rX+2][rY].lW == true)) ||
                   ((Level[rX][rY-2].visited == false) && (Level[rX][rY].bW == true && Level[rX][rY-2].tW == true)) ||
                   ((Level[rX][rY+2].visited == false) && (Level[rX][rY].tW == true && Level[rX][rY+2].bW == true)))
                {
                        random = (rand() % 4) + 1;              // Pick a random wall 1-4 to knock down
 
                         // GO UP
                        if((random == 1) && (rX > 1)) {
                                if(Level[rX-2][rY].visited == false) {        // If not visited
                                        Level[rX-1][rY].display = ' ';        // Delete display
                                        Level[rX-1][rY].visited = true;       // Mark cell as visited
                                        Level[rX][rY].lW = false;       // Knock down wall
 
                                        back_trackX.push(rY);                      // Push X for back track
                                        back_trackY.push(rX);                      // Push Y for back track
 
                                        rX -= 2;                                   // Move to next cell
                                        Level[rX][rY].visited = true;         // Mark cell moved to as visited
                                        Level[rX][rY].display = ' ';          // Update path
                                        Level[rX][rY].rW = false;       // Knock down wall
                                        visitedCells++;                                 // Increase visitedCells counter
                                }
                                else
                                        continue;
                        }
 
                        // GO DOWN
                        else if((random == 2) && (rX < size-2)) {
                                if(Level[rX+2][rY].visited == false) {        // If not visited
                                        Level[rX+1][rY].display = ' ';        // Delete display
                                        Level[rX+1][rY].visited = true;       // Mark cell as visited
                                        Level[rX][rY].rW = false;       // Knock down wall
 
                                        back_trackX.push(rY);                      // Push X for back track
                                        back_trackY.push(rX);                      // Push Y for back track
 
                                        rX += 2;                                   // Move to next cell
                                        Level[rX][rY].visited = true;         // Mark cell moved to as visited
                                        Level[rX][rY].display = ' ';          // Update path
                                        Level[rX][rY].lW = false;       // Knock down wall
                                        visitedCells++;                                 // Increase visitedCells counter
                                }
                                else
                                        continue;
                        }
 
                        // GO LEFT
                        else if((random == 3) && (rY > 1)) {
                                if(Level[rX][rY-2].visited == false) {        // If not visited
                                        Level[rX][rY-1].display = ' ';        // Delete display
                                        Level[rX][rY-1].visited = true;       // Mark cell as visited
                                        Level[rX][rY].tW = false;      // Knock down wall
 
                                        back_trackX.push(rY);                      // Push X for back track
                                        back_trackY.push(rX);                      // Push Y for back track
 
                                        rY -= 2;                                   // Move to next cell
                                        Level[rX][rY].visited = true;         // Mark cell moved to as visited
                                        Level[rX][rY].display = ' ';          // Update path
                                        Level[rX][rY].tW = false;     // Knock down wall
                                        visitedCells++;                                 // Increase visitedCells counter
                                }
                                else
                                        continue;
                        }
 
                        // GO RIGHT
                        else if((random == 4) && (rY < size-2)) {
                                if(Level[rX][rY+2].visited == false) {        // If not visited
                                        Level[rX][rY+1].display = ' ';        // Delete display
                                        Level[rX][rY+1].visited = true;       // Mark cell as visited
                                        Level[rX][rY].tW = false;     // Knock down wall
 
                                        back_trackX.push(rY);                      // Push X for back track
                                        back_trackY.push(rX);                      // Push Y for back track
 
                                        rY += 2;                                   // Move to next cell
                                        Level[rX][rY].visited = true;         // Mark cell moved to as visited
                                        Level[rX][rY].display = ' ';          // Update path
                                        Level[rX][rY].tW = false;      // Knock down wall
                                        visitedCells++;                                 // Increase visitedCells counter
                                }
                                else
                                        continue;
                        }
 
                        percent = (visitedCells*100/totalCells*100)/100;                // Progress in percentage
                        cout << endl << "       Generating a Random Maze... " << percent << "%" << endl;
                }
                else {
                        rY = back_trackX.top();
                        back_trackX.pop();
 
                        rX = back_trackY.top();
                        back_trackY.pop();
                }
 
                //ClearScreen();
                draw(Level);
        }
 
        goalX = rY;
        goalY = rX;
        Level[goalY][goalX].display = 'E';
        //system("cls");
        //ClearScreen();
        draw(Level);
        cout << endl << "\a\t   Complete!" << endl;
}*/
