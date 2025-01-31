// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseObject.h"
#include "Ball.generated.h"

UCLASS()
class P6_API ABall : public ABaseObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
