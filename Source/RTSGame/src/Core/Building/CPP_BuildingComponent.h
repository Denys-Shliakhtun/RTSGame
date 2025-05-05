// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_BuildingComponent.generated.h"
static ConstructorHelpers::FClassFinder<enu> E_BuildingTypes(TEXT("/Game/Blueprints/BP_Enemy"));


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSGAME_API UCPP_BuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_BuildingComponent();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar();

	/** Please add a function description */
	UFUNCTION(BlueprintPure)
	void GetSuitableLocation(FVector ObjLocation, UBP_GoalLocationComponent_C*& SuitableLocationRef, UBP_GoalLocationComponent_C* ClosestPoint);

	/** Please add a function description */
	UFUNCTION(BlueprintPure)
	void GetUnitPriceAndTime(UClass* UnitToProduce, int32& Price, double& Time to Produce);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void GetUnitQueue(TMap<UClass*, int32>& UnitQueue, TMap<UClass*, int32> NewLocalVar);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	TEnumAsByte<E_BuildingTypes> TypeOfBuilding;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	double Health;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	double HealthMax;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "HealthBar")
	FVector2D HealthBarDrawSize;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "HealthBar")
	FVector HealthBarRelativeLocation;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	TEnumAsByte<ETeamAttitude::Type> TeamAttitude;

	/** Please add a variable description */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingDestroyed, AActor*, ActorDestroyed);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category = "Default")
	FOnBuildingDestroyed OnBuildingDestroyed;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	bool IsDestroyed;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	TArray<FS_UnitProducionInfo> UnitProductionInfo;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	TArray<UClass*> UnitProductionQueue;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	bool IsProducingUnits;

	/** Please add a variable description */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnitCreated, AActor*, Unit);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category = "Default")
	FOnUnitCreated OnUnitCreated;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	int32 HousingValue;

		
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// Delegate declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingDestroyed, AActor*, ActorDestroyed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnitCreated, AActor*, Unit);

/**
 * Please add a class description
 */
UCLASS(Blueprintable, BlueprintType)
class RTSGAME_API UCPP_BuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar();

	/** Please add a function description */
	UFUNCTION(BlueprintPure)
	void GetSuitableLocation(FVector ObjLocation, class UBP_GoalLocationComponent_C*& SuitableLocationRef, class UBP_GoalLocationComponent_C* ClosestPoint);

	/** Please add a function description */
	UFUNCTION(BlueprintPure)
	void GetUnitPriceAndTime(UClass* UnitToProduce, int32& Price, double& TimeToProduce);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void GetUnitQueue(TMap<UClass*, int32>& UnitQueue, const TMap<UClass*, int32>& NewLocalVar);

public:

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	TEnumAsByte<E_BuildingTypes> TypeOfBuilding;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	double Health;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	double HealthMax;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "HealthBar")
	FVector2D HealthBarDrawSize;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "HealthBar")
	FVector HealthBarRelativeLocation;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	TEnumAsByte<ETeamAttitude::Type> TeamAttitude;

	/** Please add a variable description */
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category = "Default")
	FOnBuildingDestroyed OnBuildingDestroyed;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	bool IsDestroyed;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	TArray<FS_UnitProducionInfo> UnitProductionInfo;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	TArray<UClass*> UnitProductionQueue;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	bool IsProducingUnits;

	/** Please add a variable description */
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category = "Default")
	FOnUnitCreated OnUnitCreated;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	int32 HousingValue;
};
