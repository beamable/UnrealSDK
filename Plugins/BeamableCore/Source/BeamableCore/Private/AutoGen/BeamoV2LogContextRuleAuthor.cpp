
#include "BeamableCore/Public/AutoGen/BeamoV2LogContextRuleAuthor.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2LogContextRuleAuthor::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("accountId"), AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
}

void UBeamoV2LogContextRuleAuthor::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("accountId"), AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);		
}

void UBeamoV2LogContextRuleAuthor::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("accountId"), Bag, AccountId);
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
}



