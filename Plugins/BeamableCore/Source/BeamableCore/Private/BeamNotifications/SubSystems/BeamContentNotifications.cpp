#include "BeamNotifications/SubSystems/BeamContentNotifications.h"

#include "BeamLogging.h"
#include "BeamNotifications/BeamNotifications.h"
#include "Serialization/BeamJsonUtils.h"

void FContentRefreshManifest::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("created"), Created);
}

void FContentRefreshManifest::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("created"), Created);
}

void FContentRefreshManifest::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	Checksum = Bag->GetStringField(TEXT("checksum"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
}

void FContentRefreshNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString, FString>(TEXT("scopes"), Scopes, Serializer);
	Serializer->WriteValue(TEXT("delay"), Delay);
	UBeamJsonUtils::SerializeUStruct<FContentRefreshManifest>(TEXT("manifest"), Manifest, Serializer);
}

void FContentRefreshNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString, FString>(TEXT("scopes"), Scopes, Serializer);
	Serializer->WriteValue(TEXT("delay"), Delay);
	UBeamJsonUtils::SerializeUStruct<FContentRefreshManifest>(TEXT("manifest"), Manifest, Serializer);
}

void FContentRefreshNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString, FString>(Bag->GetArrayField(TEXT("scopes")), Scopes, OuterOwner);
	Delay = Bag->GetIntegerField(TEXT("delay"));
	UBeamJsonUtils::DeserializeUStruct(TEXT("manifest"), Bag, Manifest, OuterOwner);
}

void UBeamContentNotifications::Initialize(FSubsystemCollectionBase& Collection)
{
	Notifications = Collection.InitializeDependency<UBeamNotifications>();
}

void UBeamContentNotifications::SubscribeToContentRefresh(const FUserSlot& Slot, const FName& SocketName, const FOnContentRefreshNotification& Handler, UObject* ContextObject) const
{
	FDelegateHandle Handle;
	if (!Notifications->TrySubscribeForMessage<FOnContentRefreshNotification, FContentRefreshNotificationMessage>(Slot, SocketName, CTX_KEY_Content_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name, *SocketName.ToString());
	}
}

FDelegateHandle UBeamContentNotifications::CPP_SubscribeToContentRefresh(const FUserSlot& Slot, const FName& SocketName, const FOnContentRefreshNotificationCode& Handler, UObject* ContextObject) const
{
	FDelegateHandle Handle;
	if (!Notifications->TrySubscribeForMessage<FOnContentRefreshNotificationCode, FContentRefreshNotificationMessage>(Slot, SocketName, CTX_KEY_Content_Refresh, Handler, Handle, ContextObject))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s"), *Slot.Name, *SocketName.ToString());
	}
	return Handle;
}
