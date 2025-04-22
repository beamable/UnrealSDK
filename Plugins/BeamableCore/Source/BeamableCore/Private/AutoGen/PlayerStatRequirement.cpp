
#include "BeamableCore/Public/AutoGen/PlayerStatRequirement.h"
#include "Serialization/BeamJsonUtils.h"




void UPlayerStatRequirement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stat"), Stat, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("constraint"), Constraint, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("domain"), &Domain, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("access"), &Access, Serializer);
}

void UPlayerStatRequirement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stat"), Stat, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("constraint"), Constraint, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("domain"), &Domain, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("access"), &Access, Serializer);		
}

void UPlayerStatRequirement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("stat")), Stat);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("constraint")), Constraint);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("value")), Value);
	UBeamJsonUtils::DeserializeOptional<FString>("domain", Bag, Domain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("access", Bag, Access, OuterOwner);
}



