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
		SetWorkingImage(&buffer);// 先在缓冲区绘图
		cleardevice(); //clear

		settextstyle(150, 0, _T("华文彩云"));
		outtextxy(370,100,"坦  克  荣  耀");
		setfillcolor(WHITE);
		solidrectangle(875,390,640,440);	
		solidrectangle(875,510,640,560);
		settextstyle(32, 0, _T("楷体"));
		outtextxy(1100,700,"制作人: 揭英睿  黄 锴");
		outtextxy(1228,740,"黄嘉杰  赖俊文");

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
		settextstyle(64, 0, _T("楷体"));
		outtextxy(613,370,"开始游戏");
		outtextxy(613,490,"帮助说明");

		SetWorkingImage();
		putimage(0,0,&buffer);   // 把缓冲区绘图内容一次性绘制上去，这样能消除闪烁
		sleep(15);
	}

	while(1){
		help:
		SetWorkingImage(&buffer);// 先在缓冲区绘图
		cleardevice(); //clear
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
		settextstyle(48, 0, _T("楷体"));
		outtextxy(100,80,"按键说明");
		outtextxy(600,80,"地图说明");
		outtextxy(1100,80,"道具说明");
		settextstyle(42, 0, _T("楷体"));
		outtextxy(100,180,"W——上移");
		outtextxy(100,300,"A——左移");
		outtextxy(100,240,"S——下移");
		outtextxy(100,360,"D——右移");
		outtextxy(100,420,"O——顺时针旋转");
		outtextxy(100,480,"I——逆时针旋转");
		outtextxy(100,540,"U——发射炮弹");
		setfillcolor(RGB(139,117,0));
		solidrectangle(560,180,520,220);
		setlinecolor(BLACK);
		line(560,180,520,220);
		line(560,220,520,180);
		settextstyle(40, 0, _T("楷体"));
		outtextxy(600,180,"任何炮弹都能击穿");
		setfillcolor(DARKGRAY);
		solidrectangle(560,240,520,280);
		setlinecolor(BLACK);
		line(560,240,520,280);
		line(560,280,520,240);
		outtextxy(600,240,"红色炮弹可以击穿");
		setfillcolor(WHITE);
		solidrectangle(560,300,520,340);
		outtextxy(600,300,"任何炮弹都不能击穿");
		setfillcolor(RGB( 0,191,255));
		solidrectangle(560,360,520,400);
		outtextxy(600,360,"河流，阻隔坦克前进");
		setfillcolor(GREEN);
		solidrectangle(560,420,520,460);
		outtextxy(600,420,"草地");
		setfillcolor(MAGENTA);
		fillcircle(540,500,28);
		outtextxy(600,480,"双方基地 ");
		setfillcolor(WHITE);
		fillcircle(540,560,28);
		setfillcolor(GREEN);
		setlinecolor(GREEN);
		fillcircle(540,560,10);
		outtextxy(600,540,"己方防御塔");
		setfillcolor(WHITE);
		fillcircle(540,620,28);
		setfillcolor(RED);
		setlinecolor(RED);
		fillcircle(540,620,10);
		outtextxy(600,600,"敌方防御塔");

		setfillcolor(LIGHTRED);  
		fillrectangle(1060,180,1020,220);
		outtextxy(1100,180,"红BUFF,提高子弹伤害");
		setlinecolor(LIGHTBLUE);
		setfillcolor(LIGHTBLUE);  
		fillrectangle(1060,240,1020,280);
		outtextxy(1100,240,"蓝BUFF,提高子弹射速");
		setlinecolor(WHITE);
		rectangle(1060,300,1020,340);
		setfillcolor(LIGHTRED);
		fillcircle(1040,320,20);
		line(1060,300,1020,340);
		line(1060,340,1020,300);
		outtextxy(1100,300,"获得十颗红色子弹");
		setlinecolor(WHITE);
		rectangle(1060,360,1020,400);
		setfillcolor(LIGHTBLUE);
		fillcircle(1040,380,20);
		line(1060,360,1020,400);
		line(1060,400,1020,360);
		outtextxy(1100,360,"获得十颗蓝色三叉戟");
		outtextxy(900,560,"地图最左下角存在一个补血区");


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

		settextstyle(45, 0, _T("宋体"));
		outtextxy(1320,742,"Continue");
		outtextxy(350,730,"游戏中单击鼠标右键暂停");

		SetWorkingImage();
		putimage(0,0,&buffer);   // 把缓冲区绘图内容一次性绘制上去，这样能消除闪烁
		sleep(15);
	}

		while(1){
		pause:
		SetWorkingImage(&buffer);// 先在缓冲区绘图
		cleardevice(); //clear
		setfillcolor(DARKGRAY);
		solidrectangle(1015,640,500,190);
		setlinecolor(RGB(255,51,204));
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 10);
		line(1015,190,1015,640);
		line(500,190,500,640);
		line(1015,190,500,190);
		line(1015,640,500,640);
		
		settextstyle(64, 0, _T("楷体"));
		outtextxy(605,240,"游戏已暂停");
		
		MOUSEMSG m;
			m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
			goto play;
		if (m.uMsg == WM_RBUTTONDOWN)
			goto help;

		settextstyle(56, 0, _T("楷体"));
		outtextxy(650,420,"继续游戏");
		outtextxy(530,420,"单击左键继续游戏");
		outtextxy(530,520,"单击右键查看帮助");
		SetWorkingImage();
		putimage(0, 0, &buffer);  // 把缓冲区绘图内容一次性绘制上去，这样能消除闪烁
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
		SetWorkingImage(&buffer);// 先在缓冲区绘图
		cleardevice(); //clear
		setfillcolor(DARKGRAY);
		solidrectangle(1115,140,400,690);
		setlinecolor(RED);
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 10);
		line(1115,140,1115,690);
		line(400,140,400,690);
		line(1115,140,400,140);
		line(1115,690,400,690);

		settextstyle(81, 0, _T("楷体"));
		outtextxy(565,180,"游戏结束！");
		settextstyle(90, 0, _T("楷体"));
		if (me.get_health() <= 0||myBase.get_health() <= 0)
		outtextxy(595,270,"你输了！");
		if (enemyBase.get_health() <= 0)
		outtextxy(595,270,"你赢了！");
		settextstyle(56, 0, _T("楷体"));
		outtextxy(470,420,"本次得分:");
		outtextxy(470,520,"游戏用时:");
		outtextxy(950,420,"分");
		outtextxy(950,520,"秒");
		settextstyle(36, 0, _T("楷体"));
		outtextxy(570,650,"单击鼠标左键退出游戏");


		settextstyle(64, 0, _T("楷体"));
		char c1[6];
		sprintf(c1, "%d", me.get_score());//将整形a转换成字符串
		outtextxy(750, 415, c1);//将字符串输出到界面上
		char c2[6];
		sprintf(c2, "%d", counttime);//将整形a转换成字符串
		outtextxy(750, 515, c2);//将字符串输出到界面上
		
		MOUSEMSG m;
			m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
			break;

		SetWorkingImage();
		putimage(0,0,&buffer);   // 把缓冲区绘图内容一次性绘制上去，这样能消除闪烁
		sleep(5);
	}

	return 0;
}

