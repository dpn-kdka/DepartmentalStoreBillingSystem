/*
	File        : DMBS.cpp
	Description : Main working plate from
	Author      : Dipin Khadka
	Created     : 08 Jan 2012
	-----------------------------------------------------------------------
	Date          Version Author Description
	10 Jan 2012 	1.01    Dipin  Class created
	12 Jan 2012   1.02		Dipin	 Added logic to write and display searched
															 product record
	13 Jan 2012   1.03 		Dipin	 Added logic to modify and delete record
	14 Jan 2012		1.04		Dipin  Added logic to show product menu and placing
															 order
	16 Jan 2012   1.05		Dipin	 Added logic to display main, admin menu and
															 to check unique product number
*/

#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<graphics.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>

#include"common.cpp"
#include"util.cpp"
class product
{
	int pno;
	char name[50];
	double price,qty,dis;
	public:
	void takeProductDetail();
	void showProduct();
	void createProduct();
	void displayQueryProduct();
	void modifyProduct();
	void deleteProduct();
	void showProductMenu();
	void placeOrder();
	int checkUniquePno(int no);

};                         //class ends here
class menu
{
	public:
	void adminMenu();
};
/* global declaration for stream object and objects */
fstream fp;
product pr;
menu mn;

int product::checkUniquePno(int no)
{
/*
	Description : For checking unique product number
	Author      : Dipin Khadka
	Created     : 16 Jan 2012
*/
	int  flag  = 0;

	fp.open("Shop.dat",ios::in|ios::binary);
	if(!fp)
	{
		return -1;
	}
	else
	{
		while(fp.read((char*)&pr,sizeof(product)))
		{
			if(pno == no)
			{
				flag = 1;
				break;
			}
		}
	}/* end of else */
	fp.close();
	return flag;
}
void product::takeProductDetail()
{
	/*
		Description : For creating product
		Author      : Dipin Khadka
		Created     : 10 Jan 2012
	*/
		int flag = 0;
		int num  = 0;
		gotoxy(3,3); cout<<"\tEnter Products Details";
		gotoxy(3,4); cout<<"\t_______________________";
		gotoxy(3,5); cout<<"Product Number   : ";
		while(1)
		{
			num = getInt(21,5,4);
			flag = checkUniquePno(num);
			if(flag == 1)
			{
				gotoxy(3,12); cout<<"Product no must be unique.. Re-enter product no: ";
				sleep(2); /* statement will be displayed
								 at screen only for 2 seconds*/
				gotoxy(3,12); cout<<"                                                 ";
				gotoxy(21,5); cout<<"      ";
				gotoxy(21,5);
			}
			else if(flag == -1)
			{
				gotoxy(3,12); cout<<"This is the first record...";
				sleep(2);
				gotoxy(3,12); cout<<"                           ";
				break;
			}
			else if(flag == 0)
			{
				break;
			}
		} /* end of while*/
		pno = num;
		gotoxy(3,7);cout<<"Name             : ";
		getString(21,7,25,name);
		gotoxy(3,9);cout<<"Price            : ";
		price=getInt(21,9,4);
		gotoxy(3,11);cout<<"Discount Rate(%) : ";
		getCursor(21,11,2);
		gotoxy(22,11);cin>>dis;
		removeCursor(21,11,2);
}

