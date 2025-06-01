

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UCPP_BuildingComponent.generated.h"

USTRUCT(BlueprintType)
struct FS_UnitPriceAndTime
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 Price = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float TimeToProduce = 1.0f;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnitCreatedSignature, AActor*, CreatedUnit);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSGAME_API UCPP_BuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_BuildingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "UnitProduction")
    void ProducingUnitsCycle();

    //UPROPERTY(BlueprintAssignable, Category = "UnitProduction")
    //FOnUnitCreated OnUnitCreated;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UnitProduction")
    TArray<TSubclassOf<AActor>> UnitProductionQueue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UnitProduction")
    bool IsProducingUnits;

    UPROPERTY(BlueprintAssignable)
    FOnUnitCreatedSignature OnUnitCreated;

    UFUNCTION(BlueprintImplementableEvent, Category = "Production")
    FS_UnitPriceAndTime GetUnitPriceAndTime(TSubclassOf<AActor> UnitClass);	

    UFUNCTION(BlueprintImplementableEvent, Category = "Resources")
    int32 GetResource(const FString& ResourceName);

    UFUNCTION(BlueprintImplementableEvent, Category = "Resources")
    void ModifyResource(const FString& ResourceName, int32 Delta);  
};
