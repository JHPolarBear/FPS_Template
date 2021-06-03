// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float FireRate;
};
