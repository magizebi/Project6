// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"
#include "Ball.h"
#include "MeshUtils.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComponent;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 500.f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bInheritPitch = true;
	SpringArmComp->bDoCollisionTest = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;


	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void AMyPawn::Move(const FInputActionValue& Value)
{
	const FVector MoveInput = Value.Get<FVector>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
	if (!FMath::IsNearlyZero(MoveInput.Z))
	{
		AddMovementInput(GetActorUpVector(), MoveInput.Z);
	}
}

void AMyPawn::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();

	if (!LookInput.IsNearlyZero())
	{
		AddControllerYawInput(LookInput.X);

		FRotator NewRotation = SpringArmComp->GetRelativeRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + LookInput.Y, -80.0f, 80.0f);
		SpringArmComp->SetRelativeRotation(NewRotation);
	}
	// 카메라가 상하로 움직이지 않아요.............
}

void AMyPawn::Drop(const FInputActionValue& Value)
{
	TSubclassOf<ABall> Ball = ABall::StaticClass();
	FVector Location = GetActorLocation() - FVector(0, 0, 150.0f);
	AActor* SpawnedBall = GetWorld()->SpawnActor<AActor>(Ball, Location, FRotator::ZeroRotator);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInput) return;

	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
	if (!PlayerController) return;

	if (PlayerController->MoveAction)
	{
		EnhancedInput->BindAction(
			PlayerController->MoveAction,
			ETriggerEvent::Triggered,
			this,
			&AMyPawn::Move
		);
	}

	if (PlayerController->LookAction)
	{
		EnhancedInput->BindAction(
			PlayerController->LookAction,
			ETriggerEvent::Triggered,
			this,
			&AMyPawn::Look
		);
	}

	if (PlayerController->DropAction)
	{
		EnhancedInput->BindAction(
			PlayerController->DropAction,
			ETriggerEvent::Started,
			this,
			&AMyPawn::Drop
		);
	}
}

