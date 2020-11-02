/*
	File        : UTIL.cpp
	Description : Password creating
	Author      : Dipin Khadka
	Created     : 17 Jan 2012
	------------------------------------------------------------------
	Date          Version Author Description
	12 Jan 2011 	1.01    Dipin  Added logic to display styles
	17 Jan 2011 	1.02    Dipin  Added logic to password, string and
															 integer creation
*/
void initgraphics()
{
/*
		Description : Function to initialise graphics
		Author      : Dipin Khadka
		Created     : 12 Jan 2012
*/
 d=DETECT;
 initgraph(&d,&m,"c:\\tc\\bgi");

}
void border()
{
/*
		Description : For border each page
		Author      : Dipin Khadka
		Created     : 12 Jan 2012
*/
	setcolor(WHITE);
	rectangle(2,2,mx-2,my-2);
	setcolor(RED);
	rectangle(4,4,mx-4,my-4);
	setcolor(WHITE);
	rectangle(6,6,mx-6,my-6);

}
void coverBorder()
{
/*
		Description : For border main page
		Author      : Dipin Khadka
		Created     : 12 Jan 2012
*/
	setcolor(WHITE);
	rectangle(140,2,500,400);
	setcolor(RED);
	rectangle(142,4,498,398);
	setcolor(WHITE);
	rectangle(144,6,496,396);
	setcolor(WHITE);
	line(144,100,496,100);
	setcolor(RED);
	line(144,102,496,102);
	setcolor(WHITE);
	line(144,104,496,104);
}
void displayIntro()
{
/*
		Description : Function to display introduction
		Author      : Dipin Khadka
		Created     : 12 Jan 2012
*/
	char *name = "GREEN VALLEY DEPARTMENTAL STORE";
	char *add  = "HATTIGAUDA, KATHMANDU";
	char *estd = "ESTD. 2010";

	gotoxy(25,3); cout<<name;
	gotoxy(30,4); cout<<add;
	gotoxy(35,5); cout<<estd;

}
void members()
{
/*
		Description : Function to display members name
		Author      : Dipin Khadka
		Created     : 12 Jan 2012
*/
	char *dBy  = "DESIGNED BY";
	char *name2= "DIPIN KHADKA";
	char *name1= "AMAN MANANDHAR";
	char *name3= "RAJINDRA PRASAD KAFLE";
	char *name4= "SHREEKANT CHAUDHARY";

	gotoxy(36,19); cout<<dBy;
	gotoxy(35,21); cout<<name1;
	gotoxy(36,22); cout<<name2;
	gotoxy(31,23); cout<<name3;
	gotoxy(32,24); cout<<name4;

}

void greet()
{
/*
		Description : Function to display greeting
		Author      : Dipin Khadka
		Created     : 12 Jan 2012
*/
	char *greet= "WELCOME TO THIS SOFTWARE...";
	int i = 0;
	cleardevice();
	coverBorder();
	displayIntro();

	//for displaying greeting
	for(i=0;i<strlen(greet);i++)
	{
		delay(200);
		gotoxy(29+i,15); cout<<greet[i];
	}
	sleep(1); //after 1 seconds screen will be disappear
}
void terminateScreen()
{
/*
		Description : Function to display colsing message
		Author      : Dipin Khadka
		Created     : 12 Jan 2012
*/

	int i =0;
	char *greet = "THANK YOU VISIT AGAIN...";
	cleardevice();
	coverBorder();
	displayIntro();

	// for displaying greeting
	for(i=0;i<strlen(greet);i++)
	{
		delay(200);
		gotoxy(27+i,15); cout<<greet[i];
	}
	sleep(2);

}
void getPassword(int x, int y, int max, char userPassword[30])
{
/*
	Description : Password creating
	Author      : Dipin Khadka
	Created     : 17 Jan 2012
*/

	char ch   = NULL;
	int  i    = 0;
	int count = 0;

	while(1)
	{
		gotoxy(x,y);cout<<"[";
		gotoxy(x+1+i,y); cout<<"]";
		ch = getch();
		if(ch == 13)  /* for enter key  */
		{
			break;
		}
		if(ch == 8)   /* for backspace  */
		{
			gotoxy(x+i,y); cout<<" ";
			gotoxy(x+i+1,y); cout<<" ";
			if(i>0)
			{
				i--;
				count--;
			}
		}
	 else	if(i<max) /*for accepting characters until maximum level is reached*/
		{
			userPassword[i] = ch;
			i++;
			gotoxy(x+i,y); cout<<"*";
			count++;
		}
	}/* end of while*/
	if(count < 6) /* for displaying warning if charecters not met minimum level */
	{
		gotoxy(36,19); cout<<"                         ";
		gotoxy(35,21); cout<<"                         ";
		gotoxy(36,22); cout<<"                         ";
		gotoxy(31,23); cout<<"                         ";
		gotoxy(32,24); cout<<"                         ";
		gotoxy(20,y+7); cout<<"Password should be at least 6 character..";
		sleep(2);
		gotoxy(20,y+7); cout<<"                                         ";
	}/* end of if*/
	userPassword[i] = NULL;
	gotoxy(x,y);cout<<" ";
	gotoxy(x+1+i,y); cout<<" ";
}/* end of getPassword*/

