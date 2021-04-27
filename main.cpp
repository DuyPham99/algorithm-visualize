#include <iostream>
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;
#define HIGH 90 //y toolbox
#define WIDTH 70 // x toolbox
#define R 25
#define PI 3.1415926535897
#define MAX 10000

struct node{
	int number;
	int x,y;
	struct node *next;
};
typedef struct node NODE;
struct namefile{
	int n;
	string name;
	struct namefile *next;
};
typedef struct namefile NameFILE;
typedef struct{
	int amountNODE=0;
	NODE *node;
	NODE *pFirst=NULL,*pLast=NULL;
} LIST;
typedef struct{
	int n=0;
	NameFILE *pFirst=NULL, *pLast=NULL;
} LISTFILE;
//createNODE
void insertNODE(LIST &l,int x,int y){
	NODE *temp = new NODE;
	temp->x= x;
	temp->y = y;
	l.amountNODE++;
	temp->number = l.amountNODE;
	if (l.pFirst == NULL){
		l.pFirst = l.pLast = temp;
		temp->next = NULL;
	} else {
		l.pLast->next = temp;
		l.pLast = temp;
		temp->next=NULL;
	}
}
//listfile
void insertNAMEFILE(LISTFILE &l,string &str){
	NameFILE *temp = new NameFILE;
	l.n++;
	temp->n = l.n;
	temp->name = str;
	temp->next=NULL;
	if (l.pFirst == NULL){
		l.pFirst = l.pLast = temp;
	} else {
		l.pLast->next = temp;
		l.pLast = temp;
	}
}



void Tangent(int xCircle,int yCircle,int xPoint,int yPoint,int radius,float &t1,float &t2){
	float dx,dy,dd,a,b,t,ta,tb,x,y;
	dx = xCircle-xPoint;
	dy = yCircle-yPoint;
	dd = sqrt(dx*dx+dy*dy);
	a = asin(radius/dd);
	b = atan2(dy,dx);
	t1 = b-a; t2=a+b;	
}
void PointTangent(float &x1,float &y1, float &x2, float &y2,float t1, float t2, int radius){
	//t1 beta - alpha
	x1 = radius * sin(t1);
	y1 = radius * -cos(t1);
	//t2 bata + alpha
	x2 = radius * -sin(t2);
	y2 = radius * cos(t2);
}
int isIn(int x,int y, int x1, int y1,int clickX, int clickY){
		if ( (x<=clickX) and (clickX<=x1) and (clickY<=y1) and (y <= clickY ) ) return 1;
		return 0;
}
void OutValue(int startX,int startY,int endX,int endY,int value){
			float t1,t2;
			float x1,y1,x2,y2;
			int x=(startX+endX)/2;
			int y = (startY+endY)/ 2;
			Tangent(x,y,startX,startY,25,t1,t2);
			PointTangent(x1,y1,x2,y2,t1,t2,25);
			 char c[15];
			 itoa(value,c,10);
			 settextstyle(BOLD_FONT, HORIZ_DIR,1);
			outtextxy(x+x2+3,y+y2-5,c);
}
void DrawArrow(int startX,int startY,int endX,int endY){
	
	int vectorX=startX-endX,vectorY=startY-endY;
	
	//Quay vector mot goc 45 do theo chieu kim dong ho
	int newX=vectorX*cos(45)-vectorY*sin(45);
	int newY=vectorX*sin(45)+vectorY*cos(45);
	int newstartX=newX+endX;
	int newstartY=newY+endY;
	
	int newX2=vectorX*cos(-45)-vectorY*sin(-45);
	int newY2=vectorX*sin(-45)+vectorY*cos(-45);
	int newstartX2=newX2+endX;
	int newstartY2=newY2+endY;
	
	line(endX,endY,newstartX,newstartY);
	line(endX,endY,newstartX2,newstartY2);
}

void DrawLineWithArrow(int startX,int startY,int endX, int endY,int arrowleng){
	endX=(endX+startX)/2;
	endY=(endY+startY)/2;
	int VTCPX=endX-startX;
	int VTCPY=endY-startY;
	//x'=x0+k*VTCPX;
	//y'=x0+k*VTCPY;//k????????????
	int tmpX,tmpY;
	///start-------------------tmp----------end, khang cach giua tmp va end la bang arrowleng
	//Ap dung cong thuc tinh khoang cach giua 2 vector ta tim diem tmp

	float k=(((float)arrowleng/(sqrt(VTCPX*VTCPX+VTCPY*VTCPY)))-1 );
	k=-k;
	tmpX=startX+k*VTCPX;
	tmpY=startY+k*VTCPY;
	DrawArrow(tmpX,tmpY,endX,endY);
	line(startX,startY,endX*2-startX,2*endY-startY);
	
}
void DrawLineTangent(int startX,int startY,int endX,int endY,int radius,int value){

	float t1,t2,x1,x2,x3,x4,y1,y2,y3,y4;
	//tim teta
	Tangent(startX,startY,endX,endY,radius/2,t1,t2);
	// 2 diem tiep tuyen tu point den circle
	PointTangent(x1,y1,x2,y2,t1,t2,radius/2);
	PointTangent(x3,y3,x4,y4,t1,t2,radius/2);
	DrawLineWithArrow(startX+x1,startY+y1,endX+x3,endY+y3,8);
	OutValue(startX+x1,startY+y1,endX+x3,endY+y3,value);
}
void DrawHighLight(int startX,int startY,int endX,int endY,int radius,int value){
	//setcolor(BLUE);
	setlinestyle(0,0,3);
	setcolor(BLUE);
	float t1,t2,x1,x2,x3,x4,y1,y2,y3,y4;
	//tim teta
	Tangent(startX,startY,endX,endY,radius/2,t1,t2);
	// 2 diem tiep tuyen tu point den circle
	PointTangent(x1,y1,x2,y2,t1,t2,radius/2);
	PointTangent(x3,y3,x4,y4,t1,t2,radius/2);
	DrawLineWithArrow(startX+x1,startY+y1,endX+x3,endY+y3,8);
	OutValue(startX+x1,startY+y1,endX+x3,endY+y3,value);
}
void DrawHighLight1(int startX,int startY,int endX,int endY,int radius,int value){
	//setcolor(BLUE);
	setlinestyle(0,0,3);
	setcolor(RED);
	float t1,t2,x1,x2,x3,x4,y1,y2,y3,y4;
	//tim teta
	Tangent(startX,startY,endX,endY,radius/2,t1,t2);
	// 2 diem tiep tuyen tu point den circle
	PointTangent(x1,y1,x2,y2,t1,t2,radius/2);
	PointTangent(x3,y3,x4,y4,t1,t2,radius/2);
	DrawLineWithArrow(startX+x1,startY+y1,endX+x3,endY+y3,8);
	OutValue(startX+x1,startY+y1,endX+x3,endY+y3,value);
}

