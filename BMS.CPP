#include<iostream.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
class seat
{
	int stno;
	char cname[30];
	int c_age;
	int status;
     public:
	seat();
	void stn(int i,int j);
	int retstatus();
	void dispticket();
	void book1(char* name,int age);
	void unbook1();
};
class shows
{
	int hrs;
	int min;
	seat st[5][5];
	int price;
     public:
     shows();
     void init();
     void book2(int a,int b, char* name, int age);
     void unbook2(int a,int b);
     void dispsh1();
     void display();
     void displist();
     void entershow();
     int ret_hrs();
     int ret_min();
};
class movie
{
	char mname[30];
	int numsh;
	shows sh[5];
	char rating[3];
     public:
	int book3(int s,int stno1,char* name,int age);
	int unbook3(int s,int stno1);
	void dispseats(int c);
	void dispmovies();
	void dispsh2();
	void dispbook(int c);
	char* retmname();
	void entermovie();
	void dispsh(int shno);
};
class ticket
{
	public:
	       char* name;
	       int age;
	       movie* film;
	       int showno;
	       int count;
	       int seats[10];
	       int price;
	       void print();
	       void unbook();
	       ticket();
};
ticket t;
seat::seat()
{
	status=0;
}
void seat::stn(int i,int j)
{
	i++;j++;
	     stno=(10*i)+j;
}
int seat::retstatus()
{
	return status;
}
void seat::dispticket()
{
	cout<<"  "<<stno<<"\t"<<cname<<" ("<<c_age<<") ";
}
void seat::book1(char* name,int age)
{
	status=1;
	strcpy(cname,name);
	c_age=age;

}
void seat::unbook1()
{
	status=0;
	t.name=cname;
	t.age=c_age;
}
void shows::entershow()
{
	cout<<"\nEnter timings for show in:-"
	    <<"\nhours:- ";
	cin>>hrs;
	while(hrs<0||hrs>23)
	{
		cout<<"\nInvalid input, Re-enter hours:- ";
		cin>>hrs;
	}
	cout<<"minutes:- ";
	cin>>min;
	while(min<0||min>59)
	{
		cout<<"\nInvalid input, Re-enter minutes:- ";
		cin>>min;
	}
	cout<<"\nEnter price for 1 ticket:- ";
	cin>>price;
}
shows::shows()
{
   init();
}
void shows::init()
{
   for(int i=0;i<5;i++)
   {
	for(int j=0;j<5;j++)
	{
		st[i][j].stn(i,j);
	}
   }
}
void shows::book2(int a,int b, char* name, int age)
{

	if(st[a][b].retstatus()==0)
	{

		st[a][b].book1(name,age);
		t.seats[t.count++]=((a+1)*10)+b+1;
		t.price=price;
	}
	else
		cout<<"It is already booked\n";
}
void shows::unbook2(int a,int b)
{
	if(st[a][b].retstatus()==1)
	{

		st[a][b].unbook1();
		t.seats[t.count++]=((a+1)*10)+b+1;
		t.price=price;
	}
	else
		cout<<"It is not booked";
}
void shows::dispsh1()
{
	if(hrs<12)
	{
		if(hrs<10)
		    cout<<" ";
		cout<<hrs<<":"<<min<<"am";
	}
	else if(hrs==12)
		cout<<hrs<<":"<<min<<"pm";
	else
	{
		if((hrs-12)<10)
			cout<<" ";
		cout<<hrs-12<<":"<<min<<"pm";
	}
	cout<<"  Rs"<<price;
}
void shows::displist()
{
	int n=0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(st[i][j].retstatus()==1)
			{
				n++;
				cout<<endl;
				st[i][j].dispticket();
			}
		}
	}
	if(n==0)
		cout<<"\n\n\tNo tickets are booked for this show";
}
void shows::display()
{

	cout<<"\n ";
	for(int i=0;i<5;i++)
	{
		cout<<"   "<<i+1;
	}
	cout<<endl;
	for(i=0;i<5;i++)
	{
		cout<<i+1;
		for(int j=0;j<5;j++)
		{
			if(st[i][j].retstatus()==0)
			{
				textbackground(4);
				cout<<"  ";cprintf("  ");
			}
			else
			{
				 textbackground(2);
				 cout<<"  ";cprintf("  ");
			}
		}

	cout<<endl<<endl;
	}
	textbackground(BLACK);
}
int shows::ret_hrs()
{
	return hrs;
}
int shows::ret_min()
{
	return min;
}
void movie::dispsh(int shno)
{
	sh[shno-1].dispsh1();
}
char* movie::retmname()
{
	return mname;
}
void movie::entermovie()
{
	cout<<"\nEnter movie name:-\n";
	gets(mname);
	cout<<"\nEnter rating:-\n";
	cin>>rating;
	cout<<"\nEnter number of shows:-\n";
	cin>>numsh;
	for(int i=0;i<numsh;i++)
	{
		again:
		cout<<"\nEnter details for show "<<i+1;
		sh[i].entershow();
		for(int j=i-1;j>=0;j--)
		{
			if((sh[i].ret_hrs()==sh[j].ret_hrs())&&(sh[i].ret_min()==sh[j].ret_min()))
			{
				cout<<"\nA show of this timing already exists";
				goto again;
			}
		}
	}
}
int movie::book3(int s,int stno1,char* name,int age)
{
	int r=stno1/10;
	int c=stno1%10;
	if(r>0 && r<6 && c>0 && c<6)
	{
		sh[s-1].book2(r-1,c-1,name,age);
		return 0;
	}
	return 1;
}
int movie::unbook3(int s,int stno1)
{
       int r=stno1/10;
	int c=stno1%10;
	if(r>0 && r<6 && c>0 && c<6)
	{	sh[s-1].unbook2(r-1,c-1);
		return 0;
	}
	return 1;
}
void movie::dispbook(int c)
{
	sh[c-1].displist();
}
void movie::dispseats(int c)
{
	sh[c-1].display();
}
void movie::dispmovies()
{
	cout<<mname;
	cout<<" ("<<rating<<")\n";
}
void movie::dispsh2()
{
	for(int a=0;a<numsh;a++)
	{
		cout<<"\t"<<a+1<<". ";
		sh[a].dispsh1();
		cout<<endl;

	}
}

