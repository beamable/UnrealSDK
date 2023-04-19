
#include "BeamableCore/Public/AutoGen/GroupCreate.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGroupCreate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("enrollmentType"), EnrollmentType);
	Serializer->WriteValue(TEXT("requirement"), Requirement);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	Serializer->WriteValue(TEXT("maxSize"), MaxSize);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("time"), &Time, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("group"), &Group, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);
}

void UGroupCreate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("enrollmentType"), EnrollmentType);
	Serializer->WriteValue(TEXT("requirement"), Requirement);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	Serializer->WriteValue(TEXT("maxSize"), MaxSize);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("time"), &Time, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("group"), &Group, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);		
}

void UGroupCreate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	EnrollmentType = Bag->GetStringField(TEXT("enrollmentType"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("requirement")), Requirement);
	Type = UGroupTypeLibrary::SerializationNameToGroupType(Bag->GetStringField(TEXT("type")));
	MaxSize = Bag->GetIntegerField(TEXT("maxSize"));
	UBeamJsonUtils::DeserializeOptional<FString>("tag", Bag, Tag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("clientData", Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("time", Bag, Time, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("group", Bag, Group, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>("scores", Bag, Scores, OuterOwner);
}



