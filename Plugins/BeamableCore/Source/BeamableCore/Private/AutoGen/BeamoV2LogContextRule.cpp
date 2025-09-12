
#include "BeamableCore/Public/AutoGen/BeamoV2LogContextRule.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2LogContextRule::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), bEnabled, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeUObject<UBeamoV2LogContextRuleAuthor*>("author", Author, Serializer);
	Serializer->WriteValue(TEXT("logLevel"), UBeamJsonUtils::EnumToSerializationName(LogLevel));
	UBeamJsonUtils::SerializeArray<UBeamoV2ContextRuleFilter*>(TEXT("ruleFilters"), RuleFilters, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresAt"), &ExpiresAt, Serializer);
}

void UBeamoV2LogContextRule::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), bEnabled, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeUObject<UBeamoV2LogContextRuleAuthor*>("author", Author, Serializer);
	Serializer->WriteValue(TEXT("logLevel"), UBeamJsonUtils::EnumToSerializationName(LogLevel));
	UBeamJsonUtils::SerializeArray<UBeamoV2ContextRuleFilter*>(TEXT("ruleFilters"), RuleFilters, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresAt"), &ExpiresAt, Serializer);		
}

void UBeamoV2LogContextRule::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("enabled"), Bag, bEnabled);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeUObject<UBeamoV2LogContextRuleAuthor*>("author", Bag, Author, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("logLevel"), Bag, LogLevel);
	UBeamJsonUtils::DeserializeArray<UBeamoV2ContextRuleFilter*>(TEXT("ruleFilters"), Bag, RuleFilters, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdAt", Bag, CreatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("updatedAt", Bag, UpdatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("expiresAt", Bag, ExpiresAt, OuterOwner);
}



