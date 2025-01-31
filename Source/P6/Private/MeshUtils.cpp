// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshUtils.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Math/UnrealMathUtility.h"

FString MeshUtils::GetMeshPath(EMeshType MeshAsset)
{
	switch (MeshAsset)
	{
	case EMeshType::Cone:
		return TEXT("/Engine/BasicShapes/Cone.Cone");
	case EMeshType::Cube:
		return TEXT("/Engine/BasicShapes/Cube.Cube");
	case EMeshType::Cylinder:
		return TEXT("/Engine/BasicShapes/Cylinder.Cylinder");
	case EMeshType::Plane:
		return TEXT("/Engine/BasicShapes/Plane.Plane");
	case EMeshType::Sphere:
		return TEXT("/Engine/BasicShapes/Sphere.Sphere");
	default:
		UE_LOG(LogTemp, Warning, TEXT("Mesh failed to load, default sphere is used."));
		break;
	}
	return FString();
}
/*
	BaseBlue,		/Engine/TemplateResources/MI_Template_BaseBlue_Metal.MI_Template_BaseBlue_Metal
	BaseOrange,		/Engine/TemplateResources/MI_Template_BaseOrange_Metal.MI_Template_BaseOrange_Metal
	BasicAsset01,	/Engine/MapTemplates/Materials/BasicAsset01.BasicAsset01
	BasicAsset02,	/Engine/MapTemplates/Materials/BasicAsset02.BasicAsset02
	BasicAsset03,	/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03
*/
FString MeshUtils::GetMaterialPath(EMaterialType MaterialAsset)
{
	switch (MaterialAsset)
	{
	case EMaterialType::BasicShape:
		return TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial");
	case EMaterialType::CineMat:
		return TEXT("/Engine/EditorMaterials/Camera/CineMat.CineMat");
	case EMaterialType::ClothMaterial:
		return TEXT("/Engine/EngineDebugMaterials/ClothMaterial.ClothMaterial");
	case EMaterialType::FlattenMaterial:
		return TEXT("/Engine/EngineMaterials/FlattenMaterial.FlattenMaterial");
	case EMaterialType::ColorGrid:
		return TEXT("/Engine/EditorMeshes/ColorCalibrator/M_ColorGrid.M_ColorGrid");
	case EMaterialType::BoneWeightMaterial:
		return TEXT("/Engine/EngineDebugMaterials/BoneWeightMaterial.BoneWeightMaterial");
	case EMaterialType::BasicAsset01:
		return TEXT("/Engine/MapTemplates/Materials/BasicAsset01.BasicAsset01");
	case EMaterialType::BasicAsset02:
		return TEXT("/Engine/MapTemplates/Materials/BasicAsset02.BasicAsset02");
	case EMaterialType::BasicAsset03:
		return TEXT("/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03");
	default:
		break;
	}
	return FString();
}

void MeshUtils::LoadMeshAndMaterial(UStaticMeshComponent* MeshComponent, EMeshType MeshAsset, EMaterialType MaterialAsset)
{
	LoadMesh(MeshComponent, MeshAsset);
	LoadMaterial(MeshComponent, MaterialAsset);
}

void MeshUtils::LoadMesh(UStaticMeshComponent* MeshComponent, EMeshType MeshAsset)
{
	FString MeshPath = GetMeshPath(MeshAsset);

	// 스태틱메시 로드 (런타임)
	UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *MeshPath));
	if (Mesh)
	{
		MeshComponent->SetStaticMesh(Mesh);
	}
}

void MeshUtils::LoadMaterial(UStaticMeshComponent* MeshComponent, EMaterialType MaterialAsset)
{
	FString MaterialPath = GetMaterialPath(MaterialAsset);

	// 매터리얼 로드 (런타임)
	UMaterial* Material = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), nullptr, *MaterialPath));
	if (Material)
	{
		MeshComponent->SetMaterial(0, Material);
	}
}

void MeshUtils::ChangeActorMaterial(AActor* Actor, EMaterialType MaterialAsset)
{
	UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Actor->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	LoadMaterial(MeshComp, MaterialAsset);
}

EMaterialType MeshUtils::GetRandomMaterial()
{
	int32 MinMaterial = static_cast<int32>(EMaterialType::BasicShape);
	int32 MaxMaterial = static_cast<int32>(EMaterialType::End) - 1;

	EMaterialType Material = static_cast<EMaterialType>(FMath::RandRange(MinMaterial, MaxMaterial));

	return Material;
}
