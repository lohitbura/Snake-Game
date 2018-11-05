#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include <termios.h>
#include <unistd.h>




int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    printf("\n");
    return ch;
}

typedef struct Food
{
	char data;
	int x;
	int y;
}food;


typedef struct node
{
	char data;
	int x;
	int y;
	struct node* next;
}node;

void createsnake(node* *head,node* *tail)
{
	node* n1=(node*)malloc(sizeof(node));
	n1->x=11;
	n1->y=6;
	n1->data='A';
	*head=n1;

	node* n2=(node*)malloc(sizeof(node));
	n2->x=11;
	n2->y=7;
	n2->data='#';
	n1->next=n2;

	node* n3=(node*)malloc(sizeof(node));
	n3->x=11;
	n3->y=8;
	n3->data='#';
	n2->next=n3;

	node* n4=(node*)malloc(sizeof(node));
	n4->x=11;
	n4->y=9;
	n4->data='#';
	*tail=n4;
	n3->next=n4;

	node* n5=(node*)malloc(sizeof(node));
	n5->x=11;
	n5->y=10;
	n5->data='#';
	n4->next=n5;
	*tail=n5;
	n5->next=NULL;
}

food createfood(char a1[30][30],node**ptr)
{
	food Food;
	node* ptr1;
	ptr1=*ptr;
	Food.x=rand()%(27)+1;
	Food.y=rand()%(27)+1;
	Food.data='@';
	while(ptr1)
	{
		if(Food.x==ptr1->x && Food.y==ptr1->y)
		{
			Food.x=rand()%(27/2)+1;
	        Food.y=rand()%(27/2)+1;
		}
		ptr1=ptr1->next;
	}
	return Food;
}


void eatfood(char a2[30][30],node**ptr,food Food)
{
	Food=createfood(a2,ptr);
	node*ptr1=*ptr;
	node* temp=(node*)malloc(sizeof(node));
	temp->data='#';
	
	while(ptr1->next!=0)
		ptr1=ptr1->next;
	temp->x=ptr1->x;
	temp->y=ptr1->y;
	ptr1->next=temp;
	temp->next=NULL;
	
}

void snakebite(node**head)
{
	node*ptr=*head;

	ptr=ptr->next;
	{
		while(ptr!=NULL)
		{
			if(ptr->x==(*head)->x && ptr->y==(*head)->y)
			{
				printf("GAME OVER\nMR BROWN");
				exit(1);
			}
			ptr=ptr->next;
		}
		
	}
}

void movevaluetomatrix(char a1[30][30],node**head,food Food)
{
	node*temp=*head;
	while(temp!=NULL)
	{
		a1[temp->x][temp->y]=temp->data;
		temp=temp->next;
	}
	a1[Food.x][Food.y]=Food.data;
	
	snakebite(head);

}

void storeMatrixToFile(node** head,food Food)
{
	node*ptr=*head;
	FILE *fp;
	int x,y;
	char c,ch='\n',ch1='$';
	fp=fopen("lohit.txt","w");

	fprintf(fp,"%c %d %d\n",Food.data,Food.x,Food.y);
	while(ptr)
	{

		x=ptr->x;
		y=ptr->y;
		c=ptr->data;
		fprintf(fp,"%c %d %d\n",c,x,y);

		ptr=ptr->next;

	}

	fclose(fp);
} 


food getMatrixFromFile(node** head,char arr[30][30],node**tail)
{
	int x,y,count=0;

	char ch;
	food Food;
	node* temp2;
	char c;

FILE* fptr;
fptr=fopen("lohit.txt","r");

fscanf(fptr,"%c %d %d",&ch,&x,&y);
Food.x=x;
Food.y=y;
Food.data=ch;
	c=getc(fptr);

   while(fscanf(fptr,"%c %d %d",&ch,&x,&y)!=EOF)
{
		c=getc(fptr);
		node* temp=(node*)malloc(sizeof(node));
		temp->x=x;
		temp->y=y;
		temp->data=ch;
		temp->next=NULL;
		if(count==0)
		{
			*head=temp;
			temp2=temp;
			count++;
		}
		else
		{
			temp2->next=temp;
			*tail=temp;
			temp2=temp;
		}

}
return Food;
}