void getString(int x, int y, int max, char str[30])
{
/*
	Description : String creating
	Author      : Dipin Khadka
	Created     : 17 Jan 2012
*/

	char ch   = NULL;
	int  i    = 0;
	int count = 0;

	while(1)
	{
		while(1)
		{
			gotoxy(x,y);cout<<"[";
			gotoxy(x+1+i,y); cout<<"]";
			ch = getch();
			if(ch == 13)  /* for enter key  */
			{
				break;
			}
			if(ch == 8)   /* for backspace  */
			{
				gotoxy(x+i,y); cout<<" ";
				gotoxy(x+i+1,y); cout<<" ";
				if(i>0)
				{
					i--;
					count--;
				}
			}
		 else	if(i<max) /*for accepting characters until maximum level is reached*/
			{
				str[i] = ch;
				i++;
				gotoxy(x+i,y); cout<<ch;
				count++;
			}
		}/* end of while*/
		str[i] = NULL;
		if(strlen(str)!= 0 )
			break;
	}
	gotoxy(x,y);cout<<" ";
	gotoxy(x+1+i,y); cout<<" ";
}/* end of getString*/

int getInt(int x, int y, int max)
{
/*
	Description : Integer creating
	Author      : Dipin Khadka
	Created     : 17 Jan 2012
*/

	char str[30];
	int temp  = 0;
	char ch   = NULL;
	int  i    = 0;
	int count = 0;

	while(1)
	{
		while(1)
		{
			while(1)
			{
				gotoxy(x,y);cout<<"[";
				gotoxy(x+1+i,y); cout<<"]";
				ch = getch();
				if((ch >=48 && ch <= 57) || ch == 13 || ch == 8)
					break;
			}/* end of 1 while*/
			if(ch == 13)  /* for enter key  */
			{
				break;
			}
			if(ch == 8)   /* for backspace  */
			{
				gotoxy(x+i,y); cout<<" ";
				gotoxy(x+i+1,y); cout<<" ";
				if(i>0)
				{
					i--;
					count--;
				}
			}
			else if(i<max) /*for accepting characters until maximum level is reached*/
			{
				str[i] = ch;
				i++;
				gotoxy(x+i,y); cout<<ch;
				count++;
			}
		}/* end of 2nd while*/

		str[i] = NULL;
		temp   = atoi(str); /* converts the string into integer and returns it*/

		if(temp != 0 )
			break;
	}/*end of 3rd while*/

	gotoxy(x,y);cout<<" ";
	gotoxy(x+1+i,y); cout<<" ";
	return temp;

}/* end of getInt*/
void getCursor(int x, int y, int range)
{
/*
	Description : Bracket creating for indication
	Author      : Dipin Khadka
	Created     : 17 Jan 2012
*/
	gotoxy(x,y); cout<<"[";
	gotoxy(x+range,y); cout<<"]";
}
void removeCursor(int x, int y, int range)
{
/*
	Description : Bracket removing
	Author      : Dipin Khadka
	Created     : 17 Jan 2012
*/
	gotoxy(x,y); cout<<" ";
	gotoxy(x+range,y); cout<<" ";
}


