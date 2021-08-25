// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "GameFramework/Actor.h"
#include "FPSWeapon.generated.h"

UCLASS()
class FPS_API AFPSWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSWeapon();

	void SetHiddenInGame(bool NewHidden, bool bPropagateToChildren = false);

	FVector GetMuzzleLocation() const;

	float	GetFireRate() const;

	void	SetProjectileBounce(bool _val);
	float	GetProjectileBounce() const;

	virtual AActor* OnFire(FVector const& Location, FRotator const& Rotation, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	// Skeletal mesh of weapon
	UPROPERTY(VisibleAnyWhere, Category = Weapon)
	USkeletalMeshComponent* Mesh;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* MuzzleLocation;	

	/** Weapon Fire Rate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float FireRate;

	/** can the projectile from weapon can be bounce */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool  ProjectileBounce;

	
private:
	/** Weapon's component */
	/** Projectile class to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound;


	
};
