
#include "BeamableCore/Public/AutoGen/ArchiveProjectRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UArchiveProjectRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("pid"), &Pid, Serializer);
}

void UArchiveProjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("pid"), &Pid, Serializer);		
}

void UArchiveProjectRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("pid")), Pid, OuterOwner);
}



