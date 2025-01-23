// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class ASSIGNMENT6_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "PlatformSettings")
	float MoveSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "PlatformSettings")
	FVector StartPosition = FVector::Zero();

	UPROPERTY(EditAnywhere, Category = "PlatformSettings")
	FVector Destination = StartPosition;

	UPROPERTY(EditAnywhere, Category = "PlatformSettings")
	bool bIsPatrolling = false;

	UPROPERTY(EditAnywhere, Category = "PlatformSettings")
	float WaitingTime = 0;

	bool bIsMovingToDesination = false;
	bool bIsWaiting = false;

	float ElapsedTime = 0;
};
