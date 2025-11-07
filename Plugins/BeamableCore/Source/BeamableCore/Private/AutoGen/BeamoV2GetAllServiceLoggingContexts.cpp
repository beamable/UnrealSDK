
#include "BeamableCore/Public/AutoGen/BeamoV2GetAllServiceLoggingContexts.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2GetAllServiceLoggingContexts::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2GetAllServiceLoggingContexts::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceLoggingContext*>, UBeamoV2ServiceLoggingContext*>(TEXT("contexts"), &Contexts, Serializer);
}

void UBeamoV2GetAllServiceLoggingContexts::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceLoggingContext*>, UBeamoV2ServiceLoggingContext*>(TEXT("contexts"), &Contexts, Serializer);		
}

void UBeamoV2GetAllServiceLoggingContexts::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceLoggingContext*>, UBeamoV2ServiceLoggingContext*>("contexts", Bag, Contexts, OuterOwner);
}



