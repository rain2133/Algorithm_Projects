/**
 * @file horse_journey.cpp
 * @brief Implementation of Parberry’s algorithm for the knight's tour problem.
 * 
 * This program uses Parberry’s algorithm to find a knight's tour on a chessboard of size m x n.
 * The algorithm divides the board into smaller sub-boards, solves the tour for each sub-board,
 * and then combines the solutions to form a complete tour.
 * 
 * The knight's tour problem is a classic problem in which the goal is to find a sequence of moves
 * for a knight on a chessboard such that the knight visits every square exactly once.
 * 
 * The program supports boards where the difference between the number of rows and columns is at most 2.
 * 
 * @note The board size must be at least 6x6 and the difference between the number of rows and columns must be at most 2.
 * 
 * @param board Predefined basic board structure.
 * @param x1, y1 Coordinates of the top-left corner of the current board region.
 * @param x2, y2 Coordinates of the bottom-right corner of the current board region.
 * @param flag Indicates whether the board needs to be flipped.
 * 
 * @function FillBoard
 * Fills the board with the predefined basic board structure.
 * 
 * @function CombineBoard
 * Combines four sub-boards into one larger board.
 * 
 * @function DivideConquer
 * Main function implementing the divide and conquer approach to solve the knight's tour problem.
 * 
 * @function main
 * Entry point of the program. Reads the board size and starting position, validates the input,
 * and initiates the knight's tour solution.
 * 
 * @example
 * Input:
 * 8 8
 * 1 1
 * 
 * Output:
 * The knight's tour path on an 8x8 board starting from (1, 1).
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 8;
//马移动的八个方向
const int dx[8] = {1, -1, -2, -2, -1, 1, 2, 2};
const int dy[8] = {2, 2, 1, -1, -2, -2, -1, 1};
	
//保存棋盘状态
int Chess[510][510][2];

//基本结构化棋盘，数字代表移动方向在dx,dy中的下标，每格有两个移动方向
const int B6_6[6][6][2] = {																	
	{{0,7},{7,6},{0,5},{5,0},{7,5},{6,5}},
	{{1,0},{6,1},{1,4},{1,7},{6,4},{4,5}},
	{{2,7},{3,0},{4,3},{1,0},{7,2},{6,3}},
	{{7,2},{6,7},{5,0},{4,2},{3,7},{4,6}},
	{{0,1},{3,0},{0,5},{0,5},{4,2},{5,3}},
	{{1,2},{1,3},{3,4},{4,1},{2,4},{3,4}}
},
B6_7[6][7][2] = {
	{{0,7},{0,6},{0,5},{0,5},{0,6},{7,6},{6,5}},
	{{1,0},{1,6},{6,4},{6,4},{1,4},{5,4},{5,4}},
	{{2,7},{3,0},{4,0},{2,1},{2,1},{7,2},{6,3}},
	{{2,7},{6,2},{5,2},{4,6},{4,5},{7,6},{6,5}},
	{{0,1},{3,0},{1,5},{5,0},{1,0},{5,2},{5,3}},
	{{1,2},{3,1},{2,4},{4,1},{2,1},{4,2},{4,3}}
},
B6_8[6][8][2] = {
	{{0,7},{0,6},{5,0},{5,0},{0,6},{6,0},{5,7},{5,6}},
	{{0,1},{6,1},{6,4},{0,4},{4,1},{4,1},{7,4},{4,5}},
	{{2,7},{3,0},{7,4},{2,7},{7,2},{1,4},{2,7},{3,6}},
	{{7,2},{6,2},{5,6},{4,6},{6,5},{6,7},{5,7},{6,3}},
	{{0,1},{3,0},{1,5},{0,3},{3,1},{0,3},{2,5},{3,5}},
	{{1,2},{2,3},{2,4},{4,2},{1,2},{1,4},{3,2},{3,4}}
},
B7_8[7][8][2] = {
	{{0,7},{6,7},{5,0},{0,5},{6,7},{0,7},{5,7},{6,5}},
	{{0,1},{1,7},{0,4},{5,7},{4,1},{1,4},{7,5},{6,4}},
	{{7,2},{3,1},{3,4},{6,2},{1,4},{3,5},{3,2},{3,5}},
	{{7,0},{6,0},{3,6},{1,7},{3,6},{1,0},{5,2},{6,3}},
	{{7,0},{6,3},{4,2},{4,7},{6,1},{7,0},{6,7},{4,6}},
	{{0,2},{2,3},{4,5},{2,5},{3,5},{0,5},{5,2},{4,5}},
	{{1,2},{1,3},{1,4},{1,2},{3,1},{1,2},{2,3},{3,4}}
},
B8_8[8][8][2] = {
	{{0,7},{7,6},{5,7},{0,5},{7,5},{5,0},{7,5},{6,5}},
	{{7,1},{1,6},{1,4},{6,1},{1,6},{1,4},{7,6},{4,5}},
	{{2,7},{3,6},{5,3},{3,7},{7,0},{1,3},{7,2},{6,3}},
	{{2,1},{7,3},{7,2},{2,0},{5,6},{2,0},{4,7},{6,3}},
	{{2,7},{3,6},{5,1},{0,7},{3,6},{4,3},{7,2},{4,3}},
	{{7,1},{7,6},{0,3},{2,3},{0,7},{7,4},{7,2},{3,6}},
	{{2,0},{3,0},{5,0},{2,5},{3,4},{5,0},{5,4},{5,3}},
	{{2,1},{1,3},{4,3},{4,1},{4,1},{3,1},{2,3},{4,3}}
},
B8_9[8][9][2] = {
	{{0,7},{0,6},{5,0},{0,5},{0,6},{0,5},{5,0},{7,5},{6,5}},
	{{0,1},{1,6},{5,4},{1,4},{4,1},{1,4},{1,4},{7,4},{4,5}},
	{{2,1},{3,0},{6,4},{2,0},{7,5},{5,6},{1,6},{6,2},{5,3}},
	{{2,7},{0,7},{1,5},{4,1},{5,6},{4,5},{0,1},{6,7},{6,3}},
	{{1,7},{6,2},{5,1},{1,4},{2,0},{2,3},{6,2},{7,5},{6,4}},
	{{7,1},{3,6},{3,0},{2,6},{6,7},{1,5},{4,2},{7,2},{3,6}},
	{{0,2},{3,0},{5,0},{1,5},{4,0},{0,2},{5,0},{5,2},{5,3}},
	{{2,1},{1,3},{2,4},{4,2},{4,1},{3,1},{4,1},{2,4},{4,3}}
},
B8_10[8][10][2] = {
	{{0,7},{0,6},{5,0},{0,5},{0,5},{6,5},{5,0},{0,5},{7,5},{6,5}},
	{{0,1},{1,6},{1,4},{1,4},{4,1},{1,4},{1,4},{1,0},{4,7},{6,4}},
	{{2,0},{3,6},{6,4},{6,5},{0,2},{0,6},{7,5},{6,7},{7,2},{4,3}},
	{{2,7},{1,7},{4,7},{6,0},{1,7},{7,5},{0,4},{5,4},{7,2},{3,5}},
	{{2,7},{6,2},{5,2},{1,7},{2,0},{4,1},{5,2},{1,3},{3,4},{6,3}},
	{{7,1},{3,6},{3,2},{3,6},{7,1},{3,5},{4,3},{0,7},{5,7},{6,3}},
	{{0,2},{3,0},{5,0},{1,5},{3,0},{5,0},{5,1},{0,5},{5,2},{5,4}},
	{{2,1},{1,3},{2,4},{4,1},{4,1},{1,3},{4,1},{4,1},{3,2},{3,4}}
},
B9_10[9][10][2] = {
	{{0,7},{7,6},{5,0},{0,5},{7,0},{6,0},{5,0},{0,5},{7,6},{5,6}},
	{{7,1},{1,6},{7,4},{6,0},{4,1},{1,4},{4,7},{4,1},{4,7},{5,4}},
	{{2,7},{3,6},{5,3},{0,6},{6,2},{4,3},{0,5},{2,1},{2,5},{6,3}},
	{{2,1},{6,3},{0,2},{0,3},{1,7},{7,4},{1,5},{3,0},{5,4},{3,6}},
	{{2,0},{3,7},{2,0},{5,2},{1,4},{5,4},{5,1},{5,6},{7,2},{4,5}},
	{{7,2},{6,1},{4,0},{0,1},{4,1},{3,1},{5,3},{1,5},{2,7},{6,5}},
	{{7,0},{6,7},{3,7},{0,7},{4,1},{1,4},{2,5},{1,5},{6,7},{6,3}},
	{{0,2},{0,3},{4,5},{0,5},{1,0},{1,4},{5,0},{0,5},{5,2},{3,5}},
	{{1,2},{1,3},{3,4},{3,4},{3,1},{1,4},{4,1},{1,2},{4,2},{3,4}}
},
B10_10[10][10][2] = {
	{{0,7},{0,6},{7,5},{6,0},{0,5},{6,5},{7,5},{5,0},{7,5},{6,5}},
	{{1,0},{6,0},{1,4},{1,4},{1,7},{4,1},{1,4},{1,0},{7,6},{4,6}},
	{{2,0},{3,6},{4,2},{4,3},{0,2},{5,6},{7,6},{6,3},{7,2},{4,3}},
	{{0,2},{7,6},{4,6},{7,1},{7,0},{3,0},{0,4},{2,6},{2,7},{6,3}},
	{{2,7},{0,7},{5,4},{7,0},{2,6},{2,7},{4,2},{4,3},{6,4},{6,3}},
	{{2,1},{2,6},{5,3},{7,4},{5,3},{4,3},{2,6},{6,5},{6,2},{3,5}},
	{{7,1},{3,6},{3,1},{2,5},{7,3},{1,5},{3,5},{1,2},{7,2},{6,5}},
	{{2,7},{1,6},{6,7},{1,5},{1,3},{2,5},{6,2},{1,2},{7,6},{6,5}},
	{{2,0},{1,3},{5,0},{1,0},{5,0},{5,3},{5,0},{1,0},{5,2},{5,3}},
	{{2,1},{3,2},{4,1},{3,1},{4,1},{4,2},{4,1},{2,1},{4,2},{4,3}}
},
B10_11[10][11][2] = {
	{{0,7},{6,0},{0,5},{6,0},{7,5},{5,0},{0,6},{5,6},{0,7},{5,7},{6,5}},
	{{1,7},{6,0},{1,4},{4,1},{6,4},{4,1},{0,5},{4,1},{1,4},{6,5},{6,4}},
	{{0,2},{3,6},{0,2},{4,7},{1,6},{2,3},{2,6},{1,7},{5,4},{3,2},{3,6}},
	{{7,2},{3,6},{5,4},{6,2},{7,4},{5,0},{5,1},{5,6},{6,2},{6,2},{5,6}},
	{{2,1},{7,6},{7,6},{2,1},{3,1},{2,1},{7,6},{4,5},{3,1},{2,7},{6,5}},
	{{2,0},{6,3},{6,2},{0,6},{6,0},{1,3},{2,5},{6,2},{1,2},{2,5},{5,6}},
	{{2,7},{2,6},{4,3},{7,3},{1,0},{2,4},{4,5},{1,3},{7,1},{7,2},{3,6}},
	{{7,2},{6,2},{2,0},{6,2},{1,5},{6,7},{4,2},{6,7},{6,5},{2,7},{5,6}},
	{{2,0},{3,0},{1,5},{0,5},{4,3},{5,0},{1,5},{0,5},{0,1},{2,3},{5,3}},
	{{1,2},{1,3},{4,2},{4,1},{1,2},{1,4},{3,2},{4,2},{3,1},{2,4},{3,4}}
},
B10_12[10][12][2] = {
	{{0,7},{0,6},{6,5},{0,5},{7,6},{0,5},{7,5},{0,5},{0,6},{0,5},{7,6},{6,5}},
	{{1,7},{1,6},{5,4},{1,4},{1,6},{1,4},{6,5},{1,4},{7,6},{1,4},{7,4},{6,4}},
	{{2,1},{3,2},{5,6},{2,6},{1,0},{5,3},{6,7},{2,3},{5,7},{2,0},{7,2},{6,3}},
	{{2,1},{3,6},{7,0},{2,1},{5,0},{5,2},{4,1},{2,5},{5,7},{6,3},{7,2},{4,3}},
	{{0,7},{2,6},{2,1},{7,1},{4,0},{1,2},{4,1},{3,5},{0,6},{3,5},{7,2},{6,3}},
	{{2,0},{0,7},{5,4},{6,3},{0,6},{1,6},{4,5},{1,6},{7,2},{3,6},{5,4},{6,3}},
	{{2,1},{3,6},{4,5},{7,4},{1,3},{0,6},{5,4},{2,0},{5,1},{0,7},{7,2},{6,3}},
	{{1,7},{7,6},{3,2},{2,5},{2,1},{6,7},{2,1},{7,4},{2,5},{4,3},{7,2},{6,4}},
	{{2,0},{1,0},{5,0},{5,0},{2,3},{5,0},{1,0},{5,0},{5,0},{5,0},{3,2},{5,3}},
	{{2,1},{3,1},{4,3},{4,1},{4,2},{4,1},{3,1},{4,1},{4,3},{4,1},{4,2},{4,3}}
},
B11_12[11][12][2] = {
	{{0,7},{6,7},{5,0},{6,5},{7,5},{6,5},{5,0},{7,0},{5,6},{7,0},{5,7},{5,6}},
	{{7,1},{1,6},{1,4},{1,0},{4,1},{6,5},{6,1},{0,6},{4,1},{4,1},{7,5},{4,6}},
	{{7,2},{3,0},{3,2},{1,7},{0,2},{4,3},{6,7},{2,7},{1,3},{5,4},{2,3},{3,6}},
	{{2,7},{6,3},{0,7},{4,0},{7,2},{6,2},{2,4},{6,1},{0,5},{6,7},{2,7},{5,3}},
	{{7,0},{6,3},{7,6},{5,6},{3,4},{4,2},{1,6},{3,5},{3,5},{7,1},{2,4},{5,6}},
	{{7,2},{3,1},{4,0},{3,7},{6,2},{1,3},{1,2},{6,7},{5,2},{0,1},{3,5},{3,6}},
	{{0,2},{2,3},{2,7},{0,3},{4,5},{2,6},{5,1},{0,5},{1,6},{6,5},{2,3},{6,4}},
	{{0,7},{0,3},{1,4},{5,2},{3,1},{1,4},{5,2},{1,7},{3,5},{5,4},{2,7},{6,5}},
	{{7,0},{6,1},{5,4},{3,4},{2,1},{7,6},{1,5},{2,1},{6,2},{1,7},{7,2},{6,5}},
	{{0,1},{3,0},{4,5},{0,5},{1,5},{5,0},{5,0},{0,5},{3,5},{1,0},{5,2},{3,5}},
	{{1,2},{1,3},{1,4},{4,1},{2,1},{1,4},{1,3},{4,2},{4,1},{1,4},{3,2},{4,3}}
};


/**
 * @brief Fills a section of the Chess board with values from the given board array.
 *
 * This function populates a specified rectangular section of the Chess board
 * with values from the provided board array. The section is defined by the
 * coordinates (x1, y1) to (x2, y2). The flag parameter determines how the values
 * are mapped from the board array to the Chess board.
 *
 * @param board Pointer to the array containing the values to fill the Chess board.
 * @param x1 The starting x-coordinate of the section to fill.
 * @param y1 The starting y-coordinate of the section to fill.
 * @param x2 The ending x-coordinate of the section to fill.
 * @param y2 The ending y-coordinate of the section to fill.
 * @param flag If true, the values are mapped in a specific manner (7 - value).
 *             If false, the values are directly copied from the board array.
 */
