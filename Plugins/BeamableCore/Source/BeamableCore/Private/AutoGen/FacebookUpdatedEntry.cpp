
#include "BeamableCore/Public/AutoGen/FacebookUpdatedEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UFacebookUpdatedEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("time"), Time, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("changed_fields"), ChangedFields, Serializer);
}

void UFacebookUpdatedEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("time"), Time, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("changed_fields"), ChangedFields, Serializer);		
}

void UFacebookUpdatedEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("time"), Bag, Time);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("changed_fields"), Bag, ChangedFields, OuterOwner);
}



