// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/ThirdPerson/AnimInstance_ThirdPerson.h"

UAnimInstance_ThirdPerson::UAnimInstance_ThirdPerson()
{
	Speed = 0.f;
}

void UAnimInstance_ThirdPerson::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if(::IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
	}
}
