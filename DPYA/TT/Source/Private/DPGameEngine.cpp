#include "DPGameEngine.h"

#include "DPD3D.h"
#include "DPActor.h"
#include "DPMesh.h"

DPGameEngine::DPGameEngine()
{
	for (unsigned int i = 0; i < 5; i++)
	{
		DPActor ActorTemp;
		ActorTemp.CreateMesh(MeshShape::MS_Rectangle, 20.f, 20.f, Vector3(-60.f + i*40.f, 0.f, 0.f), Vector4(1.f, 0.f, 0.f, 1.f));
		ActiveActors.PushBack(ActorTemp);
	}
}

bool DPGameEngine::Tick(const float DeltaTime)
{

	return true;
}

void DPGameEngine::Draw(DPD3D* InD3D)
{
	for (DPList<DPActor>::iterator ActorIt = ActiveActors.begin(); ActorIt != ActiveActors.end(); ActorIt++)
	{
		InD3D->Draw((*ActorIt).GetTM(), Matrix4x4::IdentityMatrix(), (*ActorIt).GetMesh().GetVertices(), (*ActorIt).GetMesh().GetIndices(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}