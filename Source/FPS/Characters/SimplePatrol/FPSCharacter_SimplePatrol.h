// Fill out your copyright notice in the Description page of Project Settings.
// �����ϰ� �׺���̼� ���� ���θ� �̵��ϴ� ĳ����
// ������ ����ϱ� ���� ���� ĳ���� �и�

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

	// ���� ����Ʈ�� ��ǥ�� ����
	bool GetRallyPoint_Pos(FVector& _pos);

private:
	// Static Mesh
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh_Static;

	// Patrol position of the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Patrol, meta = (AllowPrivateAccess = true))
	class AActor* RallyPoint;
};
