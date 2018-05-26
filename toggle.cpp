#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include "cheat.h"


cheat cToggle;
// I know this file is called toggle and contains both the toggle function and the menu. It's for ease of access when I add another feature. 

using namespace std;

bool toggleFunction(HANDLE hProcess, int hNumber, int32_t pLayer)  //This is just a toggle function. The second arguement of this function defines which cheat will be activated. These values are static.
{
	switch (hNumber)
	{
	case 1:
	{
		
		cToggle.setHealth(hProcess, pLayer);             //Normally, I'd use the Handle that is contained inside the cheat class 
		return(false);					 //but I didn't really want to open and close a million handles.
	}
	case 2:
	{
		
		cToggle.setArmor(hProcess, pLayer);
		return(false);
	}
	case 3:
	{
		
		cToggle.setAmmo(hProcess, pLayer);
		return(false);
	}
	case 4:
	{
		
		cToggle.noRecoil(hProcess, pLayer);
		return(false);
	}
	case 0:
		cout << "Exiting...." << endl;
		return(true);
		break;
	default:
		return(false);
	}
}


void displayMenu()			//If you want to add more features, don't forget to add a message to the menu.  
{
	cout << "=============Features=============" << endl;
	cout << "F5: Infinite Health. (Toggle only)" << endl;
	cout << "F6: Infinite Armor.  (Toggle ony)" << endl;
	cout << "F7: Infinite Ammo.   (Toggle Only)" << endl;
	cout << "F8: No-Recoil        (Toggle Only)" << endl;
	cout << "F9: Rapid Fire       (Toggle On/Off)" << endl;
	cout << "F10: Rapid knife     (Toggle On/Off)" << endl;
	cout << "0 to exit" << endl;
}
