#pragma once

#include "DPList.h"

class DPD3D;
class DPActor;

class DPGameEngine
{
public:
	DPGameEngine();
	~DPGameEngine() { }

	bool Tick(const float DeltaTime);
	void Draw(DPD3D* InD3D);

private:
	DPList<DPActor> ActiveActors;
	DPList<DPActor> InactiveActors;
};
