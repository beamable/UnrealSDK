
#include "AutoGen/CommonResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UCommonResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("data"), Data, Serializer);
}

void UCommonResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("data"), Data, Serializer);		
}

void UCommonResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Result = Bag->GetStringField(TEXT("result"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("data")), Data, OuterOwner);
}