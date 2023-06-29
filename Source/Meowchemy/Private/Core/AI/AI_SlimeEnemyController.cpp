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

	const FVector StartVector = GetPawn()->GetActorLocation() + FVector(0, 0, 0);
	const FVector EndVector = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();

	const FVector Direction = EndVector - StartVector;

	TArray<FHitResult> HitResults;
	FCollisionShape ColShape = FCollisionShape::MakeSphere(TraceRadius);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool Hit = GetWorld()->SweepMultiByChannel(HitResults, StartVector, EndVector, FQuat::Identity,
	                                           ECC_Camera, ColShape, QueryParams);

	DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Orange, false);

	if (Direction.Length() <= TraceDistance)
	{
		if (Hit)
		{
			DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Red, false);

			for (FHitResult const HitResult : HitResults)
			{
				if (HitResult.bBlockingHit)
				{
					DrawDebugSphere(GetWorld(), HitResult.Location, TraceRadius / 2, 12, FColor::Red, false);

					const AActor* HitActor = HitResult.GetActor();
					if (HitActor->ActorHasTag("Player"))
					{
						// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(
						// 	                                 TEXT("Hit: %s"), *HitResult.GetActor()->GetName()));
						PlayerLocated = true;
					}
				}
			}
		}
	}
	else
	{
		PlayerLocated = false;
	}
}
