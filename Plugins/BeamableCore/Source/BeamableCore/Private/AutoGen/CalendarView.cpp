
#include "BeamableCore/Public/AutoGen/CalendarView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCalendarView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("nextIndex"), NextIndex, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("nextClaimSeconds"), NextClaimSeconds, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("remainingSeconds"), RemainingSeconds, Serializer);
	UBeamJsonUtils::SerializeArray<URewardCalendarDay*>(TEXT("days"), Days, Serializer);
}

void UCalendarView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("nextIndex"), NextIndex, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("nextClaimSeconds"), NextClaimSeconds, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("remainingSeconds"), RemainingSeconds, Serializer);
	UBeamJsonUtils::SerializeArray<URewardCalendarDay*>(TEXT("days"), Days, Serializer);		
}

void UCalendarView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("nextIndex"), Bag, NextIndex);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("nextClaimSeconds"), Bag, NextClaimSeconds);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("remainingSeconds"), Bag, RemainingSeconds);
	UBeamJsonUtils::DeserializeArray<URewardCalendarDay*>(TEXT("days"), Bag, Days, OuterOwner);
}



