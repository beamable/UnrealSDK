// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformIntegrations/BeamableEOS.h"
#include "BeamCoreSettings.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"

namespace
{
	// Helper function to detect and extract credentials from command line (for Exchange Code from launcher)
	bool TryGetExchangeCodeFromCommandLine(FString& OutCredentialsId, FString& OutCredentialsToken, FString& OutCredentialsType)
	{
		FString AuthLogin, AuthPassword, AuthType;

		// Check for Epic Launcher command line arguments
		// Format: -AUTH_LOGIN=unused -AUTH_PASSWORD=<exchangecode> -AUTH_TYPE=exchangecode
		if (FParse::Value(FCommandLine::Get(), TEXT("AUTH_LOGIN="), AuthLogin) &&
			FParse::Value(FCommandLine::Get(), TEXT("AUTH_PASSWORD="), AuthPassword) &&
			FParse::Value(FCommandLine::Get(), TEXT("AUTH_TYPE="), AuthType))
		{
			OutCredentialsId = AuthLogin;
			OutCredentialsToken = AuthPassword;
			OutCredentialsType = AuthType;
			return true;
		}

		return false;
	}

	// Helper function to check for Developer Auth Tool (localhost:6300)
	bool TryGetDeveloperAuthCredentials(const UObject* ContextObject, FString& OutCredentialsId, FString& OutCredentialsToken, FString& OutCredentialsType)
	{
		// Developer Auth Tool mode - localhost:6300
		// The credentials are provided by the EOS Developer Authentication Tool
		// The credential name for PIE instances follows the pattern: Context_1, Context_2, etc.

#if WITH_EDITOR
		OutCredentialsType = TEXT("Developer");
		OutCredentialsId = TEXT("localhost:6300");

		// Get the PIE instance ID from the context
		int32 PIEInstanceID = INDEX_NONE;

		// Try to get PIE instance from the world context
		if (ContextObject)
		{
			if (const UWorld* World = ContextObject->GetWorld())
			{
				if (const FWorldContext* WorldContext = GEngine->GetWorldContextFromWorld(World))
				{
					PIEInstanceID = WorldContext->PIEInstance;
				}
			}
		}

		// Fall back to the global PIE ID if we couldn't get it from the world context
		if (PIEInstanceID == INDEX_NONE)
		{
			PIEInstanceID = UE::GetPlayInEditorID();
		}

		// If we have a valid PIE instance, use it to construct the credential name
		// PIE instances start at 0, but the Dev Auth Tool uses Context_1, Context_2, etc.
		if (PIEInstanceID != INDEX_NONE && PIEInstanceID >= 0)
		{
			OutCredentialsToken = FString::Printf(TEXT("Context_%d"), PIEInstanceID + 1);
			UE_LOG(LogTemp, Verbose, TEXT("EOS Developer Auth: Using PIE Instance %d (Credential: %s)"), PIEInstanceID, *OutCredentialsToken);
		}
		else
		{
			// Not in PIE, default to Context_1
			OutCredentialsToken = TEXT("Context_1");
			UE_LOG(LogTemp, Verbose, TEXT("EOS Developer Auth: Not in PIE, using default Context_1"));
		}

		return true;
#else
		return false;
#endif
	}

	// Helper function to ensure the cached arrays are large enough for the given local player index
	void EnsureCacheSize(TArray<FString>& CachedUserIds, TArray<FString>& CachedAuthTokens, int LocalPlayerIndex)
	{
		const int RequiredSize = LocalPlayerIndex + 1;
		if (CachedUserIds.Num() < RequiredSize)
		{
			CachedUserIds.SetNum(RequiredSize);
		}
		if (CachedAuthTokens.Num() < RequiredSize)
		{
			CachedAuthTokens.SetNum(RequiredSize);
		}
	}
}

void UBeamableEOS::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// Specifically for MAC we need to load the module before calling any EOS functions to ensure the SDK is properly initialized
	FModuleManager::Get().LoadModule("OnlineServicesEOS");	
	// Initialize the cache arrays to match the size of RuntimeUserSlots
	const UBeamCoreSettings* CoreSettings = GetDefault<UBeamCoreSettings>();
	if (CoreSettings)
	{
		const int NumUserSlots = CoreSettings->RuntimeUserSlots.Num();
		CachedEOSUserIds.SetNum(NumUserSlots);
		CachedEOSAuthTokens.SetNum(NumUserSlots);
		UE_LOG(LogTemp, Log, TEXT("EOS: Initialized cache arrays for %d user slots"), NumUserSlots);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EOS: Failed to get BeamCoreSettings during initialization"));
	}
}

