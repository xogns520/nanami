#pragma once
class cAABB
{
public:
	cAABB();
	~cAABB();

	static bool IsCollision(ST_SPHERE* _Sphere1, ST_SPHERE* _Sphere2);
};

