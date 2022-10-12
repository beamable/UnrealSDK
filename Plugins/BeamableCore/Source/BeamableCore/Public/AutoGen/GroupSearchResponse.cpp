
#include "AutoGen/GroupSearchResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UGroupSearchResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGroup*>(TEXT("groups"), Groups, Serializer);
}

void UGroupSearchResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGroup*>(TEXT("groups"), Groups, Serializer);		
}

void UGroupSearchResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UGroup*>(Bag->GetArrayField(TEXT("groups")), Groups, OuterOwner);
}