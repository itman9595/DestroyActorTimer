// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorTimer.h"

// Sets default values
AActorTimer::AActorTimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Comp"));
	RootComponent = SceneComponent;
	
	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Coundown Text"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	CountdownText->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	CountdownText->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CountdownTime = 3;
}

// Called when the game starts or when spawned
void AActorTimer::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AActorTimer::AdvanceTimer, 1.0f, true);
}

void AActorTimer::UpdateTimerDisplay()
{
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void AActorTimer::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay();
	if (CountdownTime < 1)
	{
		// We're done counting down, so stop running the timer.
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		//Perform any special actions we want to do when the timer ends.
		CountdownHasFinished();
	}
}

void AActorTimer::CountdownHasFinished()
{
	//Change to a special readout
	Destroy();
}

// Called every frame
void AActorTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

