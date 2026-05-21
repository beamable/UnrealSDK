// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Farming/FarmTypes.h"
#include "BeamFarmMutationLabWidget.generated.h"

class UBeamFarmSubsystem;

/**
 * Mutation Lab panel widget for the BeamFarm demo.
 *
 * Manages a queue of raw materials that the player wants to mutate into new crops.
 * StartMutation() calls UBeamFarmSubsystem::Mutate directly; results arrive via the
 * subsystem's multicast delegates, which are bound in NativeConstruct.
 *
 * Workflow:
 *   1. UBeamFarmInventoryWidget::OnSendToLabRequested → call AddToQueue().
 *   2. Player clicks "Mutate" → StartMutation() validates the queue and calls the subsystem.
 *   3. On success/failure, NotifyMutationComplete() / NotifyMutationFailed() are called.
 *   4. Override OnMutationComplete / OnMutationFailed in Blueprint to update the UI.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamFarmMutationLabWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Current material queue waiting to be mutated.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|MutationLab")
	TArray<FBeamFarmMutationInput> MutationQueue;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|MutationLab")
	bool bIsMutating = false;

	// Adds or increments an item in the queue by its Beamable content ID.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void AddToQueue(const FString& ItemContentId, int32 Quantity);

	// Removes a material from the queue by its content ID.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void RemoveFromQueue(const FString& ItemContentId);

	// Empties the queue without triggering a mutation.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void ClearQueue();

	// Validates the queue and calls UBeamFarmSubsystem::Mutate.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void StartMutation();

	// Called by the subsystem delegate binding when the microservice returns a successful result.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void NotifyMutationComplete(const TArray<FBeamFarmMutationOutput>& Outputs);

	// Called by the subsystem delegate binding when the microservice returns an error.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void NotifyMutationFailed(const FString& ErrorMessage);

	// Override in Blueprint: rebuild the queue display.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|MutationLab")
	void OnQueueChanged(const TArray<FBeamFarmMutationInput>& Queue);

	// Override in Blueprint: show success feedback and refresh inventory display.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|MutationLab")
	void OnMutationComplete(const TArray<FBeamFarmMutationOutput>& Outputs);

	// Override in Blueprint: show error feedback.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|MutationLab")
	void OnMutationFailed(const FString& ErrorMessage);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void HandleMutationCompleted(const TArray<FBeamFarmMutationOutput>& Outputs, const FString& Message);

	UFUNCTION()
	void HandleMutationFailed(const FString& Error);
};
