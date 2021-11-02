#pragma once
#ifndef _POLYLIST_
#include "linkedlist.h"
#define _POLYLIST_

int addPolyNodeLast(LinkedList* pList, float coef, int degree);
LinkedList* polyAdd(LinkedList* pListA, LinkedList* pListB);
void displayPolyList(LinkedList* pList);

#endif