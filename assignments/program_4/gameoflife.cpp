/**
* @ProgramName: Program-4
* @Author: Sierra Richards
* @Description:
*     This program implements Game of Life which uses a 2d array of values to represent life cells.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 28 04 2017
*/



#include <iostream>
#include <string>
#include <fstream>

// #ifdef __cplusplus__
// #include <cstdlib>
// #else
// #include <stdlib.h>
// #endif

//#include <unistd.h>
//unistd.h doesn't work on windows machines 
#include <Windows.h>
//Windows.h works

using namespace std;

class GameOfLife{
private:
    int **Board;
    int **Board2;
    int Rows;
    int Cols;
public:
    GameOfLife(string filename){
        string line;
        char ch;
        ifstream fin;
        fin.open(filename);
        fin >> Rows >> Cols;
        InitBoardArray(Board);
        InitBoardArray(Board2);
        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Cols; j++){
                fin.get(ch);
                if (ch == 10){
                    continue;
                }
                Board[i][j] = int(ch) - 48;
            }
        }
    }
    
    GameOfLife(int r, int c){
        Rows = r;
        Cols = c;
        InitBoardArray(Board);
        InitBoardArray(Board2);
        PrintBoard();
    }
    
    void InitBoardArray(int **&b){
        b = new int*[Rows];
        for (int i = 0; i < Rows; i++){
            b[i] = new int[Cols];
        }
        ResetBoardArray(b);
    }
    
    void ResetBoardArray(int **&b){
        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Cols; j++){
                b[i][j] = 0;
            }
        }
    }
    
    void PrintBoard(){
        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Cols; j++){
                if (Board[i][j] == 1)
                    cout << char('X');
                else
                    cout << " ";
            }
            cout << endl;
        }
    }
    
    int CountNeighbors(int row, int col){
        int neighbors = 0;
        if (Board[row][col] == 1){
            neighbors--;
        }
        for (int i = row - 1; i <= row + 1; i++){
            for (int j = col - 1; j <= col + 1; j++){
                if (OnBoard(i, j)){
                    neighbors += Board[i][j];
                }
            }
        }
        return neighbors;
    }
    
    bool OnBoard(int row, int col){
        return (row >= 0 && row < Rows && col >= 0 && col < Cols);
    }
    
    void RandomPopulate(int num){
        int r = 0;
        int c = 0;
        for (int i = 0; i<num; i++){
            r = rand() % Rows;
            c = rand() % Cols;
            Board[r][c] = 1;
        }
    }
    
    void SetCell(int r, int c, int val){
        Board[r][c] = val;
    }
    
    void AddGens(){
        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Cols; j++){
                Board[i][j] += Board2[i][j];
            }
        }
        ResetBoardArray(Board2);
    }
    
    void clear_screen(int lines){
      for(int i=0;i<lines;i++){
        cout<<endl;
      }
    }

	void Run(int generations = 99999) {
		int neighbors = 0;
		bool stable1 = false, stable2 = false;

		int g = 0;
		while (g < generations) {
			for (int i = 0; i < Rows; i++) {
				for (int j = 0; j < Cols; j++) {
					neighbors = CountNeighbors(i, j);
					if (Board[i][j] == 1 && (neighbors < 2 || neighbors > 3)) {
						Board2[i][j] = -1;
					}
					if (Board[i][j] == 0 && neighbors == 3) {
						Board2[i][j] = 1;
					}
				}
			}

			//Set previous generation's stability to current generation's stability
			stable2 = stable1;

			//if current generation is stable, then set true
			stable1 = NoChanges();

			//if the last two generations were stable then quit.
			if (Stable(stable1, stable2))
				return;

			AddGens();
			//usleep(100000);
			Sleep(250);
			clear_screen(30);
			PrintBoard();
			g++;
		}

	}

	//Determines if changes were in the current generation
	bool NoChanges()
	{
		for (int i = 0; i < Rows; i++) {
			for (int j = 0; j < Cols; j++) {
				if (Board[i][j] != Board2[i][j])
					return false;
			}
		}
		return true;
	}

	//Determines if the system has stablized
	bool Stable(bool stable1, bool stable2) {
		if (stable1 && stable2)
			return true;
		else
			return false;
	}

	//Counts neighbors around a never ending grid
	int CountGlobalNeighbors(int row, int col) {
		int neighbors = 0;
		if (Board[row][col] == 1) {
			neighbors--;
		}
		for (int i = row - 1; i <= row + 1; i++) {
			for (int j = col - 1; j <= col + 1; j++) {

				//Calculate neighbor's value
				//Mod Rows/Cols so it will wrap around
				int r = (Rows + i) % Rows;
				int c = (Cols + j) % Cols;
				neighbors += Board[r][c];
			}
		}
		return neighbors;
	}

};

int main(){
    //GameOfLife G(26, 40);

    GameOfLife G("data2.txt");
	GameOfLife G("glidergun.txt");
    // G.RandomPopulate(60);
    // G.SetCell(0, 5, 1);
    // G.SetCell(0, 6, 1);
    // G.SetCell(0, 7, 1);
    // G.SetCell(1, 5, 1);
    // G.SetCell(1, 6, 1);
    // G.SetCell(1, 7, 1);
    // G.SetCell(2, 5, 1);
    // G.SetCell(2, 6, 1);
    // G.SetCell(2, 7, 1);
    G.Run(100);
    return 0;
}

