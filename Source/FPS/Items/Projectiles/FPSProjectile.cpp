// Copyright Epic Games, Inc. All Rights Reserved.

#include "Items/Projectiles/FPSProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

#include "Characters/ThirdPerson/FPSCharacter_ThirdPerson.h"

AFPSProjectile::AFPSProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(1.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 9750.f;
	ProjectileMovement->MaxSpeed = 9750.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) )
	{
		if(OtherComp->IsSimulatingPhysics())
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		if(IsBounce)
		{
			// Make Bounce
			ProjectileMovement->AddForce(GetVelocity() * -1 * 0.7f);
 
			//Destroy();
		}
		else
		{
			Destroy();
		}

		auto OtherCharacter = Cast<AFPSCharacter_ThirdPerson>(OtherActor);

		if(OtherCharacter != nullptr)
		{
			FDamageEvent DamageEvent;
			OtherCharacter->TakeDamage(DamageValue, DamageEvent, nullptr, this);
		}
	}
}

void AFPSProjectile::SetIsBounce(bool _val)
{
	IsBounce = _val;
}

bool AFPSProjectile::GetIsBounce() const
{
	return IsBounce;
}

void AFPSProjectile::SetDamageValue(float _val)
{
	DamageValue = _val;
}

float AFPSProjectile::GetDamageValue() const
{
	return DamageValue;
}
