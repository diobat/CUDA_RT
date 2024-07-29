#pragma once

#include "hitable.hpp"

class hitableList : public hitable
{
    public:
        hitableList() {}
        hitableList(hitable **l, int n) {list = l; listSize = n;}
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        hitable **list;
        int listSize;
};

bool hitableList::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    hit_record tempRec;
    bool hitAnything = false;
    double closestSoFar = t_max;
    for (int i = 0; i < listSize; i++)
    {
        if (list[i]->hit(r, t_min, closestSoFar, tempRec))
        {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}