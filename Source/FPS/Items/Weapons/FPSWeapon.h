// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "GameFramework/Actor.h"
#include "FPSWeapon.generated.h"

// delegate about weapon status(broadcast when weapon changed or ammo count changed)
// 무기가 변경되었거나, 무기의 상태(장탄 수 등)이 바뀌었을때 브로드캐스트되는 Delegate
DECLARE_MULTICAST_DELEGATE(FOnWeaponStateChangedDelegate);

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

	FOnWeaponStateChangedDelegate OnWeaponStateChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	// Skeletal mesh of weapon
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	USkeletalMeshComponent* Mesh;

	// Weapon ID
	UPROPERTY(Transient, VisibleAnywhere, Category = Weapon)
	int32	ID;

	// Weapon Type
	UPROPERTY(Transient, VisibleAnywhere, Category = Weapon)
	EItemTypes eType;

	// Weapon English name
	UPROPERTY(Transient, VisibleAnywhere, Category = Weapon)
	FString WeaponName_EN;

	// Weapon Thumbnail file name
	UPROPERTY(Transient, VisibleAnywhere, Category = Weapon)
	FString WeaponThumbnail_Path;

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