void FillBoard(int* board, int x1, int y1, int x2, int y2, bool flag){
	int h = x2 - x1 + 1, w = y2 - y1 + 1;
	if (flag)
		for (int i = x1; i <= x2; i++)
			for (int j = y1; j <= y2; j++){
				//反转棋盘
				Chess[i][j][0] = 7 - board[(i - x1 + (j - y1) * h) * 2];			
				Chess[i][j][1] = 7 - board[(i - x1 + (j - y1) * h) * 2 + 1];
			}
	else
		for (int i = x1; i <= x2; i++)
			for (int j = y1; j <= y2; j++){
				Chess[i][j][0] = board[((i - x1) * w + j - y1) * 2];
				Chess[i][j][1] = board[((i - x1) * w + j - y1) * 2 + 1];
			}
}


/**
 * @brief Combines sections of a chessboard based on given coordinates.
 *
 * This function modifies the global Chess array by combining sections of the board
 * defined by the coordinates (x1, y1) and (x2, y2). It performs a series of checks
 * and updates on specific positions within the defined section.
 *
 * @param x1 The starting x-coordinate of the section.
 * @param y1 The starting y-coordinate of the section.
 * @param x2 The ending x-coordinate of the section.
 * @param y2 The ending y-coordinate of the section.
 */
