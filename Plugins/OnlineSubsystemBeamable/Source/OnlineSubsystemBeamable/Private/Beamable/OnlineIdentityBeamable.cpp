#include "OnlineIdentityBeamable.h"

#include "OnlineStatsBeamable.h"
#include "OnlineSubsystem.h"
#include "Beamable/OnlineSubsystemBeamable.h"
#include "Beamable/OnlineSubsystemBeamableSettings.h"
#include "AutoGen/SubSystems/BeamAccountsApi.h"
#include "AutoGen/SubSystems/BeamAuthApi.h"
#include "AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamBackend/SemanticTypes/BeamStatsTypeLibrary.h"
#include "Engine/LocalPlayer.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "Runtime/BeamRuntime.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"

bool FUserOnlineAccountBeamable::GetAuthAttribute(const FString& AttrName, FString& OutAttrValue) const
{
	const FString* FoundAttr = AdditionalAuthData.Find(AttrName);
	if (FoundAttr != nullptr)
	{
		OutAttrValue = *FoundAttr;
		return true;
	}
	UE_LOG_ONLINE_IDENTITY(Warning, TEXT("Attribute currently unsupported. ATTR_NAME=%s"), *AttrName);
	return false;
}

FString FUserOnlineAccountBeamable::GetRealName() const
{
	UE_LOG_ONLINE_IDENTITY(Warning, TEXT("Currently unsupported. Please use the IOnlineStats interface instead."));
	return TEXT("___UNSUPPORTED___");
}

FString FUserOnlineAccountBeamable::GetDisplayName(const FString& Platform) const
{
	FString DisplayName;
	GetUserAttribute(USER_ATTR_ALIAS, DisplayName);
	return DisplayName;
}

bool FUserOnlineAccountBeamable::GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const
{
	const FString* FoundAttr = UserAttributes.Find(AttrName);
	if (FoundAttr != nullptr)
	{
		OutAttrValue = *FoundAttr;
		return true;
	}

	UE_LOG_ONLINE_IDENTITY(Warning, TEXT("Attribute currently unsupported. ATTR_NAME=%s"), *AttrName);
	return false;
}

bool FUserOnlineAccountBeamable::SetUserAttribute(const FString& AttrName, const FString& AttrValue)
{
	UserAttributes.Add(AttrName, AttrValue);
	return true;
}

FOnlineIdentityBeamable::FOnlineIdentityBeamable(FOnlineSubsystemBeamable* InSubsystem)
	: BeamableSubsystem(InSubsystem)
{
	// Read configuration variables for emulating other login systems	
	GConfig->GetBool(TEXT("OnlineSubsystemBeamable"), TEXT("bForceOfflineMode"), bForceOfflineMode, GEngineIni);
}

FOnlineIdentityBeamable::~FOnlineIdentityBeamable()
{
}

