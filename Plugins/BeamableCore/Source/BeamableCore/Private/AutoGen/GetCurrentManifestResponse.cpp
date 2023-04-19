
#include "BeamableCore/Public/AutoGen/GetCurrentManifestResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetCurrentManifestResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetCurrentManifestResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UManifestView*>("manifest", Manifest, Serializer);
}

void UGetCurrentManifestResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UManifestView*>("manifest", Manifest, Serializer);		
}

void UGetCurrentManifestResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UManifestView*>("manifest", Bag, Manifest, OuterOwner);
}



