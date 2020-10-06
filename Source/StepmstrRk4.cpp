/*************************************************************************/
/**********             	   ChanTAUrk4.cpp                *************/
/*************************************************************************/
/****                                                                 ****/
/****              Methods  for the class Stepmaster                  ****/
/****    commands initialisation and steps of attached Steppers       ****/
/****                                                                 ****/
/*************************************************************************/





#include "StepmstrRk4.h"
#include "StepperRk4.h"

// global Stepmaster:
Stepmaster gStepmaster;


Stepmaster::Stepmaster()			// constructor
{
	itsListHead = itsListTail = 0;
	itsCurIdx = 0;
}

Stepmaster::~Stepmaster()			// destructor
{
	// destroy all attached Steppers before we die
	
	StepperNode *nextNode, *curNode;
	for (curNode = itsListHead; curNode; curNode = nextNode) {
		nextNode = curNode->itsNext;
		delete curNode;
	}

	// now we can die peacefully
}


void Stepmaster::Attach( Stepper& pStepper)
{
	// first, if the Stepper is already attached to another Stepmaster,
	// then remove it
	if (pStepper.itsMaster) pStepper.itsMaster->Remove( pStepper );
	
	// now add the given stepper to the tail of the list
	StepperNode *node = new StepperNode( itsListTail, pStepper );
	itsListTail = node;
	if (!itsListHead) itsListHead = node;
	
	// and set its pointer to point to us
	pStepper.itsMaster = this;
}



void Stepmaster::doStepinit(const real dt )
{
	// call the Stepinit method for all attached Steppers
	
	for (StepperNode *node=itsListHead; node; node = node->itsNext) {
		node->itsStepper->Init(dt);
	}

}


/* General step function. The only one that update the time */ 

void Stepmaster::StepAll( const real dt )
{
	// call the Step(dt) method for all attached Steppers
	
	for (StepperNode *node=itsListHead; node; node = node->itsNext) {
		node->itsStepper->Step(dt);
	}

	// now update itsCurIdx
	itsCurIdx = !itsCurIdx;
}


/* Runge Kutta step functions : one for each step of the method */


void Stepmaster::doStepk1( const real dt )
{
	// call the Stepk1(dt) method for all attached Steppers
	
	for (StepperNode *node=itsListHead; node; node = node->itsNext) {
		node->itsStepper->Stepk1(dt);
	}

}
void Stepmaster::doStepk2( const real dt )
{
	// call the Stepk2(dt) method for all attached Steppers
	
	for (StepperNode *node=itsListHead; node; node = node->itsNext) {
		node->itsStepper->Stepk2(dt);
	}

}
void Stepmaster::doStepk3( const real dt )
{
	// call the Stepk3(dt) method for all attached Steppers
	
	for (StepperNode *node=itsListHead; node; node = node->itsNext) {
		node->itsStepper->Stepk3(dt);
	}

}

void Stepmaster::doStepk4( const real dt )
{
	// call the Stepk4(dt) method for all attached Steppers
	
	for (StepperNode *node=itsListHead; node; node = node->itsNext) {
		node->itsStepper->Stepk4(dt);
	}

}




void Stepmaster::Remove( Stepper& pStepper )
{
	// the given Stepper is either dying or attaching to another master
	// so remove it from our list, and update its pointer
	
	StepperNode *curNode, *lastNode=0;
	for (curNode = itsListHead; curNode;
				lastNode = curNode, curNode = curNode->itsNext) {
		if ( curNode->itsStepper == &pStepper ) {
			// found it!  now remove it from the list
			if (lastNode) lastNode->itsNext = curNode->itsNext;
			if (curNode==itsListHead) itsListHead = curNode->itsNext;
			if (curNode==itsListTail) itsListTail = lastNode;
			delete curNode;
			pStepper.itsMaster = 0;
			return;
		}
	}
	
	// if we get to this point, it means we didn't find the given Stepper
	// this should never happen -- if you want to throw an exception,
	// do it here
}

