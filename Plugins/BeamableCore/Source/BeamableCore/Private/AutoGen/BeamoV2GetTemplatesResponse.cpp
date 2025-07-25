
#include "BeamableCore/Public/AutoGen/BeamoV2GetTemplatesResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2GetTemplatesResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2GetTemplatesResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceTemplateView*>, UBeamoV2ServiceTemplateView*>(TEXT("templates"), &Templates, Serializer);
}

void UBeamoV2GetTemplatesResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceTemplateView*>, UBeamoV2ServiceTemplateView*>(TEXT("templates"), &Templates, Serializer);		
}

void UBeamoV2GetTemplatesResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceTemplateView*>, UBeamoV2ServiceTemplateView*>("templates", Bag, Templates, OuterOwner);
}



