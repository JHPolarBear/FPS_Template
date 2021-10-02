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

public:
	// Set weapon
	void SetWeapon(class AFPSWeapon* _weapon);

private:

	/** �⺻ ���� Ŭ���� */ 
	/** Default weapon class */
	UPROPERTY(EditInstanceOnly, Category = Weapon, meta= (AllowPrivateAccess = true) )
	TSubclassOf<class AFPSWeapon> DefaultWeaponClass;

	/** ���� ���� ���� ���� */
	/** Current equipped weapon */
	UPROPERTY(VisibleAnywhere, Category = Weapon, meta = (AllowPrivateAccess = true))
	class AFPSWeapon* Weapon;



	/*****************************************	****************************************/
	/***	AI Component								********************************/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = true))
	FVector	SingleRallyPoint;


};
