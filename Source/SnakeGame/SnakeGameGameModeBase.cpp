// Copyright Epic Games, Inc. All Rights Reserved.


#include "SnakeGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ASnakeGameGameModeBase::AddSnakeLength(int32 Amount)

{
    UE_LOG(LogTemp, Warning, TEXT("AddSnakeLength called! Current = %d, +%d"), SnakeLengthProgress, Amount);
    SnakeLengthProgress += Amount;

    if (SnakeLengthProgress >= MaxSnakeLengthGoal)
    {
        SnakeLengthProgress = MaxSnakeLengthGoal;

        // ���� ������ ���
        UE_LOG(LogTemp, Warning, TEXT("������! ���� �������� ������������ �����."));
        UGameplayStatics::OpenLevel(this, FName("WinScreen"));
    }
}