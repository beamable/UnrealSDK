
#include "BeamableCore/Public/AutoGen/GetManifestResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetManifestResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetManifestResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UManifestView*>("manifest", Manifest, Serializer);
}

void UGetManifestResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UManifestView*>("manifest", Manifest, Serializer);		
}

void UGetManifestResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UManifestView*>("manifest", Bag, Manifest, OuterOwner);
}



