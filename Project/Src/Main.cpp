/*
	ถ๎๑rWlX๊ๅwZ kใBZ
	wะิF2209423
	ผFห{๑C
	vO}[
*/

#include "Game/GameSystem.h"

//Cึ
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Q[ฬNฎ
	BOUDAMA::GameSystem::Start();

	//Q[ฬ[v
	BOUDAMA::GameSystem::MainLoop();

	//Q[ฬIน
	BOUDAMA::GameSystem::Fin();

	//vOฬIน
	return 0;

}//WinMainึIํ่ส
