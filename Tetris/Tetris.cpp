#include "Tetris.h"
#include <time.h>
#include <conio.h>
#include <stdio.h>

//���������������ֳ������ݽṹ������,����id�Ϳ��Բ���shape����id�з���ÿһ���ֵ������Լ�����height�����id��Ԫ�ؾͿ���֪������߶�
//�����ÿһ�ж�Ӧһ����״������ÿһ�����һ��Ԫ��Ϊ��ɫ
int shape[19][9] = { { 0,0,1,0,2,0,1,1,FOREGROUND_RED | FOREGROUND_INTENSITY },
                     { 0,1,1,0,1,1,1,2,FOREGROUND_RED | FOREGROUND_INTENSITY },
                     { 0,1,1,0,1,1,2,1,FOREGROUND_RED | FOREGROUND_INTENSITY },
                     { 0,0,0,1,0,2,1,1,FOREGROUND_RED | FOREGROUND_INTENSITY }, //T����4����״
					 { 0,1,1,0,1,1,2,0,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY },
                     { 0,0,0,1,1,1,1,2,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY }, //��Z��״
					 { 0,0,1,0,1,1,2,1,FOREGROUND_GREEN | FOREGROUND_RED },
                     { 0,1,0,2,1,0,1,1,FOREGROUND_GREEN | FOREGROUND_RED }, //Z��״
					 { 0,2,1,0,1,1,1,2,FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY },
					 { 0,0,0,1,1,1,2,1,FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY },
					 { 0,0,0,1,0,2,1,0,FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY },
					 { 0,0,1,0,2,0,2,1,FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY }, //��L��״
					 { 0,0,0,1,0,2,1,2,FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY },
					 { 0,0,0,1,1,0,2,0,FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY },
					 { 0,0,1,0,1,1,1,2,FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY },
					 { 0,1,1,1,2,1,2,0,FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY }, //L��״
					 { 0,0,0,1,0,2,0,3,FOREGROUND_GREEN | FOREGROUND_INTENSITY },
					 { 0,0,1,0,2,0,3,0,FOREGROUND_GREEN | FOREGROUND_INTENSITY }, //I��״
					 { 0,0,0,1,1,0,1,1,FOREGROUND_BLUE | FOREGROUND_INTENSITY } //������״
};

int height[19] = { 2,3,2,2,2,3,2,3,3,2,3,2,3,2,3,2,4,1,2 };//��¼��ͬ��״�ĸ߶�


Tetris::Tetris()
{
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 25; j++)
			map[i][j] = 0;
	pos[0] = 12;
	pos[1] = 1;
	level = 1;
	score = 0;
	top = 28;//����ߵ��ʼΪ��Ϸ����ĵײ�
}

Tetris::~Tetris()
{

}

void Tetris::setcurpos(int x, int y, int color = 1|2|4)//14��������ϳɰ�ɫ
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {(short)x,(short)y};
	SetConsoleTextAttribute(handle, color);//������ɫ
	SetConsoleCursorPosition(handle,coord);//���ù��λ��
}

void Tetris::drawmap()
{
	setcurpos(0, 0);
	for (int i = 0; i < 25; i++)
		cout << "��";
	setcurpos(0, 29);
	for (int i = 0; i < 25; i++)
		cout << "��";
	for (int i = 1; i < 29; i++) 
	{
		setcurpos(0, i);
		cout << "��";
		setcurpos(48, i);
		cout << "��";
	}
	//�����Ҳ���Ϣ��
	setcurpos(54, 0);
	cout << "��һ�ν�Ҫ��ʾ��ͼ�Σ�";
	setcurpos(54, 6);
	cout << "�÷֣�" << score;
	setcurpos(54, 7);
	cout << "�ȼ���" << level;
	setcurpos(54, 9);
	cout << "������Ϣ��a�������ƶ���d�������ƶ�";
	setcurpos(64, 10 );
	cout << "w����ת��s�����٣�ÿ����һ�е�10�֣�";
}

void Tetris::drawbox(int x,int y,int id)
{
	int cx = 0, cy = 0;

	for (int i = 0; i < 4; i++)
	{
		cx = x + shape[id][2 * i];
		cy = y + shape[id][2 * i + 1];
		setcurpos(2*cx, cy, shape[id][8]);
		cout << "��";
	}
}

void Tetris::erasebox(int x, int y, int id)
{
	int cx = 0, cy = 0;

	for (int i = 0; i < 4; i++)
	{
		cx = x + shape[id][2 * i];
		cy = y + shape[id][2 * i + 1];
		setcurpos(2*cx, cy);
		cout << "  ";
	}
}

int Tetris::judge(int x,int y,int id)
{
	int cx = 0, cy = 0;

	for (int i = 0; i < 4; i++)
	{
		cx = x + shape[id][2 * i];
		cy = y + shape[id][2 * i + 1];
		if (cx < 1 || cx > 23 || cy < 1 || cy > 28 || map[cy][cx] != 0)
			return -1;
	}

	return 0;
}

