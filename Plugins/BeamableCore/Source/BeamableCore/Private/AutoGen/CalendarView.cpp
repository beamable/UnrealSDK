
#include "BeamableCore/Public/AutoGen/CalendarView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCalendarView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("nextIndex"), NextIndex);
	Serializer->WriteValue(TEXT("nextClaimSeconds"), NextClaimSeconds);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("remainingSeconds"), RemainingSeconds);
	UBeamJsonUtils::SerializeArray<URewardCalendarDay*>(TEXT("days"), Days, Serializer);
}

void UCalendarView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("nextIndex"), NextIndex);
	Serializer->WriteValue(TEXT("nextClaimSeconds"), NextClaimSeconds);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("remainingSeconds"), RemainingSeconds);
	UBeamJsonUtils::SerializeArray<URewardCalendarDay*>(TEXT("days"), Days, Serializer);		
}

void UCalendarView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	NextIndex = Bag->GetIntegerField(TEXT("nextIndex"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("nextClaimSeconds")), NextClaimSeconds);
	Id = Bag->GetStringField(TEXT("id"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("remainingSeconds")), RemainingSeconds);
	UBeamJsonUtils::DeserializeArray<URewardCalendarDay*>(Bag->GetArrayField(TEXT("days")), Days, OuterOwner);
}



