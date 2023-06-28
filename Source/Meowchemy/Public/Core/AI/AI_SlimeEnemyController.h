// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_SlimeEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class MEOWCHEMY_API AAI_SlimeEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AAI_SlimeEnemyController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category="AI")
	float TraceRadius = 50.0f;
	
	UPROPERTY(EditAnywhere, Category="AI")
	float TraceDistance = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess=true))
	bool PlayerLocated = false;
};
