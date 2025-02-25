#include <iostream>
#include <Windows.h>

using std::cout;
using std::cin;

//Console commands for universal functionality
const char* ESC = "\x1b";
const char* CSI = "\x1b[";
const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\x1b[5C";
const char* YELLOW = "\x1b[93m";
const char* MAGENTA = "\x1b[95m";
const char* RESET_COLOR = "\x1b[0m";
const char* SAVE_CURSOR_POS = "\x1b[s";
const char* RESTORE_CURSOR_POS = "\x1b[u";

void main()
{
	//Set output mode to handle virtual terminal sequences
	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	cout << "Hello world!\n\n";

	int height = 0;
	int avatarHP = 0;
	char firstLetterOfName = 0;

	cout << TITLE << MAGENTA << "Welcome to Zorp!\n" << RESET_COLOR;
	cout << INDENT << "Zorp is a game of adventure, danger, and low cunning.\n";
	cout << INDENT << "It is definitely not related to any other text-based adventure game...\n";
	cin.get();

	cout << "First, some questions...\n";
	cin.get();

	//Save cursor position
	cout << SAVE_CURSOR_POS;
	cout << INDENT << "How tall are you in centimeters?\n" << INDENT << YELLOW;
	cin >> height;
	cout << RESET_COLOR;

	if (cin.fail())
	{
		cout << INDENT << "\nYou have failed the first challenge\nA trap door opens below your feet and the darkness consumes you as you fall\n";
		cout << INDENT << "\nYou wake to find your arms & legs scratched and battered\nLooking around in the dim light you see a larger gate roughly 100m away\n";
		cout << INDENT << "\nAs you notice, blinding lights brighten the area, revealing it to be a dugout in a cave\nThe ground shakes as the gate begins to open\n";
		cout << INDENT << "\nEmerging with a roar, a Rancor appears out of the shadows\nIn your injured state, you struggle to move\n";
		cout << INDENT << "\nIt sluggishly scoops down and grabs you in it's long limbs\nYou feel yourself getting crushed as it adjusts its grip on you\n";
		cout << INDENT << "\nIt shoves the upper part of your body in it's mouth and after a crunch, swallows it down\nIt then does the same with what's left of you\n";
		cout << INDENT << "\nYou have died\n";
	}
	else
	{
		cout << INDENT << "You entered: " << height << "\n\n";
	}

	//Clear input buffer
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

	//Move the cursor to the start of the 1st question
	cout << RESTORE_CURSOR_POS;
	//Delete the next 4 lines of text
	cout << CSI << "4M";

	cout << INDENT << "What is the first letter of your name?\n" << INDENT << YELLOW;
	cin >> firstLetterOfName;
	cout << RESET_COLOR;

	if (cin.fail() || !isalpha(firstLetterOfName))
	{
		cout << INDENT << "\nYou have failed the second challenge\nThe sound of rushing water floods the room\n";
		cout << INDENT << "\nBefore you can even process what is happening, water fills the room to chest height\nThe flames from the torches get washed away\n";
		cout << INDENT << "\nDarkness drowns out the light leaving you frozen in fear, wishing you could see\n";
		cout << INDENT << "\nAs you try to take a deep breath, some water dives into your lungs, triggering a fit of coughing\nYou don't last 2 minutes\n";
		cout << INDENT << "\nYou have died\n";
		
	}
	else
	{
		cout << INDENT << "You entered " << firstLetterOfName << "\n";
	}

	//Clear input buffer
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

	//Move the cursor to the start of the 1st question
	cout << RESTORE_CURSOR_POS;
	//Cursor up 1
	cout << CSI << "A";
	//Delete the next 4 lines of text
	cout << CSI << "4M";

	if (firstLetterOfName != 0)
	{
		avatarHP = (float)height / (firstLetterOfName * 0.02f);
	}
	else
	{
		avatarHP = 0;
	}

	cout << INDENT << "\nUsing a complex deterministic algorithm, it has been calculated that you have " << avatarHP << " hit point(s)\n";

	return;
}