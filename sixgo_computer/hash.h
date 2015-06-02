#ifndef SIXGO_H_HASH
#define SIXGO_H_HASH

#define MAXSIZE 0x100000

#include "connect_six.h"
#include <time.h>

typedef struct _BoardCode
{
	unsigned long a[23];//双方棋子位图，361*2=722,23*32=736
	unsigned long hash32;//哈希编码
}BoardCode;

typedef struct _HashInfo
{
	BoardCode code;//棋盘状态编码
	vector<Step> stepList;//着法列表
	int value,myType,denType;//保存威胁类型的主要目的是为了指导招法生成
	int index;//哈希表项储存时间戳，保存行棋数（HandNum）
	int depth;//搜索深度
	bool cut;//cut：剪枝标记，用于发起着法排序以提高剪枝效率
	bool full;//full：着法列表完整性标记，常规搜索生成完整着法列表，扩展搜索生成特殊着法
}HashInfo;

typedef struct _EndLibInfo
{
	BoardCode code;
	int side;
	_EndLibInfo *next;
}EndLibInfo;

extern HashInfo hashList[MAXSIZE];

void initialCode(BoardCode &code);
void initialHash();
bool compareCode(BoardCode &a,BoardCode &b);
unsigned long hashCode(BoardCode &code);
HashInfo *findHash(BoardCode &code,int index);
void moveCodeP(BoardCode &code,Point point,int side);
void moveCodeS(BoardCode &code,Step step,int side);
void ReadCM(int color);

EndLibInfo *findEndLib(BoardCode &code);
bool StartEndLib();
void StopEndLib();
void InsertEndLib(BoardCode &code, int side);


#endif