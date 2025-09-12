
#include "BeamableCore/Public/AutoGen/BeamoV2LogContextRuleAuthor.h"





void UBeamoV2LogContextRuleAuthor::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("accountId"), AccountId, Serializer);
}

void UBeamoV2LogContextRuleAuthor::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("accountId"), AccountId, Serializer);		
}

void UBeamoV2LogContextRuleAuthor::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("email"), Bag, Email);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("accountId"), Bag, AccountId);
}



