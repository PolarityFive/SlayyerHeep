#pragma once
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include "cheat.h"
using namespace std;
void error();
template <typename T>

bool WPM(HANDLE handle, const T& data, LPVOID address)//This is a wrapper template function. Basically, allows for various types of data and less typing. Thanks to @WLAN.
{
	return WriteProcessMemory(handle, address, &data, sizeof(T), nullptr);
}

//These functions should be self explanatory. "Cheat" class member functions.


cheat *off = new cheat; //Object declaration

HANDLE cheat::GetSetHandle()
{
	DWORD PID;
	cout << "Welcome user." << endl;
	cout << "Looking for assault cube window" << endl;
	HWND hwnd = NULL;
	do
	{
		hwnd = FindWindow(NULL, "AssaultCube");
		Sleep(1000);
	} while (hwnd == NULL);
	cout << "Window Found. Opening Process" << endl;

	GetWindowThreadProcessId(hwnd, &PID);
	HANDLE GameHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (GameHandle == NULL)
	{
		cout << "Opening proccess went wrong. Error code ------> " << GetLastError() << endl;
		cout << "Please report this error at the Unknown Cheats release thread along with the OS you're using." << endl;
		return(NULL);
	}
	else
	{
		hProcess = GameHandle;  //If you're looking at this, and you want to have a handle in another file/function, just include cheat.h, create a Handle and call this function. 
		return GameHandle;     // It's both a "Getter" and a "Setter". Depends on if you want to return a Handle.
	}

}

void cheat::setHealth(HANDLE hProcess, int32_t lPlayer)
{
	const int value = 9000;
	WPM(hProcess, value,(LPVOID)(lPlayer + off->m_health));
}

void cheat::setAmmo(HANDLE hProcess, int32_t lPlayer)
{
	const int value = 9000;
	WPM(hProcess, value, (LPVOID)(lPlayer + off->r_ammo));
	WPM(hProcess, value, (LPVOID)(lPlayer + off->m_magAmmo));
	WPM(hProcess, value, (LPVOID)(lPlayer + off->p_ammo));
}

void cheat::setArmor(HANDLE hProcess, int32_t lPlayer)
{
	const int value = 9000;
	WPM(hProcess, value, (LPVOID)(lPlayer + off->m_armor));
}

void cheat::noRecoil(HANDLE hProcess, int32_t lPlayer)
{

	DWORD protection = 0x10;
	DWORD protectionOld;
	const int value = 0;
	VirtualProtectEx(hProcess, (LPVOID)off->m_recoil, sizeof(off->m_recoil), protection, &protectionOld);//I don't know why this Address had protection and the others didn't. 
	WPM(hProcess, value, (LPVOID)(off->m_recoil));								//Maybe because I'm using a static address in m_recoil instead of 
	VirtualProtect((LPVOID)off->m_recoil, sizeof(off->m_recoil), protectionOld, NULL);			//Calculating it via offsets. 
}

void cheat::rapidFire(cheat* cheatOBJ)
{
	const int value = 70;
	int i;
	WORD arr[6] = { cheatOBJ->tArifle,cheatOBJ->tCarbine,cheatOBJ->tMgun,cheatOBJ->tShotgun,cheatOBJ->tSniper,cheatOBJ->tPistol };
	for (i = 0; i < 6; i++)														
	{
		WPM(hProcess, value, (LPVOID)(cheatOBJ->pLayer + arr[i]));
	}

}


void cheat::rapidKnife(cheat* cheatOBJ)
{
	const int value = 200;							//200 is a good value for me to have in Fast Knife. 
	WPM(hProcess, value, (LPVOID)(cheatOBJ->pLayer + cheatOBJ->KnifeTime));	//Going lower makes the animations weird.
}

void cheat::closehandle()
{
	delete off;  //I'm deleting the object here because this function is only called if the user decides to exit.
	CloseHandle(hProcess); 
}


void error()
{																																						
	cout << "Failed to WPR. " << endl;
	cout << "Last error: " << GetLastError() << endl;      
	system("PAUSE");
}
