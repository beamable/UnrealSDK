// Copyright Beamable, Inc. All Rights Reserved.

#include "UI/BeamFarmMutationLabWidget.h"

void UBeamFarmMutationLabWidget::AddToQueue(const FBeamPlantData& Item, int32 Quantity)
{
	// if (Item.ItemContentId.IsEmpty() || Quantity <= 0)
	// {
	// 	return;
	// }
	//
	// for (FBeamFarmMutationInput& Existing : MutationQueue)
	// {
	// 	if (Existing.ItemContentId == Item.ItemContentId)
	// 	{
	// 		Existing.Quantity += Quantity;
	// 		OnQueueChanged(MutationQueue);
	// 		return;
	// 	}
	// }
	//
	// FBeamFarmMutationInput NewEntry;
	// NewEntry.ItemContentId = Item.ItemContentId;
	// NewEntry.Quantity = Quantity;
	// MutationQueue.Add(NewEntry);
	// OnQueueChanged(MutationQueue);
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
	OnMutationRequested(MutationQueue);
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
