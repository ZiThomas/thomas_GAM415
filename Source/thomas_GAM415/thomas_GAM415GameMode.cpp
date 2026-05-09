// Copyright Epic Games, Inc. All Rights Reserved.

#include "thomas_GAM415GameMode.h"
#include "thomas_GAM415Character.h"
#include "UObject/ConstructorHelpers.h"

Athomas_GAM415GameMode::Athomas_GAM415GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
