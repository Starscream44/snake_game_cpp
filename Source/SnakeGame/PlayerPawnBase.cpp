// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "Components/InputComponent.h"


// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;
}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor();
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontalInput);

}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
}

void APlayerPawnBase::HandlePlayerVerticalInput(float Value)
{
	if (IsValid(SnakeActor))
	{
		if (Value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::Down)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::Up;
		}

		else if (Value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::Up)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::Down;
		}
	}
	
	
}

void APlayerPawnBase::HandlePlayerHorizontalInput(float Value)
{
	if (IsValid(SnakeActor))
	{
		if (Value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::Left)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::Right;
		}

		else if (Value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::Right)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::Left;
		}
	}
}

