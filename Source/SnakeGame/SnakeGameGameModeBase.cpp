// Copyright Epic Games, Inc. All Rights Reserved.


#include "SnakeGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ASnakeGameGameModeBase::AddSnakeLength(int32 Amount)

{
	//for debug purposes
    UE_LOG(LogTemp, Warning, TEXT("AddSnakeLength called! Current = %d, +%d"), SnakeLengthProgress, Amount);
    
    SnakeLengthProgress += Amount;

    if (SnakeLengthProgress >= MaxSnakeLengthGoal)
    {
        SnakeLengthProgress = MaxSnakeLengthGoal;

        //for debug purposes
        UE_LOG(LogTemp, Warning, TEXT("Win"));
        
        UGameplayStatics::OpenLevel(this, FName("WinScreen"));
    }
}