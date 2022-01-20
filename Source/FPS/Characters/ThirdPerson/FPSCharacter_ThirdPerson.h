// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "GameFramework/Character.h"
#include "FPSCharacter_ThirdPerson.generated.h"

UCLASS()
class FPS_API AFPSCharacter_ThirdPerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter_ThirdPerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	// Set weapon
	void SetWeapon(class AFPSWeapon* _weapon);

	// Set&Get PatrolType
	void SetPatrolType(EPatrolType _type);
	const EPatrolType GetPatrolType();

	// Get a single patrol point
	// @Params 
	// VecPatrolPosition: vector reference for patrol location
	bool GetSinglePatrol_Position(FVector& VecPatrolPosition);

	const float GetRandomMove_PratrolRadius()	{return RandomMove_PatrolRadius;}

	void AimTarget(FVector TargetLocation);

	/** Invoke OnFire and set fire time **/
	void TurnOnFire();

	/** Actual Fire Action **/
	void OnFire();

	/** Stop Fire **/
	void TurnOffFire();

	/** On character is dead */
	void OnDead();

	const FTimerHandle GetFireHandle()	{return FireHandler;}

protected:
	/** On character is dead */
	void OnDeadAction();

/** Variables */
private:

	/************************************************************************/
	/**** Weapon  ****/

	// 기본 무기 클래스
	// Default weapon class
	UPROPERTY(EditAnywhere, Category = Weapon, meta= (AllowPrivateAccess = true) )
	TSubclassOf<class AFPSWeapon> DefaultWeaponClass;

	// 현재 장착 중인 무기
	// Current equipped weapon
	UPROPERTY(VisibleAnywhere, Category = Weapon, meta = (AllowPrivateAccess = true))
	class AFPSWeapon* Weapon;

	/************************************************************************/
	/**** Weapon  ****/
	UPROPERTY(VisibleAnywhere, Category = Stat, meta = (AllowPrivateAccess = true))
	class UStatComponent_ThirdPerson* CharacterStat;

/** Basic Components */
private:
	// Dead Action Handler
	FTimerHandle DeadActionHandler;

	// Fire Handler
	FTimerHandle FireHandler;

	// Dead Action wait time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = true))
	float DeadTimer;

/** UI Components */
private:
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* StatBarWidget;

/**	AI Component */
private:

	/************************************************************************/
	/**** Commonly use ****/

	// NPC's patrol type
	UPROPERTY(EditInstanceOnly, Category = AI, meta = (AllowPrivateAccess = true))
	EPatrolType PatrolType;

	/************************************************************************/
	/**** Single Patrol ****/

	// Single patrol point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = true))
	AActor*	SinglePatrol_Position;

	/************************************************************************/
	/**** Single Patrol ****/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = true))
	float RandomMove_PatrolRadius;

};