void product::showProduct()
{
/*
		Description : Function to show product
		Author      : Dipin Khadka
		Created     : 12 Jan 2012
*/
		gotoxy(3,7);cout<<"*********************************************";
		gotoxy(3,8);cout<<"                 DETAILS                  ";
		gotoxy(3,9);cout<<"*********************************************";
		gotoxy(3,11);cout<<"PRODUCT NO.                  : "<<pno;
		gotoxy(3,13);cout<<"PRODUCT NAME                 : "<<name;
		gotoxy(3,15);cout<<"PRICE                        : Rs."<<price;
		gotoxy(3,17);cout<<"DISCOUNT RATE(in %)          : "<<dis;
		gotoxy(3,18);cout<<"*********************************************";
}
void product::createProduct()
{
/*
		Description : Function to write in file
		Author      : Dipin Khadka
		Created     : 12 Jan 2012
*/
		char answer = NULL;
		cleardevice();
		border();
		pr.takeProductDetail();
		fp.open("Shop.dat",ios::out|ios::app|ios::binary);
		if(!fp)
		{
			gotoxy(5,5);cout<<"ERROR!!! FILE COULD NOT BE OPEN!!";
			gotoxy(5,7);cout<<"Program is closing ....";
			getch();
			closegraph();
			exit(-1);
		}
		else
		{
			fp.write((char*)&pr,sizeof(product));
			gotoxy(3,17); cout<<"The Product Has Been Created!!";
		}
		fp.close();
		delay(700);
		gotoxy(3,19); cout<<"Would you like to create more products(Y/N)?";
		answer = getch();
		if(answer == 'y' || answer == 'Y')
		{
			pr.takeProductDetail();
		}
		gotoxy(3,19); cout<<"                                            ";
		gotoxy(3,19); cout<<"Press any key to return to admin menu...";
		getch();
}
void product::displayQueryProduct()
{
/*
		Description : Function to read specific record from file
		Author      : Dipin Khadka
		Created     : 12 Jan 2012
*/

		int num = 0;
		int flag = 0;
		char answer = NULL;
		cleardevice();
		border();

		fp.open("Shop.dat",ios::in|ios::binary);
		if(!fp)
		{
			 gotoxy(5,5);cout<<"ERROR!!! FILE COULD NOT BE OPEN!!";
			 gotoxy(5,7);cout<<"Program is closing ....";
			 getch();
			 closegraph();
			 exit(-1);
		}
		gotoxy(3,2);cout<<"_____________";
		gotoxy(3,3);cout<<"Query product";
		gotoxy(3,4);cout<<"_____________";
		getCursor(32,6,4);
		gotoxy(3,6);cout<<"Please Enter The Product No.:";
		gotoxy(33,6);cin>>num;
		while(fp.read((char*)&pr,sizeof(product)))
		{
			if(pno==num)
			{
				showProduct();
				flag=1;
			}
		}
		fp.close();
		if(flag==0)
		{
			gotoxy(3,13);cout<<"Record not exist!!";
		}
		delay(700);
		gotoxy(3,20); cout<<"Would you like to query more products(Y/N)?";
		answer = getch();
		if(answer == 'y' || answer == 'Y')
		{
				displayQueryProduct();
		}
		delay(200);
		gotoxy(3,20); cout<<"                                            ";
		gotoxy(3,20); cout<<"Press any key to return to admin menu...";
		getch();

}

void product::modifyProduct()
{
/*
		Description : Function to modify record of file
		Author      : Dipin Khadka
		Created     : 13 Jan 2012
*/

		int num = 0;
		int flag = 0;
		char answer = NULL;
		cleardevice();
		border();

		fp.open("Shop.dat",ios::in|ios::out|ios::binary);
		if(!fp)
		{
			 gotoxy(5,5);cout<<"ERROR!!! FILE COULD NOT BE OPEN!!";
			 gotoxy(5,7);cout<<"Program is closing ....";
			 getch();
			 closegraph();
			 exit(-1);
		}
		gotoxy(3,2);cout<<"______________";
		gotoxy(3,3);cout<<"Modify Product";
		gotoxy(3,4);cout<<"______________";
		gotoxy(3,6);cout<<"Please Enter The Product No. to modify:";
		getCursor(43,6,4);
		gotoxy(44,6);cin>>num;
		while(fp.read((char*)&pr,sizeof(product)) && flag == 0)
		{
			if(pno==num)
			 {
					showProduct();
					gotoxy(3,20);cout<<"Press any key for modify this record...";
					getch();
					cleardevice();
					border();
					gotoxy(3,4); cout<<"\tEnter Products Details";
					gotoxy(3,5); cout<<"\t_______________________";
					gotoxy(3,7);cout<<"Name             : ";
					getString(21,7,25,name);
					gotoxy(3,9);cout<<"Price            : ";
					price=getInt(21,9,4);
					gotoxy(3,11);cout<<"Discount Rate(%) : ";
					getCursor(21,11,2);
					gotoxy(22,11);cin>>dis;
					removeCursor(21,11,2);
					int pos=-1*sizeof(pr);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&pr,sizeof(product));
					gotoxy(3,13);cout<<" Record Updated!!";
					flag=1;
				}
		}
		fp.close();
		if(flag == 0)
		{
			gotoxy(3,13);cout<<" Record Not Found!! ";
		}
		delay(700);
		gotoxy(3,17); cout<<"Would you like to modify more products(Y/N)?";
		answer = getch();
		if(answer == 'y' || answer == 'Y')
		{
			modifyProduct();
		}
		delay(200);
		gotoxy(3,17); cout<<"Press any key to return to admin menu...     ";
		getch();
}

