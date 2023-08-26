#include "Path_Finder.h"
#include <iostream>

std::vector<Map*> Neighbors(Map* map[25][40],Map* m)
{
    std::vector<Map*> temp;               //Found Error map not used perfectly

    int x = m->rect.x/20;
    int y = m->rect.y/20;


    //if(x - 1 >= 0 && y - 1 >= 0)
        //temp.push_back(map[y-1][x-1]);
    if(y-1 >= 0)
        temp.push_back(map[y-1][x]);
    //if(x+1 < 40 && y-1 >= 0)
        //temp.push_back(map[y-1][x+1]);
    if(x-1 >= 0)
        temp.push_back(map[y][x-1]);
    if(x+1 < 40)
        temp.push_back(map[y][x+1]);
    //if(x-1 >= 0 && y+1 < 25)
        //temp.push_back(map[y+1][x-1]);
    if(y+1 < 25)
        temp.push_back(map[y+1][x]);
    //if(x+1 < 40 && y+1 < 25)
        //temp.push_back(map[y+1][x+1]);

    return temp;
}

Map* NeighborWithMinF(std::vector<Map*> set)
{
    Map* MapWithMinF = set[0];
    for(auto s: set)
    {
        if(s->f < MapWithMinF->f)
            MapWithMinF = s;
    }

    return MapWithMinF;
}

void Remove(std::vector<Map*> &set,Map* elem)
{
    for(auto it=set.begin();it!=set.end();it++)
    {
        if(*it == elem)
        {
            set.erase(it);
            break;
        }
    }
}


bool isPresent(std::vector<Map*> set,Map* elem)
{
    for(auto s: set)
    {
        if(s->rect.x == elem->rect.x && s->rect.y == elem->rect.y)
            return true;
    }
    return false;
}

float CalculateH(Map* elem,Map* dest)
{
    return SDL_max(SDL_abs(elem->rect.x - dest->rect.x),SDL_abs(elem->rect.y - dest->rect.y));
}

bool GreaterG(std::vector<Map*> openSet,Map* elem)
{
    for(auto s: openSet)
    {
        if(elem->g > s->g)
            return true;
    }
    return false;
}

std::vector<SDL_Rect> FindPath(SDL_Rect start,SDL_Rect dest,std::vector<SDL_Rect> body)
{
    Map* map[25][40];
    for(int i=0;i<25;i++)
    {
        for(int j=0;j<40;j++)
        {
            map[i][j] = new Map;
            map[i][j]->rect.x = j*20;
            map[i][j]->rect.y = i*20;
        }
    }

    for(int i=0;i<body.size();i++)
    {
        int x = body[i].x/20;
        int y = body[i].y/20;
        map[y][x]->wall = true;
    }

    Map* Start = new Map;
    Start->rect = start;

    Map* Dest = new Map;
    Dest->rect = dest;

    std::vector<Map*> openSet,closeSet;
    openSet.push_back(Start);
    Map* current;

    while(!openSet.empty())
    {
        current = NeighborWithMinF(openSet);
        closeSet.push_back(current);
        Remove(openSet,current);

        if(current->rect.x == Dest->rect.x && current->rect.y == Dest->rect.y)
            break;

        std::vector<Map*> neighbor = Neighbors(map,current);

        for(auto neigh: neighbor)
        {
            if(isPresent(closeSet,neigh) || neigh->wall)
                continue;

            neigh->g = current->g + 1;
            neigh->h = CalculateH(neigh,Dest);
            neigh->f = neigh->g + neigh->h;
            neigh->parent = current;

            if(isPresent(openSet,neigh))
            {
                if(GreaterG(openSet,neigh))
                    continue;
            }

            openSet.push_back(neigh);
        }
    }

    std::vector<SDL_Rect> Path;

    Map* m = closeSet[closeSet.size()-1];
    do
    {
        SDL_Rect rect = m->rect;
        Path.push_back(rect);
        m = m->parent;
    }while(m != closeSet[0]);

    for(int i=0;i<Path.size()/2;i++)
        std::swap(Path[i],Path[Path.size()-i-1]);

    return Path;
}
