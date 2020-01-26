#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <stack>
#include <string>
#define SIZE 39
using namespace std;
 
struct Cell
{
    bool visited;
    bool tW;
    bool bW;
    bool lW;
    bool rW;
    string display;
};

void initialise(Cell maze[SIZE][SIZE]);
void ClearScreen();
void draw(Cell maze[SIZE][SIZE]);
void genMaze(Cell maze[SIZE][SIZE], int &posX, int &posY, int &goalX, int &goalY);
 
int main() {
    Cell maze[SIZE][SIZE];
    int startX=0;
    int startY=0;
    int goalX=0;
    int goalY=0;
    bool k=false;
    while(!k) {
        system("cls");
        initialise(maze);
        draw(maze);
        genMaze(maze,startX,startY,goalX,goalY);
        char input;
        cout<<"Create a new Maze? (Y)/(N): ";
        cin>>input;
        if((input != 'n') && (input != 'N') && (input != 'y') && (input != 'Y'))
            cout << "Invalid option" << endl;
        else if((input == 'n') || (input == 'N')) {
            k=true;
            cout << "Done." << endl;
            }
        }
    getch();
}
 
void initialise(Cell maze[SIZE][SIZE]) {
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            maze[i][j].display = '*';
            maze[i][j].visited = false;
            maze[i][j].lW= true;
            maze[i][j].rW = true;
            maze[i][j].tW = true;
            maze[i][j].bW = true;
        }
    }
    for(int i=1; i<SIZE-1; i++) {
        for(int j=1; j<SIZE-1; j++) {
            maze[1][j].lW = false;
            maze[SIZE-2][j].rW = false;
            maze[i][1].tW = false;
            maze[i][SIZE-2].bW = false;
        }
    }
}
 
void ClearScreen()
{
        HANDLE hOut;
        COORD Position;
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        Position.X = 0;
        Position.Y = 0;
        SetConsoleCursorPosition(hOut, Position);
}
 
void draw(Cell maze[SIZE][SIZE]) {
    for(int i=0; i<SIZE; i++) {
        cout << endl;
        for(int j=0; j< SIZE; j++)
            cout << " " << maze[i][j].display;
    }
}
 
void genMaze(Cell maze[SIZE][SIZE], int &posX, int &posY, int &goalX, int &goalY) {
    srand((unsigned)time(NULL));                                                                            
    int r = 0;
    int rY = ((2*rand())+1)%(SIZE-1);                                         
    int rX = ((2*rand())+1)%(SIZE-1);                                          
    posX = rY;                                                                 
    posY = rX;                                                                
    int visitedCells = 1;
    int totalCells = ((SIZE-1)/2)*((SIZE-1)/2);
    int percent = 0;
    stack<int> btrackX, btrackY;                                            
    maze[rX][rY].display="S";                                          
    maze[rX][rY].visited = true;                                      
    while(visitedCells<totalCells){
        if(((maze[rX-2][rY].visited==false) && (maze[rX][rY].lW==true && maze[rX-2][rY].rW==true)) ||
           ((maze[rX+2][rY].visited==false) && (maze[rX][rY].rW==true && maze[rX+2][rY].lW==true)) ||
           ((maze[rX][rY-2].visited==false) && (maze[rX][rY].tW==true && maze[rX][rY-2].bW==true)) ||
           ((maze[rX][rY+2].visited==false) && (maze[rX][rY].bW==true && maze[rX][rY+2].tW==true))){
                r =(rand() % 4) + 1;
                if((r == 1) && (rX > 1)){
                    if(maze[rX-2][rY].visited==false) {    
                        maze[rX-1][rY].display=' ';        
                        maze[rX-1][rY].visited=true;       
					    maze[rX][rY].lW=false;      
                        btrackX.push(rX);                     
                        btrackY.push(rY);                      
                        rX -= 2;                                   
                        maze[rX][rY].visited=true;        
                        maze[rX][rY].display=' ';          
                        maze[rX][rY].rW = false;       
                        visitedCells++;                                
                    }
                    else continue;
                }
 
                else if((r==2) && (rX<SIZE-2)) {
                    if(maze[rX+2][rY].visited==false) {        
                        maze[rX+1][rY].display=' ';       
                        maze[rX+1][rY].visited=true;       
                        maze[rX][rY].rW=false;       
                        btrackX.push(rX);                     
                        btrackY.push(rY);                     
                        rX += 2;                                  
                        maze[rX][rY].visited=true;        
                        maze[rX][rY].display=' ';         
                        maze[rX][rY].lW=false;       
                        visitedCells++;                                 
                    }
                    else continue;
                }
                
				else if((r==3) && (rY>1)) {
                    if(maze[rX][rY-2].visited==false) {       
                        maze[rX][rY-1].display=' ';       
                        maze[rX][rY-1].visited=true;      
                        maze[rX][rY].tW=false;      
                        btrackX.push(rX);                 
                        btrackY.push(rY);                  
                        rY -= 2;                                  
                        maze[rX][rY].visited=true;       
                        maze[rX][rY].display=' ';         
                        maze[rX][rY].bW=false;    
                        visitedCells++;                             
                     }
                    else continue;
                    }
                        
				else if((r==4) && (rY<SIZE-2)) {
                    if(maze[rX][rY+2].visited == false){        
                        maze[rX][rY+1].display = ' ';        
                        maze[rX][rY+1].visited = true;  
                        maze[rX][rY].bW = false;     
                        btrackX.push(rX);                      
                        btrackY.push(rY);                     
                        rY += 2;                                   
                        maze[rX][rY].visited = true;         
                        maze[rX][rY].display = ' ';          
                        maze[rX][rY].tW = false;      
                        visitedCells++;                             
                        }
                    else continue;
                    }
                    percent = (visitedCells*100/totalCells*100)/100;      
                    cout << endl << "Generating Maze... " << percent << "%" << endl;
                }
                else {
                        rX = btrackX.top();
                        btrackX.pop();
 
                        rY = btrackY.top();
                        btrackY.pop();
                }
                ClearScreen();
                draw(maze);
        }
 
        goalX = rX;
        goalY = rY;
        maze[goalY][goalX].display = 'E';
        system("cls");
        ClearScreen();
        draw(maze);
        cout << endl << "Generation complete!" << endl;
}

