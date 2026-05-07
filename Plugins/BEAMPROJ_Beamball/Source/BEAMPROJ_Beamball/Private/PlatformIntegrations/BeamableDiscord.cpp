// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformIntegrations/BeamableDiscord.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "AutoGen/SubSystems/BeamBeamballMsApi.h"
#include "AutoGen/SubSystems/BeamballMs/BeamballMsUpdateFromDiscordRequest.h"
#include "AutoGen/SubSystems/BeamballMs/BeamballMsUpdateUserWhitelistedStatusRequest.h"
#include "AutoGen/BeamballMsUpdateFromDiscordResponse.h"
#include "AutoGen/DiscordWhitelistedInfo.h"

void UBeamableDiscord::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	TickDelegate = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UBeamableDiscord::TickDiscord), 0);
}

void UBeamableDiscord::Deinitialize()
{
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegate);
	delete Core;
	Core = nullptr;
	Super::Deinitialize();
}

void UBeamableDiscord::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	ResultOp = CPP_FetchWhitelistedStatusOperation(UserSlot, {});

	auto NotifHandler = [this, UserSlot](UDiscordWhitelistedInfo* Info)
	{
		const bool bIsWhitelisted = Info->bMatchmakingDiscordWhitelisted;
		const bool* Existing = CachedMatchmakingWhitelisted.Find(UserSlot);
		if (Existing && *Existing == bIsWhitelisted) return;
		CachedMatchmakingWhitelisted.Add(UserSlot, bIsWhitelisted);
		OnMatchmakingWhitelistChanged.Broadcast(UserSlot, bIsWhitelisted);
		OnMatchmakingWhitelistChangedCode.Broadcast(UserSlot, bIsWhitelisted);
	};
	MatchmakingRefreshHandles.Add(UserSlot, Runtime->SubscribeToCustomNotification<decltype(NotifHandler), UDiscordWhitelistedInfo*>(UserSlot, TEXT("matchmaking_refresh"), NotifHandler));
}

void UBeamableDiscord::OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	if (const FDelegateHandle* Handle = MatchmakingRefreshHandles.Find(UserSlot))
	{
		Runtime->UnsubscribeToCustomNotification(UserSlot, TEXT("matchmaking_refresh"), *Handle);
		MatchmakingRefreshHandles.Remove(UserSlot);
	}
	Super::OnUserSignedOut_Implementation(UserSlot, Reason, BeamRealmUser, ResultOp);
}

bool UBeamableDiscord::TickDiscord(float)
{
	if (Core) Core->RunCallbacks();
	return true;
}

FBeamOperationHandle UBeamableDiscord::InitializeDiscordOperation(FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
	InitializeDiscord(Handle);
	return Handle;
}

FBeamOperationHandle UBeamableDiscord::CPP_InitializeDiscordOperation(FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
	InitializeDiscord(Handle);
	return Handle;
}

void UBeamableDiscord::InitializeDiscord(FBeamOperationHandle Op)
{
	if (State == BeamDiscordInitialized)
	{
		Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
		return;
	}

	if (!ensureAlwaysMsgf(DiscordAppId != 0, TEXT("[Beamable Discord] DiscordAppId is not set. Please set DiscordAppId under [/Script/BEAMPROJ_Beamball.BeamableDiscord] in DefaultGame.ini.")))
	{
		Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("DiscordAppId is not set in DefaultGame.ini"));
		return;
	}

	State = BeamDiscordInitializing;
	PendingInitOp = Op;

	UE_LOG(LogTemp, Display, TEXT("[Beamable Discord] Initializing Discord SDK."));
	const auto Result = discord::Core::Create(DiscordAppId, DiscordCreateFlags_Default, &Core);
	if (Result == discord::Result::Ok)
	{
		UE_LOG(LogTemp, Display, TEXT("[Beamable Discord] Initialized Discord SDK. Fetching OAuth token."));
		Core->ApplicationManager().GetOAuth2Token([this](discord::Result Res, discord::OAuth2Token const& Token)
		{
			UE_LOG(LogTemp, Display, TEXT("[Beamable Discord] Received OAuth token result: %hd"), Res);
			OnAuthTokenReceived(Res, Token);
		});
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Beamable Discord] Failed to initialize Discord SDK. %d"), Result);
		State = BeamDiscordFailed;
		Runtime->RequestTrackerSystem->TriggerOperationError(PendingInitOp, TEXT("DISCORD_SDK_INIT_FAILED"));
	}
}

void UBeamableDiscord::OnAuthTokenReceived(discord::Result Res, discord::OAuth2Token const& Token)
{
	if (Res != discord::Result::Ok)
	{
		UE_LOG(LogTemp, Error, TEXT("[Beamable Discord] Failed to get Discord OAuth token."));
		State = BeamDiscordFailed;
		Runtime->RequestTrackerSystem->TriggerOperationError(PendingInitOp, TEXT("DISCORD_OAUTH_FAILED"));
	}
	else
	{
		Core->UserManager().OnCurrentUserUpdate.Connect([this, Token]()
		{
			OnUserUpdated(Token);
		});
	}
}