bool FOnlineIdentityBeamable::Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials)
{
	FString ErrorStr;
	TSharedPtr<FUserOnlineAccountBeamable> UserAccountPtr;

	const UBeamCoreSettings* CoreSettings = GetDefault<UBeamCoreSettings>();
	const UOnlineSubsystemBeamableSettings* BeamOnlineSettings = GetDefault<UOnlineSubsystemBeamableSettings>();
	checkf(CoreSettings->RuntimeUserSlots.Num() > LocalUserNum, TEXT("No UserSlot mapped to this local user num. Number of RuntimeUserSlots must match the maximum number of expected local players."));

	const FUserSlot TargetSlot = CoreSettings->RuntimeUserSlots[LocalUserNum];
	UGameInstance* GameInstance = BeamableSubsystem->GetGameInstance();
	FString LoginType = AccountCredentials.Type;

	const FBeamOperationEventHandlerCode LoginHandler = FBeamOperationEventHandlerCode::CreateRaw(this, &FOnlineIdentityBeamable::OnBeamableLoginOperationComplete, AccountCredentials);

	// valid local player index
	if (LocalUserNum < 0 || LocalUserNum >= MAX_LOCAL_PLAYERS)
	{
		ErrorStr = FString::Printf(TEXT("Invalid LocalUserNum=%d"), LocalUserNum);
		UE_LOG_ONLINE_IDENTITY(Warning, TEXT("Login request failed. %s"), *ErrorStr);
		TriggerOnLoginCompleteDelegates(LocalUserNum, false, *FUniqueNetIdBeamable::EmptyId(), ErrorStr);
		return false;
	}

	// If the user is already signed into UE's Subsystem stuff, we check for the Attach OSS_IDENTITY_TYPES
	if (const FUniqueNetIdPtr* UserId = UserIds.Find(LocalUserNum); UserId != nullptr)
	{
		// If we are trying to attach an email...
		if (LoginType.StartsWith(OSS_BEAMABLE_IDENTITY_TYPE_ATTACH_EMAIL()))
		{
			const FString Email = AccountCredentials.Id;
			const FString Password = AccountCredentials.Token;

			UBeamRuntime* BeamRuntime = GameInstance->GetSubsystem<UBeamRuntime>();
			const auto OnAttachEmail = FBeamOperationEventHandlerCode::CreateLambda(
				[this, LoginType, GameInstance, LocalUserNum, UserId, TargetSlot, LoginHandler, Email, Password, BeamOnlineSettings](FBeamOperationEvent Evt)
				{
					if (Evt.EventType == OET_SUCCESS)
					{
						UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Email] Successfully Attached!"), *Email);
						TriggerOnLoginCompleteDelegates(LocalUserNum, true, *UserId->Get(), LoginType);
						return;
					}

					// Error Handling
					if (Evt.EventCode.Contains("EMAIL_IN_USE") && BeamOnlineSettings->bAutoLoginOnAttach)
					{
						UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Email] %s - User already associated with beamable account. Logging in instead."), *Email);
						GameInstance->GetSubsystem<UBeamRuntime>()->CPP_LoginEmailAndPasswordOperation(TargetSlot, Email, Password, LoginHandler);
					}
					else
					{
						UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Email] Failed To Attach. Reason=%s."), *Evt.EventCode);
						TriggerOnLoginCompleteDelegates(LocalUserNum, false, *UserId->Get(), Evt.EventCode);
					}
				});
			BeamRuntime->CPP_AttachEmailAndPasswordOperation(TargetSlot, Email, Password, OnAttachEmail);
			return true;
		}

		// If we are attaching a federated identity...
		// See OSS_BEAMABLE_IDENTITY_TYPE_ATTACH_FEDERATED
		if (LoginType.StartsWith(TEXT("attach_extern_")))
		{
			FString FederationPath;
			FString Discarded;
			LoginType.Split("_", &Discarded, &FederationPath);
			FederationPath.Split("_", &Discarded, &FederationPath);

			FString ServiceName;
			FString Namespace;
			FederationPath.Split("/", &ServiceName, &Namespace);

			UBeamRuntime* BeamRuntime = GameInstance->GetSubsystem<UBeamRuntime>();
			const FString ExternalUserId = AccountCredentials.Id;
			const FString ExternalToken = AccountCredentials.Token;

			const auto OnAttachWithExternalId = FBeamOperationEventHandlerCode::CreateLambda(
				[this, GameInstance, LocalUserNum, LoginType, TargetSlot, LoginHandler, ServiceName, Namespace, ExternalToken, BeamOnlineSettings, UserId](FBeamOperationEvent Evt)
				{
					if (Evt.EventType == OET_SUCCESS)
					{
						UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Federated Identity] Successfully SignedUp using federated identity %s!"), *FString(ServiceName + "/" + Namespace));
						TriggerOnLoginCompleteDelegates(LocalUserNum, true, *UserId->Get(), LoginType);
						return;
					}

					// Error Handling
					if (Evt.EventCode.Contains("EXTERNAL_IDENTITY_IN_USE") && BeamOnlineSettings->bAutoLoginOnAttach)
					{
						UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Federated Identity] %s User already associated with beamable account. Logging in instead."),
						                       *FString(ServiceName + "/" + Namespace));
						GameInstance->GetSubsystem<UBeamRuntime>()->CPP_LoginFederatedOperation(TargetSlot, ServiceName, Namespace, ExternalToken, LoginHandler);
					}
					else
					{
						UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Federated Identity] Failed To Sign Up. Reason=%s."), *Evt.EventCode);
						TriggerOnLoginCompleteDelegates(LocalUserNum, false, *UserId->Get(), Evt.EventCode);
					}
				});
			BeamRuntime->CPP_AttachFederatedOperation(TargetSlot, ServiceName, Namespace, ExternalUserId, ExternalToken, OnAttachWithExternalId);
		}

		UserAccountPtr = UserAccounts.FindChecked(UserId->ToSharedRef());
		TriggerOnLoginCompleteDelegates(LocalUserNum, true, *UserId->Get(), LoginType);
		return true;
	}

	// Check for all the SignUp Cases
	{
		// If we are signing up with email/password
		if (LoginType.StartsWith(OSS_BEAMABLE_IDENTITY_TYPE_SIGNUP_EMAIL()))
		{
			const FString Email = AccountCredentials.Id;
			const FString Password = AccountCredentials.Token;

			UBeamRuntime* BeamRuntime = GameInstance->GetSubsystem<UBeamRuntime>();
			BeamRuntime->CPP_SignUpEmailAndPasswordOperation(TargetSlot, Email, Password, false, {}, LoginHandler);
		}

		// If we are signing up with a federated identity.
		// See OSS_BEAMABLE_IDENTITY_TYPE_SIGNUP_FEDERATED
		if (LoginType.StartsWith(TEXT("signup_extern_")))
		{
			FString FederationPath1;
			FString FederationPath2;
			FString Discarded;
			LoginType.Split("_", &Discarded, &FederationPath1);
			FederationPath1.Split("_", &Discarded, &FederationPath2);

			FString ServiceName;
			FString Namespace;
			FederationPath2.Split("/", &ServiceName, &Namespace);

			UBeamRuntime* BeamRuntime = GameInstance->GetSubsystem<UBeamRuntime>();
			const FString ExternalUserId = AccountCredentials.Id;
			const FString ExternalToken = AccountCredentials.Token;

			BeamRuntime->CPP_SignUpFederatedOperation(TargetSlot, ServiceName, Namespace, ExternalUserId, ExternalToken, false, {}, LoginHandler);
		}
	}

	// Check for all the Login Cases.
	{
		// If this is a frictionless login.
		if (LoginType.StartsWith(OSS_BEAMABLE_IDENTITY_TYPE_FRICTIONLESS()))
		{
			UBeamRuntime* BeamRuntime = GameInstance->GetSubsystem<UBeamRuntime>();
			BeamRuntime->CPP_LoginFrictionlessOperation(TargetSlot, {}, LoginHandler);
		}

		// If we are logging in with email/password
		if (LoginType.StartsWith(OSS_BEAMABLE_IDENTITY_TYPE_EMAIL()))
		{
			const FString Email = AccountCredentials.Id;
			const FString Password = AccountCredentials.Token;
			UBeamRuntime* BeamRuntime = GameInstance->GetSubsystem<UBeamRuntime>();

			if (BeamOnlineSettings->bAutoSignUpWhenLogin)
			{
				const auto OnSignUpWithEmail = FBeamOperationEventHandlerCode::CreateLambda(
					[this, GameInstance, LocalUserNum, AccountCredentials, TargetSlot, LoginHandler, Email, Password](FBeamOperationEvent Evt)
					{
						if (Evt.EventType == OET_SUCCESS)
						{
							UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Email] Successfully SignedUp using Email/Password!"), *Email);
							OnBeamableLoginOperationComplete(Evt, AccountCredentials);
							return;
						}

						// Error Handling
						if (Evt.EventCode.Contains("EMAIL_IN_USE"))
						{
							UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Email] %s - User already associated with beamable account. Logging in instead."), *Email);
							GameInstance->GetSubsystem<UBeamRuntime>()->CPP_LoginEmailAndPasswordOperation(TargetSlot, Email, Password, LoginHandler);
						}
						else
						{
							UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Email] Failed To Sign Up. Reason=%s."), *Evt.EventCode);
							TriggerOnLoginCompleteDelegates(LocalUserNum, false, *FUniqueNetIdBeamable::EmptyId(), Evt.EventCode);
						}
					});
				BeamRuntime->CPP_SignUpEmailAndPasswordOperation(TargetSlot, Email, Password, false, {}, OnSignUpWithEmail);
			}
			else
			{
				BeamRuntime->CPP_LoginEmailAndPasswordOperation(TargetSlot, Email, Password, LoginHandler);
			}
		}

		// If we are logging in with some external auth token
		// OSS_BEAMABLE_IDENTITY_TYPE_FEDERATED
		if (LoginType.StartsWith("extern_"))
		{
			// If we are doing some federated login
			if (LoginType.Contains("/"))
			{
				FString FederationPath;
				FString Discarded;
				LoginType.Split("_", &Discarded, &FederationPath);

				FString ServiceName;
				FString Namespace;
				FederationPath.Split("/", &ServiceName, &Namespace);

				UBeamRuntime* BeamRuntime = GameInstance->GetSubsystem<UBeamRuntime>();
				const FString ExternalUserId = AccountCredentials.Id;
				const FString ExternalToken = AccountCredentials.Token;


				if (BeamOnlineSettings->bAutoSignUpWhenLogin)
				{
					const auto OnSignUpWithExternalId = FBeamOperationEventHandlerCode::CreateLambda(
						[this, GameInstance, LocalUserNum, AccountCredentials, TargetSlot, LoginHandler, ServiceName, Namespace, ExternalToken](FBeamOperationEvent Evt)
						{
							if (Evt.EventType == OET_SUCCESS)
							{
								UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Federated Identity] Successfully SignedUp using federated identity %s!"), *FString(ServiceName + "/" + Namespace));
								OnBeamableLoginOperationComplete(Evt, AccountCredentials);
								return;
							}

							// Error Handling
							if (Evt.EventCode.Contains("EXTERNAL_IDENTITY_IN_USE"))
							{
								UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Federated Identity] %s User already associated with beamable account. Logging in instead."),
								                       *FString(ServiceName + "/" + Namespace));
								GameInstance->GetSubsystem<UBeamRuntime>()->CPP_LoginFederatedOperation(TargetSlot, ServiceName, Namespace, ExternalToken, LoginHandler);
							}
							else
							{
								UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Federated Identity] Failed To Sign Up. Reason=%s."), *Evt.EventCode);
								TriggerOnLoginCompleteDelegates(LocalUserNum, false, *FUniqueNetIdBeamable::EmptyId(), Evt.EventCode);
							}
						});
					BeamRuntime->CPP_SignUpFederatedOperation(TargetSlot, ServiceName, Namespace, ExternalUserId, ExternalToken, false, {}, OnSignUpWithExternalId);
				}
				else
				{
					GameInstance->GetSubsystem<UBeamRuntime>()->CPP_LoginFederatedOperation(TargetSlot, ServiceName, Namespace, ExternalToken, LoginHandler);
				}
			}
		}
	}

	return true;
}

