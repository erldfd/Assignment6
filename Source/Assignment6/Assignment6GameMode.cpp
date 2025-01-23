// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment6GameMode.h"
#include "Assignment6Character.h"
#include "UObject/ConstructorHelpers.h"

AAssignment6GameMode::AAssignment6GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
