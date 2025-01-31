#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObject.generated.h"

UCLASS()
class P6_API ABaseObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseObject();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Object|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object|Components")
	UStaticMeshComponent* BaseStaticMeshComp;
};