bool FOnlineIdentityBeamable::Logout(int32 LocalUserNum)
{
	const FUniqueNetIdPtr UserId = GetUniquePlayerId(LocalUserNum);

	if (UserId.IsValid())
	{
		const FUserSlot& UserSlot = UserIdToSlot.FindChecked(UserId);
		UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("Clearing user found for LocalUserNum=%d | UserSlot=%s."), LocalUserNum, *UserSlot.Name);
		if (const auto GameInstance = BeamableSubsystem->GetGameInstance())
		{
			GEngine->GetEngineSubsystem<UBeamUserSlots>()->ClearUserAtSlot(UserSlot, USCR_Manual, false, GameInstance);
			return true;
		}
	}

	UE_LOG_ONLINE_IDENTITY(Warning, TEXT("No logged in user found for LocalUserNum=%d."), LocalUserNum);
	TriggerOnLogoutCompleteDelegates(LocalUserNum, false);
	return false;
}

bool FOnlineIdentityBeamable::AutoLogin(int32 LocalUserNum)
{
	// Auto login could work with: GEngine->GetEngineSubsystem<UBeamUserSlots>()->TryLoadSavedUserAtSlot(FUserSlot{"Player0"}, )	
	return true;
}

TSharedPtr<FUserOnlineAccount> FOnlineIdentityBeamable::GetUserAccount(const FUniqueNetId& UserId) const
{
	TSharedPtr<FUserOnlineAccount> Result;

	if (const TSharedRef<FUserOnlineAccountBeamable>* FoundUserAccount = UserAccounts.Find(UserId.AsShared()))
	{
		Result = *FoundUserAccount;
	}

	return Result;
}

