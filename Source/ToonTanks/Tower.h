// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

class ATank;

UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tower Attributes", meta=(AllowPrivateAccess="true"))
	float AttackDistance;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.0f; // 2 Seconds. 

	void CheckFireCondition();
	
	ATank* Tank;
};

