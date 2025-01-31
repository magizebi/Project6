// Fill out your copyright notice in the Description page of Project Settings.


#include "Helicopter.h"
#include "Ball.h"
#include "MeshUtils.h"

// Sets default values
AHelicopter::AHelicopter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlyingRadius = 100;
	Speed = 50;
	bClockwise = true;
	DropInterval = 3;
	FallingBall = ABall::StaticClass();
	CenterLocation = FVector(0, 0, 0);
}

void AHelicopter::Turn(float value)
{
	float AngularSpeed = (value / FlyingRadius) * (bClockwise ? 1.0f : -1.0f);

	AddActorLocalRotation(FRotator(0, AngularSpeed, 0));
}

void AHelicopter::Move(float value)
{
	AddActorLocalOffset(FVector(value, 0, 0));
}

void AHelicopter::DropBall()
{
	if (FallingBall)
	{

		FVector SpawnLocation = GetActorLocation() - FVector(0, 0, 100.0f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		AActor* SpawnedBall = GetWorld()->SpawnActor<AActor>(FallingBall, SpawnLocation, SpawnRotation);
		MeshUtils::ChangeActorMaterial(SpawnedBall, MeshUtils::GetRandomMaterial());
		if (SpawnedBall)
		{
			UE_LOG(LogTemp, Warning, TEXT("공 떨어져유!"));
		}
	}
}

void AHelicopter::CalcCenterLocation()
{
	FVector RightVector = GetActorRightVector();
	CenterLocation = GetActorLocation() + RightVector * FlyingRadius * (bClockwise ? 1.0f : -1.0f);
}

void AHelicopter::BeginPlay()
{
	Super::BeginPlay();

	CalcCenterLocation();
	// 타이머 설정
	GetWorldTimerManager().SetTimer(DropTimerHandle, this, &AHelicopter::DropBall, DropInterval, true);
}

void AHelicopter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Turn(Speed * DeltaTime);
	Move(Speed * DeltaTime);
}