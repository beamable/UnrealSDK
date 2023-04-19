
#include "BeamableCore/Public/AutoGen/GetGameRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetGameRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("rootPID"), &RootPID, Serializer);
}

void UGetGameRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("rootPID"), &RootPID, Serializer);		
}

void UGetGameRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("rootPID")), RootPID, OuterOwner);
}



