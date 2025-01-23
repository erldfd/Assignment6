// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TransformationPlatform.generated.h"

UCLASS()
class ASSIGNMENT6_API ATransformationPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransformationPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void ChangeMeshRandomly();

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "PlatformSettings")
	TArray<UStaticMesh*> TransformationMeshes;

	FTimerHandle TransformationTimerHandle;

};
