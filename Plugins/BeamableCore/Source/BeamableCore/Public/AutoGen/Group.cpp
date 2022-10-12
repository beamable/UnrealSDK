
#include "AutoGen/Group.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UGroup ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("enrollmentType"), EnrollmentType);
	UBeamJsonUtils::SerializeOptional<TArray<UDonationRequestBody*>, UDonationRequestBody*>(TEXT("donations"), &Donations, Serializer);
	Serializer->WriteValue(TEXT("freeSlots"), FreeSlots);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UDonationRequestBody*>, UDonationRequestBody*>(TEXT("maybeDonations"), &MaybeDonations, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateMOTD"), &bCanUpdateMOTD, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateSlogan"), &bCanUpdateSlogan, Serializer);
	Serializer->WriteValue(TEXT("leader"), Leader);
	Serializer->WriteValue(TEXT("slogan"), Slogan);
	Serializer->WriteValue(TEXT("requirement"), Requirement);
	Serializer->WriteValue(TEXT("motd"), Motd);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("version"), &Version, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupRole*>, UGroupRole*>(TEXT("roles"), &Roles, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("scores"), Scores, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateEnrollment"), &bCanUpdateEnrollment, Serializer);
	UBeamJsonUtils::SerializeArray<UMember*>(TEXT("members"), Members, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canDisband"), &bCanDisband, Serializer);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	Serializer->WriteValue(TEXT("maxSize"), MaxSize);
	UBeamJsonUtils::SerializeArray<UGroup*>(TEXT("subGroups"), SubGroups, Serializer);
	Serializer->WriteValue(TEXT("created"), Created);
}

void UGroup::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("enrollmentType"), EnrollmentType);
	UBeamJsonUtils::SerializeOptional<TArray<UDonationRequestBody*>, UDonationRequestBody*>(TEXT("donations"), &Donations, Serializer);
	Serializer->WriteValue(TEXT("freeSlots"), FreeSlots);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UDonationRequestBody*>, UDonationRequestBody*>(TEXT("maybeDonations"), &MaybeDonations, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateMOTD"), &bCanUpdateMOTD, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateSlogan"), &bCanUpdateSlogan, Serializer);
	Serializer->WriteValue(TEXT("leader"), Leader);
	Serializer->WriteValue(TEXT("slogan"), Slogan);
	Serializer->WriteValue(TEXT("requirement"), Requirement);
	Serializer->WriteValue(TEXT("motd"), Motd);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("version"), &Version, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupRole*>, UGroupRole*>(TEXT("roles"), &Roles, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("scores"), Scores, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateEnrollment"), &bCanUpdateEnrollment, Serializer);
	UBeamJsonUtils::SerializeArray<UMember*>(TEXT("members"), Members, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canDisband"), &bCanDisband, Serializer);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	Serializer->WriteValue(TEXT("maxSize"), MaxSize);
	UBeamJsonUtils::SerializeArray<UGroup*>(TEXT("subGroups"), SubGroups, Serializer);
	Serializer->WriteValue(TEXT("created"), Created);		
}

void UGroup ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>("inFlight", Bag, InFlight, OuterOwner);
	Name = Bag->GetStringField(TEXT("name"));
	EnrollmentType = Bag->GetStringField(TEXT("enrollmentType"));
	UBeamJsonUtils::DeserializeOptional<TArray<UDonationRequestBody*>, UDonationRequestBody*>("donations", Bag, Donations, OuterOwner);
	FreeSlots = Bag->GetIntegerField(TEXT("freeSlots"));
	UBeamJsonUtils::DeserializeOptional<TMap<FString, UDonationRequestBody*>, UDonationRequestBody*>("maybeDonations", Bag, MaybeDonations, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("tag", Bag, Tag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canUpdateMOTD", Bag, bCanUpdateMOTD, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("shard", Bag, Shard, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canUpdateSlogan", Bag, bCanUpdateSlogan, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("leader")), Leader);
	Slogan = Bag->GetStringField(TEXT("slogan"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("requirement")), Requirement);
	Motd = Bag->GetStringField(TEXT("motd"));
	UBeamJsonUtils::DeserializeOptional<int32>("version", Bag, Version, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeOptional<FString>("clientData", Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupRole*>, UGroupRole*>("roles", Bag, Roles, OuterOwner);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("scores")), Scores, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canUpdateEnrollment", Bag, bCanUpdateEnrollment, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UMember*>(Bag->GetArrayField(TEXT("members")), Members, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canDisband", Bag, bCanDisband, OuterOwner);
	Type = UGroupTypeLibrary::SerializationNameToGroupType(Bag->GetStringField(TEXT("type")));
	MaxSize = Bag->GetIntegerField(TEXT("maxSize"));
	UBeamJsonUtils::DeserializeArray<UGroup*>(Bag->GetArrayField(TEXT("subGroups")), SubGroups, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
}