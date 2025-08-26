
#include "BeamableCore/Public/AutoGen/ContentDefinition.h"
#include "Serialization/BeamJsonUtils.h"




void UContentDefinition::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeMap<UContentMeta*>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FMapOfContentMeta>, FMapOfContentMeta>(TEXT("variants"), &Variants, Serializer);
}

void UContentDefinition::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeMap<UContentMeta*>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FMapOfContentMeta>, FMapOfContentMeta>(TEXT("variants"), &Variants, Serializer);		
}

void UContentDefinition::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("id"), Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("checksum"), Bag, Checksum);
	UBeamJsonUtils::DeserializeMap<UContentMeta*>(TEXT("properties"), Bag, Properties, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FMapOfContentMeta>, FMapOfContentMeta>("variants", Bag, Variants, OuterOwner);
}



