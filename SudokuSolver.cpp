//Alexander Schmidbauer
#include <iostream>
#include "include/Stack.h"
#include <fstream>
using namespace std;
Stack tae;
board attempt;
sui guess,rRow,rColumn;

const sui IS_FILLED_IN   = 0x8000;
const sui IS_MOST_RECENT = 0x4000;
const sui IS_LEGAL[10]={0x0000,0x1000,0x0800,0x0400,0x0200,0x0100,0x0080,0x0040,0x0020,0x0010};
const sui LEGAL_MASK     = 0x1ff0;
const sui CHOICE_MASK    = 0x000f;
const sui CHOICE_FACE    = 0xfff0;

bool checkChoice(int a,int b,sui n){
sui check=attempt.grid[a][b]&CHOICE_MASK;
return(check==n);
}

bool isFilledIn(int a,int b){
return ((attempt.grid[a][b]&IS_FILLED_IN)==IS_FILLED_IN);
}

bool isMostRecent(int a,int b){
sui data=attempt.grid[a][b]|IS_MOST_RECENT;
    return attempt.grid[a][b]==data;
}

bool isLegal(int a,int b,int c){
sui legal=attempt.grid[a][b]&IS_LEGAL[c];
    return (legal==IS_LEGAL[c]);
}

bool gridIsNotFull(){
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(!isFilledIn(i,j))
                return true;
        }
    return false;
}

void setMostRecent(int a,int b){
    attempt.grid[a][b]=attempt.grid[a][b]|IS_MOST_RECENT;
}

void setLegal(int a, int b,sui n){
    attempt.grid[a][b]=attempt.grid[a][b]|IS_LEGAL[n];
}

void setChoice(sui a){
    sui choice=(attempt.grid[rRow][rColumn]&CHOICE_FACE);
    choice=choice|a;
    attempt.grid[rRow][rColumn]=choice;
}

void setFilledIn(){
    attempt.grid[rRow][rColumn]=attempt.grid[rRow][rColumn]|IS_FILLED_IN;
}

void removeLegal(int k){
    attempt.grid[rRow][rColumn]=attempt.grid[rRow][rColumn]^IS_LEGAL[k];
}

void removeRecent(){
    attempt.grid[rRow][rColumn]=attempt.grid[rRow][rColumn]^IS_MOST_RECENT;
}

void findFewestLegal(){
    int Record=0;
    int Count;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(!isFilledIn(i,j))
            {
                Count=0;
                for(int k=1;k<10;k++)
                    if(!isLegal(i,j,k))
                        Count++;
            if(Count>Record)
            {
                Record=Count;
                rRow=i;
                rColumn=j;
            }
            }
        }
    setMostRecent(rRow,rColumn);
}

void findMostRecent(){
for(int i=0;i<9;i++)
    for(int j=0;j<9;j++)
        if(isMostRecent(i,j))
        {
            rRow=i;
            rColumn=j;
        }
}

void legalize(){
    bool legal;
    for(int i=0;i<9;i++)//rows
    {
        for(int j=0;j<9;j++)//columns
        {
            if(!isFilledIn(i,j))
            {
            attempt.grid[i][j]=(attempt.grid[i][j]&!LEGAL_MASK);
                for(sui k=1;k<10;k++)//numbers
                {
                    legal=true;
                    for(int a=0;a<9;a++)//row/column checks
                        {
                            if(checkChoice(i,a,k))
                                legal=false;
                            if(checkChoice(a,j,k))
                                legal=false;
                        }
                    for(int b=0;b<3;b++)//box checks
                        for(int a=0;a<3;a++)
                        {
                        int x=i/3;
                        int y=j/3;
                        x=x*3;
                        y=y*3;
                        x=x+a;
                        y=y+b;
                            if(checkChoice(x,y,k))
                                legal=false;
                        }
                    if(legal)
                        setLegal(i,j,k);
                }
            }
        }
    }
}

void userInput(){
char input;
ifstream inFile;
inFile.open("test.dat");
    for(int i=0;i<9;i++)
    {
    for(int j=0;j<9;j++)
        {
        inFile>>input;
            if(isdigit(input))
            {
                attempt.grid[i][j]=(input-'0')|IS_FILLED_IN;
                }
            else
                attempt.grid[i][j]=0;
        }

    }
}

void boardOutput(){
int output;
    for(int i=0;i<9;i++)
    {
    for(int j=0;j<9;j++)
    {
    output=CHOICE_MASK&attempt.grid[i][j];
    cout<<output;
    }
    cout<<endl;
    }
}

bool findGuess(){
    for(int k=1;k<10;k++)
    {
        if(isLegal(rRow,rColumn,k))
        {
            guess=k;
            return true;
        }
    }
    return false;
}

int main(){
    userInput();
    legalize();
    findFewestLegal();
    setMostRecent(rRow,rColumn);
    tae.push(attempt);
    do{
        findMostRecent();
        if(findGuess())
        {
            removeLegal(guess);
            tae.push(attempt);
            setChoice(guess);
            setFilledIn();
            removeRecent();
            legalize();
            findFewestLegal();
            setMostRecent(rRow,rColumn);
        }
        else
        {
            attempt=tae.peek();
            tae.pop();
        }
    }while(gridIsNotFull());
    boardOutput();
    return 0;
}
