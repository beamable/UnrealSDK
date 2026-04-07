// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "Online/CoreOnline.h"
#include "Online/OnlineServices.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "Online/OnlineResult.h"
#include "Online/Auth.h"
#include "Online/OnlineServicesEngineUtils.h"

#include "BeamableEOS.generated.h"


/**
 * Subsystem for Epic Online Services (EOS) integration.
 * Provides login functionality and auth token retrieval for Beamable authentication.
 */
UCLASS()
class BEAMPROJ_BEAMBALL_API UBeamableEOS : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamableEOS* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamableEOS>(); }

	/**
	 * Called when the subsystem is initialized.
	 * Pre-sizes the cache arrays to match the number of RuntimeUserSlots defined in UBeamCoreSettings.
	 */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	 * Called when the subsystem is being deinitialized (e.g., when exiting PIE).
	 * Logs out all EOS users and clears the cached auth data arrays.
	 */
	virtual void Deinitialize() override;

	/**
	 * Login with EOS using intelligent automatic authentication with fallback support.
	 *
	 * This function implements a robust authentication flow that automatically tries multiple login methods
	 * to ensure users can authenticate in various scenarios (PIE, packaged builds, Epic Launcher, etc.)
	 *
	 * AUTHENTICATION FLOW & FALLBACK CHAIN:
	 *
	 * When called with empty parameters (recommended for most cases):
	 *
	 * 1. PRIMARY: PersistentAuth
	 *    - Attempts to use cached refresh token from previous successful login
	 *    - Provides seamless re-authentication without user interaction
	 *    - If PersistentAuth fails → proceeds to fallback chain below
	 *
	 * 2. FALLBACK #1: Exchange Code (if available)
	 *    - Automatically detected from Epic Launcher command line arguments
	 *    - Format: -AUTH_LOGIN=unused -AUTH_PASSWORD=<exchangecode> -AUTH_TYPE=exchangecode
	 *    - Used when game is launched through Epic Games Launcher
	 *    - If not available or fails → proceeds to next fallback
	 *
	 * 3. FALLBACK #2: Developer Auth Tool (if available)
	 *    - Automatically used in editor when Developer Auth Tool is running (localhost:6300)
	 *    - Credential name derived from PIE instance: "Context_1", "Context_2", etc.
	 *    - Supports multiple PIE instances with separate authentication
	 *    - If tool not running (EOS_NoConnection error) → proceeds to final fallback
	 *
	 * 4. FALLBACK #3: Account Portal (final fallback)
	 *    - Opens browser for user authentication
	 *    - Always available as last resort
	 *    - User must complete browser-based login flow
	 *
	 * MANUAL CREDENTIAL MODE:
	 * - Provide specific credentials to bypass automatic detection and fallback chain
	 * - Useful for custom authentication flows or specific credential types
	 *
	 * @param LocalPlayerIndex - The local player index (0-N) mapped to Beamable FUserSlots in UBeamCoreSettings::RuntimeUserSlots
	 * @param CredentialsType - Type of credentials. Leave empty for automatic authentication with fallbacks.
	 *                         Manual options: "PersistentAuth", "ExchangeCode", "Developer", "AccountPortal"
	 * @param CredentialsId - Optional ID for the credentials (e.g., "localhost:6300" for Developer type)
	 *                       Leave empty for automatic detection.
	 * @param CredentialsToken - Optional token for the credentials (e.g., exchange code, Context_1)
	 *                          Leave empty for automatic detection.
	 * @param OnOperationEvent - Callback handler for operation events (success/error)
	 * @return FBeamOperationHandle - Handle to track the async operation
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|EOS", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle LoginWithEOSOperation(int LocalPlayerIndex, FString CredentialsType, FString CredentialsId, FString CredentialsToken, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc LoginWithEOSOperation
	 */
	FBeamOperationHandle CPP_LoginWithEOSOperation(int LocalPlayerIndex, FString CredentialsType, FString CredentialsId, FString CredentialsToken, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * Retrieves EOS auth data by local player index.
	 * @param LocalPlayerIndex - The local player index (0-N) to retrieve data for
	 * @param EOSUserId - Output EOS user ID
	 * @param EOSAuthToken - Output EOS auth token
	 * @param Error - Output error message if retrieval fails
	 * @return True if data was successfully retrieved, false otherwise
	 */
	UFUNCTION(BlueprintCallable, DisplayName="GetEOSDataByLocalPlayerIndex", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetEOSDataByLocalPlayerIndex(int LocalPlayerIndex, FString& EOSUserId, FString& EOSAuthToken, FString& Error);

	/**
	 * Retrieves EOS auth data for a specific Beamable user slot.
	 * Resolves the user slot to a local player index using UBeamCoreSettings::RuntimeUserSlots.
	 * @param UserSlot - The Beamable user slot to retrieve data for
	 * @param EOSUserId - Output EOS user ID
	 * @param EOSAuthToken - Output EOS auth token
	 * @param Error - Output error message if retrieval fails
	 * @return True if data was successfully retrieved, false otherwise
	 */
	UFUNCTION(BlueprintCallable, DisplayName="GetEOSDataForSlot", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetEOSDataForSlot(FUserSlot UserSlot, FString& EOSUserId, FString& EOSAuthToken, FString& Error);

private:
	void LoginWithEOS(int LocalPlayerIndex, FString CredentialsType, FString CredentialsId, FString CredentialsToken, FBeamOperationHandle Op);

	// Cached auth data per local player index (mapped to Beamable user slots)
	UPROPERTY()
	TArray<FString> CachedEOSUserIds;

	UPROPERTY()
	TArray<FString> CachedEOSAuthTokens;
};
