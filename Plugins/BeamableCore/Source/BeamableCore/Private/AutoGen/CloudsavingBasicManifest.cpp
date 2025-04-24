
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UCloudsavingBasicManifest::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCloudsavingBasicManifest::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("replacement"), bReplacement, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeArray<UCloudsavingBasicReference*>(TEXT("manifest"), Manifest, Serializer);
}

void UCloudsavingBasicManifest::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("replacement"), bReplacement, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeArray<UCloudsavingBasicReference*>(TEXT("manifest"), Manifest, Serializer);		
}

void UCloudsavingBasicManifest::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("replacement")), bReplacement);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeArray<UCloudsavingBasicReference*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
}



