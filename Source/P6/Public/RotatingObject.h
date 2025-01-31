// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseObject.h"
#include "RotatingObject.generated.h"

UCLASS()
class P6_API ARotatingObject : public ABaseObject
{
	GENERATED_BODY()

public:
	// 이 액터의 기본 값 설정
	ARotatingObject();

protected:

	// Arm 컴포넌트를 저장할 배열
	UPROPERTY()
	TArray<UStaticMeshComponent*> ArmComponents;

	// Arm의 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object|Properties", meta = (ClampMin = "1", ClampMax = "8"))
	int32 NumberOfArms;

	// Arm의 길이
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object|Properties", meta = (ClampMin = "0.1", ClampMax = "10"))
	float ArmLength;

	// 회전 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Object|Properties", meta = (ClampMin = "0", ClampMax = "1000"))
	int32 RotationSpeed;

private:
	// Arms 배열을 초기화하는 함수
	void ResetArms();

protected:

	// Arm 컴포넌트를 생성하는 함수
	void CreateArmComponents();

	// 게임 시작 시 호출
	virtual void BeginPlay() override;

	// 생성자가 호출될 때 컴포넌트를 생성하는 함수
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// 매 프레임마다 호출
	virtual void Tick(float DeltaTime) override;

};