void UBeamableEOS::Deinitialize()
{
	using namespace UE::Online;

	// Logout from EOS when the subsystem is being deinitialized (e.g., when exiting PIE)
	// This prevents the "AlreadyLoggedIn" state from persisting between PIE sessions
	IOnlineServicesPtr OnlineServices = GetServices(EOnlineServices::Epic);
	if (OnlineServices)
	{
		IAuthPtr Auth = OnlineServices->GetAuthInterface();
		if (Auth)
		{
			// Get all logged-in users and logout each one
			FAuthGetAllLocalOnlineUsers::Params GetUsersParams;
			TOnlineResult<FAuthGetAllLocalOnlineUsers> UsersResult = Auth->GetAllLocalOnlineUsers(MoveTemp(GetUsersParams));

			if (UsersResult.IsOk())
			{
				const TArray<TSharedRef<FAccountInfo>>& AllUsers = UsersResult.GetOkValue().AccountInfo;
				for (const TSharedRef<FAccountInfo>& UserInfo : AllUsers)
				{
					FAuthLogout::Params LogoutParams;
					LogoutParams.LocalAccountId = UserInfo->AccountId;
					Auth->Logout(MoveTemp(LogoutParams));
					UE_LOG(LogTemp, Log, TEXT("EOS: Logged out user %s during subsystem deinitialize"), *UE::Online::ToString(UserInfo->AccountId));
				}
			}
		}
	}

	// Clear cached auth data arrays
	CachedEOSUserIds.Empty();
	CachedEOSAuthTokens.Empty();

	Super::Deinitialize();
}

