
#include "BeamableCore/Public/AutoGen/TextDefinition.h"
#include "Serialization/BeamJsonUtils.h"




void UTextDefinition::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
}

void UTextDefinition::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);		
}

void UTextDefinition::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("checksum")), Checksum);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("properties")), Properties, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
}



