#include "tetris_process.h"
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;



bool tetris_process::collision()
{
	int test_x;
	int test_y;
	bool collided = false;
	for (int y = 0; y < blocks_width[block.type]; y++)
	{
		for (int x = 0; x < blocks_width[block.type]; x++)
		{
			test_x = block.history_x - blocks_width[block.type] / 2;
			test_y = block.history_y;
			if (blocks[block.type][block.history_rotation][blocks_width[block.type] * y + x] == 1)
			{
				board[test_y + y][test_x + x] = 0;
			}
		}
	}
	for (int y = 0; y < blocks_width[block.type]; y++)
	{
		for (int x = 0; x < blocks_width[block.type]; x++)
		{
			test_x = block.x - blocks_width[block.type] / 2;
			test_y = block.y;
			if ((test_y + y > 19 || test_x + x > 9 || test_x + x <0 || board[test_y + y][test_x + x] == 1)  && blocks[block.type][block.rotation][blocks_width[block.type] * y+x]==1)//碰到左、下、右的牆壁或方塊時被碰撞為真
			{
				collided = true;
				break;
			}
		}
		if (collided)//返回過狀態
		{
			
			block.x =block.history_x;
			block.y = block.history_y;
			block.rotation = block.history_rotation;
			break;
		}
	}
	for (int y = 0; y < blocks_width[block.type]; y++)
	{
		for (int x = 0; x < blocks_width[block.type]; x++)
		{
			test_x = block.x - blocks_width[block.type] / 2;
			test_y = block.y;
			if (blocks[block.type][block.rotation][blocks_width[block.type]*y + x] == 1)
			{
				board[test_y + y][test_x + x] = 1;
			}
		}
	}

	if (collided) { return true; }
	else { return false; }
}
void tetris_process::move()
{
	if (_kbhit()) //如果有按键按下，则_kbhit()函数返回真
	{
		int ch = _getch();//使用_getch()函数获取按下的键值
		if (ch==32||ch==75||ch==77||ch==80)
		{
			block.history_rotation = block.rotation;
			block.history_x = block.x;
			block.history_y = block.y;
			
			if (ch == 32)//space
			{
				block.rotation += 1;
				if (block.rotation >= 4)
				{
					block.rotation = 0;
				}
				if(!tetris_process::collision())block.hit_bottom = 0;
			}
			else if (ch == 75)//left arrow
			{
				block.x -= 1;
				block.hit_bottom = 0;
				if (!tetris_process::collision())block.hit_bottom = 0;
			}
			else if (ch == 77)//right arrow
			{
				block.x += 1;
				block.hit_bottom = 0;
				if (!tetris_process::collision())block.hit_bottom = 0;
			}
			else if (ch == 80)//down arrow
			{
				block.y += 1;
				if (!tetris_process::collision())block.hit_bottom = 0;
			}
		}		
	}
}
void tetris_process::generate_block()
{
	if(block.next_type==-1)block.next_type = rand() % 7;
	srand((unsigned)time(NULL));
	block.type = block.next_type;
	block.next_type=rand()%7;
	block.rotation = 0;
	block.x = 5;
	block.y = 0;
	block.history_rotation = 0;
	block.history_x = 5;
	block.history_y = 0;
	block.hit_bottom = 0;
	for (int y = 0; y < blocks_width[block.type]; y++)
	{
		for (int x = 0; x < blocks_width[block.type]; x++)
		{
			int test_x = block.x - blocks_width[block.type] / 2;
			int test_y = block.y;
			if (blocks[block.type][block.rotation][blocks_width[block.type] * y + x] == 1)
			{
				board[test_y + y][test_x + x] = 1;
			}
		}
	}
}
std::vector<std::vector<int>> tetris_process::get_board()
{
	return board;
}
void tetris_process::fall()
{
	cout << "score : " << score << endl;
	cout << "next block : " << endl;
	for (int y = 0; y < blocks_width[block.next_type]; y++)
	{
		for (int x = 0; x < blocks_width[block.next_type]; x++)
		{
			if (blocks[block.next_type][0][blocks_width[block.next_type] * y + x] == 1)cout << "⬜";
			else cout << "  ";
		}
		cout <<"    "<< endl;
	}
	block.history_rotation = block.rotation;
	block.history_x = block.x;
	block.history_y = block.y;
	block.y += 1;
	if (tetris_process::collision())
	{
		block.hit_bottom += 1;
		if (block.x == 5 && block.y == 0)end = true;
	}
	if (block.hit_bottom >= 2)
	{
		score += 10;
		tetris_process::eliminate();
		tetris_process::generate_block();
	}
}
void tetris_process::eliminate()
{
	vector<int> full_row;
	for (int y = 19; y >= 0; y--)
	{
		bool full = true;
		for (int x = 0; x < 10; x++)
		{
			if (board[y][x] == 0)
			{
				full = false;
				break;
			}
		}
		if (full)
		{
			full_row.push_back(y);
		}
	}
	for (int i = 0; i < full_row.size(); i++)
	{
		for (int y = full_row[i]; y >= 0; y--)
		{
			for (int x = 0; x < 10; x++)
			{
				if (y<full_row[i])
				{
					board[y + 1][x] = board[y][x];
				}
				board[y][x] = 0;
			}
		}
		for (int i = 0; i < full_row.size(); i++)
		{
			full_row[i]++;
		}

	}
	if (full_row.size() == 1)score += 100;
	else if (full_row.size() == 2)score += 200;
	else if (full_row.size() == 3)score += 400;
	else if (full_row.size() == 4)score += 800;
}
