// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/BTService_ThirdPerson_Detect.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/FPSCharacter.h"
#include "Characters/ThirdPerson/FPSAIController_ThirdPerson.h"
#include "DrawDebugHelpers.h"

UBTService_ThirdPerson_Detect::UBTService_ThirdPerson_Detect()
{
	NodeName = TEXT("Detect Player");
	Interval = 1.0f;
}

void UBTService_ThirdPerson_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(ControllingPawn == nullptr) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 1400.f;
	float AttackRange = 1000.f;

	bool isAttackable = false;
	AFPSCharacter* Target = nullptr;

	if(World == nullptr) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam);

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	DrawDebugSphere(World, Center, AttackRange, 16, FColor::Blue, false, 0.2f);

	if(bResult)
	{
		for(FOverlapResult OverlapResult : OverlapResults)
		{
			AFPSCharacter* FindCharacter = Cast<AFPSCharacter>(OverlapResult.GetActor());
			if(FindCharacter && FindCharacter->GetController()->IsPlayerController())
			{
				Target = FindCharacter;

				DrawDebugLine(World, Center, Target->GetActorLocation(), FColor::Orange, false, 0.2f);
				DrawDebugPoint(World, Target->GetActorLocation(), 10.f, FColor::Orange, false, 0.2f);

				float fDistance = FVector::Dist(Center, Target->GetActorLocation());

				if(fDistance <= AttackRange)
					isAttackable = true;

				break;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AFPSAIController_ThirdPerson::TargetKey, Target);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AFPSAIController_ThirdPerson::IsAttackableKey, isAttackable);
}
