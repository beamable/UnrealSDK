
#include "BeamableCore/Public/AutoGen/BeamoV2ProblemDetails.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ProblemDetails::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("detail"), &Detail, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("instance"), &Instance, Serializer);
}

void UBeamoV2ProblemDetails::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("detail"), &Detail, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("instance"), &Instance, Serializer);		
}

void UBeamoV2ProblemDetails::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("type", Bag, Type, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("title", Bag, Title, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("status", Bag, Status, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("detail", Bag, Detail, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("instance", Bag, Instance, OuterOwner);
}



