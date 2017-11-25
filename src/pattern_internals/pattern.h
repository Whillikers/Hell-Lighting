/**
 * @file pattern.h
 *
 * Abstraction and internals for patterns.
 *
 * Defines the Pattern superclass used for making every user-created pattern.
 * Also implements pattern factories, which are used to give patterns memory
 * when needed and not otherwise.
 */

#pragma once

#include "../common.h"

/**
 * A superclass and framework for all user-created patterns.
 *
 * Patterns are written by extending Pattern (or one of its abstract subclasses)
 * and filling in the methods, which are called by the system backend.
 */
class Pattern {
public:
    /**
     * Called once when a pattern begins.
     *
     * This method is called as soon as a pattern is loaded into memory and
     * should be used for initialization tasks, setup, etc. Can also in rare
     * cases implement the pattern's main functionality, leaving loop() empty.
     */
    virtual void init() {}; // Called once when a pattern begins

    /**
     * Called continuously while a pattern runs.
     *
     * This method is called immediately when [init()](@ref init()) or itself
     * returns. This is for convenience and to be more familiar for Arduino
     * users. To persist values across multiple iterations of loop(), use class
     * private variables. This method need not contain code if the pattern's
     * behavior is entirely determined by [init()](@ref init()).
     */
    virtual void loop() {};

    /**
     * Called once when a pattern ends.
     *
     * This method should be used to clean up resources, finish operations
     * cleanly, etc. Must return in reasonable time to allow the next pattern
     * to begin.
     */
    virtual void cleanup() {};

    /**
     * Returns true when a pattern is finished.
     *
     * When this method returns true, the system advances to the next pattern.
     * Note that this switch will not take place until [loop()](@ref loop())
     * returns. This method need not be implemented, in which case the pattern
     * will just switch when the button is pressed (which represents normal
     * behavior).
     *
     * @return True when the pattern is finished
     */
    virtual bool isFinished() { return false; }

    /**
     * Destructor.
     *
     * Generally, no destructor is required for pattterns.
     */
    virtual ~Pattern() {}
};

/**
 * General patttern factory superclass.
 *
 * It is used internally to create factories of arbitrary pattern types.
 */
class Factory {
public:
    /**
     * Return a new pattern instance.
     *
     * Creates a new pattern and gives it memory. Patterns must have their
     * memory freed manually.
     *
     * @return A new pattern instance with memory allocated
     */
    virtual Pattern* getInstance() = 0;
};

/**
 * Pattern-specific templated factory subclass.
 *
 * Used to create factories of specific patterns. Each pattern in the system
 * is represented by a single object of this class.
 *
 * @tparam The class of pattern represented by this template
 */
template<class pattern_type>
class PatternFactory: Factory {
public:
    Pattern* getInstance() {
        Pattern* pattern = new pattern_type();
        return pattern;
    }
};