FBeamOperationHandle UBeamableEOS::LoginWithEOSOperation(int LocalPlayerIndex, FString CredentialsType, FString CredentialsId, FString CredentialsToken, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginWithEOS(LocalPlayerIndex, CredentialsType, CredentialsId, CredentialsToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamableEOS::CPP_LoginWithEOSOperation(int LocalPlayerIndex, FString CredentialsType, FString CredentialsId, FString CredentialsToken, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginWithEOS(LocalPlayerIndex, CredentialsType, CredentialsId, CredentialsToken, Handle);
	return Handle;
}

void UBeamableEOS::LoginWithEOS(int LocalPlayerIndex, FString CredentialsType, FString CredentialsId, FString CredentialsToken, FBeamOperationHandle Op)
{
	using namespace UE::Online;

	// ===== Step 1: Validate EOS Online Services initialization =====
	IOnlineServicesPtr OnlineServices = GetServices(EOnlineServices::Epic);
	if (!OnlineServices)
	{
		UE_LOG(LogTemp, Error, TEXT("EOS Online Services is null. Check if the EOS SDK is initialized correctly."));
		Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("EOS_ONLINE_SERVICES_NULL"));
		return;
	}

	IAuthPtr Auth = OnlineServices->GetAuthInterface();
	if (!Auth)
	{
		UE_LOG(LogTemp, Error, TEXT("EOS Auth interface is null."));
		Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("EOS_AUTH_INTERFACE_NULL"));
		return;
	}

	// ===== Step 2: Determine authentication method =====
	// Hierarchical credential detection:
	// 1. Use provided credentials if all are specified
	// 2. Try PersistentAuth (cached refresh token from previous login)
	// 3. Try to detect Exchange Code from command line (Epic Launcher)
	// 4. Try Developer Auth Tool in editor
	// 5. Fall back to AccountPortal (browser-based login)
	FString FinalCredentialsType = CredentialsType;
	FString FinalCredentialsId = CredentialsId;
	FString FinalCredentialsToken = CredentialsToken;

	if (CredentialsType.IsEmpty())
	{
		// Default to PersistentAuth to enable automatic re-login using cached credentials
		// from a previous successful login session
		FinalCredentialsType = TEXT("PersistentAuth");
		FinalCredentialsId = TEXT("");
		FinalCredentialsToken = TEXT("");
		UE_LOG(LogTemp, Log, TEXT("EOS: Attempting PersistentAuth (cached credentials)"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("EOS: Using manually provided credentials (Type: %s)"), *FinalCredentialsType);
	}

	// ===== Step 3: Setup login parameters =====
	FAuthLogin::Params LoginParams;

	// PlatformUserId is required by AuthEOS.cpp (see AuthEOS.cpp:75-79)
	// It identifies the local platform user and is validated as the first step in FAuthEOS::Login
	// Using index 0 for the primary/first local user
	LoginParams.PlatformUserId = FPlatformMisc::GetPlatformUserForUserIndex(0);

	// CredentialsType determines the authentication method (see AuthEOS.cpp:115)
	// Valid types: PersistentAuth, Developer, ExchangeCode, AccountPortal, etc.
	LoginParams.CredentialsType = FName(*FinalCredentialsType);
	LoginParams.CredentialsId = FinalCredentialsId;
	LoginParams.CredentialsToken.Set<FString>(FinalCredentialsToken);

	// ===== Step 4: Perform EOS login =====
	// This initiates the full EOS authentication flow which includes:
	// - Step 1: Validate PlatformUserId (AuthEOS.cpp:75-79)
	// - Step 2: Login to EAS (Epic Account Services) (AuthEOS.cpp:102-144)
	// - Step 3: Fetch external auth token for Connect login (AuthEOS.cpp:145-172)
	// - Step 4: Login to EOS Connect (AuthEOS.cpp:173-212)
	// - Step 5: Fetch dependent data (user info, etc.)
	TOnlineAsyncOpHandle<FAuthLogin> LoginHandle = Auth->Login(MoveTemp(LoginParams));
	LoginHandle.OnComplete([this, Op, Auth, FinalCredentialsType, LocalPlayerIndex](const TOnlineResult<FAuthLogin>& Result)
	{
		if (Result.IsOk())
		{
			// ===== Login Success: Extract account information =====
			const TSharedRef<FAccountInfo> AccountInfo = Result.GetOkValue().AccountInfo;
			const FAccountId AccountId = AccountInfo->AccountId;

			// Ensure the cached arrays are large enough for this local player index
			EnsureCacheSize(CachedEOSUserIds, CachedEOSAuthTokens, LocalPlayerIndex);

			// Cache the EOS AccountId (Product User ID) for this local player
			CachedEOSUserIds[LocalPlayerIndex] = UE::Online::ToString(AccountId);
			UE_LOG(LogTemp, Log, TEXT("EOS Login successful for LocalPlayerIndex %d. AccountId: %s"), LocalPlayerIndex, *CachedEOSUserIds[LocalPlayerIndex]);

			// ===== Step 5: Query external auth token for Beamable authentication =====
			// Beamable requires an external auth token from EOS to authenticate users
			// This token is obtained via QueryExternalAuthToken after successful EOS login
			FAuthQueryExternalAuthToken::Params TokenParams;
			TokenParams.LocalAccountId = AccountId;

			TOnlineAsyncOpHandle<FAuthQueryExternalAuthToken> TokenHandle = Auth->QueryExternalAuthToken(MoveTemp(TokenParams));
			TokenHandle.OnComplete([this, Op, Auth, AccountId, LocalPlayerIndex](const TOnlineResult<FAuthQueryExternalAuthToken>& TokenResult)
			{
				if (TokenResult.IsOk())
				{
					const FExternalAuthToken& ExternalToken = TokenResult.GetOkValue().ExternalAuthToken;
					CachedEOSAuthTokens[LocalPlayerIndex] = ExternalToken.Data;
					UE_LOG(LogTemp, Log, TEXT("EOS Auth token retrieved successfully for LocalPlayerIndex %d. Type: %s"), LocalPlayerIndex, *ExternalToken.Type.ToString());
					Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
				}
				else
				{
					// Auth token retrieval failed - logout from EOS before reporting error
					// This follows the pattern in AuthEOS.cpp:159-165 where failed token retrieval triggers EAS logout
					const FOnlineError& TokenError = TokenResult.GetErrorValue();
					UE_LOG(LogTemp, Error, TEXT("EOS Auth token query failed: %s. Logging out from EOS."), *TokenError.GetLogString());

					FAuthLogout::Params LogoutParams;
					LogoutParams.LocalAccountId = AccountId;
					Auth->Logout(MoveTemp(LogoutParams));

					Runtime->RequestTrackerSystem->TriggerOperationError(Op, TokenError.GetLogString());
				}
			});
		}
		else
		{
			// ===== Login Failed: Handle errors and fallback authentication =====
			const FOnlineError& Error = Result.GetErrorValue();
			UE_LOG(LogTemp, Warning, TEXT("EOS Login failed with %s: %s"), *FinalCredentialsType, *Error.GetLogString());

			// Check if this is a NoConnection error (typically occurs when Developer Auth Tool is not running)
			bool bIsNoConnectionError = Error.GetLogString().Contains(TEXT("EOS_NoConnection"));

			// Check if this is an AlreadyLoggedIn error (user is already authenticated with EOS)
			bool bIsAlreadyLoggedIn = Error.GetLogString().Contains(TEXT("AlreadyLoggedIn"));

			// ===== Special Case: Already Logged In =====
			// If the user is already logged in to EOS, retrieve their account info and auth token
			if (bIsAlreadyLoggedIn)
			{
				UE_LOG(LogTemp, Log, TEXT("EOS: User already logged in for LocalPlayerIndex %d, retrieving cached account info"), LocalPlayerIndex);

				// Get the logged-in user's account info
				FAuthGetLocalOnlineUserByPlatformUserId::Params GetUserParams;
				GetUserParams.PlatformUserId = FPlatformMisc::GetPlatformUserForUserIndex(LocalPlayerIndex);

				TOnlineResult<FAuthGetLocalOnlineUserByPlatformUserId> UserResult = Auth->GetLocalOnlineUserByPlatformUserId(MoveTemp(GetUserParams));
				if (UserResult.IsOk())
				{
					const FAccountId AccountId = UserResult.GetOkValue().AccountInfo->AccountId;

					// Ensure the cached arrays are large enough for this local player index
					EnsureCacheSize(CachedEOSUserIds, CachedEOSAuthTokens, LocalPlayerIndex);

					CachedEOSUserIds[LocalPlayerIndex] = UE::Online::ToString(AccountId);
					UE_LOG(LogTemp, Log, TEXT("EOS: Retrieved existing AccountId for LocalPlayerIndex %d: %s"), LocalPlayerIndex, *CachedEOSUserIds[LocalPlayerIndex]);

					// Fetch external auth token for Beamable authentication
					FAuthQueryExternalAuthToken::Params TokenParams;
					TokenParams.LocalAccountId = AccountId;

					TOnlineAsyncOpHandle<FAuthQueryExternalAuthToken> TokenHandle = Auth->QueryExternalAuthToken(MoveTemp(TokenParams));
					TokenHandle.OnComplete([this, Op, LocalPlayerIndex](const TOnlineResult<FAuthQueryExternalAuthToken>& TokenResult)
					{
						if (TokenResult.IsOk())
						{
							const FExternalAuthToken& ExternalToken = TokenResult.GetOkValue().ExternalAuthToken;
							CachedEOSAuthTokens[LocalPlayerIndex] = ExternalToken.Data;
							UE_LOG(LogTemp, Log, TEXT("EOS: Auth token retrieved from existing session for LocalPlayerIndex %d. Type: %s"), LocalPlayerIndex, *ExternalToken.Type.ToString());
							Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
						}
						else
						{
							const FOnlineError& TokenError = TokenResult.GetErrorValue();
							UE_LOG(LogTemp, Error, TEXT("EOS: Failed to retrieve auth token from existing session for LocalPlayerIndex %d: %s"), LocalPlayerIndex, *TokenError.GetLogString());
							Runtime->RequestTrackerSystem->TriggerOperationError(Op, TokenError.GetLogString());
						}
					});
					return;
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("EOS: AlreadyLoggedIn but failed to retrieve account info for LocalPlayerIndex %d: %s"), LocalPlayerIndex, *UserResult.GetErrorValue().GetLogString());
					Runtime->RequestTrackerSystem->TriggerOperationError(Op, UserResult.GetErrorValue().GetLogString());
					return;
				}
			}

			// ===== Fallback Strategy 1: PersistentAuth failure =====
			// If PersistentAuth failed (no cached credentials or expired), try alternative methods
			if (FinalCredentialsType == TEXT("PersistentAuth"))
			{
				UE_LOG(LogTemp, Log, TEXT("EOS: PersistentAuth failed, trying alternative authentication methods"));

				FString FallbackCredentialsId, FallbackCredentialsToken, FallbackCredentialsType;

				// Priority 1: Try Exchange Code from Epic Launcher command line arguments
				// Format: -AUTH_LOGIN=unused -AUTH_PASSWORD=<exchangecode> -AUTH_TYPE=exchangecode
				if (TryGetExchangeCodeFromCommandLine(FallbackCredentialsId, FallbackCredentialsToken, FallbackCredentialsType))
				{
					UE_LOG(LogTemp, Log, TEXT("EOS: Falling back to Exchange Code from command line"));
					LoginWithEOS(LocalPlayerIndex, FallbackCredentialsType, FallbackCredentialsId, FallbackCredentialsToken, Op);
					return;
				}
				// Priority 2: Try Developer Auth Tool (localhost:6300) for PIE sessions
				// This requires the EOS Developer Authentication Tool to be running
				else if (TryGetDeveloperAuthCredentials(this, FallbackCredentialsId, FallbackCredentialsToken, FallbackCredentialsType))
				{
					UE_LOG(LogTemp, Log, TEXT("EOS: Falling back to Developer Auth Tool"));
					LoginWithEOS(LocalPlayerIndex, FallbackCredentialsType, FallbackCredentialsId, FallbackCredentialsToken, Op);
					return;
				}
				// Priority 3: Fall back to Account Portal (browser-based login)
				else
				{
					UE_LOG(LogTemp, Log, TEXT("EOS: Falling back to Account Portal authentication"));
					LoginWithEOS(LocalPlayerIndex, TEXT("AccountPortal"), TEXT(""), TEXT(""), Op);
					return;
				}
			}
			// ===== Fallback Strategy 2: Developer Auth Tool not available =====
			// If Developer auth failed with EOS_NoConnection (tool not running), use AccountPortal
			else if (FinalCredentialsType == TEXT("Developer") && bIsNoConnectionError)
			{
				UE_LOG(LogTemp, Warning, TEXT("EOS: Developer Auth Tool not available (EOS_NoConnection), falling back to Account Portal"));
				LoginWithEOS(LocalPlayerIndex, TEXT("AccountPortal"), TEXT(""), TEXT(""), Op);
				return;
			}

			// No fallback available - report the error to the operation tracker
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Error.GetLogString());
		}
	});
}

