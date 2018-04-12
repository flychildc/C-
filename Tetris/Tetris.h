#pragma once

#include <iostream>
using namespace std;

#include <Windows.h>

const int T1 = 0;
const int T2 = 1;
const int T3 = 2;
const int T4 = 3;
const int Z11 = 4;
const int Z12 = 5;
const int Z21 = 6;
const int Z22 = 7;
const int L11 = 8;
const int L12 = 9;
const int L13 = 10;
const int L14 = 11;
const int L21 = 12;
const int L22 = 13;
const int L23 = 14;
const int L24 = 15;
const int I1 = 16;
const int I2 = 17;
const int O = 18;

class Tetris 
{
public:
	Tetris();
	~Tetris();

	void drawmap();
	void setcurpos(int x, int y, int color);
	void drawbox(int x,int y,int id);//����x,y��������λ������ʾͼ�Σ�����Ϸ��������һ��Ҫ��ʾ��ͼ��
	void erasebox(int x,int y,int id);
	int judge(int x,int y,int id);
	int change(int id);
	void updatemap(int id);
	void run();

private:
	int map[30][25];//map������Ҫ��Ϊһ�ű�����¼��Ϸ������Щ�����з���,�����map����Ϸ�ı߿�Ҳ������ȥ��
	int pos[2];//ȷ����������Ϸ���������
	int level;
	int score;
	int top;//��¼����ѻ�����ߵ�,������ʱ����Ҫ
};
