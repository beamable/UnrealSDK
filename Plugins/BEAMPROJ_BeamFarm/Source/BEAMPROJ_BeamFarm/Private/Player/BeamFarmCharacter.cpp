// Copyright Beamable, Inc. All Rights Reserved.

#include "Player/BeamFarmCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

ABeamFarmCharacter::ABeamFarmCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PathFollowingComp = nullptr;
}

void ABeamFarmCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Create PathFollowingComponent if it doesn't exist
	if (PathFollowingComp == nullptr)
	{
		PathFollowingComp = NewObject<UPathFollowingComponent>(this);
		PathFollowingComp->RegisterComponentWithWorld(GetWorld());
		PathFollowingComp->Initialize();
	}
	
	// Bind to the path following completion delegate
	if (PathFollowingComp)
	{
		PathFollowingComp->OnRequestFinished.AddUObject(this, &ABeamFarmCharacter::OnMoveCompleted);
	}
}

void ABeamFarmCharacter::MoveToWorldLocation(const FVector& Destination)
{
	if (!PathFollowingComp || !Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("BeamFarmCharacter: PathFollowingComp or Controller is null"));
		return;
	}

	// Stop any existing movement
	if (bMovingToTarget)
	{
		PathFollowingComp->AbortMove(*this, FPathFollowingResultFlags::MovementStop);
	}

	const FVector AgentNavLocation = Controller->GetNavAgentLocation();
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	
	if (!NavSys)
	{
		UE_LOG(LogTemp, Warning, TEXT("BeamFarmCharacter: Navigation system not found"));
		return;
	}

	const ANavigationData* NavData = NavSys->GetNavDataForProps(Controller->GetNavAgentPropertiesRef(), AgentNavLocation);
	if (NavData)
	{
		FPathFindingQuery Query(Controller, *NavData, AgentNavLocation, Destination);
		FPathFindingResult Result = NavSys->FindPathSync(Query);
		
		if (Result.IsSuccessful())
		{
			FAIMoveRequest MoveRequest(Destination);
			MoveRequest.SetAcceptanceRadius(ArrivalThreshold);
			MoveRequest.SetUsePathfinding(true);
			
			CurrentMoveRequestID = PathFollowingComp->RequestMove(MoveRequest, Result.Path);
			
			if (CurrentMoveRequestID.IsValid())
			{
				bMovingToTarget = true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BeamFarmCharacter: Path finding failed"));
			if (PathFollowingComp->GetStatus() != EPathFollowingStatus::Idle)
			{
				PathFollowingComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Invalid);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BeamFarmCharacter: No navigation data found"));
	}
}

void ABeamFarmCharacter::StopMovementToTarget()
{
	bMovingToTarget = false;

	if (PathFollowingComp)
	{
		PathFollowingComp->AbortMove(*this, FPathFollowingResultFlags::MovementStop);
	}
	
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->StopMovementImmediately();
	}
}

void ABeamFarmCharacter::OnMoveCompleted(FAIRequestID FaiRequestID, const FPathFollowingResult& PathFollowingResult)
{
	// Only process if this is our current move request
	if (FaiRequestID != CurrentMoveRequestID)
	{
		return;
	}


	bMovingToTarget = false;

	// Only broadcast completion if movement succeeded
	if (PathFollowingResult.Code == EPathFollowingResult::Success)
	{
		OnMovementComplete.Broadcast();
	}
}
