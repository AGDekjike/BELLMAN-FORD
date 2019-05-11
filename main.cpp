#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct EDGE//STORE THE BEGINING, ENDING AND WEIGTH OF EDGES
{
    char START;
    char END;
    int WEIGTH;
};

struct VERTEX//STORE THE POINT, DISTANT OF IT TO THE TARGET POINT, AND THE POINT BEOFRE IT
{
    char POINT;
    char PRE;
    int DISTANT;
};

int READ_TEXT(EDGE E[],char *filename,char &TARGET)//OPEN A FILE
{
    ifstream file;
    file.open(filename,ios::in);
    int NUM;
    file>>NUM;
    file>>TARGET;
    for(int i=0;i<NUM;i++){
        file>>E[i].START;
        file>>E[i].END;
        file>>E[i].WEIGTH;
    }
    return NUM;
}

int CREATE_VERTEX(EDGE E[],VERTEX V[],int NUM)//USE THE FILE TO CREATE VERTEX STRUCTURE
{
    int A[2*NUM];
    int k=0;
    for(int i=0;i<NUM;i++)
    {
        int E1=0;
        int E2=0;
        for(int j=0;j<2*NUM;j++)
        {
            if(A[j]==E[i].START)
            {
                E1=1;
            }
            if(A[j]==E[i].END)
            {
                E2=1;
            }
        }
        if(E1==0)
        {
            V[k].POINT=E[i].START;
            A[k]=E[i].START;
            k++;
        }
        if(E2==0)
        {
            V[k].POINT=E[i].END;
            A[k]=E[i].END;
            k++;
        }
    }
    return k;
}

void INITIALIZE(EDGE E[],VERTEX V[],char &TARGET,int NUM)//INITIALIZE THE VERTEX
{
    for(int i=0;i<NUM;i++)
    {
        if(V[i].POINT==TARGET)
        {
        V[i].DISTANT=0;
        V[i].PRE='N';
        }
        else
        {
        V[i].DISTANT=99;
        V[i].PRE='N';
        }
    }
}

void RELAX(VERTEX V[],char S,char E,int WEIGTH,int i,int j,int SIZE)//FIND THE SHORTER PATH OF EACH CIRCUMSTANCE
{
    int START;
    int END;
    int e;
    for(int k=0;k<SIZE;k++)
    {
        if(V[k].POINT==S)
        {
            START=V[k].DISTANT;
        }
        if(V[k].POINT==E)
        {
            END=V[k].DISTANT;
            e=k;
        }
    }
    if(END>START+WEIGTH)
    {
        V[e].DISTANT=START+WEIGTH;
        V[e].PRE=S;
    }
}

int BF(EDGE E[],VERTEX V[],int SIZE,int NUM)//USE BELLFORD-MAN ALGORITHMS TO CALCULATE THE ULTIMATE SHORTEST PATH
{
    for(int j=0;j<SIZE;j++)//USE RELAX FOR EACH LOOP
    {
        for(int i=0;i<NUM;i++)
        {
            int WEIGTH=E[i].WEIGTH;
            char START=E[i].START;
            char END=E[i].END;
            RELAX(V,START,END,WEIGTH,i,j,SIZE);
        }
    }
    for(int i=0;i<NUM;i++)//INDICATE WHETHER THE PATH EXIST
    {
        int m,n;
        for(int j=0;j<SIZE;j++)
        {
            if(V[j].POINT==E[i].START)
            {
                m=j;
            }
            if(V[j].POINT==E[i].END)
            {
                n=j;
            }
        }
        if(V[n].DISTANT>V[m].DISTANT+E[i].WEIGTH)
        {
            return -1;
        }
    }
    return 1;
}

void PATH(VERTEX V[],char R[],int j,int n,int SIZE,char &TARGET)//PRINT THE SHORTEST PATH FROM STRUCTURE VERTEX
{
    if(V[j].PRE!='N' && V[j].PRE!=TARGET)
    {
        for(int k=0;k<SIZE;k++)
        {
           if(V[k].POINT==V[j].PRE)
           {
            R[n]=V[j].PRE;
            n--;
            j=k;
           }
        }
        PATH(V,R,j,n,SIZE,TARGET);
    }
}

int main()
{
    cout<<"U201613209 WANG, MINGXUAN\n";
    EDGE E[100];
    char TARGET;
    cout<<"PLEASE INDICATE YOUR FILE'S LOCATION:\n";//LIKE IF YOU CREATE A FILE IN DISK C NAMES bf.in, INPUT THESE:C:\\bf.in
    char filename[100];
    cin>>filename;
    cout<<"THE FILE IS:\n";
    int NUM=READ_TEXT(E,filename,TARGET);
    VERTEX V[2*NUM];
    cout<<NUM<<" "<<TARGET<<"\n";
    for(int i=0;i<NUM;i++)
    {
        cout<<E[i].START<<" "<<E[i].END<<" "<<E[i].WEIGTH<<" ";
        cout<<"\n";
    }
    cout<<"\nTHE INITIALIZED VERTEX IS:\n";
    int SIZE=CREATE_VERTEX(E,V,NUM);
    INITIALIZE(E,V,TARGET,NUM);
    for(int i=0;i<SIZE;i++)
    {
        cout<<V[i].POINT<<" ";
        cout<<"DISTANT:";
        cout<<V[i].DISTANT<<" ";
        if(V[i].DISTANT<10)
        {
            cout<<" ";
        }
        cout<<"PRE:"<<V[i].PRE<<"\n";
    }
    cout<<"\nTHE CALCULATED FIGURE IS:\n";
    int e=BF(E,V,SIZE,NUM);
    if(e==-1)
    {
        cout<<"THE PATH DOES NOT EXIST!";
    }
    else
    {
    for(int i=0;i<SIZE;i++)
    {
        cout<<V[i].POINT<<" ";
        cout<<"DISTANT:";
        if(V[i].DISTANT>=0)
        {
            cout<<" ";
        }
        cout<<V[i].DISTANT<<" ";
        if(V[i].DISTANT<10)
        {
            cout<<" ";
        }
        cout<<"PRE:"<<V[i].PRE<<"\n";
    }
    cout<<"\nTHE PATH IS:\n";
    for(int i=0;i<SIZE;i++)
    {
        char R[SIZE]={'N','N','N','N','N'};
        R[0]=TARGET;
        int n=SIZE-2;
        R[SIZE-1]=V[i].POINT;
        int j=i;
        PATH(V,R,j,n,SIZE,TARGET);
        for(int k=0;k<SIZE-1;k++)
        {
            if(R[k]!='N')
            {
                cout<<R[k]<<"-";
            }
        }
        cout<<R[SIZE-1]<<" ";
        cout<<V[i].DISTANT<<"\n";
    }
    }
    getchar();getchar();
}
/*  A SAMPLE FILE GOES LIKE:
10 s
s t 6
s y 7
t y 8
t x 5
t z -4
x t -2
y x -3
y z 9
z s 2
z x 7
THE FIRST NUMBER INDICATES THE NUMBER OF EDGES THE FILE INCLUDES, WHILE THE SECOND ONE INDICATES THE POINT WHERE THE SHORTEST PATH THAT YOU INTEND TO FIND STARTS WITH.
AFTER THAT LISTS THE EDGE WITH ITS BEGINING POINT AND END POINT, TOGETHER WITH ITS WEIGHT WHICH SHOULD BE LOWER THAN 99. OVERALL, THE FILE'S SIZE SHOULB BE UNDER 100 CHARACTERS.
*/
