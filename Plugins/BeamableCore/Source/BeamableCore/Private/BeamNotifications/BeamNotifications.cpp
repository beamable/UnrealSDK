// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamNotifications/BeamNotifications.h"

#include "BeamBackend/BeamBackend.h"
#include "UserSlots/BeamUserSlots.h"

void UBeamNotifications::Initialize(FSubsystemCollectionBase& Collection)
{
	UserSlots = Collection.InitializeDependency<UBeamUserSlots>();
	Backend = Collection.InitializeDependency<UBeamBackend>();
}

void UBeamNotifications::Deinitialize()
{
}

bool UBeamNotifications::TryConnect(const FUserSlot& Slot, const FName& SocketName, const FString& Uri, const TMap<FString, FString>& ExtraHeaders, const FOnNotificationEvent& ConnectionEventHandler,
                                    FBeamWebSocketHandle& OutHandle, UObject* ContextObject)
{
	if (FBeamRealmUser UserData; UserSlots->GetUserDataAtSlot(Slot, UserData, ContextObject))
	{
		Connect(Slot, UserData, SocketName, Uri, ExtraHeaders, ConnectionEventHandler, OutHandle, ContextObject);
		return true;
	}

	return false;
}

void UBeamNotifications::Connect(const FUserSlot& Slot, const FBeamRealmUser& UserData, const FName& SocketName, const FString& Uri, const TMap<FString, FString>& ExtraHeaders,
                                 const FOnNotificationEvent& ConnectionEventHandler, FBeamWebSocketHandle& OutHandle, UObject* ContextObject)
{
	const auto RefreshToken = UserData.AuthToken.AccessToken;
	auto Headers = TMap(ExtraHeaders);
	auto NamespacedSlot = UBeamUserSlots::GetNamespacedSlotId(Slot, ContextObject);


	const auto AuthTokenHeader = FString::Format(*UBeamBackend::HEADER_VALUE_AUTHORIZATION, {RefreshToken});
	Headers.Add(UBeamBackend::HEADER_AUTHORIZATION, AuthTokenHeader);

	const auto ScopeHeader = UserData.RealmHandle.Pid.AsString.IsEmpty()
		                         ? UserData.RealmHandle.Cid.AsString
		                         : FString::Format(TEXT("{0}.{1}"), {UserData.RealmHandle.Cid.AsString, UserData.RealmHandle.Pid.AsString});
	Headers.Add(UBeamBackend::HEADER_REQUEST_SCOPE, ScopeHeader);


	OutHandle = FBeamWebSocketHandle(NamespacedSlot, SocketName, this);
	UE_LOG(LogBeamNotifications, Verbose, TEXT("Attempting websocket connection. SLOT=%s, ID=%s, URI=%s, TOKEN_HEADER=%s, SCOPE_HEADER=%s"), *NamespacedSlot, *Uri, *SocketName.ToString(),
	       *AuthTokenHeader,
	       *ScopeHeader)


	const auto OpenSocket = FWebSocketsModule::Get().CreateWebSocket(Uri + TEXT("?send-session-start=true"), TEXT(""), Headers);
	OpenSocket->OnConnected().AddLambda([OutHandle, this]
	{
		// If this was a PIE socket and we are no longer in PIE when we connect, we should close up this connection.
#if WITH_EDITOR
		Backend->UpdatePieState();
		if (!Backend->IsInPIE() && PlayModeHandles.Contains(OutHandle))
		{
			if (OpenSockets.Contains(OutHandle.NamespacedSlot))
			{
				OpenSockets[OutHandle.NamespacedSlot].FindChecked(OutHandle.Id)->Close();
			}
			return;
		}
#endif

		FNotificationEvent Evt;
		Evt.EventType = ENotificationMessageType::BEAM_Connected;
		Evt.ConnectedData.ConnectedHandle = OutHandle;

		const FOnNotificationEvent& EvtHandler = ConnectionEventHandlers.FindChecked(OutHandle);
		const bool bDidRun = EvtHandler.ExecuteIfBound(Evt);
		ensureAlwaysMsgf(bDidRun, TEXT("Notification connection handler was not bound correctly! SLOT=%s, ID=%s, RETRY_COUNT=%d"), *OutHandle.NamespacedSlot, *OutHandle.Id.ToString(),
		                 RetryCount.FindChecked(OutHandle));

		// Reset the retry count
		RetryCount.Add(OutHandle, 0);

		UE_LOG(LogBeamNotifications, Verbose, TEXT("Connection Success. SLOT=%s, ID=%s"), *OutHandle.NamespacedSlot, *OutHandle.Id.ToString());
	});

	OpenSocket->OnConnectionError().AddLambda([this, OutHandle, OpenSocket](const FString& Error)
	{
		// If this was a PIE socket and we are no longer in PIE when we connect, we should just clean up.
#if WITH_EDITOR
		Backend->UpdatePieState();
		if (!Backend->IsInPIE() && PlayModeHandles.Contains(OutHandle))
		{
			if (OpenSockets.Contains(OutHandle.NamespacedSlot))
			{
				OpenSockets[OutHandle.NamespacedSlot].Remove(OutHandle.Id);
				PlayModeHandles.Remove(OutHandle);

				ConnectionEventHandlers.Remove(OutHandle);
				MessageEventHandlers.Remove(OutHandle);
				RetryCount.Remove(OutHandle);
			}
			return;
		}
#endif

		// Trigger the event and then remove the connection from the list
		FNotificationEvent Evt;
		Evt.EventType = ENotificationMessageType::BEAM_ConnectionFailed;
		Evt.ConnectionFailedData.Error = Error;

		// Bump the retry count
		Evt.ConnectionFailedData.RetryCount = 1 + RetryCount.FindChecked(OutHandle);
		RetryCount.Add(OutHandle, Evt.ConnectionFailedData.RetryCount);

		// Run the connection failed handler and retry.
		const FOnNotificationEvent& EvtHandler = ConnectionEventHandlers.FindChecked(OutHandle);
		const bool bDidRun = EvtHandler.ExecuteIfBound(Evt);
		ensureAlwaysMsgf(bDidRun, TEXT("Notification connection handler was not bound correctly! SLOT=%s, ID=%s"), *OutHandle.NamespacedSlot, *OutHandle.Id.ToString());

		// Try connecting again
		OpenSocket->Connect();

		UE_LOG(LogBeamNotifications, Error, TEXT("Failed to connect. Retrying connection... SLOT=%s, ID=%s, RETRY_COUNT=%d, ERROR=%s"), *OutHandle.NamespacedSlot, *OutHandle.Id.ToString(),
		       Evt.ConnectionFailedData.RetryCount, *Error);
	});

	OpenSocket->OnClosed().AddLambda([OutHandle, this](int32 StatusCode, const FString& Reason, bool bWasClean)
	{
		// If this was a PIE socket and we are no longer in PIE when try to close, we should just clean up.
#if WITH_EDITOR
		Backend->UpdatePieState();
		if (!Backend->IsInPIE() && PlayModeHandles.Contains(OutHandle))
		{
			if (OpenSockets.Contains(OutHandle.NamespacedSlot))
			{
				OpenSockets[OutHandle.NamespacedSlot].Remove(OutHandle.Id);
				PlayModeHandles.Remove(OutHandle);

				ConnectionEventHandlers.Remove(OutHandle);
				MessageEventHandlers.Remove(OutHandle);
				RetryCount.Remove(OutHandle);
			}
			return;
		}
#endif


		// Trigger the event 
		FNotificationEvent Evt;
		Evt.EventType = ENotificationMessageType::BEAM_Closed;
		Evt.ClosedData.Reason = Reason;
		Evt.ClosedData.StatusCode = StatusCode;
		Evt.ClosedData.bWasClean = bWasClean;

		const FOnNotificationEvent& EvtHandler = ConnectionEventHandlers.FindChecked(OutHandle);
		const bool bDidRun = EvtHandler.ExecuteIfBound(Evt);
		ensureAlwaysMsgf(bDidRun, TEXT("Notification connection handler was not bound correctly! SLOT=%s, ID=%s"), *OutHandle.NamespacedSlot, *OutHandle.Id.ToString());

		if (StatusCode == UserSignOutCloseCode)
		{
			ConnectionEventHandlers.Remove(OutHandle);
			MessageEventHandlers.Remove(OutHandle);
			PlayModeHandles.Remove(OutHandle);
			RetryCount.Remove(OutHandle);
		}
		UE_LOG(LogBeamNotifications, Verbose, TEXT("Connection Closed. SLOT=%s, ID=%s"), *OutHandle.NamespacedSlot, *OutHandle.Id.ToString());
	});

	OpenSocket->OnMessage().AddLambda([OutHandle, this](const FString& Message)
	{
		// If this was a PIE socket and we are no longer in PIE when we receive a message, we should close up this connection and not run any message callbacks.
#if WITH_EDITOR
		Backend->UpdatePieState();
		if (!Backend->IsInPIE() && PlayModeHandles.Contains(OutHandle))
		{
			if (OpenSockets.Contains(OutHandle.NamespacedSlot))
			{
				OpenSockets[OutHandle.NamespacedSlot].FindChecked(OutHandle.Id)->Close();
			}
			return;
		}
#endif

		FNotificationEvent Evt;
		Evt.EventType = ENotificationMessageType::BEAM_Message;
		Evt.MessageData.BeamDeserialize(Message);

		TArray<FNotificationMessageEventHandler> EvtHandlers;
		MessageEventHandlers.MultiFind(OutHandle, EvtHandlers, true);
		for (int i = 0; i < EvtHandlers.Num(); ++i)
		{
			if (Evt.MessageData.Context.Equals(EvtHandlers[i].ContextKey))
			{
				const bool bDidRun = EvtHandlers[i].Handler.ExecuteIfBound(Evt);
				ensureAlwaysMsgf(bDidRun, TEXT("Notification message handler was not bound correctly! SLOT=%s, ID=%s Message=%s"), *OutHandle.NamespacedSlot, *OutHandle.Id.ToString(), *Message);
			}
			else
			{
				UE_LOG(LogBeamNotifications, Verbose, TEXT("Skipping handler for this message: Handler doesn't care about this context. SLOT=%s, ID=%s, CONTEXT=%s"), *OutHandle.NamespacedSlot,
				       *OutHandle.Id.ToString(), *EvtHandlers[i].ContextKey)
			}
		}

		UE_LOG(LogBeamNotifications, Verbose, TEXT("Notification message received. SLOT=%s, ID=%s Message=%s"), *OutHandle.NamespacedSlot, *OutHandle.Id.ToString(), *Message);
	});

	// Add the socket to the list of open sockets
	if (OpenSockets.Contains(NamespacedSlot))
		OpenSockets.FindChecked(NamespacedSlot).Add(SocketName, OpenSocket);
	else
		OpenSockets.Add(NamespacedSlot, {{SocketName, OpenSocket}});

	// Keep track of sockets that are opened from PIE sessions
	if (ContextObject && ContextObject->GetWorld() && ContextObject->GetWorld()->IsPlayInEditor())
		PlayModeHandles.Add(OutHandle);

	// Register the ConnectionEventHandler and the retry count
	ConnectionEventHandlers.Add(OutHandle, ConnectionEventHandler);
	RetryCount.Add(OutHandle, 0);

	// Connect
	OpenSocket->Connect();
}

