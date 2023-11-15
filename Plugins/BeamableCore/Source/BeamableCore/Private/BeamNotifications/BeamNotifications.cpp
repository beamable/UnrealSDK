// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamNotifications/BeamNotifications.h"

#include "BeamBackend/BeamBackend.h"
#include "UserSlots/BeamUserSlots.h"

void UBeamNotifications::Initialize(FSubsystemCollectionBase& Collection)
{
	UserSlots = Collection.InitializeDependency<UBeamUserSlots>();
	Backend   = Collection.InitializeDependency<UBeamBackend>();
}

void UBeamNotifications::Deinitialize()
{
}

bool UBeamNotifications::TryConnect(const FUserSlot& Slot, const FName& SocketName, const FString& Uri, const TMap<FString, FString>& ExtraHeaders, const FOnNotificationEvent& ConnectionEventHandler, FBeamWebSocketHandle& OutHandle, UObject* ContextObject)
{
	if (FBeamRealmUser UserData; UserSlots->GetUserDataAtSlot(Slot, UserData))
	{
		Connect(Slot, UserData, SocketName, Uri, ExtraHeaders, ConnectionEventHandler, OutHandle, ContextObject);
		return true;
	}

	return false;
}

void UBeamNotifications::Connect(const FUserSlot& Slot, const FBeamRealmUser& UserData, const FName& SocketName, const FString& Uri, const TMap<FString, FString>& ExtraHeaders, const FOnNotificationEvent& ConnectionEventHandler, FBeamWebSocketHandle& OutHandle, UObject* ContextObject)
{
	const auto RefreshToken = UserData.AuthToken.AccessToken;
	auto       Headers      = TMap(ExtraHeaders);


	const auto AuthTokenHeader = FString::Format(*UBeamBackend::HEADER_VALUE_AUTHORIZATION, {RefreshToken});
	Headers.Add(UBeamBackend::HEADER_AUTHORIZATION, AuthTokenHeader);

	const auto ScopeHeader = UserData.RealmHandle.Pid.AsString.IsEmpty()
		                         ? UserData.RealmHandle.Cid.AsString
		                         : FString::Format(TEXT("{0}.{1}"), {UserData.RealmHandle.Cid.AsString, UserData.RealmHandle.Pid.AsString});
	Headers.Add(UBeamBackend::HEADER_REQUEST_SCOPE, ScopeHeader);


	OutHandle = FBeamWebSocketHandle(Slot, SocketName, this);
	UE_LOG(LogBeamNotifications, Verbose, TEXT("Attempting websocket connection. SLOT=%s, ID=%s, URI=%s, TOKEN_HEADER=%s, SCOPE_HEADER=%s"), *Slot.Name, *Uri, *SocketName.ToString(), *AuthTokenHeader, *ScopeHeader)

	const auto OpenSocket = FWebSocketsModule::Get().CreateWebSocket(Uri + TEXT("?send-session-start=true"), TEXT(""), Headers);
	OpenSocket->OnConnected().AddLambda([OutHandle, this]
	{
		// If this was a PIE socket and we are no longer in PIE when we connect, we should close up this connection.
		if (!Backend->bIsInPIE && PlayModeHandles.Contains(OutHandle))
		{
			if (OpenSockets.Contains(OutHandle.Slot))
			{
				OpenSockets[OutHandle.Slot].FindChecked(OutHandle.Id)->Close();
			}
			return;
		}

		FNotificationEvent Evt;
		Evt.EventType                     = ENotificationMessageType::Connected;
		Evt.ConnectedData.ConnectedHandle = OutHandle;

		const FOnNotificationEvent& EvtHandler = ConnectionEventHandlers.FindChecked(OutHandle);
		const bool                  bDidRun    = EvtHandler.ExecuteIfBound(Evt);
		ensureAlwaysMsgf(bDidRun, TEXT("Notification connection handler was not bound correctly! SLOT=%s, ID=%s"), *OutHandle.Slot.Name, *OutHandle.Id.ToString());

		UE_LOG(LogBeamNotifications, Verbose, TEXT("Connection Success. SLOT=%s, ID=%s"), *OutHandle.Slot.Name, *OutHandle.Id.ToString());
	});

	OpenSocket->OnConnectionError().AddLambda([OutHandle, this](const FString& Error)
	{
		// If this was a PIE socket and we are no longer in PIE when we connect, we should just clean up.
		if (!Backend->bIsInPIE && PlayModeHandles.Contains(OutHandle))
		{
			if (OpenSockets.Contains(OutHandle.Slot))
			{
				OpenSockets[OutHandle.Slot].Remove(OutHandle.Id);
				PlayModeHandles.Remove(OutHandle);

				ConnectionEventHandlers.Remove(OutHandle);
				MessageEventHandlers.Remove(OutHandle);
			}
			return;
		}

		// Trigger the event and then remove the connection from the list
		FNotificationEvent Evt;
		Evt.EventType                  = ENotificationMessageType::ConnectionFailed;
		Evt.ConnectionFailedData.Error = Error;

		const FOnNotificationEvent& EvtHandler = ConnectionEventHandlers.FindChecked(OutHandle);
		const bool                  bDidRun    = EvtHandler.ExecuteIfBound(Evt);
		ensureAlwaysMsgf(bDidRun, TEXT("Notification connection handler was not bound correctly! SLOT=%s, ID=%s"), *OutHandle.Slot.Name, *OutHandle.Id.ToString());

		// If there was an error when we tried to connect, we should just remove the connection.
		if (OpenSockets.Contains(OutHandle.Slot))
		{
			if (OpenSockets[OutHandle.Slot].Contains(OutHandle.Id))
			{
				OpenSockets[OutHandle.Slot].Remove(OutHandle.Id);
				ConnectionEventHandlers.Remove(OutHandle);
				MessageEventHandlers.Remove(OutHandle);
			}
		}

		UE_LOG(LogBeamNotifications, Error, TEXT("Connection Error. SLOT=%s, ID=%s"), *OutHandle.Slot.Name, *OutHandle.Id.ToString());
	});

	OpenSocket->OnClosed().AddLambda([OutHandle, this](int32 StatusCode, const FString& Reason, bool bWasClean)
	{
		// If this was a PIE socket and we are no longer in PIE when try to close, we should just clean up.
		if (!Backend->bIsInPIE && PlayModeHandles.Contains(OutHandle))
		{
			if (OpenSockets.Contains(OutHandle.Slot))
			{
				OpenSockets[OutHandle.Slot].Remove(OutHandle.Id);
				PlayModeHandles.Remove(OutHandle);

				ConnectionEventHandlers.Remove(OutHandle);
				MessageEventHandlers.Remove(OutHandle);
			}
			return;
		}

		// Trigger the event 
		FNotificationEvent Evt;
		Evt.EventType             = ENotificationMessageType::Closed;
		Evt.ClosedData.Reason     = Reason;
		Evt.ClosedData.StatusCode = StatusCode;
		Evt.ClosedData.bWasClean  = bWasClean;

		const FOnNotificationEvent& EvtHandler = ConnectionEventHandlers.FindChecked(OutHandle);
		const bool                  bDidRun    = EvtHandler.ExecuteIfBound(Evt);
		ensureAlwaysMsgf(bDidRun, TEXT("Notification connection handler was not bound correctly! SLOT=%s, ID=%s"), *OutHandle.Slot.Name, *OutHandle.Id.ToString());

		if (OpenSockets.Contains(OutHandle.Slot))
		{
			if (OpenSockets[OutHandle.Slot].Contains(OutHandle.Id))
			{
				OpenSockets[OutHandle.Slot].Remove(OutHandle.Id);
				ConnectionEventHandlers.Remove(OutHandle);
				MessageEventHandlers.Remove(OutHandle);
				PlayModeHandles.Remove(OutHandle);
			}
		}

		UE_LOG(LogBeamNotifications, Verbose, TEXT("Connection Closed. SLOT=%s, ID=%s"), *OutHandle.Slot.Name, *OutHandle.Id.ToString());
	});

	OpenSocket->OnMessage().AddLambda([OutHandle, this](const FString& Message)
	{
		// If this was a PIE socket and we are no longer in PIE when we receive a message, we should close up this connection and not run any message callbacks.
		if (!Backend->bIsInPIE && PlayModeHandles.Contains(OutHandle))
		{
			if (OpenSockets.Contains(OutHandle.Slot))
			{
				OpenSockets[OutHandle.Slot].FindChecked(OutHandle.Id)->Close();
			}
			return;
		}

		FNotificationEvent Evt;
		Evt.EventType = ENotificationMessageType::Message;
		Evt.MessageData.BeamDeserialize(Message);

		TArray<FNotificationMessageEventHandler> EvtHandlers;
		MessageEventHandlers.MultiFind(OutHandle, EvtHandlers, true);
		for (int i = 0; i < EvtHandlers.Num(); ++i)
		{
			if (Evt.MessageData.Context.Equals(EvtHandlers[i].ContextKey))
			{
				const bool bDidRun = EvtHandlers[i].Handler.ExecuteIfBound(Evt);
				ensureAlwaysMsgf(bDidRun, TEXT("Notification message handler was not bound correctly! SLOT=%s, ID=%s Message=%s"), *OutHandle.Slot.Name, *OutHandle.Id.ToString(), *Message);
			}
			else
			{
				UE_LOG(LogBeamNotifications, Verbose, TEXT("Skipping handler for this message: Handler doesn't care about this context. SLOT=%s, ID=%s, CONTEXT=%s"), *OutHandle.Slot.Name, *OutHandle.Id.ToString(), *EvtHandlers[i].ContextKey)
			}
		}

		UE_LOG(LogBeamNotifications, Verbose, TEXT("Notification message received. SLOT=%s, ID=%s Message=%s"), *OutHandle.Slot.Name, *OutHandle.Id.ToString(), *Message);
	});

	// Add the socket to the list of open sockets
	if (OpenSockets.Contains(Slot))
		OpenSockets.FindChecked(Slot).Add(SocketName, OpenSocket);
	else
		OpenSockets.Add(Slot, {{SocketName, OpenSocket}});

	// Keep track of sockets that are opened from PIE sessions
	if (ContextObject && ContextObject->GetWorld() && ContextObject->GetWorld()->IsPlayInEditor())
		PlayModeHandles.Add(OutHandle);

	// Register the ConnectionEventHandler
	ConnectionEventHandlers.Add(OutHandle, ConnectionEventHandler);

	// Connect
	OpenSocket->Connect();
}

