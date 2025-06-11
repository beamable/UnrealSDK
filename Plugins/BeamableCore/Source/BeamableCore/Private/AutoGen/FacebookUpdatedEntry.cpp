
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("time")), Time);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("changed_fields")), ChangedFields, OuterOwner);
}



