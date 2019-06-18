// Copyright Liu Hong 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIUHONGESCAPE_API UOpenDoor : public UActorComponent
{	
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	//return total mass in kg
	float GetTotalMassOfActorsOnPlate(ATriggerVolume* PressurePlate);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)

		FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

private:
	bool IsDoorOpen;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlateOne = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlateTwo = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlateThree = nullptr;

	UPROPERTY(EditAnywhere)
		float TriggerMass = 10.f;
	UPROPERTY(EditAnywhere)
		float TriggerMass2 = 11.f;
	UPROPERTY(EditAnywhere)
		float TriggerMass3 = 12.f;
	AActor* Owner = nullptr; // The owning door
};