TArray<TSharedPtr<FUserOnlineAccount>> FOnlineIdentityBeamable::GetAllUserAccounts() const
{
	TArray<TSharedPtr<FUserOnlineAccount>> Result;

	for (TUniqueNetIdMap<TSharedRef<FUserOnlineAccountBeamable>>::TConstIterator It(UserAccounts); It; ++It)
	{
		Result.Add(It.Value());
	}

	return Result;
}

FUniqueNetIdPtr FOnlineIdentityBeamable::GetUniquePlayerId(int32 LocalUserNum) const
{
	const FUniqueNetIdPtr* FoundId = UserIds.Find(LocalUserNum);
	if (FoundId != NULL)
	{
		return *FoundId;
	}
	return NULL;
}

FUniqueNetIdPtr FOnlineIdentityBeamable::CreateUniquePlayerId(uint8* Bytes, int32 Size)
{
	if (Bytes != NULL && Size > 0)
	{
		FString StrId(Size, (TCHAR*)Bytes);
		return FUniqueNetIdBeamable::Create(StrId);
	}
	return NULL;
}

FUniqueNetIdPtr FOnlineIdentityBeamable::CreateUniquePlayerId(const FString& Str)
{
	return FUniqueNetIdBeamable::Create(Str);
}

ELoginStatus::Type FOnlineIdentityBeamable::GetLoginStatus(int32 LocalUserNum) const
{
	FUniqueNetIdPtr UserId = GetUniquePlayerId(LocalUserNum);
	if (UserId.IsValid())
	{
		return GetLoginStatus(*UserId);
	}
	return ELoginStatus::NotLoggedIn;
}