void UBeamableDiscord::OnUserUpdated(discord::OAuth2Token Token)
{
	CurrentUser = new discord::User;
	Core->UserManager().GetCurrentUser(CurrentUser);

	if (CurrentUser)
	{
		// OnCurrentUserUpdate fires on every change; we only want to emit the success once.
		if (State != BeamDiscordInitialized)
		{
			CurrentToken = Token;
			State = BeamDiscordInitialized;

			CachedUserData.UserId = FString::Printf(TEXT("%lld"), CurrentUser->GetId());
			CachedUserData.Username = ANSI_TO_TCHAR(CurrentUser->GetUsername());
			CachedUserData.Discriminator = ANSI_TO_TCHAR(CurrentUser->GetDiscriminator());
			CachedUserData.Avatar = ANSI_TO_TCHAR(CurrentUser->GetAvatar());
			CachedUserData.OAuthToken = ANSI_TO_TCHAR(Token.GetAccessToken());
			Runtime->RequestTrackerSystem->TriggerOperationSuccess(PendingInitOp, TEXT(""));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Beamable Discord] Failed to get Discord user info."));
		State = BeamDiscordFailed;
		Runtime->RequestTrackerSystem->TriggerOperationError(PendingInitOp, TEXT("DISCORD_USER_INFO_FAILED"));
	}
}

bool UBeamableDiscord::TryGetDiscordData(FString& DiscordUserId, FString& DiscordAuthToken, FString& Error)
{
	if (State != BeamDiscordInitialized)
	{
		Error = TEXT("Discord SDK not initialized. Please call InitializeDiscordOperation first.");
		UE_LOG(LogTemp, Error, TEXT("%s"), *Error);
		return false;
	}

	DiscordUserId = CachedUserData.UserId;
	DiscordAuthToken = CachedUserData.OAuthToken;
	return true;
}

bool UBeamableDiscord::TryGetMatchmakingWhitelisted(FUserSlot UserSlot, bool& bIsWhitelisted, FString& Error)
{
	if (const bool* Cached = CachedMatchmakingWhitelisted.Find(UserSlot))
	{
		bIsWhitelisted = *Cached;
		return true;
	}
	Error = FString::Printf(TEXT("No cached Discord matchmaking whitelist status for user slot '%s'. Run FetchWhitelistedStatusOperation first."), *UserSlot.Name);
	return false;
}

FBeamOperationHandle UBeamableDiscord::RefreshDiscordStatusOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshDiscordStatus(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamableDiscord::CPP_RefreshDiscordStatusOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshDiscordStatus(UserSlot, Handle);
	return Handle;
}

void UBeamableDiscord::RefreshDiscordStatus(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	const auto Api = GEngine->GetEngineSubsystem<UBeamBeamballMsApi>();
	UBeamballMsUpdateFromDiscordRequest* Request = UBeamballMsUpdateFromDiscordRequest::Make(this, {});

	const auto Handler = FOnBeamballMsUpdateFromDiscordFullResponse::CreateLambda([this, Op](FBeamballMsUpdateFromDiscordFullResponse Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			UE_LOG(LogTemp, Error, TEXT("[Beamable Discord] UpdateFromDiscord failed: %s"), *Resp.ErrorData.message);
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
			return;
		}

		UE_LOG(LogTemp, Log, TEXT("[Beamable Discord] UpdateFromDiscord succeeded."));
		Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
	});

	FBeamRequestContext Ctx;
	Api->CPP_UpdateFromDiscord(UserSlot, Request, Handler, Ctx, Op, this);
}

FBeamOperationHandle UBeamableDiscord::FetchWhitelistedStatusOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchWhitelistedStatus(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamableDiscord::CPP_FetchWhitelistedStatusOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchWhitelistedStatus(UserSlot, Handle);
	return Handle;
}

void UBeamableDiscord::FetchWhitelistedStatus(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	const auto Api = GEngine->GetEngineSubsystem<UBeamBeamballMsApi>();
	const FString Namespace = Api->GetFederatedLogin_Id_Discord();

	FString ExternalId;
	if (!Runtime->TryGetExternalIdentity(UserSlot, Namespace, ExternalId))
	{
		UE_LOG(LogTemp, Log, TEXT("[Beamable Discord] User has no Discord identity — matchmaking allowed."));
		Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
		return;
	}

	UBeamballMsUpdateUserWhitelistedStatusRequest* Request = UBeamballMsUpdateUserWhitelistedStatusRequest::Make(this, {});

	const auto Handler = FOnBeamballMsUpdateUserWhitelistedStatusFullResponse::CreateLambda([this, UserSlot, Op](FBeamballMsUpdateUserWhitelistedStatusFullResponse Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			UE_LOG(LogTemp, Error, TEXT("[Beamable Discord] UpdateUserWhitelistedStatus failed: %s"), *Resp.ErrorData.message);
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
			return;
		}

		const bool bIsWhitelisted = Resp.SuccessData->bMatchmakingDiscordWhitelisted;
		const bool* Existing = CachedMatchmakingWhitelisted.Find(UserSlot);
		if (!Existing || *Existing != bIsWhitelisted)
		{
			CachedMatchmakingWhitelisted.Add(UserSlot, bIsWhitelisted);
			OnMatchmakingWhitelistChanged.Broadcast(UserSlot, bIsWhitelisted);
			OnMatchmakingWhitelistChangedCode.Broadcast(UserSlot, bIsWhitelisted);
		}

		if (!bIsWhitelisted)
		{
			UE_LOG(LogTemp, Warning, TEXT("[Beamable Discord] User is not whitelisted for Discord matchmaking."));
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("DISCORD_MATCHMAKING_NOT_WHITELISTED"));
			return;
		}

		UE_LOG(LogTemp, Log, TEXT("[Beamable Discord] User is whitelisted for Discord matchmaking."));
		Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
	});

	FBeamRequestContext Ctx;
	Api->CPP_UpdateUserWhitelistedStatus(UserSlot, Request, Handler, Ctx, Op, this);
}