void CombineBoard(int x1, int y1, int x2, int y2){

	int dw = (y2 - y1 + 1) / 4 * 2 + (y2 - y1 + 1) % 2, dh = (x2 - x1 + 1) / 4 * 2 + (x2 - x1 + 1) % 2;
	if (Chess[x1 + dh][y1 + dw - 1][0] == 6) 
		Chess[x1 + dh][y1 + dw - 1][0] = 4;
	else 
		Chess[x1 + dh][y1 + dw - 1][1] = 4;

	if (Chess[x1 + dh + 2][y1 + dw - 2][0] == 2)
		Chess[x1 + dh + 2][y1 + dw - 2][0] = 1;
	else 
		Chess[x1 + dh + 2][y1 + dw - 2][1] = 1;

	if (Chess[x1 + dh + 1][y1 + dw][0] == 1)
		Chess[x1 + dh + 1][y1 + dw][0] = 5;
	else 
		Chess[x1 + dh + 1][y1 + dw][1] = 5;

	if (Chess[x1 + dh][y1 + dw + 2][0] == 5)
		Chess[x1 + dh][y1 + dw + 2][0] = 4;
	else 
		Chess[x1 + dh][y1 + dw + 2][1] = 4;

	if (Chess[x1 + dh - 1][y1 + dw][0] == 2) 
		Chess[x1 + dh - 1][y1 + dw][0] = 0;
	else 
		Chess[x1 + dh - 1][y1 + dw][1] = 0;

	if (Chess[x1 + dh - 3][y1 + dw + 1][0] == 6) 
		Chess[x1 + dh - 3][y1 + dw + 1][0] = 5;
	else 
		Chess[x1 + dh - 3][y1 + dw + 1][1] = 5;

	if (Chess[x1 + dh - 2][y1 + dw - 1][0] == 5) 
		Chess[x1 + dh - 2][y1 + dw - 1][0] = 1;
	else 
		Chess[x1 + dh - 2][y1 + dw - 1][1] = 1;

	if (Chess[x1 + dh - 1][y1 + dw - 3][0] == 1) 
		Chess[x1 + dh - 1][y1 + dw - 3][0] = 0;
	else 
		Chess[x1 + dh - 1][y1 + dw - 3][1] = 0;
}

