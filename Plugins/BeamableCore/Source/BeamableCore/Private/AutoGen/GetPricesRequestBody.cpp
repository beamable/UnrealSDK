
#include "BeamableCore/Public/AutoGen/GetPricesRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UGetPricesRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("steamId"), SteamId);
}

void UGetPricesRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("steamId"), SteamId);		
}

void UGetPricesRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("steamId")), SteamId);
}