bool UBeamableEOS::TryGetEOSDataByLocalPlayerIndex(int LocalPlayerIndex, FString& EOSUserId, FString& EOSAuthToken, FString& Error)
{
	// Check if the local player index is valid
	if (LocalPlayerIndex < 0 || LocalPlayerIndex >= CachedEOSUserIds.Num() || LocalPlayerIndex >= CachedEOSAuthTokens.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("No cached EOS auth data for LocalPlayerIndex %d. Please call LoginWithEOSOperation first."), LocalPlayerIndex);
		Error = FString::Printf(TEXT("No cached EOS auth data for LocalPlayerIndex %d. Please call LoginWithEOSOperation first."), LocalPlayerIndex);
		return false;
	}

	// Check if we have cached auth data for this local player
	if (CachedEOSUserIds[LocalPlayerIndex].IsEmpty() || CachedEOSAuthTokens[LocalPlayerIndex].IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("No cached EOS auth data for LocalPlayerIndex %d. Please call LoginWithEOSOperation first."), LocalPlayerIndex);
		Error = FString::Printf(TEXT("No cached EOS auth data for LocalPlayerIndex %d. Please call LoginWithEOSOperation first."), LocalPlayerIndex);
		return false;
	}

	EOSUserId = CachedEOSUserIds[LocalPlayerIndex];
	EOSAuthToken = CachedEOSAuthTokens[LocalPlayerIndex];

	return true;
}

bool UBeamableEOS::TryGetEOSDataForSlot(FUserSlot UserSlot, FString& EOSUserId, FString& EOSAuthToken, FString& Error)
{
	// Get the Beamable core settings to resolve the user slot to a local player index
	const UBeamCoreSettings* CoreSettings = GetDefault<UBeamCoreSettings>();
	if (!CoreSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get BeamCoreSettings"));
		Error = TEXT("Failed to get BeamCoreSettings");
		return false;
	}

	// Find the local player index for this user slot
	const int LocalPlayerIndex = CoreSettings->RuntimeUserSlots.IndexOfByKey(UserSlot.Name);
	if (LocalPlayerIndex == INDEX_NONE)
	{
		UE_LOG(LogTemp, Error, TEXT("User slot '%s' not found in RuntimeUserSlots"), *UserSlot.Name);
		Error = FString::Printf(TEXT("User slot '%s' not found in RuntimeUserSlots"), *UserSlot.Name);
		return false;
	}

	// Use the local player index to retrieve the cached data
	return TryGetEOSDataByLocalPlayerIndex(LocalPlayerIndex, EOSUserId, EOSAuthToken, Error);
}
