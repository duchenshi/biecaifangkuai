#include<Windows.h>
#include<time.h>

#define WhiteBlock 0
#define BlackBlock 2
#define PassBlock 1

class CDontTouchWhiteBlock
{
private:
	int nOffset;
	int width;
	int height;
	SIZE block;
	bool bOver;

public:
	int map[5][4];
	CDontTouchWhiteBlock(int w, int h);
	void InitNewGame(int w, int h);
	bool Move(int nDistance);
	bool InitNewBlock();
	bool PointAt(int x, int y);
	bool IsOver(){ return bOver; }
	int GetOffet(){ return nOffset; }
};
