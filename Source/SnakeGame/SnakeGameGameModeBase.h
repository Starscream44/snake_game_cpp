// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API ASnakeGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category = "Snake Progress")
	int32 SnakeLengthProgress = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Snake Progress")
	int32 MaxSnakeLengthGoal = 30;

	UFUNCTION(BlueprintCallable, Category = "Snake Progress")
	void AddSnakeLength(int32 Amount);
	
};
