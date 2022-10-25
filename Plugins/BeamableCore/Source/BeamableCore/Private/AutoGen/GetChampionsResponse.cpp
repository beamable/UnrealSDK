
#include "AutoGen/GetChampionsResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UGetChampionsResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UChampionScore*>(TEXT("entries"), Entries, Serializer);
}

void UGetChampionsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UChampionScore*>(TEXT("entries"), Entries, Serializer);		
}

void UGetChampionsResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UChampionScore*>(Bag->GetArrayField(TEXT("entries")), Entries, OuterOwner);
}