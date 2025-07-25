
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"




void UBeamoV2EmptyMessage::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2EmptyMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UBeamoV2EmptyMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UBeamoV2EmptyMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



