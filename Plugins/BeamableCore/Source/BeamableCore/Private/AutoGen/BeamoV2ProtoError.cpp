
#include "BeamableCore/Public/AutoGen/BeamoV2ProtoError.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ProtoError::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("error"), &Error, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
}

void UBeamoV2ProtoError::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("error"), &Error, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);		
}

void UBeamoV2ProtoError::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int32>("status", Bag, Status, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("error", Bag, Error, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
}



