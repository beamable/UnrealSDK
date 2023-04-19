
#include "BeamableCore/Public/AutoGen/ContentDefinition.h"
#include "Serialization/BeamJsonUtils.h"




void UContentDefinition::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("prefix"), Prefix);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	UBeamJsonUtils::SerializeMap<UContentMeta*>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FMapOfContentMeta>, FMapOfContentMeta>(TEXT("variants"), &Variants, Serializer);
}

void UContentDefinition::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("prefix"), Prefix);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	UBeamJsonUtils::SerializeMap<UContentMeta*>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FMapOfContentMeta>, FMapOfContentMeta>(TEXT("variants"), &Variants, Serializer);		
}

void UContentDefinition::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Prefix = Bag->GetStringField(TEXT("prefix"));
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	Checksum = Bag->GetStringField(TEXT("checksum"));
	UBeamJsonUtils::DeserializeMap<UContentMeta*>(Bag->GetObjectField(TEXT("properties")), Properties, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FMapOfContentMeta>, FMapOfContentMeta>("variants", Bag, Variants, OuterOwner);
}



