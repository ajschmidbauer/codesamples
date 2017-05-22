#include <iostream>
#include "queue.h"

using namespace std;

const int rBound=20;
const int cBound=20;

int dRow,dColumn,mRow,mColumn,iRow,iColumn,nLava;
int rCurrent,cCurrent,step;
int planet[rBound][cBound];
Queue path;
Queue crumbs;
spot coord,wizard;

//loads data into ram to be processed, prepares planetary board
void input(){
    int lRow,lColumn;
    cin>>dRow>>dColumn>>mRow>>mColumn>>iRow>>iColumn>>nLava;
    for(int i=0;i<rBound;i++)
        for(int j=0;j<cBound;j++)
            planet[i][j]=-1;
    planet[iRow][iColumn]=0;
    coord.row=iRow;
    coord.column=iColumn;
    path.enqueue(coord);
    for(int i=0;i<nLava;i++)
    {
        cin>>lRow>>lColumn;
        planet[lRow][lColumn]=-2;
    }
}

//checks the spot, determines what path value it will have
//and enqueues this spot for its neighbors to be checked in BFS
void check(int cRow,int cColumn){
    if(cRow>=0&&
    cRow<rBound&&
    cColumn>=0&&
    cColumn<cBound&&
    planet[cRow][cColumn]==-1)
    {
        planet[cRow][cColumn]=planet[rCurrent][cCurrent]+1;
        coord.row=cRow;
        coord.column=cColumn;
        path.enqueue(coord);
    }
}

//resets planetary board
void clearPlanet(){
    for(int i=0;i<rBound;i++)
        for(int j=0;j<cBound;j++)
            if(planet[i][j]>0)
                planet[i][j]=-1;
}

//fills planetary board with potential paths
void bestFirstSearch(){
    clearPlanet();
    coord.row=iRow;
    coord.column=iColumn;
    while(!path.isEmpty())
    {
        coord=path.dequeue();
        rCurrent=coord.row;
        cCurrent=coord.column;
        if(cCurrent%2==0)   //even
        {
            check(rCurrent-1,cCurrent);
            check(rCurrent+1,cCurrent);
            check(rCurrent-1,cCurrent-1);
            check(rCurrent,cCurrent-1);
            check(rCurrent-1,cCurrent+1);
            check(rCurrent,cCurrent+1);
        }
        else                    //odd
        {

            check(rCurrent-1,cCurrent);
            check(rCurrent+1,cCurrent);
            check(rCurrent,cCurrent-1);
            check(rCurrent+1,cCurrent-1);
            check(rCurrent,cCurrent+1);
            check(rCurrent+1,cCurrent+1);
        }
    }
}

//used in pathFind, determines if spot is a valid move
bool checkspot(int rCheck,int cCheck){
return(rCheck>=0&&
    rCheck<rBound&&
    cCheck>=0&&
    cCheck<cBound&&
    planet[rCheck][cCheck]==step);
}

//finds best path after paths are applied to planetary board
void pathFind(int cRow,int cColumn){
    step=planet[cRow][cColumn]-1;
    coord.row=cRow;
    coord.column=cColumn;
    while(step>0)
    {
        if(coord.column%2==0)    //even
        {
            if(checkspot(coord.row-1,coord.column))
                {
                step--;
                coord.row=coord.row-1;
                crumbs.enqueue(coord);
                }
            else if(checkspot(coord.row+1,coord.column))
                {
                step--;
                coord.row=coord.row+1;
                crumbs.enqueue(coord);
                }
            else if(checkspot(coord.row-1,coord.column-1))
                {
                step--;
                coord.row=coord.row-1;
                coord.column=coord.column-1;
                crumbs.enqueue(coord);
                }
            else if(checkspot(coord.row,coord.column-1))
                {
                step--;
                coord.column=coord.column-1;
                crumbs.enqueue(coord);
                }
            else if(checkspot(coord.row-1,coord.column+1))
                {
                step--;
                coord.row=coord.row-1;
                coord.column=coord.column+1;
                crumbs.enqueue(coord);
                }
            else
                {
                step--;
                coord.column=coord.column+1;
                crumbs.enqueue(coord);
                }
        }
        else                //odd
        {
            if(checkspot(coord.row-1,coord.column))
                {
                step--;
                coord.row=coord.row-1;
                crumbs.enqueue(coord);
                }
            else if(checkspot(coord.row+1,coord.column))
                {
                step--;
                coord.row=coord.row+1;
                crumbs.enqueue(coord);
                }
            else if(checkspot(coord.row+1,coord.column-1))
                {
                step--;
                coord.row=coord.row+1;
                coord.column=coord.column-1;
                crumbs.enqueue(coord);
                }
            else if(checkspot(coord.row,coord.column-1))
                {
                step--;
                coord.column=coord.column-1;
                crumbs.enqueue(coord);
                }
            else if(checkspot(coord.row+1,coord.column+1))
                {
                step--;
                coord.row=coord.row+1;
                coord.column=coord.column+1;
                crumbs.enqueue(coord);
                }
            else
                {
                step--;
                coord.column=coord.column+1;
                crumbs.enqueue(coord);
                }
        }
    }
    coord.row=0;
    coord.column=0;
}

