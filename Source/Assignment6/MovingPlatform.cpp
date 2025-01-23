#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ensure(MeshComp);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsWaiting)
	{
		if (bIsPatrolling == false)
		{
			return;
		}

		ElapsedTime += DeltaTime;

		if (ElapsedTime >= WaitingTime)
		{
			bIsWaiting = false;
			ElapsedTime = 0;
		}

		return;
	}

	FVector CurrentPosition = GetActorLocation();
	float RemainingDistance = 0;
	FVector MoveDirection = FVector::Zero();
	float SpeedPerFrame = MoveSpeed * DeltaTime;

	if (bIsMovingToDesination)
	{
		MoveDirection = Destination - CurrentPosition;
		MoveDirection.Normalize();

		AddActorWorldOffset(MoveDirection * SpeedPerFrame);
		RemainingDistance = FVector::Distance(GetActorLocation(), Destination);
	}
	else
	{
		MoveDirection = StartPosition - CurrentPosition;
		MoveDirection.Normalize();

		AddActorWorldOffset(MoveDirection * SpeedPerFrame);
		RemainingDistance = FVector::Distance(GetActorLocation(), StartPosition);
	}

	if (FMath::IsNearlyZero(RemainingDistance, SpeedPerFrame))
	{
		bIsMovingToDesination = !bIsMovingToDesination;
		bIsWaiting = true;
	}
}

