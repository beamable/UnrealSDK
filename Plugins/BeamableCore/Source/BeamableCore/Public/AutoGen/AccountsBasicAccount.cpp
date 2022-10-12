
#include "AutoGen/AccountsBasicAccount.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UAccountsBasicAccount ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	Serializer->WriteValue(TEXT("createdTimeMillis"), CreatedTimeMillis);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("roleString"), &RoleString, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deviceIds"), &DeviceIds, Serializer);
	Serializer->WriteValue(TEXT("privilegedAccount"), bPrivilegedAccount);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("country"), &Country, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("wasMigrated"), &bWasMigrated, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UGamerTagAssociation*>(TEXT("gamerTags"), GamerTags, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URoleMapping*>, URoleMapping*>(TEXT("roles"), &Roles, Serializer);
	Serializer->WriteValue(TEXT("updatedTimeMillis"), UpdatedTimeMillis);
	UBeamJsonUtils::SerializeArray<UThirdPartyAssociation*>(TEXT("thirdParties"), ThirdParties, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("deviceId"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("userName"), &UserName, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("heartbeat"), &Heartbeat, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
}

void UAccountsBasicAccount::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	Serializer->WriteValue(TEXT("createdTimeMillis"), CreatedTimeMillis);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("roleString"), &RoleString, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deviceIds"), &DeviceIds, Serializer);
	Serializer->WriteValue(TEXT("privilegedAccount"), bPrivilegedAccount);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("country"), &Country, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("wasMigrated"), &bWasMigrated, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UGamerTagAssociation*>(TEXT("gamerTags"), GamerTags, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URoleMapping*>, URoleMapping*>(TEXT("roles"), &Roles, Serializer);
	Serializer->WriteValue(TEXT("updatedTimeMillis"), UpdatedTimeMillis);
	UBeamJsonUtils::SerializeArray<UThirdPartyAssociation*>(TEXT("thirdParties"), ThirdParties, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("deviceId"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("userName"), &UserName, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("heartbeat"), &Heartbeat, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);		
}

void UAccountsBasicAccount ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>("inFlight", Bag, InFlight, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("createdTimeMillis")), CreatedTimeMillis);
	UBeamJsonUtils::DeserializeOptional<FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("roleString", Bag, RoleString, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("deviceIds", Bag, DeviceIds, OuterOwner);
	bPrivilegedAccount = Bag->GetBoolField(TEXT("privilegedAccount"));
	UBeamJsonUtils::DeserializeOptional<FString>("country", Bag, Country, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("wasMigrated", Bag, bWasMigrated, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeArray<UGamerTagAssociation*>(Bag->GetArrayField(TEXT("gamerTags")), GamerTags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URoleMapping*>, URoleMapping*>("roles", Bag, Roles, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("updatedTimeMillis")), UpdatedTimeMillis);
	UBeamJsonUtils::DeserializeArray<UThirdPartyAssociation*>(Bag->GetArrayField(TEXT("thirdParties")), ThirdParties, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("deviceId", Bag, DeviceId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("userName", Bag, UserName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("heartbeat", Bag, Heartbeat, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("password", Bag, Password, OuterOwner);
}