// Copyright Beamable, Inc. All Rights Reserved.

#include "Player/BeamFarmPlayerController.h"
#include "Player/BeamFarmCharacter.h"
#include "Interaction/BeamFarmInteractable.h"
#include "Environment/BeamFarmEnvBase.h"
#include "UI/BeamFarmHUDWidget.h"
#include "Blueprint/UserWidget.h"

ABeamFarmPlayerController::ABeamFarmPlayerController()
{
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ABeamFarmPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass && IsLocalController())
	{
		HUDWidget = CreateWidget<UBeamFarmHUDWidget>(this, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
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
		// Always attempt to move to the interactable object
		// Distance and line of sight will be checked when trying to interact
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

	// Check if within interaction radius
	if (Distance <= Radius)
	{
		AActor* InteractableActor = Cast<AActor>(InteractableObj);

		// Check if we can actually interact (distance and line of sight)
		if (CanInteractWith(InteractableActor, InteractionPoint))
		{
			if (ABeamFarmCharacter* BeamFarmCharacter = GetBeamFarmCharacter())
			{
				BeamFarmCharacter->StopMovementToTarget();
			}

			IBeamFarmInteractable::Execute_Interact(InteractableObj, MyPawn);
			OnInteractionExecuted(Cast<AActor>(InteractableObj));

			if (ABeamFarmEnvBase* Building = Cast<ABeamFarmEnvBase>(InteractableObj))
			{
				if (HUDWidget && Building->BuildingType != EBeamFarmBuildingType::None)
				{
					HUDWidget->OpenForBuilding(Building->BuildingType);
				}
			}

			ClearPendingInteraction();
		}
		// If line of sight is blocked, keep trying (player will keep moving closer)
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

bool ABeamFarmPlayerController::CanInteractWith(AActor* InteractableActor, const FVector& InteractionPoint) const
{
	APawn* MyPawn = GetPawn();
	if (!MyPawn || !InteractableActor)
	{
		return false;
	}

	// Check line of sight if required
	if (bRequireLineOfSight)
	{
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyPawn);
		QueryParams.AddIgnoredActor(this);

		const FVector PlayerLocation = MyPawn->GetActorLocation();

		// Trace from player to the interaction point
		const bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			PlayerLocation,
			InteractionPoint,
			ECC_Visibility,
			QueryParams
		);

		// If we hit something, check if it's the target actor or we missed entirely
		if (bHit && HitResult.GetActor() != InteractableActor)
		{
			return false;
		}
	}

	return true;
}