void product::deleteProduct()
{
/*
		Description : Function to delete record of file
		Author      : Dipin Khadka
		Created     : 13 Jan 2012
*/
		int no = 0;
		int flag = 0;
		char answer = NULL;
		cleardevice();
		border();
		gotoxy(3,2);cout<<"_____________";
		gotoxy(3,3);cout<<"Delete Record";
		gotoxy(3,4);cout<<"_____________";
		getCursor(67,6,4);
		gotoxy(3,6);cout<<"Please Enter The product no. of The Product You Want To Delete:";
		gotoxy(68,6);cin>>no;
		fp.open("Shop.dat",ios::in|ios::out|ios::binary);
		fstream fp2;
		fp2.open("Temp.dat",ios::out|ios::binary);
		fp.seekg(0,ios::beg);
		while(fp.read((char*)&pr,sizeof(product)))
		{
			if(pno==no)
			{
				flag = 1;
				showProduct();
				gotoxy(3,20); cout<<"Are you sure to delete this record(Y/N)?";
				answer = getch();

				if(answer == 'y' || answer == 'Y')/* checks yes or no*/
				{
					flag = 2;
					continue;
				}
			}
			fp2.write((char*)&pr,sizeof(product));
		}
		fp2.close();
		fp.close();
		remove("Shop.dat");
		rename("Temp.dat","Shop.dat");

		cleardevice();
		border();
		if(flag == 1)
		{
			gotoxy(3,10); cout<<"Record has not been deleted!!";
		}
		else if(flag == 2)
		{
			gotoxy(3,10); cout<<"Record deleted!!";
		}
		else if(flag == 0)
		{
			gotoxy(3,10); cout<<"Sorry!!! No any record found!!";
		}
		delay(400);
		gotoxy(3,15); cout<<"Would you like to delete more records(Y/N)?";
		answer = getch();
		if(answer == 'y' || answer == 'Y')
		{
			deleteProduct();
		}
}

void product::showProductMenu()
{
/*
		Description : Function to display record from file
		Author      : Dipin Khadka
		Created     : 14 Jan 2012
*/
		 int i = 2;
		 int flag = 0; 
		 cleardevice();
		 border();
		 fp.open("Shop.dat",ios::in|ios::binary);
		 if(!fp)
		 {
			 gotoxy(5,5);cout<<"ERROR!!! FILE COULD NOT BE OPEN!!";
			 gotoxy(5,7);cout<<"Go To Admin Menu to create File";
			 gotoxy(5,9);cout<<"Program is closing ....";
			 getch();
			 closegraph();
			 exit(-1);
		 }
		 gotoxy(3,2);cout<<"____________";
		 gotoxy(3,3);cout<<"PRODUCT MENU";
		 gotoxy(3,4);cout<<"____________";
		 gotoxy(3,6);cout<<"P.NO.\t\tNAME\t\t\tPRICE\t\tDISCOUNT RATE";
		 gotoxy(3,7);cout<<"====================================================================";

		 while(fp.read((char*)&pr,sizeof(product)))
		 {
				flag =1;
				gotoxy(4,7+i);  cout<<pno;
				gotoxy(17,7+i); cout<<name;
				gotoxy(41,7+i); cout<<"Rs."<<price;
				gotoxy(60,7+i); cout<<dis<<"%"<<endl;
				i=i+2;
				if(i%16 == 0)
				{
						i=2;
						gotoxy(3,24); cout<<"Press any key for more...";
						getch();
						cleardevice();
						border();
						gotoxy(3,2);cout<<"____________";
						gotoxy(3,3);cout<<"PRODUCT MENU";
						gotoxy(3,4);cout<<"____________";
						gotoxy(3,6);cout<<"P.NO.\t\tNAME\t\t\tPRICE\t\tDISCOUNT RATE";
						gotoxy(3,7);cout<<"====================================================================";
				}
			}/*end of while */
			fp.close();
			if(flag == 0)
			{
				gotoxy(3,12); cout<<"Sorry!!! No any record exists..";
			}
			gotoxy(3,24);cout<<"                         ";
			gotoxy(3,24);cout<<"Press any key to return to admin menu..";
			getch();
}

