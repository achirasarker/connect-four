/*
Achira Sarker 

*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

//Assume no tie

int main() 
{
	ifstream fin("game_moves.txt");
	if (!fin) 
	{
		cout << "File not found!";
		return 1;
	}
	const int ROWS = 6;
	const int COL = 7;
	
	int board[ROWS][COL] = {0}; 
	bool isPlayerXTurn = true;
	int move = 0;

	while (fin >> move)
	{	
		int filledRow = 0;
		int currCol = move-1; //since column indexes are 0...6 
								//not move--!!!! ITS MOVE -1 (move-- doesnt apply the decrement to varaible since prescdence)
	
		//loop through rows of that column to find at which row index it was last filled 
		for (int rowNum = 0; rowNum < ROWS; rowNum++)
		{	
			//if there's already a 1 or 2 there
			//if we already found a filled row, then dont make it go back into the loop and check for another filled row below the already found one
			//so set condition as filledrow == 0 so it just finds the TOP filled row
			//then filled row index is that row
			if(board[rowNum][currCol] != 0 && filledRow == 0)
				filledRow = rowNum;	
		}
		
		//if column hasn't been filled yet, then insert 1 or 2 at the bottom
		if (filledRow == 0)
		{
			if(isPlayerXTurn)
				board[5][currCol] = 1;
			else 
				board[5][currCol] = 2;
		}
		//if column has been filled, then insert 1 or 2 above that row number
		else 
		{
			if(isPlayerXTurn)
				board[filledRow-1][currCol] = 1;
			else 
				board[filledRow-1][currCol] = 2;
		}
		
		if(isPlayerXTurn)
			isPlayerXTurn = false;
		else 
			isPlayerXTurn = true;
	}
	
	//print out game board
	for (int row = 0; row < ROWS; row++)
	{
		for (int cols = 0; cols < COL; cols++)
			cout << board[row][cols] << " ";
		cout << endl;
	}

	bool playerXWins = false, playerOWins = false;
	//loop through every column to check for horizontal win
	//to check for horizontal win, its similar to printing out a 2D array
	//by looping through rows in outer loop, and columns in inner loop
	int numXHorz = 0, numOHorz = 0;
	for (int rowNum = 0; rowNum < ROWS; rowNum++)
	{	
		for (int colNum = 0; colNum < COL; colNum++)
		{	
			//first check if this number and number beside is the same and make sure ur not in first column
			//if this number and number beside it not the same, then NO FOUR IN A ROW cuz its two diff moves, so then reset xHorx and OHorz to 0 
			if (board[rowNum][colNum] != board[rowNum][colNum-1] && colNum!= 0)
			{
				numXHorz = 0;
				numOHorz = 0;
			}
			if (board[rowNum][colNum] == 1)
				numXHorz++;
			if (board[rowNum][colNum] == 2)
				numOHorz++;
				
			if (numXHorz >= 4)
				playerXWins = true; 
			else if (numOHorz >= 4)
				playerOWins = true; 
		}
		//after ur done reading one row, must RESET xHorz and OHorz to find horz four in a row
		numXHorz = 0;
		numOHorz = 0;
	}
	
	int numXVert = 0, numOVert = 0;
	//if no one won horizontally, check vertically by looping through every row
	//to check for veritical win, its similar to printing out a 2D array, but 
	//loop through columns in outer loop, and rows in inner loop like ||||
	if (!playerXWins && !playerOWins)
	{
		for (int colNum = 0; colNum < COL; colNum++)
		{	
			for (int rowNum = 0; rowNum < ROWS; rowNum++)
			{	
				//if this number and number above it not same, then reset numXvert and numOvert
				if (board[rowNum][colNum] != board[rowNum-1][colNum] && rowNum!= 0) 
				{
					numXVert = 0;
					numOVert = 0;
				}
				if (board[rowNum][colNum] == 1)
					numXVert++;
				if (board[rowNum][colNum] == 2)
					numOVert++;
					
				if (numXVert >= 4)
					playerXWins = true; 
				else if (numOVert >= 4)
					playerOWins = true; 
			}
			//before moving on to next column, reset the numXvert and nbumXhorz
			numXVert = 0;
			numOVert = 0;
		}
	}
	
	if (playerXWins)
		cout << "Player X has won.";
	else if (playerOWins)
		cout << "Player O has won.";
	else if (!playerXWins && !playerOWins)
		cout << "Neither player has won yet.";
	cout << endl;
	

	fin.close();
	system("PAUSE");
	return 0;
}
