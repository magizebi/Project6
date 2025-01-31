// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EMeshType : uint8
{
	Cone,
	Cube,
	Cylinder,
	Plane,
	Sphere
};

enum class EMaterialType : uint8
{
	BasicShape,			// ��� �ݼ� ����
	CineMat,			// ȸ�� �ݼ� ����
	ClothMaterial,		//������
	FlattenMaterial,	// ������ �ݼ� ����
	ColorGrid,
	BoneWeightMaterial,
	BasicAsset01,
	BasicAsset02,
	BasicAsset03,
	End
};

class UStaticMeshComponent;

class P6_API MeshUtils
{

private:
	static FString GetMeshPath(EMeshType MeshAsset);
	static FString GetMaterialPath(EMaterialType MaterialAsset);
public:
	// �޽ÿ� ���͸����� �������� �ҷ����� �Լ�
	static void LoadMeshAndMaterial(UStaticMeshComponent* MeshComponent, EMeshType MeshAsset, EMaterialType MaterialAsset);
	static void LoadMesh(UStaticMeshComponent* MeshComponent, EMeshType MeshAsset);
	static void LoadMaterial(UStaticMeshComponent* MeshComponent, EMaterialType MaterialAsset);
	static void ChangeActorMaterial(AActor* Actor, EMaterialType MaterialAsset);
	static EMaterialType GetRandomMaterial();
};;