int Tetris::change(int id)
{
	switch (id)
	{
	case T1: id = T2; break;
	case T2: id = T3; break;
	case T3: id = T4; break;
	case T4: id = T1; break;
	case Z11: id = Z12; break;
	case Z12: id = Z11; break;
	case Z21: id = Z22; break;
	case Z22: id = Z21; break;
	case L11: id = L12; break;
	case L12: id = L13; break;
	case L13: id = L14; break;
	case L14: id = L11; break;
	case L21: id = L22; break;
	case L22: id = L23; break;
	case L23: id = L24; break;
	case L24: id = L21; break;
	case I1:  id = I2; break;
	case I2:  id = I1; break;
	case O: break;
	default:
		cout << "���ʹ���";
		break;
	}

	return id;
}

//ÿһ�η��鵽ָ��λ�þ͸���һ��
void Tetris::updatemap(int id)
{
	int clearlines = 0;//��յ�����
	
	//�����鵽��λ�ú�ʹ��map������м�¼��Щλ���з���
	for (int i = 0; i < 4; i++)
	{
		int cx = pos[0] + shape[id][2 * i];
		int cy = pos[1] + shape[id][2 * i + 1];
		//mapֻ��������ɵ�һ�ű�������ʶ��Ӧ����Ϸ�����е�ĳ�������Ƿ��з��飬����cx,cy��map���л�������ν
		map[cy][cx] = shape[id][8];
	}

	//������ߵ�
	if (pos[1] < top)
		top = pos[1];

	//��ÿ����״����ĸ߶ȷ�Χ�ڰ�������
	for (int i = pos[1]; i < pos[1] + height[id]; i++)
	{
		int flag = 0;
		for (int j = 1; j < 24; j++)
		{
			if (map[i][j] == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			for (int k = i; k > top; k--)
			{
				//k=1˵�����иպ�ȫ�Ƿ��飬��Ҫ����
				if (k == 1) 
				{
					for (int n = 1; n < 24; n++) 
					{
						map[k][n] = 0;
						setcurpos(2*n, k);
						cout << "  ";
					}
				}
				else 
				{
					for (int n = 1; n < 24; n++)
					{
						map[k][n] = map[k - 1][n];

						if (map[k][n] == 0)
						{
							setcurpos(2*n, k);
							cout << "  ";
						}
						else
						{
							setcurpos(2*n, k, map[k][n]);
							cout << "��";
						}
						//��յ�top��
						if (k == top + 1)
						{
							setcurpos(2*n,k-1);
							cout << "  ";
							map[k - 1][n] = 0;
						}
					}
				}
			}
			top++;
			clearlines++;
			score += 10 * clearlines;
		}
	}
	setcurpos(54, 6);
	cout << "�÷֣�" << score;
}


void Tetris::run()
{
	char ch = '\0';
	int num = 0;//��ʱ����,ÿ�η����½�֮ǰҪ�ȴ�num����ʱ��ȴ���������
	int autonum;//����������Զ��½�
	int flag;

	//�����������
	srand((unsigned)time(NULL));
	int curid = rand() % 19;
	int nextid = rand() % 19;

	//��ʼ��
	drawmap();
	drawbox(pos[0],pos[1],curid);
	drawbox(30,1,nextid);

	while (1)
	{
		level = score / 50 + 1;
		autonum = 10000 - 1000 * level;
		

		//�Զ��½�
		if (num > autonum)
		{
			num = 0;
			//Sleep(100);
			if (judge(pos[0],pos[1]+1,curid) == 0)//���Լ�������
			{
				erasebox(pos[0], pos[1], curid);
				pos[1]++;
				drawbox(pos[0], pos[1], curid);
			}
			else 
			{
				updatemap(curid);

				curid = nextid;
				nextid = rand() % 19;
				pos[0] = 12;
				pos[1] = 1;
				drawbox(pos[0], pos[1], curid);
				erasebox(30, 1, curid);
				drawbox(30, 1, nextid);
				//������Ϸ�ȼ�
				setcurpos(54, 7);
				cout << "�ȼ���" << level;
				//�ж��Ƿ����
				if (judge(pos[0],pos[1],curid) == -1)
				{
					setcurpos(54, 12);
					cout << "��Ϸ������";
					system("pause");
					exit(0);
				}
			}
		}
		//�ȴ��������룬��ʱ����ֹͣ
		if (_kbhit()) 
		{
			ch = _getch();//_getch�����Զ���ʾ����Ļ��

			if (ch == 'a')
			{
				if (judge(pos[0] - 1, pos[1], curid) == 0)
				{
					erasebox(pos[0], pos[1], curid);
					pos[0] --;
					drawbox(pos[0], pos[1], curid);
				}
			}
			else
				if (ch == 'd')
				{
					if (judge(pos[0] + 1, pos[1], curid) == 0)
					{
						erasebox(pos[0], pos[1], curid);
						pos[0] ++;
						drawbox(pos[0], pos[1], curid);
					}
				}
				else
					if (ch == 's')
					{
						if (judge(pos[0], pos[1] + 1, curid) == 0)
						{
							erasebox(pos[0], pos[1], curid);
							pos[1] ++;
							drawbox(pos[0], pos[1], curid);
						}
					}
					else
						if (ch == 'w')
						{
							int temp = curid;
							curid = change(curid);

							if (judge(pos[0], pos[1], curid) == 0)
							{
								erasebox(pos[0], pos[1], temp);
								drawbox(pos[0], pos[1], curid);
							}
							else
								curid = temp;
						}
						else
							if (ch = '\0')
								_getch();

			while (_kbhit())//��ȡʣ��ļ�����Ϣ
				_getch();
		}
		num++;
	}	
}
