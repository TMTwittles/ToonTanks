// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank Components", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank Components", meta=(AllowPrivateAccess="true"))
	UCameraComponent* CameraComponent;

	void Move(float Value);

public:
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