void Display(LIST &l,int **matrix){
	setcolor(WHITE);
	
	setlinestyle(0,0,2);
	//top
	line(0,80,1000,80);
	//bottom
	line(0,500,1000,500);
	//right
	line(700,0,700,700);
	
	//button
	rectangle(0,0,100,80);
	rectangle(100,0,200,80);
	rectangle(200,0,300,80);
	rectangle(300,0,400,80);
	rectangle(400,0,500,80);
	rectangle(500,0,600,80);
	
	//button save,load,delete
	rectangle(600,0,700,80);
	rectangle(700,0,800,80);
	rectangle(800,0,900,80);
	
	//buttonFeature
	//createNODE
	rectangle(700,500,800,580);	
	setlinestyle(0,1,4);
	circle(750,540,20);
	settextstyle(8,HORIZ_DIR,1);
	outtextxy(745,530,"1");
	//linkNODE
	DrawLineWithArrow(820,570,875,520,10);
	setlinestyle(0,1,1);
	setfillstyle(SOLID_FILL,8);
	rectangle(800,500,900,580);
	floodfill(801,502,WHITE);

	//Move
	rectangle(900,500,1000,580);
	settextstyle(8,HORIZ_DIR,7);
	outtextxy(925,508,"M");
	//run step
	settextstyle(8,HORIZ_DIR,4);
	line(800,580,800,800);
	outtextxy(720,600,"RUN");
	outtextxy(717,640,"STEP");
	line(900,580,900,800);
	outtextxy(810,617,"SKIP");
	outtextxy(915,625,"RUN");
	//title
	settextstyle(8,HORIZ_DIR,3);
	outtextxy(15,23,"DFS");
	outtextxy(120,23,"BFS");
	outtextxy(215,23,"TPLT");
	outtextxy(310,23,"DJ.TRA");
	outtextxy(410,23,"DTDTCC");
	settextstyle(8,HORIZ_DIR,1);
	outtextxy(505,20,"Hamilton");
	outtextxy(525,50,"Euler");
	settextstyle(8,HORIZ_DIR,3);
	outtextxy(620,23,"TOPO");
	outtextxy(720,23,"NEW");
	outtextxy(820,23,"SAVE");
	outtextxy(920,23,"LOAD");
	char c[10];
	for(NODE *k=l.pFirst; k!=NULL; k=k->next){
		settextstyle(BOLD_FONT, HORIZ_DIR,1);
		setfillstyle(SOLID_FILL,WHITE);
		setcolor(WHITE);
		circle(k->x,k->y,21);
		floodfill(k->x-7,k->y-9,WHITE);
		itoa(k->number,c,10);
		setcolor(BLACK);
		setbkcolor(WHITE);
		outtextxy(k->x-7,k->y-9,c);
		setbkcolor(8);
		setcolor(WHITE);
	}

	if(l.amountNODE==0) return;
	
	//700 991 ==200
	//80 ==200
	int n=l.amountNODE;
	n=n+1;
	char temp[50];
	for(int i=1; i<n; i++){
	itoa(i,temp,10);
	outtextxy((700+(300/n)/2)+(300/n)*i,(80+((300)/n)/2),temp);
	outtextxy((700+(300/n)/2),(80+((300)/n)/2)+(300/n)*i,temp);
//	if(i==14) break;
	for(int j=1; j<=l.amountNODE; j++){
		itoa(matrix[i][j],temp,10);
		outtextxy((700+(300/n)/2)+(300/n)*(j),(80+((300)/n)/2)+(300/n)*(i),temp);
	//	if(j==14) break;
	}
}
	for(int i=1; i<=n; i++){
		line(700+(300/n)*i,80,700+(300/n)*i,80+(300/n)*n);
		line(700,80+(300/n)*i,700+(300/n)*n,80+(300)/n*i);
	//	if(i==14) break;
	}


	
	for(NODE *k=l.pFirst; k!=NULL; k=k->next){
		for(NODE *i=l.pFirst; i!=NULL; i=i->next){
				if (matrix[k->number][i->number] > 0)
					DrawLineTangent(k->x,k->y,i->x,i->y,25,matrix[k->number][i->number]);
	}
}

}
 int isInCircle(LIST &l,int clickX, int clickY){
	for (NODE *k=l.pFirst; k!=NULL; k=k->next){
		if (sqrt(pow(k->x - clickX,2) + pow(k->y - clickY,2)) <=21 ) return k->number;
	}
	return 0;	
}
void OutLIST(LIST &l){
	for (NODE *k=l.pFirst;k!=NULL; k=k->next){
			cout << k->number << " " << k->x << " " << k->y << endl;
	}
}
void initMatrix(int **&matrix,int n){
	matrix = new int *[n];

	for (int i=0; i<=n; i++){
		matrix[i] = new int[n];
	}
	for (int i=1;i<=n; i++){
		for (int j=1 ;j<=n; j++){
			if (i==j) {
				matrix[i][j] = 0;
				continue;
			}
			matrix[i][j]=0;
		}
	}
	matrix[0][0] = n;
}
void ResizeMatrix(int **&matrix,int n,int key){
	int **temp,tempN=matrix[0][0];

	temp = matrix;
	matrix = new int *[n+1];
	initMatrix(matrix,n);
	
		for(int i=1; i<=tempN; i++){
			if(i==key) continue;
			for(int j=1; j<=tempN; j++){
				if(j==key) continue;
				matrix[i][j] = temp[i][j];
			}
		}
//	delete[] temp;

}
void createNODE(LIST &l,int **&matrix,int &clickX,int &clickY){
	
	//display number in node
	clearmouseclick(WM_LBUTTONDOWN);
	
	char c[10];
	//loop
	while(1){
		 {
		//	getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
		if (isIn(700,500,800,580,clickX,clickY)) {
			while(1){
					setlinestyle(0,1,1);	
					//if LB press
					
					if (ismouseclick(WM_LBUTTONDOWN)) {
						getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
							if(isIn(700,500,800,580,clickX,clickY)) {
								if(l.amountNODE == 0) return;
								clearmouseclick(WM_LBUTTONDOWN);
								ResizeMatrix(matrix,l.amountNODE,0);
								matrix[0][0] = l.amountNODE;
								Display(l,matrix);
								return;
							}
							if (isIn(0,81,699,499,clickX,clickY) and (isInCircle(l,clickX,clickY)==0)){
								setfillstyle(SOLID_FILL,WHITE);
								settextstyle(BOLD_FONT, HORIZ_DIR,1);
								setcolor(WHITE);
								circle(clickX,clickY,21);
								floodfill(clickX,clickY,WHITE);
								insertNODE(l,clickX,clickY);
								clickX-=7;
								clickY-=9;
								itoa(l.pLast->number,c,10);
								setbkcolor(WHITE);
								setcolor(BLACK);
								outtextxy(clickX,clickY,c);
								setbkcolor(8);
								setcolor(WHITE);
							}		
					}
					delay(200);
				}
			}
		}
		clickX=0;
		clearmouseclick(WM_LBUTTONDOWN);
		delay(200);
	}
}

NODE *searchNODE(LIST &l,int clickX, int clickY,int key){
	for (NODE *k=l.pFirst; k!=NULL; k=k->next){
		if (k->number == key) return k;
	}
	return 0;
}

long long stoi(const char *s)
{
    long i;
    i = 0;
    while(*s >= '0' && *s <= '9')
    {
        i = i * 10 + (*s - '0');
        s++;
    }
    return i;
}

