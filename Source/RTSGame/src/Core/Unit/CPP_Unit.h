// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_Unit.generated.h"

UENUM(BlueprintType)
enum class E_UnitState : uint8
{
    Idle,
    ChaseToAttack,
    Attacking
};

UCLASS()
class RTSGAME_API ACPP_Unit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Unit();

	// The method to call for attacking an actor
    UFUNCTION(BlueprintCallable)
    void AttackThisActor(AActor* ActorToAttack);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Target the unit is currently moving to / attacking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	AActor* ActorToGo;

	// Attack range used to determine when to start attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackRange = 150.f;

	// Damage to apply
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DamageToApply = 10.f;

	// Time needed for separate attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackTime = 1.0f;

	// Unit state
	E_UnitState UnitState = E_UnitState::Idle;

	// Timer handle for repeating attacks
	FTimerHandle AttackTimerHandle;

	// Called when the target actor is destroyed
	UFUNCTION()
	void OnTargetDestroyed(AActor* DestroyedActor);

	// Stops the attack, clears state
	UFUNCTION(BlueprintCallable)
	void StopAttack();

	// Called every time the unit performs an attack
	UFUNCTION(BlueprintCallable)
	void Attack();

	// Handles switching the unit's behavior/state
	UFUNCTION(BlueprintCallable)
	void HandleNewUnitState(E_UnitState NewState);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
