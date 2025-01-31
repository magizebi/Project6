// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingObject.h"
#include "MeshUtils.h"

// Sets default values
ARotatingObject::ARotatingObject()
{
    PrimaryActorTick.bCanEverTick = true;

    // 기본 메쉬와 머티리얼을 로드
    MeshUtils::LoadMeshAndMaterial(BaseStaticMeshComp, EMeshType::Cylinder, EMaterialType::FlattenMaterial);

    RotationSpeed = 100;
    NumberOfArms = 4;
    ArmLength = 1.f;
}

// Arm 배열 초기화
void ARotatingObject::ResetArms()
{
    // 기존 Arm들이 있을 경우 제거
    for (UStaticMeshComponent* Arm : ArmComponents)
    {
        if (Arm)
        {
            Arm->DestroyComponent();
        }
    }
    ArmComponents.Empty();
}

// Arm 컴포넌트 생성
void ARotatingObject::CreateArmComponents()
{
    ResetArms();

    // Arm들이 원형으로 배치될 수 있도록 각도를 나누기
    float AngleStep = 360.0f / NumberOfArms;

    for (int32 i = 0; i < NumberOfArms; i++)
    {
        // 런타임에서 새로운 컴포넌트 동적 추가
        UStaticMeshComponent* RectComp = NewObject<UStaticMeshComponent>(this);
        // 부모 컴포넌트(BaseStaticMeshComp)에 자식 컴포넌트(RectComp) 부착
        RectComp->AttachToComponent(BaseStaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);

        // 메쉬와 머티리얼 로드
        MeshUtils::LoadMeshAndMaterial(RectComp, EMeshType::Cube, EMaterialType::BasicShape);
        // 에디터에 컴포넌트 등록 (이걸 안 하면 에디터에서 컴포넌트가 보이지 않음)
        RectComp->RegisterComponent();

        // 기본 메시의 반지름 계산
        float BaseRadius = BaseStaticMeshComp->GetStaticMesh()->GetBoundingBox().GetSize().X * 0.5;
        // Arm의 반길이 계산
        float ArmHalfLength = RectComp->GetStaticMesh()->GetBoundingBox().GetSize().X * 0.5f * ArmLength;

        // 각 Arm의 위치 계산 (원형 배열에 맞게)
        float Angle = i * AngleStep;
        float X = FMath::Cos(FMath::DegreesToRadians(Angle)) * (BaseRadius + ArmHalfLength);
        float Y = FMath::Sin(FMath::DegreesToRadians(Angle)) * (BaseRadius + ArmHalfLength);

        // Arm의 상대 위치 설정
        RectComp->SetRelativeLocation(FVector(X, Y, 0.f));

        // Arm의 크기 설정 (ArmLength 기준으로 크기 조정)
        FVector Scale = FVector(ArmLength, 0.25f, 1.0f); // 기본적으로 좁은 직육면체
        RectComp->SetRelativeScale3D(Scale);

        // Arm이 원형을 따라 배치되도록 회전 설정
        FRotator Rotation = FRotator(0.0f, Angle, 0.0f); // Z축을 기준으로 회전
        RectComp->SetRelativeRotation(Rotation);

        // Arm을 배열에 추가
        ArmComponents.Add(RectComp);
    }
}

void ARotatingObject::BeginPlay()
{
    Super::BeginPlay();
}

// 액터가 생성될 때 호출
void ARotatingObject::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // Arm 컴포넌트 생성
    CreateArmComponents();
}

void ARotatingObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 원형 회전을 적용 (RotationSpeed에 따라 회전)
    AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}

