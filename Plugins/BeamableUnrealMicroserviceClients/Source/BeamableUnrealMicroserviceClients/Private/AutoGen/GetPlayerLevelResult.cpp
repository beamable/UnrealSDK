
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetPlayerLevelResult.h"

#include "Misc/DefaultValueHelper.h"


void UGetPlayerLevelResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetPlayerLevelResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("level"), Level, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("totalXp"), TotalXp, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("xpForCurrentLevel"), XpForCurrentLevel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("xpIntoCurrentLevel"), XpIntoCurrentLevel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
}

void UGetPlayerLevelResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("level"), Level, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("totalXp"), TotalXp, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("xpForCurrentLevel"), XpForCurrentLevel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("xpIntoCurrentLevel"), XpIntoCurrentLevel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);		
}

void UGetPlayerLevelResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("level"), Bag, Level);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("totalXp"), Bag, TotalXp);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("xpForCurrentLevel"), Bag, XpForCurrentLevel);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("xpIntoCurrentLevel"), Bag, XpIntoCurrentLevel);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
}



