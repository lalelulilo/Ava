#include <string>
#include "input.h"

InputHandler::InputHandler()
{
}

int InputHandler::readInput()
{
	switch (terminal_read()) {
	case TK_W:
		terminal_print(0, 0, "Oh, yeah!");
		return TK_W;
	case TK_A:
		terminal_print(0, 1, "Take off your pants and your panties.");
		return TK_A;
	case TK_S:
		terminal_print(0, 2, "Shit on the floor.");
		return TK_S;
	case TK_D:
		terminal_print(0, 3, "Time to get Schwifty in here.");
		return TK_D;
	case TK_BACKSPACE:
		terminal_clear();
		return TK_BACKSPACE;
	case TK_GRAVE:
		return TK_GRAVE;
	case TK_CLOSE:
		return TK_CLOSE;
	default:
		break;
	}

	return 0;
}

