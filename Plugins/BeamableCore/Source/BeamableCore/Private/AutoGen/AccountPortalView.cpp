
#include "AutoGen/AccountPortalView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UAccountPortalView ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("thirdPartyAppAssociations"), ThirdPartyAppAssociations, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("roleString"), &RoleString, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URoleMapping*>, URoleMapping*>(TEXT("roles"), &Roles, Serializer);
}

void UAccountPortalView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("thirdPartyAppAssociations"), ThirdPartyAppAssociations, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("roleString"), &RoleString, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URoleMapping*>, URoleMapping*>(TEXT("roles"), &Roles, Serializer);		
}

void UAccountPortalView ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("scopes")), Scopes, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("thirdPartyAppAssociations")), ThirdPartyAppAssociations, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("roleString", Bag, RoleString, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URoleMapping*>, URoleMapping*>("roles", Bag, Roles, OuterOwner);
}