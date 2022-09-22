// Copyright Epic Games, Inc. All Rights Reserved.

#include "HuluoluoGameMode.h"
#include "HuluoluoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHuluoluoGameMode::AHuluoluoGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_DodgeballCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
