#include "BaseObject.h"

ABaseObject::ABaseObject()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	BaseStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BaseStaticMeshComp->SetupAttachment(SceneRoot);
}

