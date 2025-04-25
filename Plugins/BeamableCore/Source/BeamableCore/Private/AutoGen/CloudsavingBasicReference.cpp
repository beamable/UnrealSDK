
#include "BeamableCore/Public/AutoGen/CloudsavingBasicReference.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCloudsavingBasicReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("size"), Size, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastModified"), LastModified, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("key"), Key, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("bucketName"), BucketName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("eTag"), &ETag, Serializer);
}

void UCloudsavingBasicReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("size"), Size, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastModified"), LastModified, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("key"), Key, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("bucketName"), BucketName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("eTag"), &ETag, Serializer);		
}

void UCloudsavingBasicReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("size")), Size);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("lastModified")), LastModified);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("key")), Key);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("bucketName")), BucketName);
	UBeamJsonUtils::DeserializeOptional<FString>("eTag", Bag, ETag, OuterOwner);
}



