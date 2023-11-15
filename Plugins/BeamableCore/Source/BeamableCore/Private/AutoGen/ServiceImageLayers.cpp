
#include "BeamableCore/Public/AutoGen/ServiceImageLayers.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceImageLayers::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UBeamoBasicReference*>("service", Service, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("layers"), Layers, Serializer);
}

void UServiceImageLayers::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UBeamoBasicReference*>("service", Service, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("layers"), Layers, Serializer);		
}

void UServiceImageLayers::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UBeamoBasicReference*>("service", Bag, Service, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("layers")), Layers, OuterOwner);
}



