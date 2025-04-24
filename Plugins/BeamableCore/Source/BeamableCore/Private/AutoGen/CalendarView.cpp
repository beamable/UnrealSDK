
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("nextIndex")), NextIndex);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("nextClaimSeconds")), NextClaimSeconds);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("remainingSeconds")), RemainingSeconds);
	UBeamJsonUtils::DeserializeArray<URewardCalendarDay*>(Bag->GetArrayField(TEXT("days")), Days, OuterOwner);
}



