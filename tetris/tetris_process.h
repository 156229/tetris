#pragma once
#include <vector>
struct property
{
	int type;
	int next_type=-1;
	int rotation=0;
	int x = 5;
	int y = 0;
	int history_rotation=0;
	int history_x = 5;
	int history_y = 0;
	int hit_bottom = 0;
};
class tetris_process
{
public:
	tetris_process():score(0) {
		blocks = {
			{
				{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
				{0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0},
				{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},
				{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}
			},
			{
				{1,0,0,1,1,1,0,0,0},
				{0,1,1,0,1,0,0,1,0},
				{0,0,0,1,1,1,0,0,1},
				{0,1,0,0,1,0,1,1,0}
			},
			{
				{0,0,1,1,1,1,0,0,0},
				{0,1,0,0,1,0,0,1,1},
				{0,0,0,1,1,1,1,0,0},
				{1,1,0,0,1,0,0,1,0}
			},
			{
				{0,1,0,1,1,1,0,0,0},
				{0,1,0,0,1,1,0,1,0},
				{0,0,0,1,1,1,0,1,0},
				{0,1,0,1,1,0,0,1,0}
			},
			{
				{1,1,1,1},
				{1,1,1,1},
				{1,1,1,1},
				{1,1,1,1}
			},
			{
				{0,1,1,1,1,0,0,0,0},
				{0,1,0,0,1,1,0,0,1},
				{0,0,0,0,1,1,1,1,0},
				{1,0,0,1,1,0,0,1,0}
			},
			{
				{1,1,0,0,1,1,0,0,0},
				{0,1,0,1,1,0,1,0,0},
				{0,0,0,1,1,0,0,1,1},
				{0,0,1,0,1,1,0,1,0}
			}
		};
		blocks_width = { 4,3,3,3,2,3,3 };
		board.resize(20, std::vector<int>(10));
		tetris_process::generate_block();
	}
	void fall();
	void move();
	bool end = false;
	std::vector<std::vector<int>> get_board();
private:
	property block;
	void eliminate();
	void generate_block();
	int score;
	std::vector<std::vector<int>> board;
	bool collision();
	std::vector<std::vector<std::vector<int>>> blocks;
	std::vector<int> blocks_width;
};

