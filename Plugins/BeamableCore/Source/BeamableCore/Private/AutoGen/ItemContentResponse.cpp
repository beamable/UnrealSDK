
#include "BeamableCore/Public/AutoGen/ItemContentResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UItemContentResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UItemContentResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UItemArchetype*>(TEXT("content"), Content, Serializer);
}

void UItemContentResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UItemArchetype*>(TEXT("content"), Content, Serializer);		
}

void UItemContentResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UItemArchetype*>(Bag->GetArrayField(TEXT("content")), Content, OuterOwner);
}



