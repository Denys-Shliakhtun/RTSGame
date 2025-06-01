// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Unit.h"
#include "TimerManager.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACPP_Unit::ACPP_Unit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Unit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_Unit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPP_Unit::AttackThisActor(AActor* ActorToAttack)
{
    if (!IsValid(ActorToAttack))
    {
        StopAttack();
        return;
    }

    ActorToGo = ActorToAttack;
    HandleNewUnitState(E_UnitState::ChaseToAttack);

    // Bind OnDestroyed event of the target
    ActorToAttack->OnDestroyed.AddDynamic(this, &ACPP_Unit::OnTargetDestroyed);

    // Move to target
    AAIController* AICon = Cast<AAIController>(GetController());
    if (AICon && ActorToGo)
    {
        FAIRequestID MoveRequestID = AICon->MoveToActor(ActorToGo, AttackRange);
        if (!MoveRequestID.IsValid())
        {
            AttackThisActor(ActorToGo); // Retry logic
            return;
        }
    }

    // Ensure the actor is still valid after initiating movement
    if (!IsValid(ActorToGo))
    {
        StopAttack();
        return;
    }

    // Rotate unit to face the target (only Z axis)
    FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ActorToGo->GetActorLocation());
    SetActorRotation(FRotator(0.f, LookAtRotation.Yaw, 0.f));

    HandleNewUnitState(E_UnitState::Attacking);

    // Start attack timer (1 second interval)
    GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ACPP_Unit::Attack, AttackTime, true);
}

void ACPP_Unit::StopAttack()
{
    HandleNewUnitState(E_UnitState::Idle);
    GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}

void ACPP_Unit::Attack()
{
    // If the target actor is invalid, stop attacking and return
    if (!IsValid(ActorToGo))
    {
        StopAttack();
        return;
    }

    // Check if the target is within range and unit is in Attacking state
    float DistanceToTarget = FVector::Dist(GetActorLocation(), ActorToGo->GetActorLocation());
    if (DistanceToTarget <= AttackRange && UnitState == E_UnitState::Attacking)
    {
        UGameplayStatics::ApplyDamage(ActorToGo, DamageToApply, GetController(), this, nullptr);
        return;
    }

    // Otherwise, clear and invalidate the timer
    GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);

    // If still attacking and target is valid, reattempt attack
    if (UnitState == E_UnitState::Attacking && IsValid(ActorToGo))
    {
        AttackThisActor(ActorToGo);
    }
    else
    {
        StopAttack();
    }
}


void ACPP_Unit::HandleNewUnitState(E_UnitState NewState)
{
    UnitState = NewState;
}

void ACPP_Unit::OnTargetDestroyed(AActor* DestroyedActor)
{
    StopAttack();
}
