// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AssignmentMapGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT6_API AAssignmentMapGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AAssignmentMapGameMode();
	
protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION(Exec)
	void SpawnPlatforms();

	UFUNCTION(Exec)
	void SpawnPlatform();

	void DestroyAllPlatforms();
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMovingPlatform> Model;

	TQueue<class AMovingPlatform*> SpawnedPlatforms;

	UPROPERTY()
	TArray<class AMovingPlatform*> SpawndPlatformList;

	TSet<TPair<int, int>> SpawnedPositionIndexSet;
	TMap<class AMovingPlatform*, TPair<int, int>> SpawnedPlatformMap;

	UPROPERTY()
	class AMovingPlatform* DeactivatedPlatform;

	UPROPERTY(EditAnywhere)
	int TotalSpawnCount = 1;

	int CurrentSpawnCount = 0;
};
