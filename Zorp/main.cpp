#include <iostream>

using std::cout;
using std::cin;

void main()
{
	cout << "Hello world!\n\n";

	int height = 0;
	int avatarHP = 0;
	char firstLetterOfName = 0;

	cout << "Welcome to Zorp!\n";
	cout << "Zorp is a game of adventure, danger, and low cunning.\n";
	cout << "It is definitely not related to any other text-based adventure game...\n";
	cin.get();

	cout << "First, some questions...\n";
	cin.get();

	cout << "How tall are you in centimeters?\n";
	cin >> height;

	if (cin.fail())
	{
		cout << "\nYou have failed the first challenge\nA trap door opens below your feet and the darkness consumes you as you fall\n";
		system("pause");
		cout << "\nYou wake to find your arms & legs scratched and battered\nLooking around in the dim light you see a larger gate roughly 100m away\n";
		system("pause");
		cout << "\nAs you notice, blinding lights brighten the area, revealing it to be a dugout in a cave\nThe ground shakes as the gate begins to open\n";
		system("pause");
		cout << "\nEmerging with a roar, a Rancor appears out of the shadows\nIn your injured state, you struggle to move\n";
		system("pause");
		cout << "\nIt sluggishly scoops down and grabs you in it's long limbs\nYou feel yourself getting crushed as it adjusts its grip on you\n";
		system("pause");
		cout << "\nIt shoves the upper part of your body in it's mouth and after a crunch, swallows it down\nIt then does the same with what's left of you\n";
		system("pause");
		cout << "\nYou have died\n";
	}
	else
	{
		cout << "You entered: " << height << "\n";
	}

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cout << "What is the first letter of your name?\n";
	cin >> firstLetterOfName;

	if (cin.fail() || !isalpha(firstLetterOfName))
	{
		cout << "\nYou have failed the second challenge\nThe sound of rushing water floods the room\n";
		system("pause");
		cout << "\nBefore you can even process what is happening, water fills the room to chest height\nThe flames from the torches get washed away\n";
		system("pause");
		cout << "\nDarkness drowns out the light leaving you frozen in fear, wishing you could see\n";
		system("pause");
		cout << "\nAs you try to take a deep breath, some water dives into your lungs, triggering a fit of coughing\nYou don't last 2 minutes\n";
		system("pause");
		cout << "\nYou have died\n";
		
	}
	else
	{
		cout << "You entered " << firstLetterOfName << "\n";
	}

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	if (firstLetterOfName != 0)
	{
		avatarHP = (float)height / (firstLetterOfName * 0.02f);
	}
	else
	{
		avatarHP = 0;
	}

	cout << "\nUsing a complex deterministic algorithm, it has been calculated that you have " << avatarHP << " hit point(s)\n";

	return;
}