/**
 * @brief Recursively divides the board into smaller sections and fills them using predefined patterns.
 * 
 * This function uses a divide and conquer approach to fill a board with specific dimensions.
 * It ensures that the board is divided in such a way that at least one dimension is even,
 * preventing unsolvable board configurations.
 * 
 * @param x1 The starting x-coordinate of the board section.
 * @param y1 The starting y-coordinate of the board section.
 * @param x2 The ending x-coordinate of the board section.
 * @param y2 The ending y-coordinate of the board section.
 * 
 * The function first calculates the height (h) and width (w) of the current board section.
 * If the width is less than the height, it swaps them and marks the board as flipped.
 * It then checks if the current board section matches any predefined patterns (6x6, 6x7, etc.)
 * and fills it using the corresponding pattern. If the board section is larger than 11x11,
 * it recursively divides the board into four smaller sections and processes each one.
 * Finally, it combines the smaller sections back into the original board section.
 */
void DivideConquer(int x1, int y1, int x2, int y2) {
	int h = x2 - x1 + 1, w = y2 - y1 + 1, tmpw = w / 4 * 2 + w % 2, tmph = h / 4 * 2 + h % 2;
	//tmpw, tmph 保证了至少有一个是偶数
	bool flag = false;
	if (w < h)
	{
		flag = true;
		int t = w; w = h; h = t;
		//将棋盘翻转并标记
	}
	if (h == 6 && w == 6) 
		FillBoard((int*)B6_6, x1, y1, x2, y2, flag);		
	if (h == 6 && w == 7) 
		FillBoard((int*)B6_7, x1, y1, x2, y2, flag);
	if (h == 6 && w == 8) 
		FillBoard((int*)B6_8, x1, y1, x2, y2, flag);
	if (h == 7 && w == 8) 
		FillBoard((int*)B7_8, x1, y1, x2, y2, flag);
	if (h == 8 && w == 8) 
		FillBoard((int*)B8_8, x1, y1, x2, y2, flag);
	if (h == 8 && w == 9) 
		FillBoard((int*)B8_9, x1, y1, x2, y2, flag);
	if (h == 8 && w == 10) 
		FillBoard((int*)B8_10, x1, y1, x2, y2, flag);
	if (h == 9 && w == 10) 
		FillBoard((int*)B9_10, x1, y1, x2, y2, flag);
	if (h == 10 && w == 10) 
		FillBoard((int*)B10_10, x1, y1, x2, y2, flag);
	if (h == 10 && w == 11) 
		FillBoard((int*)B10_11, x1, y1, x2, y2, flag);
	if (h == 10 && w == 12) 
		FillBoard((int*)B10_12, x1, y1, x2, y2, flag);
	if (h == 11 && w == 12) 
		FillBoard((int*)B11_12, x1, y1, x2, y2, flag);
	if (h > 11 && w > 11)
	{
		//分治
		DivideConquer(x1, y1, x1 + tmph - 1, y1 + tmpw - 1);	
		DivideConquer(x1 + tmph, y1, x2, y1 + tmpw - 1);
		DivideConquer(x1, y1 + tmpw, x1 + tmph - 1, y2);
		DivideConquer(x1 + tmph, y1 + tmpw, x2, y2);
		//合并
		CombineBoard(x1, y1, x2, y2);				
	}
}
int main()
{
	int m, n;
	//输入检验，判断是否出现非法情况
	printf("请输入棋盘大小m, n:\n");
	scanf("%d%d", &m, &n);
	if (m * n % 2 || (m < 6 || n < 6)){
		printf("非法的棋盘大小(m,n必须为偶数)\n");
		exit(0);
	}
	else if (n - m > 2 || m - n > 2){
		printf("未满足|m-n|<=2\n");
		exit(0);
	}
	
	//初始化棋盘
	int display[510][510], step = 1, i, j, x, y;												
	printf("请输入起点坐标x y:\n");
	scanf("%d%d",&x,&y);
	if (x <= 0 || x > m || y <= 0 || y > n)	
		printf("非法的坐标(x ∈ [1,m], x ∈ [1,n])\n");
	else{
		DivideConquer(0, 0, m - 1, n - 1);
		memset(display, 0, sizeof(display));
		i = --x;
		j = --y;
		//模拟马周游的过程
		do{
			display[i][j] = step++;															
			int a = i, b = j;
			i += dx[Chess[a][b][0]];
			j += dy[Chess[a][b][0]];
			if (display[i][j] > 1) {
				i = a + dx[Chess[a][b][1]];
				j = b + dy[Chess[a][b][1]];
			}
		} while (i != x || j != y);
		printf("马的周游(骑士巡游)路线如下\n");
		for (int p = 0; p < m; p++){
			for (int q = 0; q < n; q++)
				printf("%d\t", display[p][q]);
			printf("\n");
		}
	}	
	return 0;
}