int BoxMassage(int start, int end){
	string str; 
	int x,i=0,clickX,clickY;
	char c[30];
	
	
	////
	setlinestyle(0,1,2); 
	settextstyle(BOLD_FONT, HORIZ_DIR,2);
	setcolor(BLACK);
	//box
	setfillstyle(SOLID_FILL,WHITE);
	rectangle(375,263,665,400);
	floodfill(400,280,BLACK);

	setfillstyle(SOLID_FILL,1);
	rectangle(375,291,665,291);
	floodfill(465,280,BLACK);
	//exit
	setfillstyle(SOLID_FILL,RED);
	rectangle(637,263,637,291);
	floodfill(645,270,BLACK);
	//input
	rectangle(433,318,656,342);
	//ok cancle
	setbkcolor(WHITE);
	settextstyle(BOLD_FONT, HORIZ_DIR,1);
	outtextxy(470+6,356-3+14,"OK");
	rectangle(458,350+17,520,375+17);
	outtextxy(543,356-3+15,"Cancle");
	rectangle(540,350+17,615,375+17);
	//notice
	setfillstyle(SOLID_FILL,11);
	circle(401,314,16);
	floodfill(400,313,BLACK);
	setbkcolor(11);
	outtextxy(401-6,304,"i");
	//taskbar	
	setcolor(WHITE);
	setbkcolor(1);
	outtextxy(385,265,"Opps!!");
	setbkcolor(RED);
	setcolor(BLACK);
	outtextxy(645,265,"X");
	//input value
	char tempStart[10],tempEnd[10];
	itoa(start,tempStart,10);
	itoa(end,tempEnd,10);
	settextstyle(BOLD_FONT, HORIZ_DIR,1);
	setbkcolor(WHITE);
	outtextxy(438,295,"Input value " );
	outtextxy(565,295,tempStart);
	outtextxy(580,295,"to");
	outtextxy(608,295,tempEnd);
	outtextxy(620,295,":");
	//process input
	
	while(1){
	 	setbkcolor(WHITE);
		if(kbhit()){
			 x = getch();
			 //delete
			 if(x==8 and str.length()>0){
			 	str.resize(str.length()-1);
			 	outtextxy(435,319,"           ");
			 	strcpy(c,str.c_str());
				outtextxy(435,319,c);
			 	continue;
			 }
			 if (x==13) return stoi(str.c_str());
			 if ( (x>57 or x<48) and (x!= 13)){
			 	//settextstyle(8,0,1);
			 	setbkcolor(WHITE);
			 	setcolor(12);
			 	outtextxy(450,343,"                  ");
			 	outtextxy(450,344,"(INPUT NUMBER!!!)");
			 	settextstyle(BOLD_FONT, HORIZ_DIR,1);
			 	setbkcolor(WHITE);
			 	setcolor(BLACK);
			 	continue;
			 } 
			 if(str.length()<=9 ){
						outtextxy(450,343,"                  ");
						x-=48;
						itoa(x,c,10);
						str.insert(str.length(),c);
						strcpy(c,str.c_str());
						outtextxy(435,319,c);
			}
			else
			  {
			 	while(!kbhit()){
			 		setcolor(12);
			 		outtextxy(440,343,"(Max 10 characters!)");
			 		setcolor(BLACK);
			 		delay(500);
			 		outtextxy(440,343,"                    ");
			 		delay(500);
			 		getmouseclick(WM_LBUTTONUP,clickX,clickY);
					if(isIn(459,366,519,391,clickX,clickY)) {
					return stoi(str.c_str());
					if(isIn(541,366,613,389,clickX,clickY) or isIn(638,262,664,289,clickX,clickY)) return 0;
					
				}
			 	}
			 }
		 }
		 if (str.length()==0)
		  {
			outtextxy(435,319,"|");
			delay(200);
			outtextxy(436,319,"  ");
			delay(500);
		}
		//click ok, exit
		
		if(ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,clickX,clickY);
			if(isIn(459,366,519,391,clickX,clickY)) return stoi(str.c_str());
			if(isIn(541,366,613,389,clickX,clickY) or isIn(638,262,664,289,clickX,clickY)) return 0;
		}
		// highlight
		getmouseclick(WM_MOUSEMOVE,clickX,clickY);
		if(isIn(459,366,519,391,clickX,clickY)){
				setfillstyle(SOLID_FILL,YELLOW);
				setcolor(BLACK);
				setbkcolor(YELLOW);
				floodfill(470,370,BLACK);
				outtextxy(470+6,356-3+15,"OK");
			} else if (clickX!=-1){
				setfillstyle(SOLID_FILL,WHITE);
				setcolor(BLACK);
				setbkcolor(WHITE);
				floodfill(470,370,BLACK);
				outtextxy(470+6,356-3+15,"OK");
			}
		if (isIn(541,366,613,389,clickX,clickY)){
				settextstyle(BOLD_FONT, HORIZ_DIR,1);
				setfillstyle(SOLID_FILL,YELLOW);
				setcolor(BLACK);
				setbkcolor(YELLOW);
				floodfill(550,380,BLACK);
				outtextxy(543,356-3+15,"Cancle");
		}else if (clickX!=-1){
				settextstyle(BOLD_FONT, HORIZ_DIR,1);
				setfillstyle(SOLID_FILL,WHITE);
				setcolor(BLACK);
				setbkcolor(WHITE);
				floodfill(550,380,BLACK);
				outtextxy(543,356-3+15,"Cancle");
			}
			//x
		if(isIn(638,263,664,289,clickX,clickY)){
				setfillstyle(SOLID_FILL,12);
				floodfill(640,280,BLACK);
		} else if(clickX!=-1) {
			setfillstyle(SOLID_FILL,RED);
			floodfill(640,280,BLACK);
		}
		clearmouseclick(WM_LBUTTONDOWN);
		clearmouseclick(WM_LBUTTONUP);
		delay(10);
}
}
void ThuocDo(){
	int clickX, clickY;
	while(1){
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
			cout << clickX << " " << clickY << endl;
		}
		delay(500);
	}
}
void linkNODE(LIST &l,int **&matrix,int &clickXStart, int &clickYStart){
	int clickXEnd,clickYEnd,tempClickXEnd,tempClickYEnd;
	NODE *tempNODE1 = new NODE, *tempNODE2 = new NODE;
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(801,502,WHITE);
	while(1){
		//click buttom
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONUP,clickXStart,clickYStart);
			if (isIn(800,500,900,580,clickXStart,clickYStart)){
				while(1){	
							getmouseclick(WM_LBUTTONDOWN,clickXStart,clickYStart);
							 {
									if (isIn(800,500,900,580,clickXStart,clickYStart)) {
										cleardevice();
										Display(l,matrix);
										return;
								}
							}
							if(isInCircle(l,clickXStart,clickYStart)!=0){
								//draw line
								while (1)
								{ 	
									delay(50);
									getmouseclick(WM_MOUSEMOVE,tempClickXEnd,tempClickYEnd);
									if(ismouseclick(WM_LBUTTONUP)) goto x;
									if (tempClickXEnd<1) continue;
									clickXEnd = tempClickXEnd;
									clickYEnd = tempClickYEnd;
									cleardevice();
									Display(l,matrix);
									setfillstyle(SOLID_FILL,YELLOW);
									floodfill(801,502,WHITE);
									DrawLineWithArrow(clickXStart,clickYStart,clickXEnd,clickYEnd,10);
								x:	if(ismouseclick(WM_LBUTTONUP)) {
										getmouseclick(WM_LBUTTONUP,clickXEnd,clickYEnd);
										if ((isInCircle(l,clickXStart,clickYStart) == isInCircle(l,clickXEnd,clickYEnd))) break;
										if(isInCircle(l,clickXEnd+1,clickYEnd+1)){
										tempNODE1 = searchNODE(l,clickXStart,clickYStart,isInCircle(l,clickXStart,clickYStart));
										tempNODE2 = searchNODE(l,clickXEnd,clickYEnd,isInCircle(l,clickXEnd,clickYEnd));
										matrix[tempNODE1->number][tempNODE2->number] = BoxMassage(tempNODE1->number,tempNODE2->number);
										//cout << matrix[tempNODE1->number][tempNODE2->number] << endl;
										setbkcolor(8);
										setcolor(WHITE);
										//clr box and finish link
										DrawLineWithArrow(tempNODE1->x, tempNODE1->y ,tempNODE2->x,tempNODE2->y,10);
										cleardevice();
										Display(l,matrix);
										setfillstyle(SOLID_FILL,YELLOW);
										floodfill(801,502,WHITE);
										break;
										} else {
											cleardevice();
											Display(l,matrix);
											setfillstyle(SOLID_FILL,YELLOW);
											floodfill(801,502,WHITE);
											break;
										}
									}
								
								}
								
							}
							delay(100);
						}
						delay(100);
						clearmouseclick(WM_LBUTTONDOWN);
						clearmouseclick(WM_LBUTTONUP);	
				}	
			
			}
	
		
		delay(10);
	}
}
NODE *TempNODE(LIST l, int key){
	for (NODE *k=l.pFirst; k!=NULL; k=k->next){
		if (k->number == key) return k;
	}
}
void MoveCircle(LIST &l, int **&matrix,int &x,int &y){
	int tempX,tempY;
	NODE *temp = new NODE;
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(902,502,WHITE);
	while(1){
			if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONUP,x,y);
			if (isIn(901,501,990,580,x,y)){
				while(1){
					if(ismouseclick(WM_LBUTTONDOWN)){
						getmouseclick(WM_LBUTTONDOWN,x,y);
						if(isIn(901,501,990,580,x,y)) return;
						if(isInCircle(l,x,y)){
							temp = TempNODE(l,isInCircle(l,x,y));
							while(1){
								if(ismouseclick(WM_LBUTTONUP)) break;
								getmouseclick(WM_MOUSEMOVE,tempX,tempY);
								if(tempX>0) {
								x = tempX;
								y = tempY;
							}
						if(!isIn(0,80,700,500,x,y)) break;
								cleardevice();
								temp->x=x;
								temp->y=y;
								Display(l,matrix);
								setfillstyle(SOLID_FILL,YELLOW);
								floodfill(902,502,WHITE);
								delay(100);
								
							}
						}
					}
					clearmouseclick(WM_LBUTTONDOWN);
					clearmouseclick(WM_LBUTTONUP);
						delay(100);
				}
			}		
	}
	clearmouseclick(WM_LBUTTONDOWN);
	delay(100);
}
}
//deletetnode

