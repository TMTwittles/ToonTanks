// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Check fire condition will get called every 2 seconds. 
	//GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (Tank != nullptr)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (Distance <= AttackDistance)
		{
			RotateTurret(Tank->GetActorLocation());
		}
	}*/
}

void ATower::CheckFireCondition()
{
	if (Tank != nullptr)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= AttackDistance)
		{
			Fire();
		}
	}
}
