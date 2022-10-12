
#include "AutoGen/EventObjectData.h"
#include "Serialization/BeamJsonUtils.h"


void UEventObjectData ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("rootEventId"), &RootEventId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("originType"), &OriginType, Serializer);
	Serializer->WriteValue(TEXT("state"), UEventStateLibrary::EventStateToSerializationName(State));
	Serializer->WriteValue(TEXT("running"), bRunning);
	UBeamJsonUtils::SerializeOptional<UEventPhaseRuntime*>(TEXT("phase"), &Phase, Serializer);
	UBeamJsonUtils::SerializeOptional<UClientPermission*>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lastChildEventId"), &LastChildEventId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("origin"), &Origin, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeUObject<UEvent*>("content", Content, Serializer);
	Serializer->WriteValue(TEXT("done"), bDone);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
	UBeamJsonUtils::SerializeOptional<TArray<UEventPhaseTime*>, UEventPhaseTime*>(TEXT("phaseTimes"), &PhaseTimes, Serializer);
}

void UEventObjectData::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("rootEventId"), &RootEventId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("originType"), &OriginType, Serializer);
	Serializer->WriteValue(TEXT("state"), UEventStateLibrary::EventStateToSerializationName(State));
	Serializer->WriteValue(TEXT("running"), bRunning);
	UBeamJsonUtils::SerializeOptional<UEventPhaseRuntime*>(TEXT("phase"), &Phase, Serializer);
	UBeamJsonUtils::SerializeOptional<UClientPermission*>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lastChildEventId"), &LastChildEventId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("origin"), &Origin, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeUObject<UEvent*>("content", Content, Serializer);
	Serializer->WriteValue(TEXT("done"), bDone);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
	UBeamJsonUtils::SerializeOptional<TArray<UEventPhaseTime*>, UEventPhaseTime*>(TEXT("phaseTimes"), &PhaseTimes, Serializer);		
}

void UEventObjectData ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>("inFlight", Bag, InFlight, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("startTime", Bag, StartTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("rootEventId", Bag, RootEventId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("originType", Bag, OriginType, OuterOwner);
	State = UEventStateLibrary::SerializationNameToEventState(Bag->GetStringField(TEXT("state")));
	bRunning = Bag->GetBoolField(TEXT("running"));
	UBeamJsonUtils::DeserializeOptional<UEventPhaseRuntime*>("phase", Bag, Phase, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UClientPermission*>("permissions", Bag, Permissions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("lastChildEventId", Bag, LastChildEventId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("endTime", Bag, EndTime, OuterOwner);
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeOptional<FString>("origin", Bag, Origin, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdAt", Bag, CreatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UEvent*>("content", Bag, Content, OuterOwner);
	bDone = Bag->GetBoolField(TEXT("done"));
	LeaderboardId = Bag->GetStringField(TEXT("leaderboardId"));
	UBeamJsonUtils::DeserializeOptional<TArray<UEventPhaseTime*>, UEventPhaseTime*>("phaseTimes", Bag, PhaseTimes, OuterOwner);
}