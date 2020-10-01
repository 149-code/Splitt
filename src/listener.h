#ifndef LISTENER_H
#define LISTENER_H

#include <stdio.h>
#include <stdbool.h>

#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

int start_listener();
char keycode_to_char(CGKeyCode keycode);

#endif
