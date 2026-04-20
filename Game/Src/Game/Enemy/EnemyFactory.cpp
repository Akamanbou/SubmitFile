#include"Enemy.h"
using namespace std;

class EnemyFactory
{
public:
	static Enemy* CreateEnemy(const string& type, int x, int z)
	{
		if (type == "Normal")return new Enemy(x, z);
	}
};