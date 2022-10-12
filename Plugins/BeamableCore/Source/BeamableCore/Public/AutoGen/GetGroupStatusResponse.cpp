
#include "AutoGen/GetGroupStatusResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UGetGroupStatusResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGroupStatus*>(TEXT("statuses"), Statuses, Serializer);
}

void UGetGroupStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGroupStatus*>(TEXT("statuses"), Statuses, Serializer);		
}

void UGetGroupStatusResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UGroupStatus*>(Bag->GetArrayField(TEXT("statuses")), Statuses, OuterOwner);
}