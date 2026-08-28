![Screenshot](https://github.com/JoeDavisson/JoeCalc/blob/master/screenshots/screenshot.png)

### Overview

JoeCalc is a calculator with a C-style interface. Input equations may include a mix of number bases and bitwise operators: decimal, hexadecimal, octal, and binary are supported.

### Using the Calculator

The input field accepts numbers prefixed with 0x, 0o, 0b (hexadecimal, octal, binary). Hitting <kbd>return</kbd> calculates the result. The buttons to the right of the display work directly on the result.

Text may be copied from the output display to the input field by either using cut/paste via the right-click menus, or <kbd>Ctrl-C</kbd> and <kbd>Ctrl-V</kbd> . The insert ins key copies selected text from the display to the input field at the current cursor position.

The field supports undo/redo via <kbd>Ctrl-Z</kbd> and <kbd>Shift-Ctrl-Z</kbd>, or simply use the up/down arrow keys.

Adding a function will automatically surrounds any selected text in the input field.

FLTK 1.4.x supports DPI scaling with <kbd>Ctrl +</kbd>, <kbd>Ctrl -</kbd>. Reset to 100% with <kbd>Ctrl 0</kbd>.

### Notes

* Prefixes are required for hexadecimal, octal, and binary, regardless of the output mode.
* Input may be signed or unsigned, but non-decimal results are always displayed as unsigned.
* Bitwise operations truncate the immediate results of those operations.
* Results are limited to the INT64_MIN / UINT64_MAX range.

### Building

Please see the Makefile for compilation instructions.

### Dependencies

* fltk-1.4.5 source
