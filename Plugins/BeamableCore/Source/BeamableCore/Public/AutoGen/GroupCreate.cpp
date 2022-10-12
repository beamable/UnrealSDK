
#include "AutoGen/GroupCreate.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UGroupCreate ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("enrollmentType"), EnrollmentType);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	Serializer->WriteValue(TEXT("requirement"), Requirement);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("time"), &Time, Serializer);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	Serializer->WriteValue(TEXT("maxSize"), MaxSize);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("group"), &Group, Serializer);
}

void UGroupCreate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("enrollmentType"), EnrollmentType);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	Serializer->WriteValue(TEXT("requirement"), Requirement);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("time"), &Time, Serializer);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	Serializer->WriteValue(TEXT("maxSize"), MaxSize);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("group"), &Group, Serializer);		
}

void UGroupCreate ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	EnrollmentType = Bag->GetStringField(TEXT("enrollmentType"));
	UBeamJsonUtils::DeserializeOptional<FString>("tag", Bag, Tag, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("requirement")), Requirement);
	UBeamJsonUtils::DeserializeOptional<FString>("clientData", Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>("scores", Bag, Scores, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("time", Bag, Time, OuterOwner);
	Type = UGroupTypeLibrary::SerializationNameToGroupType(Bag->GetStringField(TEXT("type")));
	MaxSize = Bag->GetIntegerField(TEXT("maxSize"));
	UBeamJsonUtils::DeserializeOptional<int64>("group", Bag, Group, OuterOwner);
}