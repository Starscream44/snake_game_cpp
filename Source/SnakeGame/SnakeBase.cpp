// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"
#include "CoolFood.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovementDirection::Down;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	BaseMovementSpeed = MovementSpeed;
	SetActorTickInterval(BaseMovementSpeed);
	AddSnakeElement(3);
	
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)

{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation;

		if (SnakeElements.Num() == 0)
		{
			// Первый сегмент — в позиции головы
			NewLocation = GetActorLocation();
		}
		else
		{
			// Все последующие — на месте последнего сегмента
			ASnakeElementBase* Tail = SnakeElements.Last();
			NewLocation = Tail->GetActorLocation();
		}

		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElem->SnakeOwner = this;

		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType();
		}
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector(ForceInitToZero);

	switch (LastMoveDirection)
	{
	case EMovementDirection ::Up:
		MovementVector.X += ElementSize;
		break;

	case EMovementDirection::Down:
		MovementVector.X -= ElementSize;
		break;

	case EMovementDirection::Left:
		MovementVector.Y += ElementSize;
		break;

	case EMovementDirection::Right:
		MovementVector.Y -= ElementSize;
		break;
	}

	//MovementVector.Z = 0.f;
	//AddActorWorldOffset(MovementVector);

	SnakeElements[0]->ToggleCollision();



	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor*Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this,bIsFirst);
		}
	}
}

void ASnakeBase::SpawnFood()
{
	FVector NewLocation;
	bool bValidLocationFound = false;
	int MaxTries = 100;

	while (!bValidLocationFound && MaxTries-- > 0)
	{
		int32 RandX = FMath::RandRange(-FoodSpawnRangeX, FoodSpawnRangeX);
		int32 RandY = FMath::RandRange(-FoodSpawnRangeY, FoodSpawnRangeY);
		NewLocation = FVector(RandX * ElementSize, RandY * ElementSize, 0.f);

		bValidLocationFound = true;
		for (auto* Elem : SnakeElements)
		{
			if (Elem->GetActorLocation().Equals(NewLocation, 0.1f))
			{
				bValidLocationFound = false;
				break;
			}
		}
	}

	if (bValidLocationFound)
	{
		// Выбор класса для спавна
		TSubclassOf<AFood> ClassToSpawn = FoodClass;
		if (FMath::FRand() < 0.3f) // 30% шанс
		{
			ClassToSpawn = CoolFoodClass;
		}

		//Спавн еды
		GetWorld()->SpawnActor<AFood>(ClassToSpawn, NewLocation, FRotator::ZeroRotator);
	}
}

void ASnakeBase::ResetSpeed()
{
	CurrentSpeedMultiplier = 1.f;
	SetActorTickInterval(BaseMovementSpeed);
}

void ASnakeBase::SetSpeedMultiplier(float Multiplier)
{
	if (Multiplier < CurrentSpeedMultiplier)
		return; // не даём сделать ещё быстрее

	CurrentSpeedMultiplier = Multiplier;
	SetActorTickInterval(BaseMovementSpeed / CurrentSpeedMultiplier);

	GetWorld()->GetTimerManager().ClearTimer(SpeedResetTimer);
	GetWorld()->GetTimerManager().SetTimer(SpeedResetTimer, this, &ASnakeBase::ResetSpeed, 5.f, false);
}

