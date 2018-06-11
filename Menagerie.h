/**
 * @file Menagerie.h - Menagerie game
 * @author Prof. Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include <fstream>
#include <gtest/gtest_prod.h> //import this FRIEND_TEST is here not in gtest.h
#include "ListA.h"
#include "adt/Display.h"
#include "adt/Critter.h"
#include "QueueL.h"

/**
 * @class Menagerie - the old-school shoot-the-critters terminal game
 *
 * Critters go traipsing back and forth across the screen while the
 * user positions his cannon and tries to shoot them down before they
 * get to him and kill him.
 */
class Menagerie {
public:
    /**
     * Use the given display for this Menagerie game
     *
     * @param display  display to use
     */
    Menagerie(Display &display);

    // big 5
    ~Menagerie();
    Menagerie() = delete;
    Menagerie(const Menagerie &other) = delete;
    Menagerie(Menagerie &&temp) = delete;
    Menagerie& operator=(const Menagerie &other) = delete;
    Menagerie& operator=(Menagerie &&temp) = delete;

    /*
     * Reset to a fresh game state and play.
     */
    void play();

private:
    /**
     * @enum EventType - an event on the queue can be either a MOVE, saying move a Critter
     *                   or a COMMAND, saying we got a keystroke from the user
     */
    enum EventType {
        MOVE,       // Move the critter along
        COMMAND     // Keystroke from the user
    };

    /**
     * @struct Event - Event is a MOVE, in which case data is the index into our lists
     *                 for the corresponding Critter, i.e., critters.get(event.data)->move.
     *                 Or event is a COMMAND, in which case data is the key pressed.
     */
    struct Event {
        EventType type;
        int data;       // for MOVE, this is the index of the artifact
                        // for COMMAND, this is the keystroke character
        Event(EventType type = MOVE, int data = 0) : type(type), data(data) {}
        friend std::ostream& operator<<(std::ostream& out, const Event& event);
    };

    /**
     * number of events to process between display refreshes
     */
    static const int EVENT_CYCLE = 3;

    /**
     * number of scenes without movement to wait before game is over
     * (we detect movement by comparing previous scene painted to the display
     * and the current scene)
     */
    static const int NO_MOVEMENT = 50;

    /**
     * after a turn, the number of moves we will make before giving up on the
     * critter making an appearance on the screen
     */
    static const int TURN_REVIVAL = 10;

    /**
     * number of cannonballs to start each game
     * Once the user has shot this many, they cannot shoot any more.
     */
    static const int CANNON_BALLS = 7;

    /**
     * If this is true, then a call to the log() method writes some text to dbug.log.
     * Used for debugging, since it is difficult to print stuff out when the display
     * is active.
     */
    static const bool LOGGING = true;

    /**
     * How many events have been processed since start of game, resetGame()
     */
    int eventCount;

    /**
     * Last event when we saw some movement in scene (used to decide game over).
     * Game is over after NO_MOVEMENT number of events with no change in scene.
     */
    int lastMovement;

    /**
     * Number of cannonballs left to user for this game -- CANNON_BALLS less number used
     */
    int cannonballs;

    /**
     * Our display
     */
    Display& display;

    /**
     * Pixel map sent to display (is the composite of all the renderings)
     */
    PixelMatrix scene;

    /**
     * List of all the critters (pointers to them), nullptr if the critter is dead
     */
    ListA<Critter*> critters;

    /**
     * Queue of unprocessed events
     */
    QueueL<Event> events;

    /**
     * One pixel matrix for each critter (will be composited onto scene).
     * Filled in by getRenderings().
     */
    ListA<PixelMatrix> pxms;

    /**
     * Logfile used internally by log() if LOGGING == true
     */
    std::ostream *logfile;

    /**
     * empty out the data members: critters, events, etc.
     */
    void clear();

    /**
     * reset the game to original state -- ready for play()
     */
    void resetGame();

    /**
     * render each live critter into pxms
     * critters.get(i) is rendered into pxms.get(i)
     */
    void getRenderings();

    /**
     * Look for and process each collision.
     * A collision is where pxms.get(i).get(r,c) and pxms.get(j).get(r,c)
     * are both not transparent.
     *
     * For any collision, we kill both colliding critters with killCritter.
     */
    void processCollisions();

    /**
     * look for and process all side-of-screen critter turns
     *
     * We detect turns when a critter's rendering is a blank screen.
     * Then we rotate to get them pointing down, move, then rotate back
     * the other direction. If after this procedure and several moves (say
     * TURN_REVIVAL of them), we still have a blank rendering, then kill the
     * critter.
     */
    void doTurns();

    /**
     * do the compositing of all the critters
     * @return   true if we still have movement (within the last
     *           NO_MOVEMENT events
     */
    bool compositeScene();

    /**
     * Refresh the display with the current scene
     */
    void refreshDisplay();

    /**
     * process next event
     *
     * If it is a MOVE, look up the critter and if still alive, call its move()
     * method and queue another move.
     *
     * If it is a COMMAND, if data is:
     * 'q'  - quit current game (return false)
     * 'h'  - move Cannon (the user's Cannon is at critters.get(0))
     * 'g'  - reverse Cannon
     * 'i'  - shoot a Cannonball (call shoot())
     *
     * @return   true if game still alive (i.e., if the event wasn't a COMMAND('q'))
     */
    bool processEvent();

    /**
     * Make critter.get(i) dead
     * Delete and set to nullptr to indicate it is dead.
     *
     * @param i   critter index (into critters)
     */
    void killCritter(int i);

    /**
     * shoot a cannonball starting above user's Cannon (which is at critters.get(0)),
     * i.e. add a Cannonball critter to critters list and queue a MOVE event for it.
     */
    void shoot();

    /**
     * Write to log file, dbug.log if LOGGING is true.
     *
     * The log file, dbug.log, is rewritten for every game. It contains a timestamp and the output
     * from the given object (prefixed by the optional label). This is useful
     * for debugging while the display is taken over by the game.
     * @tparam T      datatype of object to be printed -- must support << operator
     * @param what    object to be printed
     * @param label   optional label to put next to timestamp
     */
    template <typename T>
    void log(const T &what, std::string label = "") const {
        if (logfile != nullptr) {
            time_t rawtime;
            time(&rawtime);
            std::string timestamp(ctime(&rawtime));
            timestamp.pop_back(); // strip trailing newline
            *logfile << timestamp << " " << label << "(" << eventCount << "):" << what << ":" << std::endl;
        }
    }

    /**
     * Printout Event to ostream.
     *
     * @param out    ostream to print out to
     * @param event  event to print
     * @return       ostream out when done
     */
    friend std::ostream& operator<<(std::ostream& out, const Menagerie::Event& event);

	/**
	 * Testing -- allows p1_test.cpp to work with private methods.
	 */
	FRIEND_TEST(P1Test, Test_Reset);
};


