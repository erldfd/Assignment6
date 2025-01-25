#include "AssignmentMapGameMode.h"

#include "MovingPlatform.h"

AAssignmentMapGameMode::AAssignmentMapGameMode()
{

}

void AAssignmentMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAssignmentMapGameMode::SpawnPlatforms, 3, true);

	for (int i = 0; i < TotalSpawnCount; ++i)
	{
		SpawnPlatform();
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAssignmentMapGameMode::SpawnPlatform, 0.2, true);

	DeactivatedPlatform = GetWorld()->SpawnActor<AMovingPlatform>(Model);
	DeactivatedPlatform->SetActorEnableCollision(false);
	DeactivatedPlatform->SetActorHiddenInGame(true);
}

void AAssignmentMapGameMode::SpawnPlatforms()
{
	if (Model == nullptr)
	{
		return;
	}

	if (SpawnedPlatforms.IsEmpty() == false)
	{
		DestroyAllPlatforms();
	}

	TSet<TPair<int, int>> DuplicateCheckSet;

	for (int i = 0; i < TotalSpawnCount; ++i)
	{
		while (true)
		{
			TPair<int, int> IndexPair;
			IndexPair.Key = FMath::RandRange(0, 10);
			IndexPair.Value = FMath::RandRange(0, 10);

			if (IndexPair.Key == 0 && IndexPair.Value == 0 ||
				IndexPair.Key == 10 && IndexPair.Value == 10 ||
				DuplicateCheckSet.Contains(IndexPair))
			{
				continue;
			}

			SpawnedPlatforms.Enqueue(GetWorld()->SpawnActor<AMovingPlatform>(Model, FVector(550 + 260 * IndexPair.Key, 2920 - 260 * IndexPair.Value, 200), FRotator::ZeroRotator));
			DuplicateCheckSet.Add(IndexPair);
			break;
		}
	}
}

void AAssignmentMapGameMode::SpawnPlatform()
{
	if (Model == nullptr)
	{
		return;
	}

	if (TotalSpawnCount <= 0)
	{
		return;
	}

	if (TotalSpawnCount < CurrentSpawnCount)
	{
		AMovingPlatform* Platform = SpawndPlatformList.Pop();
		SpawnedPositionIndexSet.Remove(SpawnedPlatformMap[Platform]);
		SpawnedPlatformMap.Remove(Platform);

		Platform->Destroy();
		CurrentSpawnCount--;
	}
	else if (TotalSpawnCount == CurrentSpawnCount)
	{
		while (true)
		{
			TPair<int, int> PositionIndexPair;
			PositionIndexPair.Key = FMath::RandRange(0, 10);
			PositionIndexPair.Value = FMath::RandRange(0, 10);

			if (PositionIndexPair.Key == 0 && PositionIndexPair.Value == 0 ||
				PositionIndexPair.Key == 10 && PositionIndexPair.Value == 10 ||
				SpawnedPositionIndexSet.Contains(PositionIndexPair))
			{
				continue;
			}


			int SelectedIndex = FMath::RandRange(0, CurrentSpawnCount - 1);
			AMovingPlatform* Temp = DeactivatedPlatform;

			DeactivatedPlatform = SpawndPlatformList[SelectedIndex];
			DeactivatedPlatform->SetActorEnableCollision(false);
			DeactivatedPlatform->SetActorHiddenInGame(true);

			SpawndPlatformList[SelectedIndex] = Temp;
			SpawndPlatformList[SelectedIndex]->SetActorEnableCollision(true);
			SpawndPlatformList[SelectedIndex]->SetActorHiddenInGame(false);

			SpawnedPositionIndexSet.Remove(SpawnedPlatformMap[DeactivatedPlatform]);
			SpawnedPositionIndexSet.Add(PositionIndexPair);
			if (SpawnedPlatformMap.Contains(SpawndPlatformList[SelectedIndex]))
			{
				SpawnedPlatformMap[SpawndPlatformList[SelectedIndex]] = PositionIndexPair;
			}
			else
			{
				SpawnedPlatformMap.Add(TPair<AMovingPlatform*, TPair<int, int>>(SpawndPlatformList[SelectedIndex], PositionIndexPair));
			}

			SpawndPlatformList[SelectedIndex]->SetActorLocation(FVector(550 + 260 * PositionIndexPair.Key, 2920 - 260 * PositionIndexPair.Value, 200), false, nullptr, ETeleportType::ResetPhysics);
			break;
		}
	
	}
	else // if (TotalSpawnCount > CurremteSpawnCount)
	{
		while (true)
		{
			TPair<int, int> PositionIndexPair;
			PositionIndexPair.Key = FMath::RandRange(0, 10);
			PositionIndexPair.Value = FMath::RandRange(0, 10);

			if (PositionIndexPair.Key == 0 && PositionIndexPair.Value == 0 ||
				PositionIndexPair.Key == 10 && PositionIndexPair.Value == 10 ||
				SpawnedPositionIndexSet.Contains(PositionIndexPair))
			{
				continue;
			}

			AMovingPlatform* Platform = GetWorld()->SpawnActor<AMovingPlatform>(Model, FVector(550 + 260 * PositionIndexPair.Key, 2920 - 260 * PositionIndexPair.Value, 200), FRotator::ZeroRotator);

			SpawndPlatformList.Emplace(Platform);
			SpawnedPositionIndexSet.Add(PositionIndexPair);
			SpawnedPlatformMap.Add(TPair<AMovingPlatform*, TPair<int, int>>(Platform, PositionIndexPair));
			CurrentSpawnCount++;

			break;
		}
	}
}

void AAssignmentMapGameMode::DestroyAllPlatforms()
{
	while (SpawnedPlatforms.IsEmpty() == false)
	{
		AMovingPlatform* Platform;

		SpawnedPlatforms.Dequeue(Platform);
		ensure(Platform);

		Platform->Destroy();
	}
}
