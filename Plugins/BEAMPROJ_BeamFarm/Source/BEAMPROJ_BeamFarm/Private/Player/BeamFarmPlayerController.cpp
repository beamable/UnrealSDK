// Copyright Beamable, Inc. All Rights Reserved.

#include "Player/BeamFarmPlayerController.h"
#include "Player/BeamFarmCharacter.h"
#include "Interaction/BeamFarmInteractable.h"

ABeamFarmPlayerController::ABeamFarmPlayerController()
{
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ABeamFarmPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ABeamFarmPlayerController::HandleClick);
	InputComponent->BindTouch(IE_Pressed, this, &ABeamFarmPlayerController::HandleTouch);
}

void ABeamFarmPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckProximityAndInteract();
}

void ABeamFarmPlayerController::HandleClick()
{
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		ProcessHitResult(HitResult);
	}
}

void ABeamFarmPlayerController::HandleTouch(ETouchIndex::Type FingerIndex, FVector TouchLocation)
{
	FHitResult HitResult;
	if (GetHitResultUnderFinger(FingerIndex, ECC_Visibility, false, HitResult))
	{
		ProcessHitResult(HitResult);
	}
}

void ABeamFarmPlayerController::ProcessHitResult(const FHitResult& HitResult)
{
	AActor* HitActor = HitResult.GetActor();

	if (HitActor && HitActor->Implements<UBeamFarmInteractable>())
	{
		TScriptInterface<IBeamFarmInteractable> Interactable;
		Interactable.SetObject(HitActor);
		Interactable.SetInterface(Cast<IBeamFarmInteractable>(HitActor));
		RequestInteractionWith(Interactable);
	}
	else
	{
		ClearPendingInteraction();

		if (ABeamFarmCharacter* BeamFarmCharacter = GetBeamFarmCharacter())
		{
			BeamFarmCharacter->MoveToWorldLocation(HitResult.Location);
			OnMoveToLocation(HitResult.Location);
		}
	}
}

void ABeamFarmPlayerController::RequestInteractionWith(TScriptInterface<IBeamFarmInteractable> Interactable)
{
	PendingInteractable = Interactable;

	const FVector TargetPoint = IBeamFarmInteractable::Execute_GetInteractionPoint(Interactable.GetObject());

	if (ABeamFarmCharacter* BeamFarmCharacter = GetBeamFarmCharacter())
	{
		BeamFarmCharacter->MoveToWorldLocation(TargetPoint);
	}

	OnInteractionPending(Cast<AActor>(Interactable.GetObject()));
}

void ABeamFarmPlayerController::CheckProximityAndInteract()
{
	if (!PendingInteractable.GetInterface())
	{
		return;
	}

	APawn* MyPawn = GetPawn();
	if (!MyPawn)
	{
		return;
	}

	UObject* InteractableObj = PendingInteractable.GetObject();
	if (!IsValid(InteractableObj))
	{
		ClearPendingInteraction();
		return;
	}

	const FVector InteractionPoint = IBeamFarmInteractable::Execute_GetInteractionPoint(InteractableObj);
	const float Radius = IBeamFarmInteractable::Execute_GetInteractionRadius(InteractableObj);

	const float Distance = FVector::Dist2D(MyPawn->GetActorLocation(), InteractionPoint);
	if (Distance <= Radius)
	{
		if (ABeamFarmCharacter* BeamFarmCharacter = GetBeamFarmCharacter())
		{
			BeamFarmCharacter->StopMovementToTarget();
		}

		IBeamFarmInteractable::Execute_Interact(InteractableObj, MyPawn);
		OnInteractionExecuted(Cast<AActor>(InteractableObj));
		ClearPendingInteraction();
	}
}

void ABeamFarmPlayerController::ClearPendingInteraction()
{
	PendingInteractable = TScriptInterface<IBeamFarmInteractable>();
}

ABeamFarmCharacter* ABeamFarmPlayerController::GetBeamFarmCharacter() const
{
	return Cast<ABeamFarmCharacter>(GetPawn());
}
