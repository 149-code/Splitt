#include "listener.h"

bool escape_seq = false;
bool ctrl = false;
int window = -1; // -1 is the none type

int keycodeIsNum(int keycode)
{
	switch (keycode) {
		case kVK_ANSI_1:
			return 1;
		case kVK_ANSI_2:
			return 2;
		case kVK_ANSI_3:
			return 3;
		case kVK_ANSI_4:
			return 4;
		case kVK_ANSI_5:
			return 5;
		case kVK_ANSI_6:
			return 6;
		case kVK_ANSI_7:
			return 7;
		case kVK_ANSI_8:
			return 8;
		case kVK_ANSI_9:
			return 9;
		default:
			return 0;
	}
}

char keycode_to_char(CGKeyCode keycode)
{
	switch (keycode) {
		case kVK_ANSI_A: return 'a';
		case kVK_ANSI_B: return 'b';
		case kVK_ANSI_C: return 'c';
		case kVK_ANSI_D: return 'd';
		case kVK_ANSI_E: return 'e';
		case kVK_ANSI_F: return 'f';
		case kVK_ANSI_G: return 'g';
		case kVK_ANSI_H: return 'h';
		case kVK_ANSI_I: return 'i';
		case kVK_ANSI_J: return 'j';
		case kVK_ANSI_K: return 'k';
		case kVK_ANSI_L: return 'l';
		case kVK_ANSI_M: return 'm';
		case kVK_ANSI_N: return 'n';
		case kVK_ANSI_O: return 'o';
		case kVK_ANSI_P: return 'p';
		case kVK_ANSI_Q: return 'q';
		case kVK_ANSI_R: return 'r';
		case kVK_ANSI_S: return 's';
		case kVK_ANSI_T: return 't';
		case kVK_ANSI_U: return 'u';
		case kVK_ANSI_V: return 'v';
		case kVK_ANSI_W: return 'w';
		case kVK_ANSI_X: return 'x';
		case kVK_ANSI_Y: return 'y';
		case kVK_ANSI_Z: return 'z';
		default: return '\0';
	}
}

CGEventRef handler(CGEventTapProxy proxy, CGEventType event_type, CGEventRef event, void *userInfo)
{
	CGKeyCode keycode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
	if (escape_seq && event_type == kCGEventKeyDown) {
		if (keycodeIsNum(keycode) != 0) {
			window = keycodeIsNum(keycode);
			return NULL;
		} else {
			do_shortcut(keycode_to_char(keycode), window);
			escape_seq = false;
                        window = -1;
			return NULL;
		}
	}

	if (event_type == kCGEventFlagsChanged && keycode == kVK_Control) {
		ctrl = !ctrl;
	}

	if (ctrl && event_type == kCGEventKeyDown && keycode == kVK_ANSI_S) {
		escape_seq = true;
		return NULL;
	}

	return event;
}

int start_listener()
{
	CGEventMask event_mask = (1 << kCGEventKeyDown) | 
		(1 << kCGEventKeyUp) | 
		(1 << kCGEventFlagsChanged);

	CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap,
			kCGHeadInsertEventTap,
			kCGEventTapOptionDefault,
			event_mask,
			handler,
			NULL);

	if (!eventTap) {
		fprintf(stderr, "ERROR: enable assistive devices & give application correct permisions");
		return 1;
	}

	CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
	CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
	CFRunLoopRun();

	return 0;
}
