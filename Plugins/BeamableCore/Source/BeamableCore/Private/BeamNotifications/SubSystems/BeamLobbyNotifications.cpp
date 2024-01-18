#include "BeamNotifications/SubSystems/BeamLobbyNotifications.h"

#include "BeamLogging.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "BeamNotifications/BeamNotifications.h"
#include "Serialization/BeamJsonUtils.h"

void FLobbyUpdateNotificationMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("event"), UBeamJsonUtils::EnumToSerializationName<EBeamLobbyEvent>(Type));
	switch (Type)
	{
	case EBeamLobbyEvent::BEAM_LobbyCreated:
		{
			break;
		}
	case EBeamLobbyEvent::BEAM_LobbyDisbanded:
		{
			break;
		}
	case EBeamLobbyEvent::BEAM_DataChanged:
		{
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerJoined:
		{
			Serializer->WriteValue(TEXT("playerId"), PlayerJoinedData.JoinedGamerTag.AsString);
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerLeft:
		{
			Serializer->WriteValue(TEXT("playerId"), PlayerLeftData.LeftGamerTag.AsString);
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerKicked:
		{
			Serializer->WriteValue(TEXT("playerId"), PlayerKickedData.KickedGamerTag.AsString);
			break;
		}
	case EBeamLobbyEvent::BEAM_HostPlayerChanged:
		{
			Serializer->WriteValue(TEXT("playerId"), HostPlayerChangedData.NewHostGamerTag.AsString);
			break;
		}
	default:
		{
			break;
		}
	}
}

void FLobbyUpdateNotificationMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("event"), UBeamJsonUtils::EnumToSerializationName<EBeamLobbyEvent>(Type));
	switch (Type)
	{
	case EBeamLobbyEvent::BEAM_LobbyCreated:
		{
			break;
		}
	case EBeamLobbyEvent::BEAM_LobbyDisbanded:
		{
			break;
		}
	case EBeamLobbyEvent::BEAM_DataChanged:
		{
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerJoined:
		{
			Serializer->WriteValue(TEXT("playerId"), PlayerJoinedData.JoinedGamerTag.AsString);
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerLeft:
		{
			Serializer->WriteValue(TEXT("playerId"), PlayerLeftData.LeftGamerTag.AsString);
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerKicked:
		{
			Serializer->WriteValue(TEXT("playerId"), PlayerKickedData.KickedGamerTag.AsString);
			break;
		}
	case EBeamLobbyEvent::BEAM_HostPlayerChanged:
		{
			Serializer->WriteValue(TEXT("playerId"), HostPlayerChangedData.NewHostGamerTag.AsString);
			break;
		}
	default:
		{
			break;
		}
	}
}

void FLobbyUpdateNotificationMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("event")), Type, OuterOwner);
	switch (Type)
	{
	case EBeamLobbyEvent::BEAM_LobbyCreated:
		{
			break;
		}
	case EBeamLobbyEvent::BEAM_LobbyDisbanded:
		{
			break;
		}
	case EBeamLobbyEvent::BEAM_DataChanged:
		{
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerJoined:
		{
			PlayerJoinedData.JoinedGamerTag = Bag->GetStringField(TEXT("playerId"));
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerLeft:
		{
			PlayerLeftData.LeftGamerTag = Bag->GetStringField(TEXT("playerId"));
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerKicked:
		{
			PlayerKickedData.KickedGamerTag = Bag->GetStringField(TEXT("playerId"));
			break;
		}
	case EBeamLobbyEvent::BEAM_HostPlayerChanged:
		{
			HostPlayerChangedData.NewHostGamerTag = Bag->GetStringField(TEXT("playerId"));
			break;
		}
	default:
		{
			break;
		}
	}
}

void UBeamLobbyNotifications::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Notifications = Collection.InitializeDependency<UBeamNotifications>();
}

void UBeamLobbyNotifications::SubscribeToLobbyUpdate(const FUserSlot& Slot, const FName& SocketName, FGuid LobbyId, const FOnLobbyUpdateNotification& Handler) const
{
	FDelegateHandle Handle;
	const auto      Key = FString::Format(*CTX_KEY_Lobby_Update, {LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower)});
	if (!Notifications->TrySubscribeForMessage<FOnLobbyUpdateNotification, FLobbyUpdateNotificationMessage>(Slot, SocketName, Key, Handler, Handle))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
	else
	{
		UE_LOG(LogBeamNotifications, Verbose, TEXT("Subscribed to message. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
}

FDelegateHandle UBeamLobbyNotifications::CPP_SubscribeToLobbyUpdate(const FUserSlot& Slot, const FName& SocketName, FGuid LobbyId, const FOnLobbyUpdateNotificationCode& Handler) const
{
	FDelegateHandle Handle;
	const auto      Key = FString::Format(*CTX_KEY_Lobby_Update, {LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower)});
	if (!Notifications->TrySubscribeForMessage<FOnLobbyUpdateNotificationCode, FLobbyUpdateNotificationMessage>(Slot, SocketName, Key, Handler, Handle))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("Trying to subscribe to a non-existent socket. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
	else
	{
		UE_LOG(LogBeamNotifications, Verbose, TEXT("Subscribed to message. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
	return Handle;
}

FDelegateHandle UBeamLobbyNotifications::CPP_UnsubscribeToLobbyUpdate(const FUserSlot& Slot, const FName& SocketName, FGuid LobbyId, const FDelegateHandle& Handle) const
{
	const auto Key = FString::Format(*CTX_KEY_Lobby_Update, {LobbyId.ToString(EGuidFormats::DigitsWithHyphensLower)});
	if (!Notifications->TryUnsubscribeFromMessage(Slot, SocketName, Key, Handle))
	{
		UE_LOG(LogBeamNotifications, Verbose, TEXT("Failed to find the given handle so there was no need to unsubscribe. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
	else
	{
		UE_LOG(LogBeamNotifications, Verbose, TEXT("Unsubscribe from message. SLOT=%s, ID=%s, KEY=%s"), *Slot.Name, *SocketName.ToString(), *Key);
	}
	return Handle;
}
