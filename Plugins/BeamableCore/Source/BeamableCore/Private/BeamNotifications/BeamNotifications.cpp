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
		if (!bDidRun)
		{
			UE_LOG(LogBeamNotifications, Verbose, TEXT("Notification connection handler was not bound correctly! SLOT=%s, ID=%s, RETRY_COUNT=%d"), *OutHandle.NamespacedSlot, *OutHandle.Id.ToString(),
				 RetryCount.FindChecked(OutHandle));
		}
		
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
		if (!bDidRun)
		{
			UE_LOG(LogBeamNotifications, Verbose, TEXT("Notification connection handler was not bound correctly! SLOT=%s, ID=%s"), *OutHandle.NamespacedSlot, *OutHandle.Id.ToString());
		}

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

bool UBeamNotifications::TrySubscribeForMessage_DynamicStruct(
	const FUserSlot& Slot, const FName& SocketName, const FString& ContextKey,
	UScriptStruct* MessageStruct, const FOnBeamCustomNotificationStructDynamic& Handler,
	FDelegateHandle& OutHandle, UObject* ContextObject)
{
	if (!MessageStruct)
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("TrySubscribeForMessage_DynamicStruct: MessageStruct is null. SLOT=%s, CONTEXT=%s"),
		       *Slot.Name, *ContextKey);
		return false;
	}
	if (!MessageStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("TrySubscribeForMessage_DynamicStruct: %s does not derive from FBeamJsonSerializableUStruct. SLOT=%s, CONTEXT=%s"),
		       *MessageStruct->GetName(), *Slot.Name, *ContextKey);
		return false;
	}

	const FString NamespacedSlot = UBeamUserSlots::GetNamespacedSlotId(Slot, ContextObject);
	if (!OpenSockets.Contains(NamespacedSlot) || !OpenSockets.FindChecked(NamespacedSlot).Contains(SocketName))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("TrySubscribeForMessage_DynamicStruct: socket not open. SLOT=%s, SOCKET=%s, CONTEXT=%s"),
		       *Slot.Name, *SocketName.ToString(), *ContextKey);
		return false;
	}

	UE_LOG(LogBeamNotifications, Verbose, TEXT("Subscribing dynamic-struct notification handler. SLOT=%s, SOCKET=%s, CONTEXT=%s, MSG_TYPE=%s"),
	       *Slot.Name, *SocketName.ToString(), *ContextKey, *MessageStruct->GetName());

	const FOnNotificationEvent EventHandler = FOnNotificationEvent::CreateLambda(
		[Slot, SocketName, ContextKey, MessageStruct, Handler](FNotificationEvent Evt) mutable
		{
			ensureAlways(Evt.EventType == BEAM_Message);
			ensureAlways(Evt.MessageData.Context.Equals(ContextKey));

			UE_LOG(LogBeamNotifications, Verbose, TEXT("Notification received (dynamic-struct). SLOT=%s, SOCKET=%s, CONTEXT=%s, MSG_TYPE=%s, PAYLOAD=%s"),
			       *Slot.Name, *SocketName.ToString(), *ContextKey, *MessageStruct->GetName(), *Evt.MessageData.MessageFull);

			const int32 Size = MessageStruct->GetStructureSize();
			const int32 Align = MessageStruct->GetMinAlignment();
			void* Buffer = FMemory_Alloca_Aligned(Size, Align);
			MessageStruct->InitializeStruct(Buffer);

			// Single-inheritance USTRUCT layout guarantees the FBeamJsonSerializableUStruct subobject sits at offset 0.
			FBeamJsonSerializableUStruct* AsBase = reinterpret_cast<FBeamJsonSerializableUStruct*>(Buffer);
			AsBase->OuterOwner = GetTransientPackage();
			AsBase->BeamDeserialize(Evt.MessageData.MessageFull);

			FBeamCustomNotificationStructPayload Payload;
			Payload.Type = MessageStruct;
			Payload.Data = Buffer;
			const bool bDidRun = Handler.ExecuteIfBound(Payload, ContextKey);
			ensureAlwaysMsgf(bDidRun, TEXT("BP dynamic-struct notification handler was not bound. SLOT=%s, SOCKET=%s, CONTEXT=%s"),
			                 *Slot.Name, *SocketName.ToString(), *ContextKey);
			UE_LOG(LogBeamNotifications, Verbose, TEXT("Dispatched dynamic-struct via ExecuteIfBound. SLOT=%s, CONTEXT=%s, BOUND=%s"),
			       *Slot.Name, *ContextKey, bDidRun ? TEXT("true") : TEXT("false"));

			MessageStruct->DestroyStruct(Buffer);
		});

	OutHandle = EventHandler.GetHandle();
	MessageEventHandlers.Add(FBeamWebSocketHandle(NamespacedSlot, SocketName, this),
	                         FNotificationMessageEventHandler{ContextKey, EventHandler});
	return true;
}