ELoginStatus::Type FOnlineIdentityBeamable::GetLoginStatus(const FUniqueNetId& UserId) const
{
	TSharedPtr<FUserOnlineAccount> UserAccount = GetUserAccount(UserId);
	if (UserAccount.IsValid() && UserAccount->GetUserId()->IsValid())
	{
		if (bForceOfflineMode)
		{
			return ELoginStatus::UsingLocalProfile;
		}
		return ELoginStatus::LoggedIn;
	}
	return ELoginStatus::NotLoggedIn;
}

FString FOnlineIdentityBeamable::GetPlayerNickname(int32 LocalUserNum) const
{
	FUniqueNetIdPtr UniqueId = GetUniquePlayerId(LocalUserNum);
	if (UniqueId.IsValid())
		return GetPlayerNickname(*UniqueId);

	return TEXT("BeamableUser");
}

FString FOnlineIdentityBeamable::GetPlayerNickname(const FUniqueNetId& UserId) const
{
	if (UserId.IsValid())
	{
		TSharedPtr<FUserOnlineAccount> Account = GetUserAccount(UserId);

		if (Account.IsValid())
		{
			return Account->GetDisplayName();
		}
	}

	return TEXT("BeamableUser");
}

FString FOnlineIdentityBeamable::GetAuthToken(int32 LocalUserNum) const
{
	FUniqueNetIdPtr UserId = GetUniquePlayerId(LocalUserNum);
	if (UserId.IsValid())
	{
		TSharedPtr<FUserOnlineAccount> UserAccount = GetUserAccount(*UserId);
		if (UserAccount.IsValid())
		{
			return UserAccount->GetAccessToken();
		}
	}
	return FString();
}

