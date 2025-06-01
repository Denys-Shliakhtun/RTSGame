


#include "UCPP_BuildingComponent.h"


// Sets default values for this component's properties
UCPP_BuildingComponent::UCPP_BuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCPP_BuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCPP_BuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCPP_BuildingComponent::ProducingUnitsCycle()
{
    if (UnitProductionQueue.IsEmpty())
    {
        IsProducingUnits = false;
        return;
    }

    IsProducingUnits = true;

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    TSubclassOf<AActor> UnitClass = UnitProductionQueue[0];

    FS_UnitPriceAndTime UnitPriceAndTime = GetUnitPriceAndTime(UnitClass);
    int32 Gold = GetResource(TEXT("Gold"));
    int32 Housing = GetResource(TEXT("Housing"));

    if (UnitPriceAndTime.Price <= Gold && Housing > 0)
    {
        ModifyResource(TEXT("Gold"), -UnitPriceAndTime.Price);

        // Find goal location
        TArray<UActorComponent*> GoalComponents = GetOwner()->GetComponentsByClass(USceneComponent::StaticClass());
        TArray<USceneComponent*> ValidLocations;

        for (UActorComponent* Comp : GoalComponents)
        {
            if (Comp->GetName().Contains(TEXT("Goal")))
            {
                if (USceneComponent* Scene = Cast<USceneComponent>(Comp))
                {
                    ValidLocations.Add(Scene);
                }
            }
        }

        if (ValidLocations.Num() > 0)
        {
            FVector SpawnLocation = ValidLocations[FMath::RandRange(0, ValidLocations.Num() - 1)]->GetComponentLocation();

            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, UnitClass, SpawnLocation]()
            {
                AActor* SpawnedUnit = GetWorld()->SpawnActor<AActor>(UnitClass, SpawnLocation, FRotator::ZeroRotator);
                if (SpawnedUnit)
                {
                    OnUnitCreated.Broadcast(SpawnedUnit);
                }

                UnitProductionQueue.RemoveAt(0);
                ProducingUnitsCycle();

            }, UnitPriceAndTime.TimeToProduce, false);

            return;
        }
    }

    UnitProductionQueue.RemoveAt(0);
    ProducingUnitsCycle();
}



