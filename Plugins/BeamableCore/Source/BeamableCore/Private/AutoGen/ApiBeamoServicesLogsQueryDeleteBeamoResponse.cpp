
#include "BeamableCore/Public/AutoGen/ApiBeamoServicesLogsQueryDeleteBeamoResponse.h"




void UApiBeamoServicesLogsQueryDeleteBeamoResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UApiBeamoServicesLogsQueryDeleteBeamoResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UApiBeamoServicesLogsQueryDeleteBeamoResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UApiBeamoServicesLogsQueryDeleteBeamoResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



