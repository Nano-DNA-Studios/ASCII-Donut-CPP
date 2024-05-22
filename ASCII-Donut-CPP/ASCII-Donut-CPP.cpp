// ASCII-Donut-CPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Donut.h"

int main()
{
    std::cout << "Resize your console, once you're ready input (Y) : ";

	char reply;

    std::cin >> reply;

	reply = tolower(reply);

	if (reply == 'y')
    {
		Light* light = new Light(0, 1, -1, 50);

		Donut* donut = new Donut(light);

		while (true)
		{
			donut->A += 0.04f;
			donut->B += 0.02f;
			donut->drawDonut();
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