void ticket::print()
{
	cout<<name<<" ("<<age<<") has booked the following ticket:-\n";
	film->dispmovies();
	cout<<" ";
	film->dispsh(showno);
	cout<<"\n Seats:- ";
	for(int i=0;i<count;i++)
		cout<<" "<<seats[i];
	cout<<"\nTotal price = "<<count*price;
}
ticket::ticket()
{
	price=0;
	count=0;
	for(int i=0;i<10;i++)
		seats[i]=0;
}
void ticket::unbook()
{
	cout<<name<<" ("<<age<<") has unbooked the following ticket:-\n";
	film->dispmovies();
	cout<<" ";
	film->dispsh(showno);
	cout<<"\nSeats:- ";
	for(int i=0;i<count;i++)
		cout<<" "<<seats[i];
	cout<<"\nTotal refund = "<<count*price;
}
void writepass(char* pass)
{
	ofstream pout;
	pout.open("password.txt",ios::trunc);
	for(int i=0;pass[i]!='\0';i++)  //password encryption
		pass[i]+=5;
	pout<<pass;
	pout.close();
}
void readpass(char* pass)
{
	ifstream pin;
	pin.open("password.txt",ios::in);
	pin>>pass;
	for(int i=0;pass[i]!='\0';i++)  //password decryption
		pass[i]-=5;
}
void main()
{
	movie m;
	ifstream fin;
	ofstream fout;
	fstream fio;
	char name[20],mov[30],found='f',confirm='n',pass[20],pass1[20];
	char password[20]={"1234"};
	fin.open("password.txt",ios::in);
	if(!fin)
	{
		 writepass(password);
	}
	fin.close();
	int command,age,choice,mno,shno,i,stno,status;
	long pos;
   do
   {
	clrscr();
	textcolor(4+BLINK);
	cout<<"\t\t\t\t";
	cprintf("BOOK");
	textcolor(2+BLINK);
	cprintf(" MY");
	textcolor(3+BLINK);
	cprintf(" SHOW");
	cout<<"\n\n\n\t    ";
	textcolor(2);
	cprintf("Made By Siddharth Jain XII-A and Nikhil Vats XII-E");
	cout<<"\n\n\n\t\t\t   ";
	textcolor(4+BLINK);
	cprintf("Welcome to BOOK MY SHOW");
	cout<<"\n\n\n\t\t\t     ";
	textcolor(7);
	cout<<"Please log in here";
	cout<<"\n\n1.Login as admin"
	      <<"\n2.Login as user"
	      <<"\n0.Exit"
	      <<"\nEnter choice ";
	cin>>command;
	switch(command)
	{
		case 1:
		    for(i=0;i<3;i++)
		    {
			cout<<"\nEnter Admin Password:-\n";
			cin>>pass;
			readpass(password);
			if(strcmp(pass,password)==0)
				break;
			else
				cout<<"\nIncorrect Password";
		    }
		    if(i==3)
			cout<<"Maximum trials exceeded";
		    clrscr();
		    do
		    {
			clrscr();
			cprintf("Welcome admin what would you like to do?");
			cout<<"\n1.Add a movie"
			    <<"\n2.Delete a movie"
			    <<"\n3.Modify a movie"
			    <<"\n4.Display all movies"
			    <<"\n5.Display list of booked tickets"
			    <<"\n6.Change admin password"
			    <<"\n0.Logout";
			cprintf("\nEnter choice:- ");
			cin>>choice;
			switch(choice)
			{
				case 1:
				       fout.open("show.txt",ios::binary|ios::app);
				       m.entermovie();
				       fout.write((char*)&m,sizeof(m));
				       fout.close();
				 break;
				case 2:
				       fin.open("show.txt",ios::binary|ios::in);
				       if(!fin)
					{
						cout<<"\nFirst add movies and shows";
						break;
					}
				       fout.open("temp.txt",ios::binary|ios::out);
				       cout<<"Enter name of the movie to be deleted ";
				       gets(mov);
				       found='f';confirm='N';
				       while(!fin.eof())
				       {
						fin.read((char*)&m,sizeof(m));
						if(fin.eof())
						break;
						if(strcmpi(mov,m.retmname())==0)
						{
						    m.dispmovies();
						    found='t';
						    cout<<"Are you sure you want to delete this movie?(Y/N) ";
						    cin>>confirm;
						    if(confirm=='N')
							fout.write((char*)&m,sizeof(m));
						}
						else
							fout.write((char*)&m,sizeof(m));
				       }
				       if(found=='f')
						cout<<"Movie not found!!\n";
				       fout.close();
				       fin.close();
				       remove("show.txt");
				       rename("temp.txt","show.txt");
				 break;
				case 3:
				       fio.open("show.txt",ios::in|ios::out|ios::binary|ios::nocreate);
				       if(!fio)
					{
						cout<<"\nFirst add movies and shows";
						break;
					}
				       cout<<"Enter name of the movie to be modified ";
				       gets(mov);
				       while(!fio.eof())
				       {
						pos=fio.tellg();
						fio.read((char*)&m,sizeof(m));
						if(fio.eof())
							break;
						if(strcmpi(mov,m.retmname())==0)
						{
						    m.dispmovies();
						    m.dispsh2();
						    cout<<"\nEnter new details\n";
						    m.entermovie();
						    fio.seekg(pos);
						    fio.write((char*)&m,sizeof(m));
						    found='t';
						}
				       }
				       if(found=='f')
						cout<<"Movie not found!!\n";
				       fio.seekg(0);
				       fio.close();
				 break;
				case 4:
					fin.open("show.txt",ios::binary|ios::in);
					i=1;
					if(!fin)
					{
						cout<<"\nFirst add movies and shows";
						break;
					}
					while(!fin.eof())
					{
						fin.read((char*)&m,sizeof(m));
						if(fin.eof())
							break;
						cout<<i++<<". ";
						m.dispmovies();
						m.dispsh2();
					}

					fin.close();
				 break;
				 case 5:
					fin.open("show.txt",ios::in|ios::binary);
					if(!fin)
					{
						cout<<"\nFirst add movies and shows";
						break;
					}
					cout<<"\nEnter Movie Number:- ";
					cin>>mno;
					cout<<"Show Number:- ";
					cin>>shno;
					found='t';
					for(i=1;i<=mno;i++)
					{
						fin.read((char*)&m,sizeof(m));
						if(fin.eof())
						{
							found='f';
							break;
						}
					}
					if(found=='t')
					{
						m.dispmovies();
						m.dispsh(shno);
						m.dispbook(shno);
					}
					else
						cout<<"Movie not found!!\n";
					fin.close();
					break;
				 case 6:
					cout<<"\nEnter old password:-\n";
					cin>>pass;
					readpass(password);
					if(strcmp(pass,password)==0)
					{
						cout<<"\nEnter new password:-\n";
						cin>>pass;
						cout<<"\nRetype new password:-\n";
						cin>>pass1;
						if(strcmp(pass,pass1)==0)
						{
							writepass(pass);
							cout<<"Password changed";

						}
						else
							cout<<"Password does not match";
					}
					else
						cout<<"Old password does not match";
			 }//end of switch
			 getche();
		    }while(choice!=0);
		 break;
		case 2:
		    cout<<"\nEnter name:-\n";
		    gets(name);
		    cout<<"\nEnter Age:-\n";
		    cin>>age;
		    t.name=name;
		    t.age=age;
		    clrscr();
		    cprintf("Welcome user ") ;
		    puts(name);
		    do
		    {
			clrscr();
			cprintf("What would you like to do");
			cout<<"\n1.View details of movies"
			    <<"\n2.Book a ticket"
			    <<"\n3.Cancel a ticket"
			    <<"\n4.Status of a show"
			    <<"\n0.Logout";
			cprintf("\nEnter choice-");
			cin>>choice;
			switch(choice)
			{
				case 1:
					fin.open("show.txt",ios::binary|ios::in);
					i=1;
					if(!fin)
					{
						cout<<"\nNo movies, Please check later";
						break;
					}
					while(!fin.eof())
					{

						fin.read((char*)&m,sizeof(m));
						if(fin.eof())
						break;
						cout<<i++<<". ";
						m.dispmovies();
						m.dispsh2();
					}
					fin.close();

				 break;
				case 2:
					fio.open("show.txt",ios::in|ios::out|ios::binary|ios::nocreate);
					if(!fio)
					{
						cout<<"\nNo movies, Please check later";
						break;
					}
					cout<<"\nEnter Movie Number:- ";
					cin>>mno;
					cout<<"Show Number:- ";
					cin>>shno;
					found='t';
					for(i=1;i<=mno;i++)
					{
						pos=fio.tellg();
						fio.read((char*)&m,sizeof(m));
						if(fio.eof())
						{
							found='f';
							break;
						}
					}
					if(found=='t')
					{
						t.film=&m;
						t.showno=shno;
						cout<<endl;
						m.dispmovies();
						m.dispsh(shno);
						m.dispseats(shno);
						t.count=0;
						cout<<"\nEnter 0 to finish\n";
						do
						{
							cout<<"Enter seat number (rownocolno) to book:- ";
							cin>>stno;
							status=m.book3(shno,stno,name,age);
						}while(status==0);
						clrscr();
						m.dispseats(shno);
						t.print();
						 fio.seekg(pos);
						    fio.write((char*)&m,sizeof(m));
					}
					else
						cout<<"Movie not found!!\n";
					fio.close();
				 break;
				case 3:
					fio.open("show.txt",ios::in|ios::out|ios::binary|ios::nocreate);
					if(!fio)
					{
						cout<<"\nNo movies, Please check later";
						break;
					}
					cout<<"\nEnter Movie Number:- ";
					cin>>mno;
					cout<<"Show Number:- ";
					cin>>shno;
					found='t';
					for(i=1;i<=mno;i++)
					{
						pos=fio.tellg();
						fio.read((char*)&m,sizeof(m));
						if(fio.eof())
						{
							found='f';
							break;
						}
					}
					if(found=='t')
					{
						t.film=&m;
						t.showno=shno;
						cout<<endl;
						m.dispmovies();
						m.dispsh(shno);
						m.dispseats(shno);
						t.count=0;
						cout<<"\nEnter 0 to finish\n";
						do
						{
							cout<<"Enter seat number(rownocolno) to unbook:- ";
							cin>>stno;
							status=m.unbook3(shno,stno);
						}while(status==0);
						clrscr();
						m.dispseats(shno);
						cout<<endl;
						t.unbook();
						 fio.seekg(pos);
						    fio.write((char*)&m,sizeof(m));
					}
					else
						cout<<"Movie not found!!\n";
					fio.close();
				 break;
				case 4:
					fin.open("show.txt",ios::in|ios::binary);
					if(!fin)
					{
						cout<<"\nNo movies, Please check later";
						break;
					}
					cout<<"\nEnter Movie Number:- ";
					cin>>mno;
					cout<<"Show Number:- ";
					cin>>shno;
					found='t';
					for(i=1;i<=mno;i++)
					{
						fin.read((char*)&m,sizeof(m));
						if(fin.eof())
						{
							found='f';
							break;
						}
					}
					if(found=='t')
					{
						m.dispmovies();
						m.dispsh(shno);
						m.dispseats(shno);
					}
					else
						cout<<"Movie not found!!\n";
					fin.close();
					break;

			}//end of switch
			getche();
		    }while(choice!=0);

	}//end of switch

	}while(command!=0);
}



