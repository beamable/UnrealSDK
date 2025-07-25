
#include "BeamableCore/Public/AutoGen/BeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse.h"




void UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



