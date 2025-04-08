
#include "BeamableCore/Public/AutoGen/Group.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UGroup::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGroup::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("requirement"), Requirement);
	Serializer->WriteValue(TEXT("maxSize"), MaxSize);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("motd"), Motd);
	Serializer->WriteValue(TEXT("slogan"), Slogan);
	Serializer->WriteValue(TEXT("leader"), Leader);
	Serializer->WriteValue(TEXT("created"), Created);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("enrollmentType"), EnrollmentType);
	Serializer->WriteValue(TEXT("freeSlots"), FreeSlots);
	UBeamJsonUtils::SerializeArray<UGroup*>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeArray<UMember*>(TEXT("members"), Members, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("scores"), Scores, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canDisband"), &bCanDisband, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateEnrollment"), &bCanUpdateEnrollment, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateMOTD"), &bCanUpdateMOTD, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateSlogan"), &bCanUpdateSlogan, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("version"), &Version, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UDonationRequestBody*>, UDonationRequestBody*>(TEXT("donations"), &Donations, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupRole*>, UGroupRole*>(TEXT("roles"), &Roles, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UDonationRequestBody*>, UDonationRequestBody*>(TEXT("maybeDonations"), &MaybeDonations, Serializer);
}

void UGroup::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("requirement"), Requirement);
	Serializer->WriteValue(TEXT("maxSize"), MaxSize);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("motd"), Motd);
	Serializer->WriteValue(TEXT("slogan"), Slogan);
	Serializer->WriteValue(TEXT("leader"), Leader);
	Serializer->WriteValue(TEXT("created"), Created);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("enrollmentType"), EnrollmentType);
	Serializer->WriteValue(TEXT("freeSlots"), FreeSlots);
	UBeamJsonUtils::SerializeArray<UGroup*>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeArray<UMember*>(TEXT("members"), Members, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("scores"), Scores, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canDisband"), &bCanDisband, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateEnrollment"), &bCanUpdateEnrollment, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateMOTD"), &bCanUpdateMOTD, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateSlogan"), &bCanUpdateSlogan, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("version"), &Version, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UDonationRequestBody*>, UDonationRequestBody*>(TEXT("donations"), &Donations, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupRole*>, UGroupRole*>(TEXT("roles"), &Roles, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UDonationRequestBody*>, UDonationRequestBody*>(TEXT("maybeDonations"), &MaybeDonations, Serializer);		
}

void UGroup::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("requirement")), Requirement);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("maxSize")), MaxSize);
	Type = UGroupTypeLibrary::SerializationNameToGroupType(Bag->GetStringField(TEXT("type")));
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("motd")), Motd);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("slogan")), Slogan);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("leader")), Leader);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("enrollmentType")), EnrollmentType);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("freeSlots")), FreeSlots);
	UBeamJsonUtils::DeserializeArray<UGroup*>(Bag->GetArrayField(TEXT("subGroups")), SubGroups, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UMember*>(Bag->GetArrayField(TEXT("members")), Members, OuterOwner);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("scores")), Scores, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canDisband", Bag, bCanDisband, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canUpdateEnrollment", Bag, bCanUpdateEnrollment, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canUpdateMOTD", Bag, bCanUpdateMOTD, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canUpdateSlogan", Bag, bCanUpdateSlogan, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("shard", Bag, Shard, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("clientData", Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("version", Bag, Version, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("tag", Bag, Tag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UDonationRequestBody*>, UDonationRequestBody*>("donations", Bag, Donations, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupRole*>, UGroupRole*>("roles", Bag, Roles, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>("inFlight", Bag, InFlight, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, UDonationRequestBody*>, UDonationRequestBody*>("maybeDonations", Bag, MaybeDonations, OuterOwner);
}



