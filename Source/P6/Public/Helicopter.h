// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Helicopter.generated.h"

UCLASS()
class P6_API AHelicopter : public AActor
{
	GENERATED_BODY()
	
public:	

	AHelicopter();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Helicopter|Properties", meta = (ClampMin = "0", ClampMax = "1000"))
	int32 Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Helicopter|Properties", meta = (ClampMin = "1", ClampMax = "10"))
	int32 DropInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Helicopter|Properties", meta = (ClampMin = "1", ClampMax = "100"))
	int32 FlyingRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Helicopter|Properties")
	bool bClockwise;  // true: 시계 방향, false: 반시계 방향

	TSubclassOf<AActor> FallingBall;
	FTimerHandle DropTimerHandle;

private:
	void Turn(float value);
	void Move(float value);
	void DropBall();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