bool UBeamNotifications::TryGetHandle(const FUserSlot& Slot, const FName& SocketName, FBeamWebSocketHandle& OutHandle, UObject* ContextObject)
{
	auto NamespacedSlot = UBeamUserSlots::GetNamespacedSlotId(Slot, ContextObject);
	if (OpenSockets.Contains(NamespacedSlot))
	{
		const auto& UserSockets = OpenSockets.FindChecked(NamespacedSlot);
		if (UserSockets.Contains(SocketName))
		{
			OutHandle = FBeamWebSocketHandle(NamespacedSlot, SocketName, this);
			return true;
		}
	}

	OutHandle = FBeamWebSocketHandle(FUserSlot{}, {}, this);
	return false;
}

void UBeamNotifications::CloseSocketsForSlot(const FUserSlot& Slot, UObject* ContextObject)
{
	auto NamespacedSlot = UBeamUserSlots::GetNamespacedSlotId(Slot, ContextObject);
	if (const auto Slots = OpenSockets.Find(NamespacedSlot))
	{
		for (const auto& WebSocket : *Slots)
		{
			FBeamWebSocketHandle Handle;
			Handle.NamespacedSlot = NamespacedSlot;
			Handle.Id = WebSocket.Key;

			WebSocket.Value->Close(UserSignOutCloseCode, TEXT("User signed out"));
		}
		Slots->Reset();
	}
}

