
#include "BeamableCore/Public/AutoGen/FacebookUpdatedEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UFacebookUpdatedEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("time"), Time);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("changed_fields"), ChangedFields, Serializer);
}

void UFacebookUpdatedEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("time"), Time);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("changed_fields"), ChangedFields, Serializer);		
}

void UFacebookUpdatedEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("time")), Time);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("changed_fields")), ChangedFields, OuterOwner);
}



