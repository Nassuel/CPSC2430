/**
 * @file Menagerie.cpp - implementation of the Menagerie.h class (cont.)
 * @author Nassuel Valera
 * @see "Seattle University, CPSC 2430, Spring 2018"
 * @see Menagerie2.cpp
 *
 * Note: there's a out_of_bounds random bug, but was unable to debug due
 *		 to the process not showing on the separate bash.
 */

#include "Explosion.h"
#include "Cannonball.h"
#include "adt/Critter.h"
#include "InchWorm.h"
#include "Menagerie.h"
#include "QueueL.h"
#include "Cannon.h"
#include "PixelMatrix.h"
#include "Pacer.h"
using namespace std;

void Menagerie::resetGame() {
	eventCount = 0;
	clear();
	cannonballs = CANNON_BALLS;	
	// Canon
	Cannon *canon = new Cannon(display.getRowCount()-1,display.getColCount()/2);
	critters.append(canon);
	// Pacer
	int pace = critters.append(new Pacer(.002));
	events.enqueue(Event(MOVE,pace));
	// First InchWorm
	InchWorm *cody = new InchWorm(2, display.getColCount()/4);
	int codyI = this->critters.append(cody); // Composite has to work
	this->events.enqueue(Event(MOVE,codyI));
	// Second InchWorm
	InchWorm *cody2 = new InchWorm(4,display.getColCount()/3.5);
	int cody2I = this->critters.append(cody2);
	this->events.enqueue(Event(MOVE,cody2I));
	// Third Worm
	InchWorm *cody3 = new InchWorm(6,display.getColCount()/3);
	int cody3I = this->critters.append(cody3);
	this->events.enqueue(Event(MOVE,cody3I));
	// Fourth Worm
	InchWorm *cody4 = new InchWorm(8,display.getColCount()/2.5);
	int cody4I = this->critters.append(cody4);
	this->events.enqueue(Event(MOVE,cody4I));
}

bool Menagerie::processEvent() {
	// Check event
	Event eve = this->events.peek();
	this->events.dequeue();
	
	if (eve.type == MOVE) {
		Critter *c = critters.get(eve.data);
		if (c != nullptr) {
			c->move();
			this->events.enqueue(Event(MOVE,eve.data));
		}
		return true;
	} else {
		int keyPress = eve.data;
		Critter *cannon = critters.get(0);
		
		if (keyPress == 'q')
			return false;
		else if (keyPress == 'h' || eve.data == Display::RIGHT_ARROW_KEY)
			cannon->move();
		else if (keyPress == 'g' || eve.data == Display::LEFT_ARROW_KEY)
			cannon->reverse();
		else if (keyPress == 'i' || eve.data == Display::UP_ARROW_KEY)
			shoot();
	}
	
	this->events.dequeue();
	eventCount++;
	return true;
}

bool Menagerie::compositeScene() {
	PixelMatrix old = scene;
	
	int sizeC = critters.size();
	int dRows = display.getRowCount();
	int dCols = display.getColCount();
	
	PixelMatrix blackPxm(dRows,dCols,RGB::BLACK);
	scene = blackPxm;
	
	for(int i = 0; i < sizeC; i++)
		if(critters.get(i) != nullptr)
			scene += pxms.get(i);
	
	for(int i = 0; i < pxms.size(); i++) {
		scene.overlay(pxms.get(i));
	}
	refreshDisplay();
	
	if (scene != old)
		lastMovement = eventCount;
	else {
		log("no movement");
		eventCount++;
	}
	
	return eventCount - lastMovement <= NO_MOVEMENT;
}

void Menagerie::processCollisions() {
	log("collisions");
	
	int sizeC = critters.size();
	int dRows = display.getRowCount();
	int dCols = display.getColCount();
	
	for(int i = 0; i < sizeC; i++) {
		for(int j = i + 1; j < sizeC; j++) {
			bool collision = false;
			for(int r = 0; !collision && r < dRows; r++) {
				for (int c = 0; !collision && c < dCols; c++) {
					if (!pxms.get(i).get(r,c).transparent && !pxms.get(j).get(r,c).transparent) {
						collision = true;
					
						killCritter(i);
						killCritter(j);
						
						log("explosion");
						// Where is the explosion?
						Explosion *exp = new Explosion(r,c);
						// Add it to critters
						int expId = critters.append(exp);
						// Add it to event queue
						events.enqueue(Event(MOVE,expId));
						eventCount++;
					}
				}
			}
		}
	}
}

void Menagerie::shoot() {
	Critter *canon = critters.get(0);
	int cBallID;
	if (!(canon == nullptr || cannonballs == 0))
		cBallID = critters.append(new Cannonball(display.getRowCount()-3, canon->getColumn()));
		this->events.enqueue(Event(MOVE, cBallID));
		eventCount++;
		cannonballs--;
}