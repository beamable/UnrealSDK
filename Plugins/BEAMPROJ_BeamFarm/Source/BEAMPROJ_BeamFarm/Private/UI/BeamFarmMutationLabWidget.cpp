// Copyright Beamable, Inc. All Rights Reserved.

#include "UI/BeamFarmMutationLabWidget.h"
#include "Subsystem/BeamFarmSubsystem.h"

void UBeamFarmMutationLabWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		// Sub->OnMutationCompleted.AddDynamic(this, &UBeamFarmMutationLabWidget::HandleMutationCompleted);
		// Sub->OnMutationFailed.AddDynamic(this, &UBeamFarmMutationLabWidget::HandleMutationFailed);
	}
}

void UBeamFarmMutationLabWidget::NativeDestruct()
{
	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		// Sub->OnMutationCompleted.RemoveDynamic(this, &UBeamFarmMutationLabWidget::HandleMutationCompleted);
		// Sub->OnMutationFailed.RemoveDynamic(this, &UBeamFarmMutationLabWidget::HandleMutationFailed);
	}

	Super::NativeDestruct();
}

void UBeamFarmMutationLabWidget::AddToQueue(const FString& ItemContentId, int32 Quantity)
{
	if (ItemContentId.IsEmpty() || Quantity <= 0)
	{
		return;
	}

	for (FBeamFarmMutationInput& Existing : MutationQueue)
	{
		if (Existing.ItemContentId == ItemContentId)
		{
			Existing.Quantity += Quantity;
			OnQueueChanged(MutationQueue);
			return;
		}
	}

	FBeamFarmMutationInput NewEntry;
	NewEntry.ItemContentId = ItemContentId;
	NewEntry.Quantity = Quantity;
	MutationQueue.Add(NewEntry);
	OnQueueChanged(MutationQueue);
}

void UBeamFarmMutationLabWidget::RemoveFromQueue(const FString& ItemContentId)
{
	const int32 Removed = MutationQueue.RemoveAll([&ItemContentId](const FBeamFarmMutationInput& Entry)
	{
		return Entry.ItemContentId == ItemContentId;
	});

	if (Removed > 0)
	{
		OnQueueChanged(MutationQueue);
	}
}

void UBeamFarmMutationLabWidget::ClearQueue()
{
	if (MutationQueue.IsEmpty())
	{
		return;
	}
	MutationQueue.Empty();
	OnQueueChanged(MutationQueue);
}

void UBeamFarmMutationLabWidget::StartMutation()
{
	if (bIsMutating || MutationQueue.IsEmpty())
	{
		return;
	}
	bIsMutating = true;

	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		// Sub->Mutate(MutationQueue);
	}
	else
	{
		bIsMutating = false;
	}
}

void UBeamFarmMutationLabWidget::NotifyMutationComplete(const TArray<FBeamFarmMutationOutput>& Outputs)
{
	bIsMutating = false;
	ClearQueue();
	OnMutationComplete(Outputs);
}

void UBeamFarmMutationLabWidget::NotifyMutationFailed(const FString& ErrorMessage)
{
	bIsMutating = false;
	OnMutationFailed(ErrorMessage);
}

void UBeamFarmMutationLabWidget::HandleMutationCompleted(const TArray<FBeamFarmMutationOutput>& Outputs, const FString& Message)
{
	NotifyMutationComplete(Outputs);
}

void UBeamFarmMutationLabWidget::HandleMutationFailed(const FString& Error)
{
	NotifyMutationFailed(Error);
}
