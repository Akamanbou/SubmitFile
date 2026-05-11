#pragma once
#include"Enemy.h"
using namespace std;

class EnemyFactory
{
public:
	static Enemy* CreateEnemy(const string& type, int x, int z);
};