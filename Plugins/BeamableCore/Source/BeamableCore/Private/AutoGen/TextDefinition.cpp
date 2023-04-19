
#include "BeamableCore/Public/AutoGen/TextDefinition.h"
#include "Serialization/BeamJsonUtils.h"




void UTextDefinition::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
}

void UTextDefinition::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);		
}

void UTextDefinition::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	Checksum = Bag->GetStringField(TEXT("checksum"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("properties")), Properties, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
}



