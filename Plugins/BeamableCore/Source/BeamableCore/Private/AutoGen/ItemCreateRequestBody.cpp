
#include "BeamableCore/Public/AutoGen/ItemCreateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UItemCreateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	UBeamJsonUtils::SerializeArray<UItemProperty*>(TEXT("properties"), Properties, Serializer);
}

void UItemCreateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	UBeamJsonUtils::SerializeArray<UItemProperty*>(TEXT("properties"), Properties, Serializer);		
}

void UItemCreateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ContentId = Bag->GetStringField(TEXT("contentId"));
	UBeamJsonUtils::DeserializeArray<UItemProperty*>(Bag->GetArrayField(TEXT("properties")), Properties, OuterOwner);
}



