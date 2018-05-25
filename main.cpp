#include <iostream>		// Like I said below, all feedback is appreciated and taken into consideration.
#include <cstdlib>
#include <Windows.h>
#include <stdio.h>
#include "cheat.h"
using namespace std;
bool fireStatus = false, knifeStatus = false;		//Global Bool functions to control on/off switches on Rapid Fire and Rapid knife cheats. 
void displayMenu();					//The menu displaying function.  It is located in the toggle.cpp file. 
bool toggleFunction(HANDLE hProcess, int hNumber, int32_t pLayer);

DWORD WINAPI RapidFire(LPVOID cheatOBJ);//Thread functions. Defined below main.
DWORD WINAPI RapidKnife(LPVOID cheatOBJ);


cheat* cheatObj = new cheat;	//Global Object, because I gotta use it in Thread Functions below.  I'm not sure if this is a good solution at the problem I had. 
int main()
{
	int32_t pLayer;
	bool flag = false;


	cheatObj->GetSetHandle();
	ReadProcessMemory(cheatObj->hProcess, (LPCVOID)(cheatObj->BaseAdress + cheatObj->offsetToLocalPlayer), &pLayer, sizeof(cheatObj->pLayer), NULL); //Dereferencing pointers to Offset to the local player
	cheatObj->pLayer = pLayer;//Seding pLayer address to the Object pLayer 										//For easier access inside main function.
	displayMenu();
	do
	{
		if (GetAsyncKeyState(0x74) & 1)							//0x74 == F5 key.
			toggleFunction(cheatObj->hProcess, 1, pLayer);
		else if (GetAsyncKeyState(0x75) & 1)						//0x75 == F6 key.
			toggleFunction(cheatObj->hProcess, 2, pLayer);
		else if (GetAsyncKeyState(0x76) & 1)						//0x76 == F7 key.
			toggleFunction(cheatObj->hProcess, 3, pLayer);
		else if (GetAsyncKeyState(0x77) & 1)						//0x77 == F8 key.
			toggleFunction(cheatObj->hProcess, 4, pLayer);
		else if (GetAsyncKeyState(0x78) & 1)						//0x78 == F9 key.
		{
			fireStatus = !fireStatus;
			if (fireStatus == true)
				CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RapidFire, 0, 0, 0);
		}
		else if (GetAsyncKeyState(0x79) & 1)						//0x79 == F10 key.
		{
			knifeStatus = !knifeStatus;
			if (knifeStatus == true)
				CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RapidKnife, 0, 0, 0);
		}
		else if (GetAsyncKeyState(0x30) & 1)						//0x30 == F11 key.
		{
			knifeStatus = false;
			fireStatus = false;
			flag = toggleFunction(cheatObj->hProcess, 0, pLayer);	//This flag is used for user exit. If game is closed before this is called, you'll get errors. Ignore them.
		}
		Sleep(200);
	} while (flag == false);

	cout << "Thank you for trying out my first project. All feedback is appreaciated and" << endl << "taken into consideration." << endl;

	cheatObj->closehandle();	//Closing Handle. 
	system("PAUSE");
	return(0);
}


DWORD WINAPI RapidFire(LPVOID Param)
{
	while (fireStatus == true)	//This is the RapidFire toggle check
	{
		cheatObj->rapidFire(cheatObj);
	}
	return(0);
}

DWORD WINAPI RapidKnife(LPVOID Param)	//This is the RapidKnife toggle check. 
{
	while (knifeStatus == true)
	{
		cheatObj->rapidKnife(cheatObj);
	}
	return(0);
}
