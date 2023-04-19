
#include "BeamableCore/Public/AutoGen/ItemUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UItemUpdateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UItemProperty*>(TEXT("properties"), Properties, Serializer);
}

void UItemUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UItemProperty*>(TEXT("properties"), Properties, Serializer);		
}

void UItemUpdateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ContentId = Bag->GetStringField(TEXT("contentId"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeArray<UItemProperty*>(Bag->GetArrayField(TEXT("properties")), Properties, OuterOwner);
}



