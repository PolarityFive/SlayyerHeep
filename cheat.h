#pragma once
#pragma once
#include <iostream>
#include <cstdlib>
#include <Windows.h>

class cheat
{
public:
	int32_t BaseAdress = 0x400000;
	int32_t offsetToLocalPlayer = 0x10F4F4;
	int32_t pLayer;
	int32_t m_recoil = 0x4EE444;		//This address has protection. Maybe because I'm trying to access it directly. I'm not sure. Check the noRecoil function.
	HANDLE hProcess;
	WORD m_health = 0xF8;
	WORD m_armor = 0xFC;
	WORD m_magAmmo = 0x128;
	WORD r_ammo = 0x150;
	WORD p_ammo = 0x13C;
	WORD KnifeTime = 0x160;				// 350 Is a good value for Rapid Knife.. 
	WORD tCarbine = 0x168;
	WORD tPistol = 0x164;
	WORD tShotgun = 0x16C;				// 70 is a good value for Rapid Fire. 
	WORD tMgun = 0x170;
	WORD tSniper = 0x174;
	WORD tArifle = 0x178;
	WORD m_XPos = 0x38;
	WORD m_YPos = 0x3C;
	WORD m_ZPos = 0x40;
public:
	void setHealth(HANDLE hProcess, int32_t lPlayer);
	void setAmmo(HANDLE hProcess, int32_t lPlayer);
	void setArmor(HANDLE hProcess, int32_t lPlayer);
	void noRecoil(HANDLE hProcess, int32_t lPlayer);
	void rapidFire(cheat* cheatOBJ);
	void rapidKnife(cheat* cheatOBJ);
	void closehandle();
	HANDLE GetSetHandle();
};



//If you can't find an offset on this file, that means I don't have/use it. If an offset is incorrect, well, shit happens. I didn't get these myself. 
//Credits to many users accross the web from which I got the offsets. 
/*

Player Position XY : 0x4
Player Position XY : 0x8
Player Position Z : 0xC
Player Yaw : 0x40
Player Pitch : 0x44
Player Roll : 0x48
Player Health : 0xF8
Player Armor : 0xFC
Player Pistol : 0x114
Player Carbine : 0x118
Player Shotgun : 0x11C
Player MachineGun : 0x120
Player Sniper : 0x124
Player A - Rifle : 0x128
Player Pistol Clip : 0x13C
Player Carbine Clip : 0x140
Player Shotgun Clip 0x144
Player MachineGun Clip : 0x148
Player Sniper Clip : 0x14C
Player A - Rifle Clip : 0x150
Player Grenade Ammo : 0x158
Time Between Knifes : 0x160
Pistol Timer : 0x164
Carbine Timer : 0x168
Shotgun Timer : 0x16C
Machine Gun Timer : 0x170
Sniper Timer : 0x174
A - Rifle Timer : 0x178

EntityBase Offsets : 0x0
0x0 + (4 bytes per player)
*/
