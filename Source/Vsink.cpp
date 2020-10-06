/*************************************************************************/
/**********             	   Vsink.cpp                     *************/
/*************************************************************************/
/****                                                                 ****/
/****              Methods to for a node of currents                  ****/
/****                                                                 ****/
/*************************************************************************/


#include "VSink.h"
#include "CurrentRk4.h"

VSink::VSink( void )
{	
	itsCurrentList = NULL;
	isDying = 0;
}

VSink::~VSink( void )
{
	isDying = 1;
	
	// We delete our Currents before we die.
	
	CurrentNode *cur=itsCurrentList;
	CurrentNode *next;
	
	while (cur) {
		next = cur->itsNext;
		delete cur->itsCurrent;
		delete cur;
		cur = next;
	}
}

void VSink::AddCurrent( Current *pCurrent )
{
	CurrentNode *newbie = new CurrentNode( pCurrent );
	CurrentNode *prev = NULL;
	for (CurrentNode *cur=itsCurrentList; cur; prev=cur, cur=cur->itsNext)
		;
	if (prev) prev->itsNext = newbie;
	else itsCurrentList = newbie;
}
	
void VSink::RemoveCurrent( Current *pCurrent )
{
	// Remove the Current from our list (unless we're already dying).
	// This function does not actually destroy the Current.
	
	if (isDying) return;
	
	CurrentNode *cur,*prev=NULL;
	
	for (cur=itsCurrentList; cur; prev=cur, cur=cur->itsNext) {
		if (cur->itsCurrent == pCurrent) {
			if (prev) prev->itsNext = cur->itsNext;
			else itsCurrentList = cur->itsNext;
			delete cur;
			return;
		}
	}
}
