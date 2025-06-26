// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "CoolFood.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"


class ASnakeElementBase;

UENUM()
enum class EMovementDirection
{
	Up,
	Down,
	Left,
	Right
};

UCLASS()
class SNAKEGAME_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementClass; // Class of the snake element

	UPROPERTY(BlueprintReadOnly)
	TArray<ASnakeElementBase*> SnakeElements; // Array to hold the snake elements

	UPROPERTY(EditDefaultsOnly)
	float ElementSize; // Size of the snake element

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

	UPROPERTY()
	EMovementDirection LastMoveDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddSnakeElement(int ElementsNum = 1); // Function to add a new snake element

	void Move();
	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other); // Function to handle overlap events
	
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFood> FoodClass;

	void SpawnFood();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACoolFood> CoolFoodClass;

	// метод для ускорения (если ещё нет)
	void SetSpeedMultiplier(float Multiplier);

	UPROPERTY(EditAnywhere, Category = "Food Spawn")
	int32 FoodSpawnRangeX = 5;

	UPROPERTY(EditAnywhere, Category = "Food Spawn")
	int32 FoodSpawnRangeY = 5;

	float BaseMovementSpeed = 10.f;
	float CurrentSpeedMultiplier = 1.f;
	FTimerHandle SpeedResetTimer;

	void ResetSpeed();
	

};
