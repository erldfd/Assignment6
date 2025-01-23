// Fill out your copyright notice in the Description page of Project Settings.


#include "TransformationPlatform.h"

// Sets default values
ATransformationPlatform::ATransformationPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	ensure(MeshComp);

	SetRootComponent(MeshComp);

}

// Called when the game starts or when spawned
void ATransformationPlatform::BeginPlay()
{
	Super::BeginPlay();

	
	GetWorld()->GetTimerManager().SetTimer(TransformationTimerHandle, this, &ATransformationPlatform::ChangeMeshRandomly, 1, true);
}

void ATransformationPlatform::ChangeMeshRandomly()
{
	int32 MeshCount = TransformationMeshes.Num();

	if (MeshCount <= 0)
	{
		return;
	}

	MeshComp->SetStaticMesh(TransformationMeshes[FMath::RandRange(0, MeshCount - 1)]);
}
