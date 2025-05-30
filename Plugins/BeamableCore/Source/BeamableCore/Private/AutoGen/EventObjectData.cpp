
#include "BeamableCore/Public/AutoGen/EventObjectData.h"
#include "Serialization/BeamJsonUtils.h"



void UEventObjectData::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UEventObjectData::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("done"), bDone, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("running"), bRunning, Serializer);
	Serializer->WriteValue(TEXT("state"), UBeamJsonUtils::EnumToSerializationName(State));
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("leaderboardId"), LeaderboardId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeUObject<UEvent*>("content", Content, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lastChildEventId"), &LastChildEventId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("rootEventId"), &RootEventId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("originType"), &OriginType, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventPhaseRuntime*>(TEXT("phase"), &Phase, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("origin"), &Origin, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventPhaseTime*>, UEventPhaseTime*>(TEXT("phaseTimes"), &PhaseTimes, Serializer);
}

void UEventObjectData::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("done"), bDone, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("running"), bRunning, Serializer);
	Serializer->WriteValue(TEXT("state"), UBeamJsonUtils::EnumToSerializationName(State));
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("leaderboardId"), LeaderboardId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeUObject<UEvent*>("content", Content, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lastChildEventId"), &LastChildEventId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("rootEventId"), &RootEventId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("originType"), &OriginType, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventPhaseRuntime*>(TEXT("phase"), &Phase, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("origin"), &Origin, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventPhaseTime*>, UEventPhaseTime*>(TEXT("phaseTimes"), &PhaseTimes, Serializer);		
}

void UEventObjectData::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("done")), bDone);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("running")), bRunning);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("state")), State);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("leaderboardId")), LeaderboardId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeUObject<UEvent*>("content", Bag, Content, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("lastChildEventId", Bag, LastChildEventId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("startTime", Bag, StartTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("rootEventId", Bag, RootEventId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("originType", Bag, OriginType, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UEventPhaseRuntime*>("phase", Bag, Phase, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamClientPermission>("permissions", Bag, Permissions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("endTime", Bag, EndTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("origin", Bag, Origin, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdAt", Bag, CreatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>("inFlight", Bag, InFlight, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventPhaseTime*>, UEventPhaseTime*>("phaseTimes", Bag, PhaseTimes, OuterOwner);
}



