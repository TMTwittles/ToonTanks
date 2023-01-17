// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerReference != nullptr)
	{
		FHitResult HitResult;
		bool Hit = PlayerControllerReference->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
			);

		if (Hit)
		{
			RotateTurret(HitResult.ImpactPoint);
		}
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerReference = Cast<APlayerController>(GetController());
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("FIRE"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = RootComponent->GetForwardVector();
	DeltaLocation.Normalize();
	DeltaLocation *= Value * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorWorldOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	float Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaRotation.Yaw = Yaw;
	AddActorWorldRotation(DeltaRotation, true);
}

