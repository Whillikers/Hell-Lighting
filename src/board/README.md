This will eventually contain the board abstraction. A board object will
specify which hardware (from the HAL) it has, manage access to the
hardware and pin mappings, and handle setup/cleanup of hardware-specific
and board-specific features. It will also specify how much memory, etc the
board has. Patterns will have access to board definitions, specify which
hardware features / sensors / etc they require, and be passively disabled
when those features are not available.
