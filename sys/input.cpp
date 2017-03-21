#include <string>
#include "input.h"

int InputHandler::readInput(Character character)
{
	char str[5];
	switch (terminal_read()) {
	case TK_W:
		terminal_clear();
		character.yPosition++;
		terminal_print(4, 4, itoa(character.xPosition,str,10));
		terminal_print(4, 5, itoa(character.yPosition, str, 10));
		terminal_print(character.xPosition, character.yPosition, character.body);
		return TK_W;
	case TK_A:
		terminal_clear();
		character.xPosition--;
		terminal_print(4, 4, itoa(character.xPosition, str, 10));
		terminal_print(4, 5, itoa(character.yPosition, str, 10));
		terminal_print(character.xPosition, character.yPosition, character.body);
		return TK_A;
	case TK_S:
		terminal_clear();
		character.yPosition--;
		terminal_print(4, 4, itoa(character.xPosition, str, 10));
		terminal_print(4, 5, itoa(character.yPosition, str, 10));
		terminal_print(character.xPosition, character.yPosition, character.body);
		return TK_S;
	case TK_D:
		terminal_clear();
		character.xPosition++;
		terminal_print(4, 4, itoa(character.xPosition, str, 10));
		terminal_print(4, 5, itoa(character.yPosition, str, 10));
		terminal_print(character.xPosition, character.yPosition, character.body);
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