void DeleteNODE(LIST &l,int key,int **&matrix){
	if (l.pFirst->number == key){
		l.pFirst = l.pFirst->next; 
		 l.amountNODE--;
		//delete colum
		for(int i=1; i<=matrix[0][0]; i++){
			for(int j=key; j<matrix[0][0]; j++){
				matrix[i][j]= matrix[i][j+1];
			}
		}
		//delete row
		for(int i=key; i<matrix[0][0]; i++){
			for(int j=1; j<=matrix[0][0]; j++){
				matrix[i][j]= matrix[i+1][j];
			}
		}
		//update creen
		for(int i=0; i<=2; i++){
			cleardevice();
			Display(l,matrix);
		}
		matrix[0][0]--;
	} 
	else {
		for(NODE *k= l.pFirst ; k!=NULL; k=k->next){
			if (k->next->number == key){
				if(l.pLast == k->next) l.pLast = k;
				k->next = k->next->next;
				 l.amountNODE--;
				//delete colum
				for(int i=1; i<=matrix[0][0]; i++){
					for(int j=key; j<matrix[0][0]; j++){
						matrix[i][j]= matrix[i][j+1];
					}
				}
				//delete row
				for(int i=key; i<matrix[0][0]; i++){
					for(int j=1; j<=matrix[0][0]; j++){
						matrix[i][j]= matrix[i+1][j];
					}
				}
				//update creen
				for(int i=0; i<=2; i++){
					cleardevice();
					Display(l,matrix);
				}
				
			}
			}
		}
	
			matrix[0][0]--;
			int count=1;
			
			for(NODE *k= l.pFirst ; k!=NULL; k=k->next)
				{
					k->number = count;
					count++;
				}

}
void ListFile(LISTFILE &l){
	ifstream readFile;
	readFile.open("ListFile.txt",ios::in);
	string temp;
	int n;
	readFile>>n;
	while(!readFile.eof()){
		readFile >> temp;
		insertNAMEFILE(l,temp);
		n--;
		if(n==0) break;
	}
	readFile.close();
	return;
}
void ShowListFile(LISTFILE &l, int start,int x, int y,string &str){
	fflush(stdin);
	int end= start + 7,space =0;
	char temp[50],*check;
	for (NameFILE *k =l.pFirst; k!=NULL; k=k->next){
		outtextxy(x,y+space,"                                   ");
		space +=20;
		if(k->n >end) break;
	}
	space =0;
	settextstyle(BOLD_FONT, HORIZ_DIR,3);
	for (NameFILE *k =l.pFirst; k!=NULL; k=k->next){;
			check = strstr(k->name.c_str(),str.c_str());
			if(check!=NULL and space <180) {
				outtextxy(x,y+space,"                                   ");
				strcpy(temp,k->name.c_str());
				outtextxy(x,y+space,temp);
				space +=20;
		}
	}
}
string NameFile(LIST &list,LISTFILE &l1,char *name){
	setlinestyle(0,0,2);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,WHITE);
	settextstyle(BOLD_FONT, HORIZ_DIR,3);
	fflush(stdin);
	
	//box
	rectangle(177,196,793,558);
	floodfill(178,200,BLACK);
	line(177,235,792,235);
	setfillstyle(SOLID_FILL,1);
	floodfill(433,218,BLACK);
	line(748,196,748,235);
	setfillstyle(SOLID_FILL,RED);
	floodfill(749,200,BLACK);
	setbkcolor(WHITE);
	outtextxy(194,255,"Name: ");
	outtextxy(700,258,".txt");
	setcolor(WHITE);
	setbkcolor(1);
	outtextxy(185,202,name);
	setbkcolor(RED);
	outtextxy(762,205,"X");
	setcolor(BLACK);
	//input
	rectangle(265,252,696,309-25);
	//show file
	rectangle(217+15,327-15,723+15,523-15);
	//oke,cancle
	setbkcolor(WHITE);
	rectangle(312+20,520,400+20,547+5);
	outtextxy(360,524,"OK");
	rectangle(440+120,520,535+120,547+5);
	outtextxy(565,524,"Cancle");

	
	char temp,c[50];
	string str;
	int clickX,clickY,mark=0;
	ShowListFile(l1,1,242,315,str);
	outtextxy(270,256,"                 			   ");
	while(1){
		if(kbhit()){
			temp = getch();
			if(temp==8 and str.length()>0){
			 	str.resize(str.length()-1);
			 	outtextxy(270,256,"                 			   ");
			 	strcpy(c,str.c_str());
				outtextxy(270,256,c);
				ShowListFile(l1,1,242,315,str);
			 	continue;
			 } 
			if ( (toupper(temp)>90 or toupper(temp)<65) and ( (int) temp < 48 or (int) temp > 57 )){
				settextstyle(BOLD_FONT, HORIZ_DIR,1);
				setcolor(12);
				outtextxy(350,286,"( No special characters!!! )");
				setcolor(BLACK);
				continue;
			}
			if (str.length()<30){
					settextstyle(BOLD_FONT, HORIZ_DIR,1);
					outtextxy(350,286,"                                   ");
					str.insert(str.length(),&temp);
					ShowListFile(l1,1,242,315,str);
					strcpy(c,str.c_str()); 
					outtextxy(270,256,c);	
				} else
				{
							settextstyle(BOLD_FONT, HORIZ_DIR,1);
							setcolor(12);
							delay(500);
							outtextxy(350,286,"( Maximum characters!! )");
							delay(500);
							outtextxy(350,285,"                           ");
							setcolor(BLACK);
						
				}		
		}
	if (str.length()==0)
		  {
			outtextxy(268,254,"|");
			delay(500);
			outtextxy(268,254,"  ");
			delay(500);
		}
			//highlight
		getmouseclick(WM_MOUSEMOVE,clickX,clickY);
		if(isIn(332,520,420,552,clickX,clickY)){
				settextstyle(BOLD_FONT, HORIZ_DIR,3);
				setfillstyle(SOLID_FILL,YELLOW);
				setcolor(BLACK);
				setbkcolor(YELLOW);
				floodfill(335,550,BLACK);
				outtextxy(360,524,"OK");

			} else if (clickX!=-1){
				settextstyle(BOLD_FONT, HORIZ_DIR,3);
				setfillstyle(SOLID_FILL,WHITE);
				setcolor(BLACK);
				setbkcolor(WHITE);
				floodfill(335,550,BLACK);
				outtextxy(360,524,"OK");

			}	
		if (isIn(560,520,654,550,clickX,clickY)){
				setfillstyle(SOLID_FILL,YELLOW);
				setcolor(BLACK);
				setbkcolor(YELLOW);
				floodfill(580,535,BLACK);
				outtextxy(565,524,"Cancle");
				setbkcolor(WHITE);
			//	setcolor(BLACK);
		}else if (clickX!=-1){
				setfillstyle(SOLID_FILL,WHITE);
				setcolor(BLACK);
				setbkcolor(WHITE);
				floodfill(580,535,BLACK);
				outtextxy(565,524,"Cancle");
			//	setcolor(BLACK);
			}	
		if (isIn(749,196,792,233,clickX,clickY)){
				
				setfillstyle(SOLID_FILL,12);
				floodfill(785,216,BLACK);
				setbkcolor(12);
				outtextxy(762,205,"X");
				setbkcolor(WHITE);
			//	setcolor(BLACK);
				
		}else if (clickX!=-1){
				settextstyle(BOLD_FONT, HORIZ_DIR,3);
				setfillstyle(SOLID_FILL,RED);
				floodfill(785,216,BLACK);
				setbkcolor(RED);
				setcolor(WHITE);
				outtextxy(762,205,"X");
				setbkcolor(WHITE);
				setcolor(BLACK);
			}				
	// click
	if(ismouseclick(WM_LBUTTONDOWN)){
		getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
		if (isIn(333,520,419,551,clickX,clickY)) {
				cleardevice();
				setbkcolor(8);
				setcolor(WHITE);
				return str;	
			}
		if (isIn(560,519,655,551,clickX,clickY) or isIn(749,195,792,234,clickX,clickY)) {
				cleardevice();
				setbkcolor(8);
				setcolor(WHITE);
				return " ";
	}
		
	clearmouseclick(WM_LBUTTONDOWN);
	clearmouseclick(WM_LBUTTONUP);
	delay(10);
}	
		
}
}

