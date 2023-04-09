#ifndef PAGES_H
#define PAGES_H
#include<QPixmap>
class Pages
{
public:
    int currentpage;
public:
    Pages():currentpage(0)
    {

    }
    void moveMap(int x,int y);
};


#endif // PAGES_H
