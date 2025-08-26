
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceComponent.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ServiceComponent::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
}

void UBeamoV2ServiceComponent::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);		
}

void UBeamoV2ServiceComponent::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
}



