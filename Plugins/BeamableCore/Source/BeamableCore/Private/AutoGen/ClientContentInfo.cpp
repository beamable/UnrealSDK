
#include "BeamableCore/Public/AutoGen/ClientContentInfo.h"
#include "Serialization/BeamJsonUtils.h"




void UClientContentInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uri"), Uri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("contentId"), &ContentId, Serializer);
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
}

void UClientContentInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uri"), Uri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("contentId"), &ContentId, Serializer);
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);		
}

void UClientContentInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("uri"), Bag, Uri);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("version"), Bag, Version);
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("contentId"), Bag, ContentId, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("type"), Bag, Type);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("tags"), Bag, Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("updatedAt", Bag, UpdatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdAt", Bag, CreatedAt, OuterOwner);
}



