
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
	Serializer->WriteValue(TEXT("replacement"), bReplacement);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeArray<UCloudsavingBasicReference*>(TEXT("manifest"), Manifest, Serializer);
}

void UCloudsavingBasicManifest::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("replacement"), bReplacement);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeArray<UCloudsavingBasicReference*>(TEXT("manifest"), Manifest, Serializer);		
}

void UCloudsavingBasicManifest::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bReplacement = Bag->GetBoolField(TEXT("replacement"));
	Id = Bag->GetStringField(TEXT("id"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeArray<UCloudsavingBasicReference*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
}



