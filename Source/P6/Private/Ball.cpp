// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "MeshUtils.h"

// Sets default values
ABall::ABall()
{
	//������ �ִ� ��θ� ���ؼ� �޽�/���͸��� ���� �ҷ�����
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

