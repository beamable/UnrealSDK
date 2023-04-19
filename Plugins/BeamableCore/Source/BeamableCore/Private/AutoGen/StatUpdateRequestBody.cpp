
#include "BeamableCore/Public/AutoGen/StatUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatUpdateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("emitAnalytics"), &bEmitAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamStatsType, FString>(TEXT("objectId"), &ObjectId, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("set"), &Set, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("add"), &Add, Serializer);
}

void UStatUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("emitAnalytics"), &bEmitAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamStatsType, FString>(TEXT("objectId"), &ObjectId, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("set"), &Set, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("add"), &Add, Serializer);		
}

void UStatUpdateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("emitAnalytics", Bag, bEmitAnalytics, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamStatsType, FString>("objectId", Bag, ObjectId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("set", Bag, Set, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("add", Bag, Add, OuterOwner);
}