//outputs path from queue
void pathOutput(){
    while(!crumbs.isEmpty())
    {
        coord=crumbs.dequeue();
        cout<<"("<<coord.row<<","<<coord.column<<") ";
    }
    cout<<"("<<iRow<<","<<iColumn<<") ";
        cout<<endl;
}

//obstacle placement
bool gandalfPlace(){
        pathFind(mRow,mColumn);
        Queue gandalf;
        while(!crumbs.isEmpty())
            gandalf.enqueue(crumbs.dequeue());
        while(!gandalf.isEmpty())
            {
               wizard=gandalf.dequeue();
               planet[wizard.row][wizard.column]=-2;
               coord.row=iRow;
               coord.column=iColumn;
               path.enqueue(coord);
               bestFirstSearch();
               if(planet[dRow][dColumn]<planet[mRow][mColumn])
                   {
                    return true;
                   }
                planet[wizard.row][wizard.column]=-1;
            }
        return false;
}

int main(){
    input();
    bestFirstSearch();

    if(planet[dRow][dColumn]==-1&&planet[mRow][mColumn]==-1)
        cout<<"Neither Duck Dodgers nor Marvin the Martian could reach the Illudium Phosdex."<<endl;

    else if(planet[mRow][mColumn]==-1)
        {
        cout<<"Duck Dodgers beat Marvin the Martian to the Illudium Phosdex!"<<endl;
        pathFind(dRow,dColumn);
        cout<<"Duck Dodgers path:"<<endl;
        pathOutput();
        cout<<"Marvin the Martian could not reach the Illudieum Phosdex."<<endl;
        }

    else if(planet[dRow][dColumn]==planet[mRow][mColumn])
        {
            cout<<"It was a tie! Marvin the Martian disintegrated Duck Dodgers with his disintegration gun!"<<endl;
            pathFind(dRow,dColumn);
            cout<<"Duck Dodgers path:"<<endl;
            pathOutput();
            pathFind(mRow,mColumn);
            cout<<"Marvin the Martian path:"<<endl;
            pathOutput();
        }

    else if(planet[dRow][dColumn]<planet[mRow][mColumn])
        {
            cout<<"Duck Dodgers beat Marvin the Martian to the Illudium Phosdex!"<<endl;
            pathFind(dRow,dColumn);
            cout<<"Duck Dodgers path:"<<endl;
            pathOutput();
            pathFind(mRow,mColumn);
            cout<<"Marvin the Martian path:"<<endl;
            pathOutput();
        }

    else if(planet[dRow][dColumn]>planet[mRow][mColumn])
        {
               if(gandalfPlace())
                   {
                    cout<<"Obstacle placed at "<<wizard.row<<wizard.column<<endl;
                    cout<<"Duck Dodgers beat Marvin the Martian to the Illudium Phosdex!"<<endl;
                    pathFind(dRow,dColumn);
                    cout<<"Duck Dodgers path:"<<endl;
                    pathOutput();
                    pathFind(mRow,mColumn);
                    cout<<"Marvin the Martian path:"<<endl;
                    pathOutput();
                    return 0;
                    }
        cout<<"Marvin the Martian beat Duck Dodgers to the Illudium Phosdex!"<<endl;
        pathFind(dRow,dColumn);
        cout<<"Duck Dodgers path:"<<endl;
        pathOutput();
        pathFind(mRow,mColumn);
        cout<<"Marvin the Martian path:"<<endl;
        pathOutput();
        }
    return 0;
}
