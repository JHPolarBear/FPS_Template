// Fill out your copyright notice in the Description page of Project Settings.
// 랜덤하게 네비게이션 볼륨 내부를 이동하는 캐릭터
// 예제로 사용하기 위해 별도 캐릭터 분리

#pragma once

#include "CommonDefines.h"
#include "GameFramework/Character.h"
#include "FPSCharacter_SimplePatrol.generated.h"

UCLASS()
class FPS_API AFPSCharacter_SimplePatrol : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter_SimplePatrol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 랠리 포인트의 좌표를 리턴
	bool GetRallyPoint_Pos(FVector& _pos);

private:
	// Static Mesh
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh_Static;

	// Patrol position of the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Patrol, meta = (AllowPrivateAccess = true))
	class AActor* RallyPoint;
};
