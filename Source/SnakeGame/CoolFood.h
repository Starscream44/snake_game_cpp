// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "GameFramework/Actor.h"
#include "CoolFood.generated.h"

UCLASS()
class SNAKEGAME_API ACoolFood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoolFood();

	virtual void Interact(AActor* Interactor, bool bIsHead);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};