// Fill out your copyright notice in the Description page of Project Settings.


#include "CoolFood.h"
#include "SnakeBase.h"
#include "SnakeGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACoolFood::ACoolFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoolFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoolFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoolFood::Interact(AActor* Interactor, bool bIsHead)
{
    if (!bIsHead) return;

    auto Snake = Cast<ASnakeBase>(Interactor);
    if (!IsValid(Snake)) return;

    int32 Points = 1; // по умолчанию

    if (FMath::RandBool()) // 50%
    {
        Snake->SetSpeedMultiplier(2.f); // Ускорение
    }
    else
    {
        Snake->AddSnakeElement(2); // +2 блока
        Points = 2;
    }

    Snake->SpawnFood();

    ASnakeGameGameModeBase* GameMode = Cast<ASnakeGameGameModeBase>(UGameplayStatics::GetGameMode(this));
    if (GameMode)
    {
        UE_LOG(LogTemp, Warning, TEXT("CoolFood добавляет %d очков."), Points); //  для отладки
        GameMode->AddSnakeLength(Points);
    }

    Destroy();
}