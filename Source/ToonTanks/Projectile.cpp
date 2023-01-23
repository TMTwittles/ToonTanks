// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "HealthComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	RootComponent = MeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector HitNormal, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr) return;

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != nullptr && OtherActor != MyOwner)
	{
		UHealthComponent* OtherActorHealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
		if (OtherActorHealthComponent != nullptr)
		{
			OtherActorHealthComponent->TakeDamage(ProjectileDamageAmount);	
		}

		// THIS CODE DOES NOT WORK
		/*UGameplayStatics::ApplyDamage(
			OtherActor,
			ProjectileDamageAmount,
			MyOwnerInstigator,
			this,
			DamageTypeClass);*/
		
		Destroy();
	}
}

