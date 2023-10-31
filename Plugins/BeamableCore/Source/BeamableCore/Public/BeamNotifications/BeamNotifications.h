// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamLogging.h"
#include "WebSocketsModule.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/EngineSubsystem.h"
#include "UserSlots/UserSlot.h"
#include "WebSockets/Public/IWebSocket.h"

#include "BeamNotifications.generated.h"

class UBeamNotifications;
class UBeamUserSlots;
class UBeamBackend;

/**
 * Type of notification events (map to each of UE's WebSocket callbacks).
 */
UENUM(BlueprintType)
enum ENotificationMessageType
{
	Connected,
	ConnectionFailed,
	Message,
	Closed
};

/**
 * Handle for a websocket connection. In Beamable, each WebSocket connection is associated with a name AND a FUserSlot.
 * The combination of these form this unique handle.
 * During BeamRuntime authentication, we create a WebSocket connection to Beamable and store the handle in association with that user.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamWebSocketHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FUserSlot Slot;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FName Id;

	FBeamWebSocketHandle() = default;

	FBeamWebSocketHandle(const FUserSlot& Owner, const FName& Id, UBeamNotifications* Socket)
		: Slot(Owner),
		  Id(Id),
		  Socket(Socket)
	{
	}

	friend bool operator==(const FBeamWebSocketHandle& Lhs, const FBeamWebSocketHandle& RHS)
	{
		return Lhs.Id == RHS.Id;
	}

	friend bool operator!=(const FBeamWebSocketHandle& Lhs, const FBeamWebSocketHandle& RHS)
	{
		return !(Lhs == RHS);
	}

private:
	UPROPERTY()
	UBeamNotifications* Socket = nullptr;
};

FORCEINLINE uint32 GetTypeHash(const FBeamWebSocketHandle& SocketHandle) { return GetTypeHash(SocketHandle.Id); }

/**
 * Data struct for the Connected ENotificationMessageType type.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FNotificationConnected
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FBeamWebSocketHandle ConnectedHandle;
};

/**
 * Data struct for the ConnectionFailed ENotificationMessageType type.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FNotificationConnectionFailed
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString Error;
};

/**
 * Data for the Message ENotificationMessageType.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FNotificationMessage : public FBeamJsonSerializable
{
	GENERATED_BODY()

	/**
	 * This is a unique key that defines the "type" of the message that was received. For example:
	 * 'content.refresh' means that new content was published to the connected realm.
	 * 'inventory.refresh' means that the player's inventory was updated in some way. 
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString Context;

	/**
	 * A JSON string, to be deserialized into a FBeamJsonSerializable struct, containing some data associated with the context.
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString MessageFull;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("context"), Context);
		Serializer->WriteValue(TEXT("messageFull"), MessageFull);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("context"), Context);
		Serializer->WriteValue(TEXT("messageFull"), MessageFull);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Context     = Bag->GetStringField(TEXT("context"));
		MessageFull = Bag->GetStringField(TEXT("messageFull"));
	}
};

/**
 * Data for the Closed ENotificationMessageType.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FNotificationClosed
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	int32 StatusCode = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FString Reason;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	bool bWasClean = false;
};

/**
 * Notification event type. Only the data for the current ENotificationMessageType is ever filled.
 * Since BPs don't support unions, this can't be a tagged union.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FNotificationEvent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	TEnumAsByte<ENotificationMessageType> EventType = Connected;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FNotificationConnected ConnectedData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FNotificationConnectionFailed ConnectionFailedData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FNotificationClosed ClosedData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FNotificationMessage MessageData;
};

DECLARE_DELEGATE_OneParam(FOnNotificationEvent, const FNotificationEvent&);

USTRUCT()
struct FNotificationMessageEventHandler
{
	GENERATED_BODY()

	FNotificationMessageEventHandler() = default;	

	friend bool operator==(const FNotificationMessageEventHandler& Lhs, const FNotificationMessageEventHandler& RHS)
	{
		return Lhs.ContextKey == RHS.ContextKey;
	}

	friend bool operator!=(const FNotificationMessageEventHandler& Lhs, const FNotificationMessageEventHandler& RHS)
	{
		return !(Lhs == RHS);
	}

	
	FString              ContextKey;
	FOnNotificationEvent Handler;
};

FORCEINLINE uint32 GetTypeHash(const FNotificationMessageEventHandler& MessageEventHandler) { return GetTypeHash(MessageEventHandler.ContextKey); }


/**
 * Notification engine system. This system keeps track of all Open Websocket connections in association with a UserSlot and a connection name.
 * It also handles disposing of PIE connections.
 *
 * This is integral for Runtime connectivity management. See BeamRuntime class for details.
 */
