// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BEAMPROJ_Beamball/ThirdParty/Discord/core.h"

#include "BeamableDiscord.generated.h"


UENUM()
enum EBeamableDiscordState
{
	BeamDiscordUninitialized,
	BeamDiscordInitializing,
	BeamDiscordFailed,
	BeamDiscordInitialized,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDiscordMatchmakingWhitelistChanged, FUserSlot, UserSlot, bool, bIsWhitelisted);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDiscordMatchmakingWhitelistChangedCode, FUserSlot, bool);

USTRUCT(BlueprintType)
struct FBeamableDiscordUserData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Discord")
	FString UserId;
	UPROPERTY(BlueprintReadOnly, Category = "Discord")
	FString Username;
	UPROPERTY(BlueprintReadOnly, Category = "Discord")
	FString Discriminator;
	UPROPERTY(BlueprintReadOnly, Category = "Discord")
	FString Avatar;
	UPROPERTY(BlueprintReadOnly, Category = "Discord")
	FString OAuthToken;
};

/**
 * Subsystem for Discord integration.
 * Wraps the Discord Game SDK to fetch the current Discord user's OAuth token.
 *
 * Also, to get the Discord SDK to compile in certain cases, you'll need to replace the <Windows.h> includes
 * in some discord files. Here's an explanation on how:
 * https://github.com/ryanjon2040/Discord-UE4#compile-error-when-using-as-engine-plugin
 */
UCLASS(Config=Game, DefaultConfig)
class BEAMPROJ_BEAMBALL_API UBeamableDiscord : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;
	virtual void OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp) override;
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamableDiscord* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamableDiscord>(); }	

	/**
	 * Initializes the Discord SDK and resolves the current Discord user/OAuth token.
	 * Requires a running Discord client.
	 *
	 * @param OnOperationEvent - Callback handler for operation events (success/error)
	 * @return FBeamOperationHandle - Handle to track the async operation
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Discord", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle InitializeDiscordOperation(FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc InitializeDiscordOperation
	 */
	FBeamOperationHandle CPP_InitializeDiscordOperation(FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * Retrieves the currently resolved Discord user id and OAuth token.
	 * @return True if Discord is initialized and the data was populated.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="GetDiscordData", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetDiscordData(FString& DiscordUserId, FString& DiscordAuthToken, FString& Error);

	/**
	 * Reads the cached "matchmaking_discord_whitelisted" flag for a user slot.
	 * The cache is populated when FetchWhitelistedStatusOperation succeeds and refreshed live
	 * via the "matchmaking_refresh" notification while the user is signed in.
	 * @return True if a cached value exists for the slot.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="GetMatchmakingWhitelisted", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetMatchmakingWhitelisted(FUserSlot UserSlot, bool& bIsWhitelisted, FString& Error);

	/**
	 * Fires whenever the cached matchmaking whitelist flag changes for a user slot, either via
	 * a server-pushed "matchmaking_refresh" notification or after FetchWhitelistedStatusOperation completes.
	 */
	UPROPERTY(BlueprintAssignable, Category="Beam|Discord")
	FOnDiscordMatchmakingWhitelistChanged OnMatchmakingWhitelistChanged;
	FOnDiscordMatchmakingWhitelistChangedCode OnMatchmakingWhitelistChangedCode;

	/**
	 * Asks the server to re-query Discord for the user's current guild roles and refresh
	 * the "matchmaking_discord_whitelisted" stat. On success, the cached whitelist flag
	 * (see GetMatchmakingWhitelisted) is updated from the server response.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Discord", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle RefreshDiscordStatusOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc RefreshDiscordStatusOperation
	 */
	FBeamOperationHandle CPP_RefreshDiscordStatusOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * Reads the cached "matchmaking_discord_whitelisted" stat from the server (does not query Discord itself).
	 * On success, the cached whitelist flag (see GetMatchmakingWhitelisted) is updated from the response.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Discord", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchWhitelistedStatusOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchWhitelistedStatusOperation
	 */
	FBeamOperationHandle CPP_FetchWhitelistedStatusOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent);

	UPROPERTY(Config)
	int64 DiscordAppId;

private:
	bool TickDiscord(float Delta);

	void InitializeDiscord(FBeamOperationHandle Op);
	void RefreshDiscordStatus(FUserSlot UserSlot, FBeamOperationHandle Op);
	void FetchWhitelistedStatus(FUserSlot UserSlot, FBeamOperationHandle Op);

	void OnAuthTokenReceived(discord::Result Res, discord::OAuth2Token const& Token);
	void OnUserUpdated(discord::OAuth2Token Token);

	discord::Core* Core{};
	discord::User* CurrentUser{};
	discord::OAuth2Token CurrentToken{};

	FBeamableDiscordUserData CachedUserData;

	TEnumAsByte<EBeamableDiscordState> State = BeamDiscordUninitialized;
	FTSTicker::FDelegateHandle TickDelegate;

	FBeamOperationHandle PendingInitOp;

	TMap<FUserSlot, bool> CachedMatchmakingWhitelisted;
	TMap<FUserSlot, FDelegateHandle> MatchmakingRefreshHandles;

};
