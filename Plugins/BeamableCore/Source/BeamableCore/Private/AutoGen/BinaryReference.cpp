
#include "BeamableCore/Public/AutoGen/BinaryReference.h"
#include "Serialization/BeamJsonUtils.h"




void UBinaryReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uploadMethod"), UploadMethod, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uri"), Uri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uploadUri"), UploadUri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("visibility"), Visibility, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lastChanged"), &LastChanged, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("created"), &Created, Serializer);
}

void UBinaryReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uploadMethod"), UploadMethod, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uri"), Uri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uploadUri"), UploadUri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("visibility"), Visibility, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tags"), Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lastChanged"), &LastChanged, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("created"), &Created, Serializer);		
}

void UBinaryReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("uploadMethod")), UploadMethod);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("uri")), Uri);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("version")), Version);
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("uploadUri")), UploadUri);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("type")), Type);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("visibility")), Visibility);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("tags")), Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("lastChanged", Bag, LastChanged, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("created", Bag, Created, OuterOwner);
}