void FOnlineIdentityBeamable::RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate)
{
	UE_LOG_ONLINE_IDENTITY(Display, TEXT("FOnlineIdentityBeamable::RevokeAuthToken not implemented"));
}


void FOnlineIdentityBeamable::GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI)
{
	if (bForceOfflineMode && Privilege == EUserPrivileges::CanPlayOnline)
	{
		Delegate.ExecuteIfBound(UserId, Privilege, (uint32)EPrivilegeResults::NetworkConnectionUnavailable);
	}
	Delegate.ExecuteIfBound(UserId, Privilege, (uint32)EPrivilegeResults::NoFailures);
}

FPlatformUserId FOnlineIdentityBeamable::GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const
{
	for (int i = 0; i < MAX_LOCAL_PLAYERS; ++i)
	{
		auto CurrentUniqueId = GetUniquePlayerId(i);
		if (CurrentUniqueId.IsValid() && (*CurrentUniqueId == UniqueNetId))
		{
			return GetPlatformUserIdFromLocalUserNum(i);
		}
	}

	return PLATFORMUSERID_NONE;
}

FString FOnlineIdentityBeamable::GetAuthType() const
{
	return TEXT("Beamable");
}

TSharedPtr<FUserOnlineAccountBeamable> FOnlineIdentityBeamable::GetUserAccountBeamable(const FUniqueNetId& UserId) const
{
	TSharedPtr<FUserOnlineAccountBeamable> Result;

	if (const TSharedRef<FUserOnlineAccountBeamable>* FoundUserAccount = UserAccounts.Find(UserId.AsShared()))
	{
		Result = *FoundUserAccount;
	}

	return Result;
}

const TUniqueNetIdMap<TSharedRef<FUserOnlineAccountBeamable>> FOnlineIdentityBeamable::GetBeamableUsers() const
{
	return UserAccounts;
}

const FUniqueNetIdPtr FOnlineIdentityBeamable::GetBeamableUser(FUserSlot Slot) const
{
	if (SlotToUserId.Contains(Slot))
		return SlotToUserId[Slot];
	return nullptr;
}