int CheckFile(LISTFILE &listFILE,string str){ 
	for(NameFILE *k=listFILE.pFirst; k!=NULL; k=k->next){
		if(str.compare(k->name) == 0) return 1;
	}
	return 0;
}
void SaveFile(LIST &listNODE,LISTFILE &listFILE,int **&matrix){
	string nameFile;
	ofstream saveFile;
	fflush(stdin);
	nameFile = NameFile(listNODE,listFILE,"SAVE!!!");
	if(nameFile == " ") {
			setbkcolor(8);
			cleardevice();
			Display(listNODE,matrix);
			return;
	}
	if(!CheckFile(listFILE,nameFile)) {
		insertNAMEFILE(listFILE,nameFile);
		cout << "save";
	}
	string str;
	char c[50];
	str.insert(str.length(),nameFile);
	str.insert(str.length(),"NODE.txt");
	strcpy(c,str.c_str());
	saveFile.open(c, ios::out);
	for (NODE *k=listNODE.pFirst; k!=NULL; k=k->next){
		saveFile << k->x << " ";
		saveFile << k->y << endl;
	}
	saveFile.close();
	str="";	
	str.insert(str.length(),nameFile);
	str.insert(str.length(),"MATRIX.txt");
	strcpy(c,str.c_str());
	saveFile.open(c, ios::out);
	saveFile << matrix[0][0] << endl;
	for(int i=1; i<=matrix[0][0]; i++){
		for (int j=1; j<=matrix[0][0]; j++){
			saveFile << matrix[i][j] <<" ";
		}
		saveFile << endl;
	}
	
	saveFile.close();
	saveFile.open("ListFile.txt",ios::out);
	saveFile << listFILE.n << endl; 
	for (NameFILE *k=listFILE.pFirst; k!=NULL; k=k->next){
		saveFile << k->name << endl;
	}
	saveFile.close();
	

	setbkcolor(8);
	cleardevice();
	Display(listNODE,matrix);
}
void LoadFile(LIST &listNODE,LISTFILE &listFILE,int **&matrix){
	string nameFile;
	ifstream readFile;
	int x,y,n;
	string str;
	char c[50];
	fflush(stdin);
	nameFile = NameFile(listNODE,listFILE,"LOAD!!!");
	if(nameFile == " ") {
		cleardevice();
		Display(listNODE,matrix);
		return;
	}
	// read matrix
	str = nameFile;
	str.insert(str.length(),"MATRIX.txt");
	strcpy(c,str.c_str());
	readFile.open(c,ios::in);
	if(!ifstream(c)){
		cleardevice();
		Display(listNODE,matrix);
		setcolor(BLACK);
		setfillstyle(SOLID_FILL,WHITE);
		rectangle(254,234,760,396);
		floodfill(255,300,BLACK);
		settextstyle(BOLD_FONT, HORIZ_DIR,5);
		setcolor(RED);
		setbkcolor(WHITE);
		outtextxy(300,290,"FILE UNAVAILABLE!!");
		setbkcolor(8);
		delay(2000);
		cleardevice();
		Display(listNODE,matrix);
		return;
	}
	readFile >> matrix[0][0];
	cout << matrix[0][0];
	initMatrix(matrix,matrix[0][0]);
	for (int i=1; i<= matrix[0][0];i++){
		for (int j=1; j<= matrix[0][0]; j++){
			readFile >> matrix[i][j];
		}
	}
	readFile.close();	
	//read node
	int temp=matrix[0][0];
	str = nameFile;
	str.insert(str.length(),"NODE.txt");
	strcpy(c,str.c_str());
	readFile.open(c,ios::in);
	while(!readFile.eof()){
		readFile >> x;
		readFile >> y;
		insertNODE(listNODE,x,y);
		temp--;
		if(temp==0) break;
	}
	readFile.close();

	readFile.close();
	setbkcolor(8);
	cleardevice();
	Display(listNODE,matrix);
}
void HighLightNode(LIST &listNODE,int **&matrix,int key,bool free[]){
	NODE *temp;
	for (NODE *k=listNODE.pFirst; k!=NULL; k=k->next){
		if (k->number == key){
			temp=k;
			setcolor(BLACK);
			setfillstyle(SOLID_FILL,YELLOW);
			circle(k->x,k->y,23);
			floodfill(k->x-10,k->y,BLACK);
		} else if( free[k->number] == true){
			setcolor(BLACK);
			setfillstyle(SOLID_FILL,BLUE);
			circle(k->x,k->y,23);
			floodfill(k->x-10,k->y,BLACK);
		}
}
	
	for (NODE *k=listNODE.pFirst; k!=NULL; k=k->next){
		if(matrix[k->number][temp->number]>0 and free[k->number]==true){
			DrawHighLight(k->x,k->y,temp->x,temp->y,25,matrix[k->number][temp->number]);
		}
	}
	
}
void DFS(LIST &listNODE,int u,int **&matrix, bool free[],string &visit,int &mark){
	free[u]=true;
	char c[20000],temp[20000];
	int clickX,clickY;
	itoa(u,temp,10);
	visit.insert(visit.length(),temp);
	visit.insert(visit.length()," ");
	strcpy(c,visit.c_str());
	setcolor(RED);
	setbkcolor(BLUE);
	outtextxy(757,393,"Visited");
	setbkcolor(8);
	outtextxy(150,522,"                                                ");
	outtextxy(30,520,"Result: ");
	outtextxy(110,520,c);
	setbkcolor(YELLOW);
	itoa(u,c,10);
	outtextxy(757,420,"Current");
	setbkcolor(8);
//	outtextxy(150,550,c);
	
	
	HighLightNode(listNODE,matrix,u,free);
	while(1){
		if(mark==1) break;
		if(mark==2){
			delay(500);
			break;
		}
		getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
		if(isIn(700,579,799,686,clickX,clickY)){
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(701,580,WHITE);
			setfillstyle(SOLID_FILL,8);
			floodfill(701,580,WHITE);
			break;
		}
		if(isIn(801,582,901,686,clickX,clickY)){
			mark=1;
		}
		if(isIn(902,582,990,686,clickX,clickY)){
			mark=2;
		}
		delay(100);
	}
	
	for(int i=1; i<=matrix[0][0]; i++){
		if(matrix[u][i]>0 and free[i]==false){
			DFS(listNODE,i,matrix,free,visit,mark);
		}
	}
	
}
void OutNODE(LIST &l){
	for (NODE *k = l.pFirst; k!=NULL; k=k->next){
		cout << k->number;
	}
}
void BFS(LIST &listNODE,int i,int **&matrix, bool free[],string &visit,int &mark){
	int queue[MAX],d,c,clickX,clickY;
	char temp[1000];
	d=c=0;
	queue[c++] = i;
	free[i]=1;
	HighLightNode(listNODE,matrix,i,free);

		setcolor(WHITE);
		setbkcolor(BLUE);
		outtextxy(757,393,"Visited");
		setcolor(RED);
		setbkcolor(8);
		outtextxy(30,520,"Result: ");
		setbkcolor(8);
		outtextxy(150,522,"                                                ");
					itoa(i,temp,10);
					visit.insert(visit.length(),temp);
					visit.insert(visit.length(),"->");
					strcpy(temp,visit.c_str());
					outtextxy(150,522,temp);
	while(d!=c){
		i=queue[d++];
		for(int j=1; j<=listNODE.amountNODE; j++){
		
			if(free[j]==false and matrix[i][j]>0){
					while(1){
					if(mark==1) break;
					if(mark==2){
						delay(500);
						break;
					}
					getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
					if(isIn(700,579,799,686,clickX,clickY)){
						setfillstyle(SOLID_FILL,YELLOW);
						floodfill(701,580,WHITE);
						setfillstyle(SOLID_FILL,8);
						floodfill(701,580,WHITE);
						break;
					}
					if(isIn(801,582,901,686,clickX,clickY)){
						mark=1;
					}
					if(isIn(902,582,990,686,clickX,clickY)){
						mark=2;
					}
					delay(100);
				}
					setcolor(RED);
					outtextxy(150,522,"                                                ");
					itoa(j,temp,10);
					visit.insert(visit.length(),temp);
					visit.insert(visit.length(),"->");
					strcpy(temp,visit.c_str());
					outtextxy(150,522,temp);
				HighLightNode(listNODE,matrix,j,free);
				queue[c++]=j;
				free[j] = 1;
			}
		}
	}
	setcolor(RED);
	visit.erase(visit.length()-2);
		outtextxy(150,522,"                                                ");
		strcpy(temp,visit.c_str());
		outtextxy(150,522,temp);
	
}
void DFS(LIST &listNODE,int **matrix,int u,int free[],string &str){
	free[u] = 1;
	char temp[50];
	itoa(u,temp,10);
	str.insert(str.length(),temp);
	str.insert(str.length()," ");
	for (int i=1;i<=listNODE.amountNODE; i++){
		if (matrix[u][i]>0 and free[i]==0){
			DFS(listNODE,matrix,i,free,str);
		}
	}
}
void CpyMatrix(int **&temp,int **&matrix,int n){
	initMatrix(temp,n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			temp[i][j] = matrix[i][j];
		}
	}
}
void TPLT(LIST &listNODE,int **&matrix1,int free[]){
	int **matrix;
	CpyMatrix(matrix,matrix1,listNODE.amountNODE);
	
	for(int i=1;i<=listNODE.amountNODE; i++){
		for(int j=1; j<=listNODE.amountNODE; j++){
			if(matrix[i][j]>0) matrix[j][i] = matrix[i][j];
			else if(matrix[j][i] >0) matrix[i][j] = matrix[j][i];
		}
	}	cout << endl;
		for(int i=1;i<=listNODE.amountNODE; i++){
			for(int j=1; j<=listNODE.amountNODE; j++){
				cout << matrix[i][j] << " ";
		}	
		cout << endl;
	}
	setcolor(RED);

	int count=0; char c[100];
	for(int i=1;i<=listNODE.amountNODE; i++){
		if(free[i]==0) {
			string str;
			DFS(listNODE,matrix,i,free,str);
			outtextxy(30,510+(180/listNODE.amountNODE)*count,"TPLT ");
			itoa(count+1,c,10);
			outtextxy(80,510+(180/listNODE.amountNODE)*count,c);
			outtextxy(100,510+(180/listNODE.amountNODE)*count,": ");
			strcpy(c,str.c_str());
			outtextxy(120,510+(180/listNODE.amountNODE)*count,c);
			count++;
		}
	}
}
void Result(int B[],int n,int &d){ 
		char c[50];
		string str;
		 for(int i=n; i>0; i--) {
		 	itoa(B[i],c,10);
		 	str.insert(str.length(),c);
		 	str.insert(str.length()," ");
		 }
		  setcolor(RED);
		  outtextxy(30,510+20*d,"Hamilton ");
		  itoa(d+1,c,10);
		  outtextxy(120,510+20*d,c);
		  outtextxy(130,510+20*d,": ");
		  itoa(B[0],c,10);
		  str.insert(str.length(),c);
		  strcpy(c,str.c_str());
		  outtextxy(145,510+20*d,c);
		  d++; 
		 cout<<endl;
} 
void Hamilton(LIST &l,int **&matrix, int B[], int C[], int i,int &d){ 
		 int j, k; 
		 for(j=1; j<=l.amountNODE; j++){ 
			  if(matrix[B[i-1]][j]!=0 && C[j]==0){ 
					   B[i]=j; C[j]=1; 	
					   if(i<l.amountNODE) Hamilton(l,matrix,B, C, i+1,d); 
					   else if(B[i]==B[0]) Result(B,l.amountNODE,d); 
					   C[j]=0; 
			  } 
		 } 
} 
//EulerCycle
int KtraDoThiEuler(int **matrix, int n)
{
	int BBR=0,BBV=0;
      for (int i=1; i<=n;i++)
      {
      		BBR=BBV=0;     
                  for(int j=1;j<=n;j++){
                  	if(i==j) continue;
                              if(matrix[i][j] > 0)       BBV++; // kt bbr = bbv
                              
                              if(matrix[j][i] > 0) 	BBR++;
                          }               
				  if( BBR!=BBV )   return 0;

      }
	 return 1;
}

