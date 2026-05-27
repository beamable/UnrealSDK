// Copyright Beamable, Inc. All Rights Reserved.

#include "UI/BeamFarmResearchWidget.h"
#include "Subsystem/BeamFarmSubsystem.h"

void UBeamFarmResearchWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->OnResearchStarted.AddDynamic(this, &UBeamFarmResearchWidget::HandleResearchStarted);
		Sub->OnResearchStartFailed.AddDynamic(this, &UBeamFarmResearchWidget::HandleResearchStartFailed);
		Sub->OnResearchCollected.AddDynamic(this, &UBeamFarmResearchWidget::HandleResearchCollected);
		Sub->OnResearchCollectFailed.AddDynamic(this, &UBeamFarmResearchWidget::HandleResearchCollectFailed);
	}
}

void UBeamFarmResearchWidget::NativeDestruct()
{
	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->OnResearchStarted.RemoveDynamic(this, &UBeamFarmResearchWidget::HandleResearchStarted);
		Sub->OnResearchStartFailed.RemoveDynamic(this, &UBeamFarmResearchWidget::HandleResearchStartFailed);
		Sub->OnResearchCollected.RemoveDynamic(this, &UBeamFarmResearchWidget::HandleResearchCollected);
		Sub->OnResearchCollectFailed.RemoveDynamic(this, &UBeamFarmResearchWidget::HandleResearchCollectFailed);
	}

	Super::NativeDestruct();
}

void UBeamFarmResearchWidget::SelectProject(const FString& ProjectContentId)
{
	SelectedProjectContentId = ProjectContentId;
	bHasSelectedProject      = true;
}

void UBeamFarmResearchWidget::ClearSelectedProject()
{
	SelectedProjectContentId = TEXT("");
	bHasSelectedProject      = false;
}

void UBeamFarmResearchWidget::SelectItemForResearch(int64 ItemInstanceId, const FString& ItemContentId)
{
	SelectedItemInstanceId = ItemInstanceId;
	SelectedItemContentId  = ItemContentId;
	bHasSelectedItem       = true;
}

void UBeamFarmResearchWidget::ClearSelectedItem()
{
	SelectedItemInstanceId = 0;
	SelectedItemContentId  = TEXT("");
	bHasSelectedItem       = false;
}

void UBeamFarmResearchWidget::ConfirmResearch()
{
	if (!bHasSelectedProject || !bHasSelectedItem || bIsStartingResearch)
	{
		return;
	}

	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (!Sub)
	{
		return;
	}

	bIsStartingResearch = true;
	Sub->StartResearch(SelectedItemInstanceId, SelectedItemContentId, SelectedProjectContentId);
}

void UBeamFarmResearchWidget::CollectResearch(int64 ItemInstanceId, const FString& ItemContentId)
{
	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->CollectResearch(ItemInstanceId, ItemContentId);
	}
}

void UBeamFarmResearchWidget::HandleResearchStarted(int64 ItemInstanceId, int64 StartedAtUtcSeconds, int32 PointsSpent)
{
	bIsStartingResearch = false;
	ClearSelectedProject();
	ClearSelectedItem();
	OnResearchStarted(ItemInstanceId, StartedAtUtcSeconds, PointsSpent);
}

void UBeamFarmResearchWidget::HandleResearchStartFailed(int64 ItemInstanceId, const FString& ErrorMessage)
{
	bIsStartingResearch = false;
	OnResearchStartFailed(ItemInstanceId, ErrorMessage);
}

void UBeamFarmResearchWidget::HandleResearchCollected(int64 ItemInstanceId, const FString& OutputContentId, int32 OutputQuantity, const FString& OutputType)
{
	OnResearchCollected(ItemInstanceId, OutputContentId, OutputQuantity, OutputType);
}

void UBeamFarmResearchWidget::HandleResearchCollectFailed(int64 ItemInstanceId, const FString& ErrorMessage)
{
	OnResearchCollectFailed(ItemInstanceId, ErrorMessage);
}
