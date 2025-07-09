
#include "BeamableCore/Public/AutoGen/SaveManifestResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void USaveManifestResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USaveManifestResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uid"), Uid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("diffUrl"), &DiffUrl, Serializer);
}

void USaveManifestResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uid"), Uid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("diffUrl"), &DiffUrl, Serializer);		
}

void USaveManifestResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("checksum")), Checksum);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("uid")), Uid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeOptional<FString>("diffUrl", Bag, DiffUrl, OuterOwner);
}



