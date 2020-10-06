/**************************************************************************

	VSink.h														JJS 8/29/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	A VSink, or voltage sink, is an object which can can receive current
	through a Current.

	Requires:
		nothing
		
**************************************************************************/

#ifndef VSINK_H
#define VSINK_H

class Current;

#ifndef NULL
#define NULL 0
#endif

// define a "CurrentNode" class which will be used to keep
// a list of Currents to this VSink...
// NOTE: though a public class, this CurrentNode should NOT be used
// by users!  Its implementation may change in the future.

class CurrentNode
{
  public:
	CurrentNode( Current *pCurrent ) { itsCurrent=pCurrent; itsNext=NULL; }
	Current *itsCurrent;
	CurrentNode *itsNext;
};

class VSink
{
  friend class Current;
  public:

	VSink( void );					// constructor
	~VSink( void );					// destructor
	
  protected:
  	
  	CurrentNode *itsCurrentList;				// list of Currents
  	virtual void AddCurrent( Current *pCurrent );		// add a Current to the list
	virtual void RemoveCurrent( Current *pCurrent );	// remove a Current
												//	(happens automatically when the Current dies)
	char isDying;
};

#endif
