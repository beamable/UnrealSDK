
#include "AutoGen/LaunchMessageListResponse.h"
#include "Serialization/BeamJsonUtils.h"


void ULaunchMessageListResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("files"), Files, Serializer);
}

void ULaunchMessageListResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("files"), Files, Serializer);		
}

void ULaunchMessageListResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("files")), Files, OuterOwner);
}