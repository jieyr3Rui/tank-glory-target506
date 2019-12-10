#include "main.h"



int main(){
	initgraph(1525,800);
	set_scene();
	create_base();
	create_boundary();
	create_road(400,400,800,2200);//left
	create_road(400,400,2800,800);//top
	create_road(2400,1000,2800,2800);//right
	create_road(1000,2400,2800,2800);//bottom
	create_midroad();

	while(1){
		start:
		SetWorkingImage(&buffer);// ���ڻ�������ͼ
		cleardevice(); //clear

		settextstyle(150, 0, _T("���Ĳ���"));
		outtextxy(370,100,"̹  ��  ��  ҫ");
		setfillcolor(WHITE);
		solidrectangle(875,390,640,440);	
		solidrectangle(875,510,640,560);
		settextstyle(32, 0, _T("����"));
		outtextxy(1100,700,"������: ��Ӣ�  �� ��");
		outtextxy(1228,740,"�Ƽν�  ������");

		MOUSEMSG m;
			m = GetMouseMsg();
		if ((m.x<=875)&&(m.x>=620)&&(m.y<=440)&&(m.y>=370)){
			setfillcolor(YELLOW);
			solidrectangle(880,390,640,445);
			if (m.uMsg == WM_LBUTTONDOWN)
				goto play;
		}
		
		if ((m.x<=875)&&(m.x>=620)&&(m.y<=560)&&(m.y>=490)){
			setfillcolor(YELLOW);
			solidrectangle(880,510,640,565);
			if (m.uMsg == WM_LBUTTONDOWN)
				goto help;
		}
		settextstyle(64, 0, _T("����"));
		outtextxy(613,370,"��ʼ��Ϸ");
		outtextxy(613,490,"����˵��");

		SetWorkingImage();
		putimage(0,0,&buffer);   // �ѻ�������ͼ����һ���Ի�����ȥ��������������˸
		sleep(15);
	}

	while(1){
		help:
		SetWorkingImage(&buffer);// ���ڻ�������ͼ
		cleardevice(); //clear
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
		settextstyle(48, 0, _T("����"));
		outtextxy(100,80,"����˵��");
		outtextxy(600,80,"��ͼ˵��");
		outtextxy(1100,80,"����˵��");
		settextstyle(42, 0, _T("����"));
		outtextxy(100,180,"W��������");
		outtextxy(100,300,"A��������");
		outtextxy(100,240,"S��������");
		outtextxy(100,360,"D��������");
		outtextxy(100,420,"O����˳ʱ����ת");
		outtextxy(100,480,"I������ʱ����ת");
		outtextxy(100,540,"U���������ڵ�");
		setfillcolor(RGB(139,117,0));
		solidrectangle(560,180,520,220);
		setlinecolor(BLACK);
		line(560,180,520,220);
		line(560,220,520,180);
		settextstyle(40, 0, _T("����"));
		outtextxy(600,180,"�κ��ڵ����ܻ���");
		setfillcolor(DARKGRAY);
		solidrectangle(560,240,520,280);
		setlinecolor(BLACK);
		line(560,240,520,280);
		line(560,280,520,240);
		outtextxy(600,240,"��ɫ�ڵ����Ի���");
		setfillcolor(WHITE);
		solidrectangle(560,300,520,340);
		outtextxy(600,300,"�κ��ڵ������ܻ���");
		setfillcolor(RGB( 0,191,255));
		solidrectangle(560,360,520,400);
		outtextxy(600,360,"���������̹��ǰ��");
		setfillcolor(GREEN);
		solidrectangle(560,420,520,460);
		outtextxy(600,420,"�ݵ�");
		setfillcolor(MAGENTA);
		fillcircle(540,500,28);
		outtextxy(600,480,"˫������ ");
		setfillcolor(WHITE);
		fillcircle(540,560,28);
		setfillcolor(GREEN);
		setlinecolor(GREEN);
		fillcircle(540,560,10);
		outtextxy(600,540,"����������");
		setfillcolor(WHITE);
		fillcircle(540,620,28);
		setfillcolor(RED);
		setlinecolor(RED);
		fillcircle(540,620,10);
		outtextxy(600,600,"�з�������");

		setfillcolor(LIGHTRED);  
		fillrectangle(1060,180,1020,220);
		outtextxy(1100,180,"��BUFF,����ӵ��˺�");
		setlinecolor(LIGHTBLUE);
		setfillcolor(LIGHTBLUE);  
		fillrectangle(1060,240,1020,280);
		outtextxy(1100,240,"��BUFF,����ӵ�����");
		setlinecolor(WHITE);
		rectangle(1060,300,1020,340);
		setfillcolor(LIGHTRED);
		fillcircle(1040,320,20);
		line(1060,300,1020,340);
		line(1060,340,1020,300);
		outtextxy(1100,300,"���ʮ�ź�ɫ�ӵ�");
		setlinecolor(WHITE);
		rectangle(1060,360,1020,400);
		setfillcolor(LIGHTBLUE);
		fillcircle(1040,380,20);
		line(1060,360,1020,400);
		line(1060,400,1020,360);
		outtextxy(1100,360,"���ʮ����ɫ�����");
		outtextxy(900,560,"��ͼ�����½Ǵ���һ����Ѫ��");


		setfillcolor(DARKGRAY);
		solidrectangle(1525,730,1310,800);
		
		MOUSEMSG m;
			m = GetMouseMsg();
		if ((m.x<=1525)&&(m.x>=1310)&&(m.y<=800)&&(m.y>=730)){
			setfillcolor(WHITE);
			solidrectangle(1525,730,1310,800);
			if (m.uMsg == WM_LBUTTONDOWN)
			goto play;
		}

		settextstyle(45, 0, _T("����"));
		outtextxy(1320,742,"Continue");
		outtextxy(350,730,"��Ϸ�е�������Ҽ���ͣ");

		SetWorkingImage();
		putimage(0,0,&buffer);   // �ѻ�������ͼ����һ���Ի�����ȥ��������������˸
		sleep(15);
	}

		while(1){
		pause:
		SetWorkingImage(&buffer);// ���ڻ�������ͼ
		cleardevice(); //clear
		setfillcolor(DARKGRAY);
		solidrectangle(1015,640,500,190);
		setlinecolor(RGB(255,51,204));
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 10);
		line(1015,190,1015,640);
		line(500,190,500,640);
		line(1015,190,500,190);
		line(1015,640,500,640);
		
		settextstyle(64, 0, _T("����"));
		outtextxy(605,240,"��Ϸ����ͣ");
		
		MOUSEMSG m;
			m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
			goto play;
		if (m.uMsg == WM_RBUTTONDOWN)
			goto help;

		settextstyle(56, 0, _T("����"));
		outtextxy(650,420,"������Ϸ");
		outtextxy(530,420,"�������������Ϸ");
		outtextxy(530,520,"�����Ҽ��鿴����");
		SetWorkingImage();
		putimage(0, 0, &buffer);  // �ѻ�������ͼ����һ���Ի�����ȥ��������������˸
		sleep(15);
	}

	while(1){
		play:
		
		count_game();
		creat();
		enemy_decision();
		//debug();
		tower_Fire();
		me_get_input();
		
		judge_bullet_dis();
		judge_shoot();
		show();
		MOUSEMSG m;
		if (MouseHit())
			m = GetMouseMsg();
		if (m.uMsg == WM_RBUTTONDOWN){
			goto pause;
		}
		if (me.get_health() <= 0||myBase.get_health() <= 0||enemyBase.get_health() <= 0){
			goto die;}

		sleep(5);
	}

		while(1){
		die:
		SetWorkingImage(&buffer);// ���ڻ�������ͼ
		cleardevice(); //clear
		setfillcolor(DARKGRAY);
		solidrectangle(1115,140,400,690);
		setlinecolor(RED);
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 10);
		line(1115,140,1115,690);
		line(400,140,400,690);
		line(1115,140,400,140);
		line(1115,690,400,690);

		settextstyle(81, 0, _T("����"));
		outtextxy(565,180,"��Ϸ������");
		settextstyle(90, 0, _T("����"));
		if (me.get_health() <= 0||myBase.get_health() <= 0)
		outtextxy(595,270,"�����ˣ�");
		if (enemyBase.get_health() <= 0)
		outtextxy(595,270,"��Ӯ�ˣ�");
		settextstyle(56, 0, _T("����"));
		outtextxy(470,420,"���ε÷�:");
		outtextxy(470,520,"��Ϸ��ʱ:");
		outtextxy(950,420,"��");
		outtextxy(950,520,"��");
		settextstyle(36, 0, _T("����"));
		outtextxy(570,650,"�����������˳���Ϸ");


		settextstyle(64, 0, _T("����"));
		char c1[6];
		sprintf(c1, "%d", me.get_score());//������aת�����ַ���
		outtextxy(750, 415, c1);//���ַ��������������
		char c2[6];
		sprintf(c2, "%d", counttime);//������aת�����ַ���
		outtextxy(750, 515, c2);//���ַ��������������
		
		MOUSEMSG m;
			m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
			break;

		SetWorkingImage();
		putimage(0,0,&buffer);   // �ѻ�������ͼ����һ���Ի�����ȥ��������������˸
		sleep(5);
	}

	return 0;
}