bool UBeamNotifications::TrySubscribeForMessage_DynamicObject(
	const FUserSlot& Slot, const FName& SocketName, const FString& ContextKey,
	UClass* MessageClass, const FOnBeamCustomNotificationObjectDynamic& Handler,
	FDelegateHandle& OutHandle, UObject* ContextObject)
{
	if (!MessageClass)
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("TrySubscribeForMessage_DynamicObject: MessageClass is null. SLOT=%s, CONTEXT=%s"),
		       *Slot.Name, *ContextKey);
		return false;
	}
	if (!MessageClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("TrySubscribeForMessage_DynamicObject: %s does not implement IBeamJsonSerializableUObject. SLOT=%s, CONTEXT=%s"),
		       *MessageClass->GetName(), *Slot.Name, *ContextKey);
		return false;
	}

	const FString NamespacedSlot = UBeamUserSlots::GetNamespacedSlotId(Slot, ContextObject);
	if (!OpenSockets.Contains(NamespacedSlot) || !OpenSockets.FindChecked(NamespacedSlot).Contains(SocketName))
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("TrySubscribeForMessage_DynamicObject: socket not open. SLOT=%s, SOCKET=%s, CONTEXT=%s"),
		       *Slot.Name, *SocketName.ToString(), *ContextKey);
		return false;
	}

	UE_LOG(LogBeamNotifications, Verbose, TEXT("Subscribing dynamic-object notification handler. SLOT=%s, SOCKET=%s, CONTEXT=%s, MSG_CLASS=%s"),
	       *Slot.Name, *SocketName.ToString(), *ContextKey, *MessageClass->GetName());

	const FOnNotificationEvent EventHandler = FOnNotificationEvent::CreateLambda(
		[Slot, SocketName, ContextKey, MessageClass, Handler](FNotificationEvent Evt) mutable
		{
			ensureAlways(Evt.EventType == BEAM_Message);
			ensureAlways(Evt.MessageData.Context.Equals(ContextKey));

			UE_LOG(LogBeamNotifications, Verbose, TEXT("Notification received (dynamic-object). SLOT=%s, SOCKET=%s, CONTEXT=%s, MSG_CLASS=%s, PAYLOAD=%s"),
			       *Slot.Name, *SocketName.ToString(), *ContextKey, *MessageClass->GetName(), *Evt.MessageData.MessageFull);

			UObject* MsgObject = NewObject<UObject>(GetTransientPackage(), MessageClass);
			IBeamJsonSerializableUObject* AsInterface = Cast<IBeamJsonSerializableUObject>(MsgObject);
			if (!AsInterface)
			{
				UE_LOG(LogBeamNotifications, Error, TEXT("Dynamic-object dispatch: %s reports it implements IBeamJsonSerializableUObject but Cast<> failed. SLOT=%s, CONTEXT=%s"),
				       *MessageClass->GetName(), *Slot.Name, *ContextKey);
				return;
			}
			AsInterface->OuterOwner = GetTransientPackage();
			AsInterface->BeamDeserialize(Evt.MessageData.MessageFull);

			const bool bDidRun = Handler.ExecuteIfBound(MsgObject, ContextKey);
			ensureAlwaysMsgf(bDidRun, TEXT("BP dynamic-object notification handler was not bound. SLOT=%s, SOCKET=%s, CONTEXT=%s"),
			                 *Slot.Name, *SocketName.ToString(), *ContextKey);
			UE_LOG(LogBeamNotifications, Verbose, TEXT("Dispatched dynamic-object via ExecuteIfBound. SLOT=%s, CONTEXT=%s, BOUND=%s"),
			       *Slot.Name, *ContextKey, bDidRun ? TEXT("true") : TEXT("false"));
		});

	OutHandle = EventHandler.GetHandle();
	MessageEventHandlers.Add(FBeamWebSocketHandle(NamespacedSlot, SocketName, this),
	                         FNotificationMessageEventHandler{ContextKey, EventHandler});
	return true;
}

void UBeamNotifications::K2_CopyNotificationStructPayload(const FBeamCustomNotificationStructPayload& Payload, int32& OutMessage)
{
	// Stub — never called directly. The CustomThunk below is what actually runs from BP-generated code.
	checkNoEntry();
}

DEFINE_FUNCTION(UBeamNotifications::execK2_CopyNotificationStructPayload)
{
	P_GET_STRUCT_REF(FBeamCustomNotificationStructPayload, Payload);

	// Pull the wildcard struct reference off the BP VM stack.
	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FStructProperty>(nullptr);
	void* DestAddr = Stack.MostRecentPropertyAddress;
	const FStructProperty* DestProp = CastField<FStructProperty>(Stack.MostRecentProperty);

	P_FINISH;

	if (!DestProp || !DestAddr)
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("K2_CopyNotificationStructPayload: wildcard pin is not a struct or unbound."));
		return;
	}
	if (Payload.Type == nullptr || Payload.Data == nullptr)
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("K2_CopyNotificationStructPayload: payload is empty (Type or Data null)."));
		DestProp->Struct->ClearScriptStruct(DestAddr);
		return;
	}
	if (DestProp->Struct != Payload.Type)
	{
		UE_LOG(LogBeamNotifications, Warning, TEXT("K2_CopyNotificationStructPayload: pin type %s does not match payload type %s — clearing pin."),
		       *DestProp->Struct->GetName(), *Payload.Type->GetName());
		DestProp->Struct->ClearScriptStruct(DestAddr);
		return;
	}

	P_NATIVE_BEGIN;
	Payload.Type->CopyScriptStruct(DestAddr, Payload.Data);
	P_NATIVE_END;
}