void setmatrix(char a1[30][30])
{
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if(i==0 || i==29)
				a1[i][j]='*';
			if(j==0 || j==29)
				a1[i][j]='*';
			if(i!=0&&j!=0&&i!=29&&j!=29)
				a1[i][j]=' ';
		}
	}
}



void moveleft(node**ptr,char a2[30][30])
{
	node*temp=*ptr;
	int m=temp->x;
	int n=temp->y;
	temp->y=temp->y-1;
	if(temp->y==0)
	{
		temp->y=29;
		//temp->x=temp->x+1;
	}
	temp=temp->next;
	while(temp!=NULL)
	{
		int i=temp->x;
		int j=temp->y;
		temp->x=m;
		temp->y=n;
		m=i;
		n=j;
		temp=temp->next;
	}

}

void moveright(node**ptr,char a2[30][30])
{
	node*temp=*ptr;
	int m=temp->x;
	int n=temp->y;
	temp->y=temp->y+1;
	if(temp->y==29)
	{
		temp->y=0;
		//temp->x=temp->x+1;
	}
	temp=temp->next;
	while(temp!=NULL)
	{
		int i=temp->x;
		int j=temp->y;
		temp->x=m;
		temp->y=n;
		m=i;
		n=j;
		temp=temp->next;
	}

}

void moveup(node**ptr,char a2[30][30])
{
	node*temp=*ptr;
	int m=temp->x;
	int n=temp->y;
	temp->x=temp->x-1;
	if(temp->x==0)
	{
		temp->x=29;
		//temp->y=temp->y+1;
	}
	temp=temp->next;
	while(temp!=NULL)
	{
		int i=temp->x;
		int j=temp->y;
		temp->x=m;
		temp->y=n;
		m=i;
		n=j;
		temp=temp->next;
	}

}

void movedown(node**ptr,char a2[30][30])
{
	node*temp=*ptr;
	int m=temp->x;
	int n=temp->y;
	temp->x=temp->x+1;
	if(temp->x==29)
	{
		temp->x=0;
		//temp->y=temp->y+1;
	}
	temp=temp->next;
	while(temp!=NULL)
	{
		int i=temp->x;
		int j=temp->y;
		temp->x=m;
		temp->y=n;
		m=i;
		n=j;
		temp=temp->next;
	}

}
void snakemovement(char a1[30][30],node**head,node**tail,food Food)
{
	while(1)
	{
	char ch;
	ch=getche();
	switch(ch)
	{
		case 'a':
		moveleft(head,a1);
		break;
    	case 'w':
		moveup(head,a1);
		break;
		case 's':
		movedown(head,a1);
		break;
		case 'd':
		moveright(head,a1);
		break;
		case 'x':
		storeMatrixToFile(head,Food);
						printf("Your Game Has been saved");
							exit(1);
		//default:
		//gameover();
	}
	setmatrix(a1);

	if((*head)->x==Food.x && (*head)->y==Food.y)
	{
		eatfood(a1,head,Food);
		Food=createfood(a1,head);
		movevaluetomatrix(a1,head,Food);
	}
	
	else movevaluetomatrix(a1,head,Food);


	for (int i = 0; i < 30; ++i)
    {
    for (int j = 0; j < 30; ++j)
    	{
    		printf("%c",a1[i][j]);
    	}	printf("\n");
    }
}
}


int main()
{
	char a[30][30];
	setmatrix(a);
	node* Head=NULL;
	node* Tail=NULL;
	food Food,Food2;
	char c;
	printf("do you want new match or old \nPress n for new \npress o for old");
	scanf("%c",&c);
	switch (c)
	{

		case 'n':
	createsnake(&Head,&Tail);
	Food=createfood(a,&Head);
	
	movevaluetomatrix(a,&Head,Food);
	snakemovement(a,&Head,&Tail,Food);

		case 'o':
		Food2=getMatrixFromFile(&Head,a,&Tail);
		snakemovement(a,&Head,&Tail,Food2);
		break;
		default:
		printf("enter correct option\n");

}
   
}