/**
 * @file adt/Display.h - Display ADT
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */
#pragma once
#include "../ListA.h"
#include "../PixelMatrix.h"

/**
 * @class Display - Display ADT
 *
 * Generic description of a pixel-based display with keyboard input.
 */
class Display {
public:
    /**
     * Get the dimensions of the terminal.
     *
     * @param rowCount  returned by reference the number of rows in the terminal emulator
     * @param colCount  returned by reference the number of columns in the terminal emulator
     */
    virtual void getSize(int &rowCount, int &colCount) const = 0;

    /**
     * Get the number of rows in the terminal.
     *
     * @return number of rows
     */
    virtual int getRowCount() const = 0;

    /**
     * Get the nubmer of columns in the display.
     *
     * @return number of columns
     */
    virtual int getColCount() const = 0;

    /**
     * Paint the display character cells with the color from the pxm (only those pixels which correspond
     * to valid character cells in the display). Pixel colors are given the best match of the available
     * colors. Character cells are "painted" by typing a space character with the color background most
     * closely matching the pixel color.
     *
     * @param pixels  the pixel map with the desired colors for each character cell
     */
    virtual void paint(const PixelMatrix &pixels) = 0;

    /**
     * Write some text onto the display.
     *
     * @param r     row where to start writing
     * @param c     column where to start writing
     * @param text  what to write
     */
    virtual void setText(int r, int c, const std::string &text) = 0;

    /**
     * Check if a key has been pressed and is waiting to be read.
     *
     * @return true if getKey will return with a key instantly.
     */
    virtual bool hasKey() const = 0;

    /**
     * Get the last keypress from the display.
     * Typically, this is an ASCII letter, like 'q'.
     * Other keys will be returned as values outside the ASCII range
     * (values of these will be added in a future version).
     * If there is no keypress waiting to be read, then the method
     * either blocks, waiting for a key from the display (if in blocking mode,
     * typically set during construction, is true) or throws (if blocking
     * mode is false).
     *
     * @return  the key pressed
     * @throws  logic_error if blockInGetKey is false and there is no key pressed
     */
    virtual int getKey() = 0;

	// non-ASCII keys
    static const int DOWN_ARROW_KEY	 = 0402;
    static const int UP_ARROW_KEY	 = 0403;
    static const int LEFT_ARROW_KEY	 = 0404;
    static const int RIGHT_ARROW_KEY = 0405;
    static const int BACKSPACE_KEY   = 0407;
    static const int ENTER_KEY       = 0527;

    /**
     * Simulate a key being pressed on the display. This is pushed onto the
     * beginning of the input queue from the display. There is a limit to how
     * many characters can be pushed determined by the details of the display.
     *
     * @param c  make this the next character read from getKey
     * @post     next getKey() == c (if no subsequent pushbackKey called)
     */
    virtual void pushbackKey(int c) = 0;

    /**
     * Get a list of the colors supported by the display emulator.
     *
     * @return  a list of the supported colors
     */
    virtual const ListA<RGB>& getColors() const = 0;

    virtual ~Display() {}  // make destructors virtual

};
