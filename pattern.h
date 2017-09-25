/*
 * Pattern.h:
 *  Defines a Pattern abstraction and constants about patterns
 *  as a whole. Patterns may implement the init(), loop(),
 *  cleanup(), and isFinished() methods.
 */

#pragma once

#include "common.h"

class Pattern {
public:
    /*
     * Called once when a pattern begins. If you want, you can
     * put all of your logic in init() and disregard loop().
     */
    virtual void init() {}; // Called once when a pattern begins

    /*
     * Called continuously while a pattern runs; called instantly
     * as soon as it returns. This is mainly for convenience (and
     * to be more familiar to Arduino users) and need not contain
     * code if init() has an infinite loop or if you're getting
     * clever with something. To persist values across
     * iterations of loop(), use class private variables.
     */
    virtual void loop() {};

    /*
     * Called once when a pattern ends. Use to clean up resources,
     * finish operations cleanly, etc. Must terminate in reasonable
     * time to allow the next pattern to begin.
     */
    virtual void cleanup() {};

    /*
     * Retrn true when a pattern is finished, advancing the system
     * to the next pattern. Note that this switch will not take
     * place until loop() finishes, so patterns with loops or long
     * instructions within loop() may experience strange behavior.
     * To only switch the pattern when a button is pressed, just
     * return false.
     */
    virtual bool isFinished() { return false; }

    virtual ~Pattern() {} // No destructor required for patterns
};
