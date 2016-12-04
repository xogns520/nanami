#include "stdafx.h"
#include "cAABB.h"


cAABB::cAABB()
{
}


cAABB::~cAABB()
{
}

bool cAABB::IsCollision(ST_SPHERE * _Sphere1, ST_SPHERE * _Sphere2)
{
	float x2 = abs(_Sphere1->vCenter.x - _Sphere2->vCenter.x);
	float y2 = abs(_Sphere1->vCenter.y - _Sphere2->vCenter.y);
	float z2 = abs(_Sphere1->vCenter.z - _Sphere2->vCenter.z);

	float len = (x2 * x2) + (y2 * y2) + (z2 * z2);
	float R2 = (_Sphere1->fRadius + _Sphere2->fRadius) * (_Sphere1->fRadius + _Sphere2->fRadius);
	
	if (len < R2) return true;
	else return false;
}