void UBeamNotifications::ClearPIESockets(UObject* ContextObject)
{
	TArray<FBeamWebSocketHandle> HandlesToClear;
	for (FBeamWebSocketHandle PlayModeHandle : PlayModeHandles)
	{
		FUserSlot HandleSlot;
		if (UBeamUserSlots::GetSlotIdFromNamespacedSlotId(PlayModeHandle.NamespacedSlot, HandleSlot))
		{
			FString NamespaceCheck = UBeamUserSlots::GetNamespacedSlotId(HandleSlot, ContextObject);
			if (NamespaceCheck == PlayModeHandle.NamespacedSlot)
			{
				HandlesToClear.Add(PlayModeHandle);
			}
		}
	}

	for (FBeamWebSocketHandle PlayModeHandle : HandlesToClear)
	{
		if (const auto Slots = OpenSockets.Find(PlayModeHandle.NamespacedSlot))
		{
			if (const auto Socket = Slots->FindRef(PlayModeHandle.Id))
			{
				Socket->Close(1000, TEXT("PIE Closed"));
				UE_LOG(LogBeamNotifications, Verbose, TEXT("Closed runtime websocket for slot. SLOT=%s"), *PlayModeHandle.NamespacedSlot);
			}
		}
	}
}

void UBeamNotifications::Reconnect(FBeamWebSocketHandle Value)
{
	if (OpenSockets.Contains(Value.NamespacedSlot))
	{
		if (const auto& UserSockets = OpenSockets.FindChecked(Value.NamespacedSlot); UserSockets.Contains(Value.Id))
		{
			const FBeamWebSocketHandle Key(Value.NamespacedSlot, Value.Id, this);

			auto Connection = UserSockets[Value.Id];
			if (!Connection->IsConnected())
			{
				Connection->Connect();
			}
		}
	}
}
