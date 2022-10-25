
#include "AutoGen/GetPlayerStatusResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UGetPlayerStatusResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UPlayerStatus*>(TEXT("statuses"), Statuses, Serializer);
}

void UGetPlayerStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UPlayerStatus*>(TEXT("statuses"), Statuses, Serializer);		
}

void UGetPlayerStatusResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UPlayerStatus*>(Bag->GetArrayField(TEXT("statuses")), Statuses, OuterOwner);
}