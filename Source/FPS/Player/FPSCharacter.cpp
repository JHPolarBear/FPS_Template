// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/FPSCharacter.h"
#include "Player/FPSPlayerState.h"
#include "Player/FPSPlayerController.h"

#include "Items/Weapons/FPSWeapon.h"

#include "Items/Projectiles/FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId


DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AFPSCharacter

AFPSCharacter::AFPSCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	
	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	// Find Default weapon class and save into character's wepaon db	
	static ConstructorHelpers::FClassFinder<AFPSWeapon> BP_WEAPON_DEFAULT(TEXT("/Game/BluePrints/Weapons/BP_Weapon_Default.BP_Weapon_Default_C"));
	if (BP_WEAPON_DEFAULT.Succeeded())
	{
		WeaponClass = BP_WEAPON_DEFAULT.Class;		
	}

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

	IsShift = false;
}

void AFPSCharacter::SetWeapon(class AFPSWeapon* weapon)
{
	FP_Weapon = weapon;

	FP_Weapon->SetOwner(this);
	FP_Weapon->SetHiddenInGame(false);
	FP_Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("GripPoint"));
	
	FP_Weapon->OnWeaponChanged.Broadcast();
}

void AFPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	// Create and Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	if(WeaponClass != nullptr)
	{
		auto DefalutWeapon = GetWorld()->SpawnActor<AFPSWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		SetWeapon(DefalutWeapon);
	}

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}

	FPSPlayerController = Cast<AFPSPlayerController>(GetController());
	ASSERT_CHECK(FPSPlayerController != nullptr);

	FPSPlayerState = FPSPlayerController->GetPlayerState<AFPSPlayerState>();
	ASSERT_CHECK(FPSPlayerState != nullptr);

	FPSPlayerState->SetDefaultWalkSpeed(GetCharacterMovement()->MaxWalkSpeed);
	FPSPlayerState->SetRunMultiplier(2.0f);
}

void AFPSCharacter::Tick(float DeltaSeconds)
{
	if(FPSPlayerState)
	{
		if (IsShift == false)
		{
			FPSPlayerState->IncreaseAP();
		}

		if (FPSPlayerState->GetCurrentAP() <= 0.f)
		{
			GetCharacterMovement()->MaxWalkSpeed = FPSPlayerState->GetDefaultWalkSpeed();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::TurnOnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::TurnOffFire);

	// Bind Shift pressed
	PlayerInputComponent->BindAction("Shift", IE_Pressed, this, &AFPSCharacter::OnShift);
	PlayerInputComponent->BindAction("Shift", IE_Released, this, &AFPSCharacter::OffShift);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFPSCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPSCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPSCharacter::LookUpAtRate);
}

void AFPSCharacter::OnFire()
{
	// try and fire a projectile
	if (FP_Weapon != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// Diable VR Fire Function temporary
			if (bUsingMotionControllers)
			{
				/*const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
				const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
				World->SpawnActor<AFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);*/
			}
			else
			{
				const FRotator SpawnRotation = GetControlRotation();

				// Weapon's projectile start location
				FVector WeaponMuzzleLocation = FVector::ZeroVector; 
				if(FP_Weapon)
				{
					WeaponMuzzleLocation = FP_Weapon->GetMuzzleLocation();
				}

				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((WeaponMuzzleLocation != FVector::ZeroVector) ? WeaponMuzzleLocation : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				// Activate equipped player weapon
				FP_Weapon->OnFire(SpawnRotation);

				// Shake camera
				World->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake, 1.0);
			}
		}
	}

	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AFPSCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFPSCharacter::OnShift()
{
	IsShift = true;

	if(FPSPlayerState->GetCurrentAP() > 0.f)
	{
		GetCharacterMovement()->MaxWalkSpeed *= FPSPlayerState->GetRunMultiplier();
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = FPSPlayerState->GetDefaultWalkSpeed();
	}
}

void AFPSCharacter::OffShift()
{
	IsShift = false;

	GetCharacterMovement()->MaxWalkSpeed = FPSPlayerState->GetDefaultWalkSpeed();	
}

void AFPSCharacter::TurnOnFire()
{
	OnFire();

	UWorld* World = GetWorld();
	if(World)
	{
		float FireRate = 1.f;
		
		if(FP_Weapon)
			FireRate = FP_Weapon->GetFireRate();

		World->GetTimerManager().SetTimer(FireHandler, this, &AFPSCharacter::OnFire, 1.0f/FireRate, true);
	}
}


void AFPSCharacter::TurnOffFire()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(FireHandler);
	}
}

void AFPSCharacter::OnDead()
{
	// Simply destroy character
	Destroy();
}

void AFPSCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AFPSCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AFPSCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void AFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		if(IsShift)
		{
			FPSPlayerState->DecreaseAP();
		}

		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPSCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPSCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AFPSCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AFPSCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AFPSCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AFPSCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}