bool UBeamNotifications::TryGetHandle(const FUserSlot& Slot, const FName& SocketName, FBeamWebSocketHandle& OutHandle)
{
	if (OpenSockets.Contains(Slot))
	{
		const auto& UserSockets = OpenSockets.FindChecked(Slot);
		if (UserSockets.Contains(SocketName))
		{
			OutHandle = FBeamWebSocketHandle(Slot, SocketName, this);
			return true;
		}
	}

	OutHandle = FBeamWebSocketHandle(FUserSlot{}, {}, this);
	return false;
}

void UBeamNotifications::CloseSocketsForSlot(const FUserSlot& Slot)
{
	if (const auto Slots = OpenSockets.Find(Slot))
	{
		for (const auto WebSocket : *Slots)
		{
			WebSocket.Value->Close(1000, TEXT("User signed out"));
		}
		Slots->Reset();
	}
}

void UBeamNotifications::ClearPIESockets()
{
	for (FBeamWebSocketHandle PlayModeHandle : PlayModeHandles)
	{
		if (const auto Slots = OpenSockets.Find(PlayModeHandle.Slot))
		{
			if (const auto Socket = Slots->FindRef(PlayModeHandle.Id))
			{
				Socket->Close(1000, TEXT("PIE Closed"));
			}
		}
	}
}
