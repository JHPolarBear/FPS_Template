// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/FPSWeapon.h"
#include "Items/Projectiles/FPSProjectile.h"

#include "Kismet/GameplayStatics.h"

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

}

// Called when the game starts or when spawned
void AFPSWeapon::BeginPlay()
{
	Super::BeginPlay();		


	auto GameInstance = Cast<UFPSGameInstance>(GetGameInstance());
	ASSERT_CHECK(GameInstance != nullptr)
	ItemData = GameInstance->GetItemData(0);
}

FItemData* AFPSWeapon::GetItemData() const
{
	return ItemData;
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
	return ItemData->FireRate;
}

void AFPSWeapon::SetProjectileBounce(bool _val)
{
	ItemData->IsProjectileBounce = _val;

	if(ProjectileClass)
	{
		AFPSProjectile* pProjectileClass = Cast<AFPSProjectile>(ProjectileClass);

		if(pProjectileClass)
			pProjectileClass->SetIsBounce(_val);
	}
}

float AFPSWeapon::GetProjectileBounce() const
{
	return ItemData->IsProjectileBounce;
}

AActor* AFPSWeapon::OnFire(FVector const& Location, FRotator const& Rotation, const FActorSpawnParameters& SpawnParameters /*= FActorSpawnParameters()*/)
{
	if(ProjectileClass)
	{
		auto Bullet = GetWorld()->SpawnActor<AFPSProjectile>(ProjectileClass, Location, Rotation, SpawnParameters);

		//return Bullet;
	}

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		LOG_WARNING(TEXT("Sound Start"));
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	OnWeaponStateChanged.Broadcast();

	return NULL;
}