//euler
void Tim(LIST &l,int **&temp,int u){
		int **matrix;
		CpyMatrix(matrix,temp,l.amountNODE); 
		 int v, x, top, dCE,n=l.amountNODE; 
		 int stack[MAX], CE[MAX]; 
		 top=1;
		 stack[top]=u;
		 dCE=0; 
		 do { 
		  v = stack[top];
		  x=1; 
		  while (x<=n && matrix[v][x]==0) 
		   x++; 
		  if (x>n) { 
		   dCE++;
		   CE[dCE]=v;
		   top--; 
		  } 
		  else { 
		   top++; 
		   stack[top]=x; 
		   matrix[v][x]=0;
		  } 
		 } while(top!=0); 
		 cleardevice();
		 Display(l,temp);
		 setcolor(RED);
		  outtextxy(30,510,"Chu trinh Euler: ");
		  string str; char c[50];
		 for(x=dCE; x>0; x--) {
		 	itoa(CE[x],c,10);
		 	str.insert(str.length(),c);
		 	str.insert(str.length()," ");
		 }
		 strcpy(c,str.c_str());
		 outtextxy(230,510,c);
		  
} 

// thuat toan Dijkstra
NODE *TimNODE(LIST &l,int key){
	for(NODE *k=l.pFirst; k!=NULL; k=k->next){
		if(k->number == key) return k;
	}
}
void Dijkstra(LIST &l,int **&matrix, int n, int D, int C,int &mark) {
  bool DanhDau[MAX];
  int clickX,clickY;
  int Nhan[MAX], Truoc[MAX], XP, min,**A,j,i;
  CpyMatrix(A,matrix,l.amountNODE);
  for( i=1; i<=n; i++){
        Nhan[i] = MAX;
        DanhDau[i] = false;
        Truoc[i] = D;
  }
  Nhan[D] = 0;
  DanhDau[D] = true;
  XP = D;
  
  while(XP != C){
       for(j=1; j<=n; j++)
          if(A[XP][j]>0 && Nhan[j]>A[XP][j]+Nhan[XP] && DanhDau[j]==false) {
              Nhan[j] = A[XP][j]+Nhan[XP];
              Truoc[j] = XP;
          }
          if(min==MAX){
          	setcolor(RED);
          	outtextxy(30,510, "Khong co duong di");
          	return;
          }
          min = MAX;
        for(j = 1; j<=n; j++)
               if(min>Nhan[j]&& DanhDau[j]==false){
                      min = Nhan[j];
                      XP = j;
                      
                   	while(1){
					if(mark==1) break;
					if(mark==2){
						delay(500);
						break;
					}
					getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
					if(isIn(700,579,799,686,clickX,clickY)){
						setfillstyle(SOLID_FILL,YELLOW);
						floodfill(701,580,WHITE);
						setfillstyle(SOLID_FILL,8);
						floodfill(701,580,WHITE);
						break;
					}
					if(isIn(801,582,901,686,clickX,clickY)){
						mark=1;
					}
					if(isIn(902,582,990,686,clickX,clickY)){
						mark=2;
					}
					delay(100);
				}
                      HighLightNode(l,A,XP,DanhDau);
              }
        DanhDau[XP] = true;
}
   string str;
    char c[1000]; NODE *tmp1 = new NODE,*tmp2 = new NODE;
  	cleardevice();
  	Display(l,matrix);
    itoa(C,c,10);
    str.insert(str.length(),c);
     str.insert(str.length(),"<-");
	itoa(Truoc[C],c,10);
	str.insert(str.length(),c);
	str.insert(str.length(),"<-");
	
	tmp1 = TimNODE(l,C);
	tmp2 = TimNODE(l,Truoc[C]);
	DrawHighLight1(tmp2->x,tmp2->y,tmp1->x,tmp1->y,25,matrix[tmp2->number][tmp1->number]);

	
    i = Truoc[C];
    int tempI=i;
    while(i!=D){
          i = Truoc[i];
        itoa(i,c,10);
        str.insert(str.length(),c);
        str.insert(str.length(),"<-");
        tmp1 = TimNODE(l,tempI);
		tmp2 = TimNODE(l,i);
		setcolor(RED);
		DrawHighLight1(tmp2->x,tmp2->y,tmp1->x,tmp1->y,25,matrix[tmp2->number][tmp1->number]);
		tempI=i;
      }
      settextstyle(8,HORIZ_DIR,3);
      setcolor(RED);
      str.erase(str.length()-2);
      outtextxy(30,510,"Path: ");
      strcpy(c,str.c_str());
      outtextxy(100,510,c);
     

}

