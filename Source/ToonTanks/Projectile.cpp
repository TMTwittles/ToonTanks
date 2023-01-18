// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
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
	AActor* ProjectileOwner = GetOwner();
	if (ProjectileOwner == NULL)
	{
		return;
	}

	if (OtherActor == NULL || OtherActor == ProjectileOwner || OtherActor == this)
	{
		return;
	}
	
	AController* OwnerEventInstigator = ProjectileOwner->GetInstigatorController();
	UClass* DamageType = UDamageType::StaticClass();
	
	UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamageAmount, OwnerEventInstigator, this, DamageType);
}

