
#include "BeamableCore/Public/AutoGen/PlayerStatRequirement.h"
#include "Serialization/BeamJsonUtils.h"




void UPlayerStatRequirement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("stat"), Stat);
	Serializer->WriteValue(TEXT("constraint"), Constraint);
	Serializer->WriteValue(TEXT("value"), Value);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("domain"), &Domain, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("access"), &Access, Serializer);
}

void UPlayerStatRequirement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("stat"), Stat);
	Serializer->WriteValue(TEXT("constraint"), Constraint);
	Serializer->WriteValue(TEXT("value"), Value);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("domain"), &Domain, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("access"), &Access, Serializer);		
}

void UPlayerStatRequirement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Stat = Bag->GetStringField(TEXT("stat"));
	Constraint = Bag->GetStringField(TEXT("constraint"));
	Value = Bag->GetStringField(TEXT("value"));
	UBeamJsonUtils::DeserializeOptional<FString>("domain", Bag, Domain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("access", Bag, Access, OuterOwner);
}