UCLASS(BlueprintType, NotBlueprintable)
class BEAMABLECORE_API UBeamNotifications : public UEngineSubsystem
{
	GENERATED_BODY()

	TMap<FUserSlot, TMap<FName, TSharedPtr<IWebSocket>>> OpenSockets;

	TArray<FBeamWebSocketHandle> PlayModeHandles;

	TMap<FBeamWebSocketHandle, FOnNotificationEvent>                  ConnectionEventHandlers;
	TMultiMap<FBeamWebSocketHandle, FNotificationMessageEventHandler> MessageEventHandlers;

	UPROPERTY()
	UBeamUserSlots* UserSlots;
	UPROPERTY()
	UBeamBackend* Backend;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

public:
	bool TryConnect(const FUserSlot& Slot, const FName& SocketName, const FString& Uri, const TMap<FString, FString>& ExtraHeaders, const FOnNotificationEvent& ConnectionEventHandler, FBeamWebSocketHandle& OutHandle, UObject* ContextObject = nullptr);

	void Connect(const FUserSlot& Slot, const FBeamRealmUser& UserData, const FName& SocketName, const FString& Uri, const TMap<FString, FString>& ExtraHeaders, const FOnNotificationEvent& ConnectionEventHandler, FBeamWebSocketHandle& OutHandle, UObject* ContextObject = nullptr);

	bool TryGetHandle(const FUserSlot& Slot, const FName& SocketName, FBeamWebSocketHandle& OutHandle);

	void ClearPIESockets();

	template <typename THandler, typename TMessage>
	bool TrySubscribeForMessage(const FUserSlot& Slot, const FName& SocketName, const FString& ContextKey, THandler Handler)
	{
		if (OpenSockets.Contains(Slot))
		{
			if (const auto& UserSockets = OpenSockets.FindChecked(Slot); UserSockets.Contains(SocketName))
			{
				// Make sure the Handler is an actual delegate
				static_assert(TIsDerivedFrom<THandler, TDelegate<void(TMessage)>>::Value ||
					TIsDerivedFrom<THandler, TBaseDynamicDelegate<FWeakObjectPtr, void, TMessage>>::Value);

				// Make sure the Message type is a FBeamJsonSerializable
				static_assert(TIsDerivedFrom<TMessage, FBeamJsonSerializable>::Value);

				const FOnNotificationEvent EventHandler = FOnNotificationEvent::CreateLambda([Slot, SocketName, ContextKey, Handler](FNotificationEvent Evt)
				{
					ensureAlways(Evt.EventType == Message);
					ensureAlways(Evt.MessageData.Context.Equals(ContextKey));

					TMessage MsgData;
					MsgData.BeamDeserialize(Evt.MessageData.MessageFull);

					const bool bDidRun = Handler.ExecuteIfBound(MsgData);
					ensureAlwaysMsgf(bDidRun, TEXT("The notification message handler was not bound. SLOT=%s, ID=%s, CONTEXT=%s"), *Slot.Name, *SocketName.ToString(), *ContextKey);
				});

				MessageEventHandlers.Add(FBeamWebSocketHandle(Slot, SocketName, this), {ContextKey, EventHandler});
				return true;
			}
		}

		return false;
	}

	bool TryUnsubscribeAllFromMessage(const FUserSlot& Slot, const FName& SocketName, const FString& ContextKey)
	{
		if (OpenSockets.Contains(Slot))
		{
			if (const auto& UserSockets = OpenSockets.FindChecked(Slot); UserSockets.Contains(SocketName))
			{
				const FBeamWebSocketHandle Key(Slot, SocketName, this);

				TArray<FNotificationMessageEventHandler> Handlers;
				MessageEventHandlers.MultiFind(Key, Handlers);
				for (const auto& NotificationMessageEventHandler : Handlers)
				{
					if (NotificationMessageEventHandler.ContextKey.Equals(ContextKey))
						MessageEventHandlers.RemoveSingle(Key, NotificationMessageEventHandler);
				}

				return true;
			}
		}

		return false;
	}
};
