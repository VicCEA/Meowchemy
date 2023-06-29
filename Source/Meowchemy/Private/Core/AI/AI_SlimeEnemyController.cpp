// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/AI_SlimeEnemyController.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AAI_SlimeEnemyController::AAI_SlimeEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAI_SlimeEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void AAI_SlimeEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AAI_SlimeEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// if (!M_PossessedPawn)return;

	const FVector StartVector = GetPawn()->GetActorLocation();
	const FVector EndVector = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	// EndVector.Normalize();

	TArray<FHitResult> HitResults;
	FCollisionShape ColShape = FCollisionShape::MakeSphere(TraceRadius);
	FCollisionQueryParams QueryParams;
	const AActor* SelfActor = GetPawn();
	QueryParams.AddIgnoredActor(SelfActor);

	bool Hit = GetWorld()->SweepMultiByChannel(HitResults, StartVector, EndVector, FQuat::Identity,
	                                           ECC_Visibility, ColShape, QueryParams);

	DrawDebugSphere(GetWorld(), StartVector, TraceRadius, 12, FColor::Orange, false);
	DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Orange, false);

	const FVector Direction = EndVector - StartVector;
	if (Direction.Length() <= TraceDistance)
	{
			DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Red, false);
			PlayerLocated = true;
		
		if (Hit)
		{

			for (FHitResult const HitResult : HitResults)
			{
				DrawDebugSphere(GetWorld(), HitResult.Location, TraceRadius / 2, 12, FColor::Red, false);

				const AActor* HitActor = HitResult.GetActor();
				if (HitActor->ActorHasTag("Player"))
				{
					GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Orange, FString::Printf(
						                                 TEXT("Hit: %s"), *HitResult.GetActor()->GetName()));
					// break;
				}
				// PlayerLocated = false;
			}
		}
	}
}
