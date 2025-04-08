
#include "BeamableCore/Public/AutoGen/CloudsavingBasicReference.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCloudsavingBasicReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("size"), Size);
	Serializer->WriteValue(TEXT("lastModified"), LastModified);
	Serializer->WriteValue(TEXT("key"), Key);
	Serializer->WriteValue(TEXT("bucketName"), BucketName);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("eTag"), &ETag, Serializer);
}

void UCloudsavingBasicReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("size"), Size);
	Serializer->WriteValue(TEXT("lastModified"), LastModified);
	Serializer->WriteValue(TEXT("key"), Key);
	Serializer->WriteValue(TEXT("bucketName"), BucketName);
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