void FOnlineIdentityBeamable::OnBeamableLoginOperationComplete(FBeamOperationEvent Evt, FOnlineAccountCredentials AccountCredentials)
{
	const auto Slots = GEngine->GetEngineSubsystem<UBeamRequestTracker>()->ActiveOperationState[Evt.OwnerHandle]->DependentUserSlots;
	const FUserSlot LoggedInSlot = Slots[0];

	const UBeamCoreSettings* CoreSettings = GetDefault<UBeamCoreSettings>();
	const int32 LocalUserNum = CoreSettings->RuntimeUserSlots.Find(LoggedInSlot.Name);

	// If the login operation failed, let's notify Epic's stuff.
	if (Evt.EventType != OET_SUCCESS)
	{
		UE_LOG_ONLINE_IDENTITY(Error, TEXT("%s"), *Evt.EventCode);
		TriggerOnLoginCompleteDelegates(LocalUserNum, false, *FUniqueNetIdBeamable::EmptyId(), Evt.EventCode);
		return;
	}

	// Otherwise, let's prepare the FUserOnlineAccountBeamable representation of a beamable player.
	UBeamUserSlots* UserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();

	// Get the logged in user's data from the logged in user slot.
	const UGameInstance* GameInstance = BeamableSubsystem->GetGameInstance();
	if (FBeamRealmUser LoggedInUser; UserSlots->GetUserDataAtSlot(LoggedInSlot, LoggedInUser, GameInstance))
	{
		// Create a UserOnlineAccountBeamable object.
		TSharedPtr<FUserOnlineAccountBeamable> UserAccountPtr = MakeShareable(new FUserOnlineAccountBeamable(LoggedInUser, LoggedInSlot, AccountCredentials.Type));
		const FUniqueNetIdRef NewIdRef = UserAccountPtr->GetUserId();

		// Store AuthCredential Type
		UserAccountPtr->AdditionalAuthData.Add(TEXT("AuthType"), AccountCredentials.Type);

		// Configure the ULocalPlayer that logged in		
		ULocalPlayer* LocalPlayer = GameInstance->GetLocalPlayerByIndex(LocalUserNum);

		// If we don't have a local player, let's sign out from beamable.		
		if (!LocalPlayer)
		{
			const auto LogoutHandler = FBeamOperationEventHandlerCode::CreateLambda([this, LocalUserNum](FBeamOperationEvent Evt)
			{
				ensureAlwaysMsgf(Evt.EventType == OET_SUCCESS, TEXT("It should be impossible for this operation to fail. If you see this, contact Beamable."));

				UE_LOG_ONLINE_IDENTITY(Error, TEXT("No local player found. %d"), LocalUserNum);
				TriggerOnLoginCompleteDelegates(LocalUserNum, false, *FUniqueNetIdBeamable::EmptyId(), FString::Printf(TEXT("%d"), LocalUserNum));
			});
			GameInstance->GetSubsystem<UBeamRuntime>()->CPP_LogoutOperation(LoggedInSlot, USCR_OnlineSubsystem_NoLocalPlayer, true, LogoutHandler);
			return;
		}

		// Update/add cached entry for user		
		UserAccounts.Add(NewIdRef, UserAccountPtr.ToSharedRef());

		// Keep track of user ids for local users and beamable user slots		 
		UserIds.Add(LocalUserNum, NewIdRef);

		SlotToUserId.Add(LoggedInSlot, NewIdRef);
		UserIdToSlot.Add(NewIdRef, LoggedInSlot);

		// Let's configure the LocalPlayer object with the Replicatable NetId.
		const FUniqueNetIdRepl IdRep(NewIdRef);
		LocalPlayer->SetCachedUniqueNetId(IdRep);

		// Map the Stats
		auto StatsSubsystem = GameInstance->GetSubsystem<UBeamStatsSubsystem>();
		auto StatsType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, FBeamGamerTag(UserAccountPtr->GetUserId()->ToString()));
		auto Settings = GetDefault<UOnlineSubsystemBeamableSettings>();

		// If the user stats were pre-fetched as part of the signed in user's serialization
		if (const auto UserStatsPtr = StatsSubsystem->PlayerStatCache.Find(StatsType))
		{
			const auto UserStats = *UserStatsPtr;
			const auto StatsMapping = Settings->StatsToLocalUserAttributeMapping;

			FBeamStatsUpdatedEvent Event;
			Event.GamerTag = FBeamGamerTag(UserAccountPtr->GetUserId()->ToString());
			for (const auto& Stat : UserStats->StringStats)
			{
				Event.NewValues.Add(Stat);
			}

			BeamableSubsystem->GetStatsInterfacePtr()->OnStatsUpdated(Event);

			for (TTuple<FString, FString> Mapping : StatsMapping)
			{
				bool bFoundStat = false;
				if (const auto StatPtr = UserStats->StringStats.Find(Mapping.Key))
				{
					UserAccountPtr->SetUserAttribute(Mapping.Value, *StatPtr);
					bFoundStat = true;
				}

				if (!bFoundStat)
				{
					UE_LOG_ONLINE_IDENTITY(Warning, TEXT("Stat %s not found."), *Mapping.Key);
				}
			}
		}
		else
		{
			UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("Skipping Stats to UserAttributes synchronization."));
		}

		// Trigger the hook.
		const auto HookWaitHandler = TDelegate<void(FBeamWaitCompleteEvent)>::CreateLambda([this, GameInstance, UserAccountPtr, AccountCredentials](FBeamWaitCompleteEvent Evt)
		{
			TArray<FString> Errs;
			if (BeamableSubsystem->GetRequestTracker()->IsWaitFailed(Evt, Errs))
			{
				FString Err;
				for (const auto& Error : Errs) Err += FString::Printf(TEXT("%s\n"), *Error);
				UE_LOG_ONLINE_IDENTITY(Error, TEXT("Failed in OnBeamableUserReadyHook. ERRORS=%s"), *Err);

				// TODO Add support for Multiple Local User Here.
				TriggerOnLoginCompleteDelegates(0, false, *UserAccountPtr->GetUserId(), Err);
				return;
			}

			TriggerOnLoginCompleteDelegates(0, true, *UserAccountPtr->GetUserId(), AccountCredentials.Type);
			GameInstance->GetSubsystem<UBeamRuntime>()->CPP_UnregisterOnUserReady(OnUserReadyCodeHandle);
		});
		FBeamWaitHandle WaitHandle;
		BeamableSubsystem->GetRequestTracker()->InvokeAndWaitForHooks(WaitHandle, OnBeamableUserReadyHook, HookWaitHandler, LoggedInSlot, UserAccountPtr);
	}
}