int main(){
	initwindow(1000,700);
x:	setbkcolor(8);
	cleardevice();

	int clickX,clickY;
	LIST listNODE;
	LISTFILE listFILE;
	ListFile(listFILE);
	int **matrix;
	initMatrix(matrix,0);
	Display(listNODE,matrix);
	
//	ThuocDo();


	//bootom
	while(1){
		getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
		if(isIn(700,500,800,579,clickX,clickY)){
			setfillstyle(SOLID_FILL,YELLOW);
			rectangle(700,500,800,580);	
			setlinestyle(0,1,4);
			circle(750,540,20);
			floodfill(701,502,WHITE);
			floodfill(750,540,WHITE);
			settextstyle(8,HORIZ_DIR,1);
			setbkcolor(YELLOW);
			outtextxy(745,530,"1");
			createNODE(listNODE,matrix,clickX,clickY);
			setbkcolor(8);
			cleardevice();
			Display(listNODE,matrix);
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if(isIn(801,501,899,579,clickX,clickY)){
			linkNODE(listNODE,matrix,clickX,clickY);	
			setfillstyle(SOLID_FILL,8);
			cleardevice();
			Display(listNODE,matrix);
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if(isIn(901,501,991,579,clickX,clickY)){
			MoveCircle(listNODE,matrix,clickX,clickY);
			clearmouseclick(WM_LBUTTONDOWN);
			cleardevice();
			Display(listNODE,matrix);
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if(isIn(700,1,798,77,clickX,clickY)){
			goto x;
		}
		
		//save
		if(isIn(801,1,899,78,clickX,clickY)){
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(clickX,clickY,WHITE);
			SaveFile(listNODE,listFILE,matrix);
			clearmouseclick(WM_LBUTTONDOWN);
			Display(listNODE,matrix);
		}
		//load
		if(isIn(901,1,990,78,clickX,clickY)){
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(clickX,clickY,WHITE);
			LoadFile(listNODE,listFILE,matrix);
			clearmouseclick(WM_LBUTTONDOWN);
			Display(listNODE,matrix);
		}
		//delete
		if(isInCircle(listNODE,clickX,clickY)){
			int key=isInCircle(listNODE,clickX,clickY);
			char c;
			for(NODE *k = listNODE.pFirst; k!=NULL; k=k->next){
				if (k->number == key){
					setfillstyle(SOLID_FILL,YELLOW);
					setcolor(BLACK);
					circle(k->x,k->y,23);
					floodfill(k->x-10,k->y,BLACK);
					break;
				}
			}
			while(1){
				if(ismouseclick(WM_LBUTTONDOWN)) break;
				if(kbhit()){
					c = getch();
					c = getch();
					if ( (int) c == 83 ) {
						DeleteNODE(listNODE,key,matrix);
						cleardevice();
						break;
					}
				}
				delay(100);
			}
			cleardevice();
			Display(listNODE,matrix);
			clearmouseclick(WM_LBUTTONDOWN);
		}
	//	ThuocDo();
		//demo dfs
		if(isIn(1,1,97,78,clickX,clickY)){
			if(listNODE.amountNODE==0) continue;
			char c[2000];
			int key,mark=0;
			bool free[listNODE.amountNODE+2];
			for(int i=0; i<=listNODE.amountNODE;i++) free[i]=false;
			string visit,result;	
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(clickX,clickY,WHITE);
			while(1){
			getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
			if(isIn(1,1,97,78,clickX,clickY)) break;
			if(isInCircle(listNODE,clickX,clickY)) {
			key = isInCircle(listNODE,clickX,clickY);
			//demo
			DFS(listNODE,key,matrix,free,visit,mark);
		
			while(1)
				{settextstyle(BOLD_FONT, HORIZ_DIR,2);
				setcolor(RED);
				outtextxy(159,648,"Press DFS button to the end!!" );
				delay(500);
				outtextxy(150,648,"                               ");
				delay(300);
				getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
				if(isIn(1,1,97,78,clickX,clickY)) break;
				delay(300);
			}
			break;
		}
			delay(100);
			}
			cleardevice();
			clearmouseclick(WM_LBUTTONDOWN);
			Display(listNODE,matrix);
		}
		//bfs
	//	ThuocDo();
		if(isIn(101,1,197,78,clickX,clickY)){
			if(listNODE.amountNODE==0) continue;
			char c[2000];
			int key,mark=0;
			bool free[listNODE.amountNODE+2];
			for(int i=0; i<=listNODE.amountNODE;i++) free[i]=false;
			string visit,result;	
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(clickX,clickY,WHITE);
			while(1){
			getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
			if(isInCircle(listNODE,clickX,clickY)) {
			key = isInCircle(listNODE,clickX,clickY);
			//demo
			if(isIn(101,1,197,78,clickX,clickY)) break;
			BFS(listNODE,key,matrix,free,visit,mark);
			while(1)
				{settextstyle(BOLD_FONT, HORIZ_DIR,2);
				setcolor(RED);
				outtextxy(159,648,"Press BFS button to the end!!" );
				delay(500);
				outtextxy(150,648,"                               ");
				delay(300);
				getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
				if(isIn(101,1,197,78,clickX,clickY)) break;
				delay(300);
			}
			break;
		}
			delay(100);
			}
			cleardevice();
			clearmouseclick(WM_LBUTTONDOWN);
			Display(listNODE,matrix);
			
		}
		//tplt
		if(isIn(202,1,298,77,clickX,clickY)){
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(clickX,clickY,WHITE);
			int free[listNODE.amountNODE+1];
			for(int i=1; i<=listNODE.amountNODE; i++){
				free[i] = 0;
			}
			TPLT(listNODE,matrix,free);
			while(1){
				if(ismouseclick(WM_LBUTTONDOWN)) {
					cleardevice();
					Display(listNODE,matrix);
					clearmouseclick(WM_LBUTTONDOWN);
					break;
				}
				delay(100);
			}
		}
		
		//demo hemintol
		if(isIn(501,1,599,78,clickX,clickY)){
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(clickX,clickY,WHITE);
			int i=1, d=0, B[listNODE.amountNODE], C[listNODE.amountNODE];
			B[0] = 1;
			if(listNODE.amountNODE>0){
			for(int i=1; i<=listNODE.amountNODE; i++) C[i] = 0;
			Hamilton(listNODE,matrix,B,C,i,d);
			setcolor(RED);
			if (d==0) outtextxy(30,510,"Khong co duong di Hamilton") ;
			while(1){
				getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
				if(isIn(501,1,599,78,clickX,clickY)) break;
				delay(200);
			}
			if(!KtraDoThiEuler(matrix,listNODE.amountNODE)){
				cleardevice();
				Display(listNODE,matrix);
				outtextxy(30,510, "Khong co chu trinh Euler");
			} else{
				int CE[listNODE.amountNODE*2];
				int nCE=0;
				Tim(listNODE,matrix,1);
		}
			setcolor(RED);
		
			while(1){
				if(ismouseclick(WM_LBUTTONDOWN)) {
					cleardevice();
					Display(listNODE,matrix);
					clearmouseclick(WM_LBUTTONDOWN);
					break;
				}
				delay(200);
			}
			} else {
				cleardevice();
				Display(listNODE,matrix);
			}
		}
		//djsktra
		if(isIn(302,1,399,78,clickX,clickY)){
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(clickX,clickY,WHITE);
			setfillstyle(SOLID_FILL,RED);
			int D,C;
			while(1){
				getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
				if(isInCircle(listNODE,clickX,clickY)){
					D = isInCircle(listNODE,clickX,clickY);
					for(NODE *k=listNODE.pFirst; k!=NULL; k=k->next){
						if(k->number == D){
							setcolor(BLACK);
							circle(k->x,k->y,23);
							floodfill(k->x-7,k->y,BLACK);
						}
					}
					break;
			}
			delay(200);
		}
			clearmouseclick(WM_LBUTTONDOWN);
			setfillstyle(SOLID_FILL,GREEN);
			while(1){
				getmouseclick(WM_LBUTTONDOWN,clickX,clickY);
				if(isInCircle(listNODE,clickX,clickY) and D!=isInCircle(listNODE,clickX,clickY)){
					C = isInCircle(listNODE,clickX,clickY);
					for(NODE *k=listNODE.pFirst; k!=NULL; k=k->next){
						if(k->number == C){
							setcolor(BLACK);
							circle(k->x,k->y,23);
							floodfill(k->x-7,k->y,BLACK);
							break;
						}
					}
		
			break;
		}
		delay(200);
	}
		
			int mark=0;
			clearmouseclick(WM_LBUTTONDOWN);
			Dijkstra(listNODE,matrix,listNODE.amountNODE,D,C,mark);
			while(1){
				if(ismouseclick(WM_LBUTTONDOWN)) {
					cleardevice();
					Display(listNODE,matrix);
						clearmouseclick(WM_LBUTTONDOWN);
					break;
				}
				delay(100);
			}
			
		
	}
		delay(200);
	}
	
	
	getch();
	return 0;
}


