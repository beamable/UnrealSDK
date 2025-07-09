
#include "BeamableCore/Public/AutoGen/GetTemplatesResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetTemplatesResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetTemplatesResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UServiceTemplateView*>, UServiceTemplateView*>(TEXT("templates"), &Templates, Serializer);
}

void UGetTemplatesResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UServiceTemplateView*>, UServiceTemplateView*>(TEXT("templates"), &Templates, Serializer);		
}

void UGetTemplatesResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceTemplateView*>, UServiceTemplateView*>("templates", Bag, Templates, OuterOwner);
}