void FOnlineIdentityBeamable::OnBeamableUserReady(const FUserSlot& Slot, TSharedPtr<FUserOnlineAccountBeamable> UserAccountPtr)
{
	const UGameInstance* GameInstance = BeamableSubsystem->GetGameInstance();

	auto StatsSubsystem = GameInstance->GetSubsystem<UBeamStatsSubsystem>();
	auto StatsType = UBeamStatsTypeLibrary::MakeStatsType(Client, EBeamStatsVisibility::Public, FBeamGamerTag(UserAccountPtr->GetUserId()->ToString()));

	auto Settings = GetDefault<UOnlineSubsystemBeamableSettings>();

	// If the user stats were pre-fetched as part of the signed in user's serialization
	if (const auto UserStatsPtr = StatsSubsystem->PlayerStatCache.Find(StatsType))
	{
		const auto UserStats = *UserStatsPtr;
		const auto StatsMapping = Settings->StatsToLocalUserAttributeMapping;

		FBeamStatsUpdatedEvent Event;
		Event.GamerTag = FBeamGamerTag(UserAccountPtr->GetUserId()->ToString());
		for (const auto& Stat : UserStats->StringStats)
		{
			Event.NewValues.Add(Stat);
		}

		BeamableSubsystem->GetStatsInterfacePtr()->OnStatsUpdated(Event);

		for (TTuple<FString, FString> Mapping : StatsMapping)
		{
			bool bFoundStat = false;
			if (const auto StatPtr = UserStats->StringStats.Find(Mapping.Key))
			{
				UserAccountPtr->SetUserAttribute(Mapping.Value, *StatPtr);
				bFoundStat = true;
			}

			if (!bFoundStat)
			{
				UE_LOG_ONLINE_IDENTITY(Warning, TEXT("Stat %s not found."), *Mapping.Key);
			}
		}
	}
	else
	{
		UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("Skipping Stats to UserAttributes synchronization."));
	}

	const auto HookWaitHandler = FOnWaitCompleteCode::CreateLambda([this, GameInstance, UserAccountPtr](FBeamWaitCompleteEvent Evt)
	{
		TArray<FString> Errs;
		if (BeamableSubsystem->GetRequestTracker()->IsWaitFailed(Evt, Errs))
		{
			FString Err;
			for (const auto& Error : Errs) Err += FString::Printf(TEXT("%s\n"), *Error);
			UE_LOG_ONLINE_IDENTITY(Error, TEXT("Failed in OnBeamableUserReadyHook. ERRORS=%s"), *Err);

			// TODO Add support for Multiple Local User Here.
			TriggerOnLoginCompleteDelegates(0, false, *UserAccountPtr->GetUserId(), Err);
			return;
		}

		TriggerOnLoginCompleteDelegates(0, true, *UserAccountPtr->GetUserId(), "");
		GameInstance->GetSubsystem<UBeamRuntime>()->CPP_UnregisterOnUserReady(OnUserReadyCodeHandle);
	});

	FBeamWaitHandle WaitHandle;
	BeamableSubsystem->GetRequestTracker()->InvokeAndWaitForHooks(WaitHandle, OnBeamableUserReadyHook, HookWaitHandler, Slot, UserAccountPtr);
}
