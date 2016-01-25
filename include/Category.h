#ifndef CATEGORY_H
#define CATEGORY_H

// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Scene				= 1 << 0,
		PlayerShip		    = 1 << 1,
		AlliedShip	    	= 1 << 2,
		EnemyShip   		= 1 << 3,
		Planet         		= 1 << 4,
	};
}

#endif

