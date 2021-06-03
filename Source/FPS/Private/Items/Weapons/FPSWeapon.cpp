// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/FPSWeapon.h"

// Sets default values
AFPSWeapon::AFPSWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Mesh->SetOnlyOwnerSee(false);
	Mesh->bCastDynamicShadow = false;
	Mesh->CastShadow = false;

	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/FirstPerson/FPWeapon/Mesh/SK_FPGun.SK_FPGun"));
	if(SK_WEAPON.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_WEAPON.Object);
	}

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(Mesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	FireRate = 10.0f;
}

// Called when the game starts or when spawned
void AFPSWeapon::BeginPlay()
{
	Super::BeginPlay();	
}

void AFPSWeapon::SetHiddenInGame(bool NewHidden, bool bPropagateToChildren /*= false*/)
{
	Mesh->SetHiddenInGame(NewHidden, bPropagateToChildren);
}

FVector AFPSWeapon::GetMuzzleLocation() const
{
	if(MuzzleLocation)
		return MuzzleLocation->GetComponentLocation();
	
	return FVector::ZeroVector;
}

float AFPSWeapon::GetFireRate() const
{
	return FireRate;
}