void product::placeOrder()
{
/*
		Description : Function to place order and generating bill for Products
		Author      : Dipin Khadka
		Created     : 14 Jan 2012
*/
		int  order_arr[50], quan[50];
		int i = 0;
		int n = 0;
		int num = 0;
		int flag = 0;
		int count = 0;
		float amount = 0;
		float amtAfterDis = 0;
		float total = 0;
		char ch = NULL;

		cleardevice();
		border();
		gotoxy(3,3);cout<<"****************************";
		gotoxy(3,4);cout<<"      PLACE YOUR ORDER";
		gotoxy(3,5);cout<<"****************************";
		do
		{
			if(count<5)
			{
				gotoxy(3,7); cout<<"Enter The Product NO. : ";
				while(1)
				{
					num = getInt(27,7,4);
					flag = checkUniquePno(num);
					if(flag == 0)
					{
						gotoxy(3,12); cout<<"Sorry!! This product no. is not available...";
						sleep(2); /* statement will be displayed
								 at screen only for 2 seconds*/
						gotoxy(3,12); cout<<"                                            ";
						gotoxy(27,7); cout<<"      ";
						gotoxy(27,7);
					}
					else if(flag == 1 || flag == -1)
					{
						break;
					}
				}
				order_arr[i] = num;
				gotoxy(3,9); cout<<"Quantity in number    : ";
				quan[i] = getInt(27,9,4);
				i++;
				count++;
			}
			else
			{
				gotoxy(3,15);cout<<"Only 5 items at a time can be ordered!!";
				ch = 'n';
				goto afterCinCh;
			}
			delay(200);
			gotoxy(3,15);cout<<"Thank You For Placing The Order!!         ";
			getch();
			gotoxy(3,17);cout<<"Do You Want To Order Another Product(y/n)?";
			cin>>ch;
			afterCinCh:
			if(ch == 'y' || ch == 'Y')
			{
				cleardevice();
				border();
				gotoxy(3,3);cout<<"****************************";
				gotoxy(3,4);cout<<"      PLACE YOUR ORDER";
				gotoxy(3,5);cout<<"****************************";
			}
		}while(ch=='y' ||ch=='Y');

		cleardevice();
		border();
		gotoxy(3,3);cout<<"*********************************************************";
		gotoxy(3,4);cout<<"                         INVOICE ";
		gotoxy(3,5);cout<<"*********************************************************";
		gotoxy(3,7);cout<<"Pr No.  Pr Name        Quantity  Price       Amount     Amt After Dis";
		gotoxy(3,8);cout<<"_____________________________________________________________________________";
		for(int x=0;x<=i;x++)
		{
			fp.open("Shop.dat",ios::in|ios::binary);
			fp.read((char*)&pr,sizeof(product));
			while(!fp.eof())
			{
				if(pno==order_arr[x])
				{
					amount = price*quan[x];
					amtAfterDis = amount-(amount*dis/100);
					gotoxy(4,10+n);  cout<<order_arr[x];
					gotoxy(11,10+n); cout<<name;
					gotoxy(27,10+n); cout<<quan[x];
					gotoxy(36,10+n); cout<<"Rs."<<price;
					gotoxy(48,10+n); cout<<"Rs."<<amount;
					gotoxy(59,10+n); cout<<"Rs."<<amtAfterDis;
					total=total + amtAfterDis;
					n=n+2;
				}
				fp.read((char*)&pr,sizeof(product));
			}

		 fp.close();
	 }
	 gotoxy(3,10+n); cout<<"\t\t_____________";
	 gotoxy(3,11+n); cout<<"\t\tTOTAL AMOUNT = Rs."<<total;
	 gotoxy(3,12+n); cout<<"\t\t_____________";
	 getch();
}
void menu::adminMenu()
{
/*
		Description : Adminstrator menu function
		Author      : Dipin Khadka
		Created     : 16 Jan 2012
*/
	char choice2 = NULL;
	do
	{
		cleardevice();
		coverBorder();
		displayIntro();
		rectangle(180,127,330,162);
		gotoxy(28,10);cout<<"ADMIN MENU";
		gotoxy(23,12);cout<<"1.CREATE PRODUCT";
		gotoxy(23,14);cout<<"2.VIEW PRODUCT MENU";
		gotoxy(23,16);cout<<"3.QUERY ";
		gotoxy(23,18);cout<<"4.MODIFY PRODUCT";
		gotoxy(23,20);cout<<"5.DELETE PRODUCT";
		gotoxy(23,22);cout<<"6.BACK TO MAIN MENU";
		getCursor(57,24,2);
		gotoxy(23,24);cout<<"Please Enter Your Choice (1-6): ";
		gotoxy(58,24);cin>>choice2;
		switch(choice2)
		{
			case '1':
								pr.createProduct();
								break;
			case '2':
								pr.showProductMenu();
								break;
			case '3':
								pr.displayQueryProduct();
								break;
			case '4':
								pr.modifyProduct();
								break;
			case '5':
								pr.deleteProduct();
								break;
			case '6':
							break;

			default:cout<<"\a";

		}
	}while(choice2!='6');
}
void main()
{
/*
		Description : Main function of the program
		Author      : Dipin Khadka
		Created     : 10 Jan 2012
*/
	clrscr();
	char userName[20];
	char userPassword[20];
	char fileUserName[20] = "admin";
	char filePassword[20] = "password";
	int  attempt          = 3;
	char choice = NULL;
	initgraphics();
	highvideo();
	do
	{
		starting:
		cleardevice();
		coverBorder();
		displayIntro();
		members();
		rectangle(410,170,230,130);
		gotoxy(34,10);cout<<"LOGIN SECTION";
		rectangle(410,250,230,180);
		gotoxy(31,13);cout<<"Admin   : ";
		gotoxy(31,15);cout<<"Password: ";
		getString(40, 13, 9, userName);
		getPassword(40, 15, 9, userPassword);
		if(strcmp(userPassword,filePassword)==0 && strcmp(userName,fileUserName)==0) /* checks the valid password*/
		{
			greet();
			afterLogin:
			attempt = 3;
			cleardevice();
			coverBorder();
			displayIntro();
			rectangle(180,127,330,162);
			gotoxy(28,10); cout<<"MAIN MENU";
			gotoxy(23,12); cout<<"1. CUSTOMER";
			gotoxy(23,14); cout<<"2. ADMINISTRATOR";
			gotoxy(23,16); cout<<"3. EXIT";
			getCursor(57,18,2);
			gotoxy(23,18);cout<<"Please Select Your Option (1-3): ";
			gotoxy(58,18);cin>>choice;
			switch(choice)
			{
				case '1':
									pr.placeOrder();
									goto afterLogin;
				case '2':
									mn.adminMenu();
									goto afterLogin;
				case '3':
									terminateScreen();
									closegraph();
									exit(0);

				default : cout<<"\a";
			}
		}/* end of if */
		else
		{
			gotoxy(36,19); cout<<"                          ";
			gotoxy(35,21); cout<<"                          ";
			gotoxy(36,22); cout<<"                          ";
			gotoxy(31,23); cout<<"                          ";
			gotoxy(32,24); cout<<"                          ";
			if(attempt>1)
			{
				attempt--;
				gotoxy(30,22); cout<<"Please!!! Try again!!!";
				gotoxy(33,23); cout<<"Attempt left:"<<attempt;
				getch();
				gotoxy(33,23); cout<<"                   ";
				goto starting;

			}
			else
			{
				gotoxy(23,22); cout<<"Maximum Number of Attempts Exceeded!!!";
				gotoxy(26,23); cout<<"System is going to shutdown...";
				sleep(3);
				terminateScreen();
				closegraph();
				exit(0);
			}
		}  /*end of else*/
	}while(choice!='3');
}

