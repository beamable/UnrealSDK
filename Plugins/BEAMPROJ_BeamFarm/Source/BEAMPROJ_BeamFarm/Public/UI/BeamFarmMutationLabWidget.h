// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Farming/FarmTypes.h"
#include "BeamSeedData.h"
#include "BeamFarmMutationLabWidget.generated.h"

/**
 * Mutation Lab panel widget for the BeamFarm demo.
 *
 * Manages a queue of raw materials that the player wants to mutate into new crops.
 * The actual microservice call is delegated to Blueprint via OnMutationRequested so that
 * the auto-generated BeamFarmMs client (regenerated via `dotnet beam generate`) can be
 * wired up in Blueprint without changing C++.
 *
 * Workflow:
 *   1. UBeamFarmInventoryWidget::OnSendToLabRequested → call AddToQueue().
 *   2. Player clicks "Mutate" → StartMutation() validates the queue and fires OnMutationRequested.
 *   3. Blueprint calls the auto-generated BeamFarmMsMutate node with the queue data.
 *   4. On success/failure, Blueprint calls NotifyMutationComplete() / NotifyMutationFailed().
 *   5. Override OnMutationComplete / OnMutationFailed in Blueprint to update the UI.
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

	// Adds or increments a seed material in the queue.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void AddToQueue(const FBeamSeedData& Item, int32 Quantity);

	// Removes a material from the queue by its content ID.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void RemoveFromQueue(const FString& ItemContentId);

	// Empties the queue without triggering a mutation.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void ClearQueue();

	// Validates the queue and fires OnMutationRequested. Blueprint should call the microservice there.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void StartMutation();

	// Call from Blueprint when the microservice returns a successful result.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void NotifyMutationComplete(const TArray<FBeamFarmMutationOutput>& Outputs);

	// Call from Blueprint when the microservice returns an error.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|MutationLab")
	void NotifyMutationFailed(const FString& ErrorMessage);

	// Override in Blueprint: rebuild the queue display.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|MutationLab")
	void OnQueueChanged(const TArray<FBeamFarmMutationInput>& Queue);

	// Override in Blueprint: call the auto-generated BeamFarmMsMutate microservice node.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|MutationLab")
	void OnMutationRequested(const TArray<FBeamFarmMutationInput>& Inputs);

	// Override in Blueprint: show success feedback and refresh inventory display.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|MutationLab")
	void OnMutationComplete(const TArray<FBeamFarmMutationOutput>& Outputs);

	// Override in Blueprint: show error feedback.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|MutationLab")
	void OnMutationFailed(const FString& ErrorMessage);
};
