// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "MeshUtils.h"

// Sets default values
ABall::ABall()
{
	//에셋이 있는 경로를 통해서 메시/메터리얼 에셋 불러오기
	MeshUtils::LoadMeshAndMaterial(BaseStaticMeshComp, EMeshType::Sphere, EMaterialType::BasicShape);

	BaseStaticMeshComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

