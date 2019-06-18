// Copyright Liu Hong 2019


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	IsDoorOpen = false;
	Owner = GetOwner();
	if (!PressurePlateOne) {
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName())
	}
}

void UOpenDoor::OpenDoor()
{
	IsDoorOpen = true;
	OnOpen.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	IsDoorOpen = false;	
	OnClose.Broadcast();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (!PressurePlateOne) { return; }
	if (PressurePlateOne && GetTotalMassOfActorsOnPlate(PressurePlateOne) == TriggerMass &&
		GetTotalMassOfActorsOnPlate(PressurePlateTwo) == TriggerMass2 && GetTotalMassOfActorsOnPlate(PressurePlateThree) ==
		TriggerMass3) {
		OpenDoor();
	}
	else {
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate(ATriggerVolume* PressurePlate)
{
	float TotalMass = 0.f;

	//Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* Element:OverlappingActors) {
		TotalMass += Element->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Element->GetName());
	}
	//Iterate all mass
	return TotalMass;
}