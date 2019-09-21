#include"CDontTouchWhiteBlock.h"

CDontTouchWhiteBlock::CDontTouchWhiteBlock(int w, int h)
{
	this->InitNewGame(w, h);
}
void CDontTouchWhiteBlock::InitNewGame(int w, int h)
{
	srand((unsigned int)time(0));
	width = w;
	height = h;
	block.cx = width / 4;
	block.cy = height / 4;
	bOver = false;
	nOffset = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = WhiteBlock;
		}
		map[i][rand() % 4] = BlackBlock;
	}
}
bool CDontTouchWhiteBlock::Move(int nDistance)
{
	if (nDistance>block.cy)
		return true;
	nOffset += nDistance;
	if (nOffset < block.cy)
		return true;
	return InitNewBlock();
}

bool CDontTouchWhiteBlock::InitNewBlock()
{
	for (int i = 0; i < 4; i++)
	{
		if (map[4][i] == BlackBlock)
		{
			bOver = true;
			return false;
		}
	}
	for (int r = 3; r>-1; r--)
	{
		for (int c = 0; c < 4; c++)
		{
			map[r + 1][c] = map[r][c];
			map[r][c] = WhiteBlock;
		}
	}
	map[0][rand() % 4] = BlackBlock;
	nOffset -= block.cy;//此时noffset大于block.cy;
	return !bOver;
}

bool CDontTouchWhiteBlock::PointAt(int x, int y)
{
	y = y + block.cy - nOffset;
	int r = y / block.cy;
	int c = x / block.cx;
	if (map[r][c] == PassBlock)
		return true;
	if (map[r][c] == BlackBlock)
	{
		map[r][c] = PassBlock;
		return true;
	}
	if (map[r][c] == WhiteBlock)
	{
		map[r][c] = -1;
		bOver=true;
	}
	return false;
}