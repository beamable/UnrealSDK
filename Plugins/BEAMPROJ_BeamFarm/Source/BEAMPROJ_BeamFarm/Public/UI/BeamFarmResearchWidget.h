// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BeamFarmResearchWidget.generated.h"

class UBeamFarmSubsystem;

/**
 * Research Lab panel widget for the BeamFarm demo.
 *
 * Research is item-instance-based: the player picks an item from their inventory
 * and a research project, then calls ConfirmResearch(). The server deducts research
 * points and stores research state as properties on the item (changing its instance ID).
 * After the timer elapses the player calls CollectResearch() to receive the output reward.
 *
 * To identify in-research items in the player's inventory check for the property key
 * returned by UBeamFarmSubsystem::GetResearchStartedAtKey(). Items with that property
 * are in research and should not appear in other inventory UIs.
 *
 * Workflow:
 *   1. Show inventory items that do NOT have the research_started_at property.
 *   2. Player picks a project (SelectProject) and an item (SelectItemForResearch).
 *   3. Call ConfirmResearch(). On success: OnResearchStarted fires — refresh inventory.
 *   4. Show in-research items (those with research_started_at property) with a countdown.
 *   5. When timer elapses, player taps Collect: call CollectResearch(instanceId, contentId).
 *   6. On success: OnResearchCollected fires — refresh inventory and show reward.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamFarmResearchWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Content ID of the research_project.* template the player selected.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Research")
	FString SelectedProjectContentId;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Research")
	bool bHasSelectedProject = false;

	// Beamable item instance ID (int64) of the item the player wants to research.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Research")
	int64 SelectedItemInstanceId = 0;

	// Content ID of the selected item (itemplant.*).
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Research")
	FString SelectedItemContentId;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Research")
	bool bHasSelectedItem = false;

	// True while a StartResearch call is in-flight.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Research")
	bool bIsStartingResearch = false;

	// ─── Actions ───────────────────────────────────────────────────────────

	// Records the research project template the player selected.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Research")
	void SelectProject(const FString& ProjectContentId);

	// Clears the selected project.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Research")
	void ClearSelectedProject();

	// Records which inventory item the player wants to submit for research.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Research")
	void SelectItemForResearch(int64 ItemInstanceId, const FString& ItemContentId);

	// Clears the selected item.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Research")
	void ClearSelectedItem();

	// Submits the research: requires bHasSelectedProject, bHasSelectedItem, and !bIsStartingResearch.
	// Outcome arrives via OnResearchStarted / OnResearchStartFailed.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Research")
	void ConfirmResearch();

	// Collects completed research for the given item instance.
	// Outcome arrives via OnResearchCollected / OnResearchCollectFailed.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Research")
	void CollectResearch(int64 ItemInstanceId, const FString& ItemContentId);

	// ─── Blueprint implementable events ────────────────────────────────────

	// Override in Blueprint: update UI to show the item is now in research.
	// ItemInstanceId is the OLD id — refresh inventory to find the new in-research item.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Research")
	void OnResearchStarted(int64 ItemInstanceId, int64 StartedAtUtcSeconds, int32 PointsSpent);

	// Override in Blueprint: show error feedback for a failed StartResearch call.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Research")
	void OnResearchStartFailed(int64 ItemInstanceId, const FString& ErrorMessage);

	// Override in Blueprint: refresh inventory and show the granted reward.
	// OutputType is "PlantModifier", "Item", or "Currency".
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Research")
	void OnResearchCollected(int64 ItemInstanceId, const FString& OutputContentId, int32 OutputQuantity, const FString& OutputType);

	// Override in Blueprint: show error feedback for a failed CollectResearch call.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Research")
	void OnResearchCollectFailed(int64 ItemInstanceId, const FString& ErrorMessage);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void HandleResearchStarted(int64 ItemInstanceId, int64 StartedAtUtcSeconds, int32 PointsSpent);

	UFUNCTION()
	void HandleResearchStartFailed(int64 ItemInstanceId, const FString& ErrorMessage);

	UFUNCTION()
	void HandleResearchCollected(int64 ItemInstanceId, const FString& OutputContentId, int32 OutputQuantity, const FString& OutputType);

	UFUNCTION()
	void HandleResearchCollectFailed(int64 ItemInstanceId, const FString& ErrorMessage);
};
