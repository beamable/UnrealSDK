// Fill out your copyright notice in the Description page of Project Settings.


#include "UserSlots/BeamUserSlots.h"

#include "BeamCoreSettings.h"
#include "BeamLogging.h"
#include "JsonObjectConverter.h"
#include "HAL/FileManagerGeneric.h"

void UBeamUserSlots::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency(UBeamEnvironment::StaticClass());
	UE_LOG(LogBeamUserSlots, Display, TEXT("Initializing UBeamUserSlots Subsystem!"));

	// Prepare data structures to hold all authenticated user data. 
	AuthenticatedUsers.Reserve(128);
	AuthenticatedUserMapping.Reserve(128);
}

void UBeamUserSlots::Deinitialize()
{
	AuthenticatedUsers.Empty();
	AuthenticatedUserMapping.Empty();
}

FString UBeamUserSlots::GetSavedSlotsDirectory()
{
	return FPaths::ProjectSavedDir() / TEXT("Beamable") / TEXT("UserSlots");
}

FString UBeamUserSlots::GetSavedSlotAuthFilePath(FString NamespacedSlotId)
{
	return GetSavedSlotsDirectory() / NamespacedSlotId + TEXT("_Auth.json");
}

FString UBeamUserSlots::GetSavedSlotAccountFilePath(FString NamespacedSlotId)
{
	return GetSavedSlotsDirectory() / NamespacedSlotId + TEXT("_Account.json");
}

FString UBeamUserSlots::GetSlotDataSavedFilePath(FString SlotDataType, FUserSlot SlotId, const UObject* CallingContext)
{
	const auto NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext);
	return GetSavedSlotsDirectory() / NamespacedSlotId + TEXT("_") + SlotDataType + TEXT(".json");
}

bool UBeamUserSlots::IsPIEContext(const UObject* CallingContext)
{
#if WITH_EDITOR
	if (!CallingContext) return false;

	const auto WorldContext = GEngine->GetWorldContextFromWorld(CallingContext->GetWorld());
	return WorldContext && WorldContext->WorldType == EWorldType::PIE;
#else
	return false;
#endif
}

FString UBeamUserSlots::GetNamespacedSlotId(FUserSlot SlotId, const UObject* CallingContext)
{
#if WITH_EDITOR
	// If we are already a namespaced name, we just return it.
	if (SlotId.Name.StartsWith("PIE_"))
		return SlotId;

	if (CallingContext)
	{
		const auto WorldContext = GEngine->GetWorldContextFromWorld(CallingContext->GetWorld());
		if (WorldContext && WorldContext->WorldType == EWorldType::PIE)
		{
			// Format the namespace  
			return FString::Printf(TEXT("PIE_%d_%s"), WorldContext->PIEInstance, *SlotId.Name);
		}
	}
#endif

	return SlotId.Name;
}

FString UBeamUserSlots::GetNamespacedSlotId(FUserSlot SlotId, int32 PIEInstance)
{
#if WITH_EDITOR
	// If we are already a namespaced name, we just return it.
	if (SlotId.Name.StartsWith("PIE_"))
		return SlotId;

	// Format the namespace  
	return FString::Printf(TEXT("PIE_%d_%s"), PIEInstance, *SlotId.Name);

#else
	
	return SlotId.Name;

#endif
}

bool UBeamUserSlots::GetSlotIdFromNamespacedSlotId(const FString NamespacedSlotId, FUserSlot& OutUserSlot)
{
	// If we start with PIE, we'll have the following format: PIE_-1_UserSlotName
	if (int LastUnderscoreIdx = -1; NamespacedSlotId.StartsWith("PIE_") && NamespacedSlotId.FindLastChar('_', LastUnderscoreIdx))
	{
		// So we extract only the user slot name from it.
		OutUserSlot = NamespacedSlotId.RightChop(LastUnderscoreIdx + 1);
		return true;
	}

	OutUserSlot = NamespacedSlotId;
	return false;
}

bool UBeamUserSlots::IsSameSlot(FUserSlot SlotA, FUserSlot SlotB, const UObject* SlotAContext, const UObject* SlotBContext)
{
	const auto SlotANamespacedId = GetNamespacedSlotId(SlotA, SlotAContext);
	const auto SlotBNamespacedId = GetNamespacedSlotId(SlotB, SlotBContext);

	return SlotANamespacedId.Equals(SlotBNamespacedId);
}

TArray<FUserSlot> UBeamUserSlots::GetKnownSlots()
{
	TArray<FUserSlot> KnownSlots = {};
	for (const auto& UserMapping : AuthenticatedUserMapping)
	{
		const auto NamespacedSlotId = UserMapping.Key;
		FUserSlot Slot;
		GetSlotIdFromNamespacedSlotId(NamespacedSlotId, Slot);
		if (!KnownSlots.Contains(Slot))
			KnownSlots.Add(Slot);
	}
	return KnownSlots;
}

bool UBeamUserSlots::GetUserDataAtSlot(FUserSlot SlotId, FBeamRealmUser& OutUserData, const UObject* CallingContext) const
{
	if (const FString NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext); AuthenticatedUserMapping.Contains(NamespacedSlotId))
	{
		const auto idx = AuthenticatedUserMapping.FindChecked(NamespacedSlotId);
		OutUserData = AuthenticatedUsers[idx];

		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Found User Data At Slot!\nUSER_SLOT=%s"), *NamespacedSlotId);
		return true;
	}

	OutUserData.AccountId = -1;
	OutUserData.GamerTag = -1;
	OutUserData.Email = TEXT("");
	OutUserData.AuthToken = FBeamAuthToken{TEXT(""), TEXT(""), 0};
	OutUserData.RealmHandle = FBeamRealmHandle{FString(""), FString("")};

	return false;
}

bool UBeamUserSlots::GetUserDataWithGamerTag(const FBeamGamerTag& GamerTag, FBeamRealmUser& OutUserData, FUserSlot& OutUserSlot, FString& NamespacedSlotId) const
{
	for (const auto& UserMapping : AuthenticatedUserMapping)
	{
		OutUserData = AuthenticatedUsers[UserMapping.Value];
		if (OutUserData.GamerTag == GamerTag)
		{
			NamespacedSlotId = UserMapping.Key;
			GetSlotIdFromNamespacedSlotId(NamespacedSlotId, OutUserSlot);
			UE_LOG(LogBeamUserSlots, Verbose, TEXT("Found User Data with PID and RefreshToken At Slot!\nUSER_SLOT=%s"), *OutUserSlot.Name);
			return true;
		}
	}

	OutUserData.AccountId = -1;
	OutUserData.GamerTag = -1;
	OutUserData.Email = TEXT("");
	OutUserData.AuthToken = FBeamAuthToken{TEXT(""), TEXT(""), 0};
	OutUserData.RealmHandle = FBeamRealmHandle{FString(""), FString("")};

	OutUserSlot.Name = TEXT("");
	return false;
}

bool UBeamUserSlots::GetUserDataWithRefreshTokenAndPid(const FString& RefreshToken, const FBeamPid& Pid, FBeamRealmUser& OutUserData, FUserSlot& OutUserSlot, FString& NamespacedSlotId) const
{
	for (const auto& UserMapping : AuthenticatedUserMapping)
	{
		OutUserData = AuthenticatedUsers[UserMapping.Value];
		if (OutUserData.AuthToken.RefreshToken == RefreshToken && OutUserData.RealmHandle.Pid == Pid)
		{
			NamespacedSlotId = UserMapping.Key;
			GetSlotIdFromNamespacedSlotId(NamespacedSlotId, OutUserSlot);
			UE_LOG(LogBeamUserSlots, Verbose, TEXT("Found User Data with PID and RefreshToken At Slot!\nUSER_SLOT=%s"), *OutUserSlot.Name);
			return true;
		}
	}

	OutUserData.AccountId = -1;
	OutUserData.GamerTag = -1;
	OutUserData.Email = TEXT("");
	OutUserData.AuthToken = FBeamAuthToken{TEXT(""), TEXT(""), 0};
	OutUserData.RealmHandle = FBeamRealmHandle{FString(""), FString("")};

	OutUserSlot.Name = TEXT("");
	return false;
}

void UBeamUserSlots::SetAuthenticationDataAtNamespacedSlot(const FString& NamespacedSlotId, const FString& AccessToken, const FString& RefreshToken, const int64& IssuedAt, const int64& ExpiresIn,
                                                           const FBeamCid& Cid, const FBeamPid& Pid)
{
	const auto AuthenticatedUser = FBeamAuthToken{AccessToken, RefreshToken, ExpiresIn, IssuedAt};
	const auto UserRealmData = FBeamRealmHandle{Cid, Pid};
	const auto RealmUser = FBeamRealmUser{-1, -1, TEXT(""), UserRealmData, AuthenticatedUser};

	if (!AuthenticatedUserMapping.Contains(NamespacedSlotId))
	{
		AuthenticatedUsers.Add(RealmUser);
		AuthenticatedUserMapping.Add(NamespacedSlotId, AuthenticatedUsers.Num() - 1);

		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Added User Data to slot!\nUSER_SLOT=%s"), *NamespacedSlotId);
	}
	else
	{
		const auto UserSlotIdx = AuthenticatedUserMapping.FindRef(NamespacedSlotId);
		auto& ExistingRealmUser = AuthenticatedUsers[UserSlotIdx];
		ExistingRealmUser.RealmHandle = UserRealmData;
		ExistingRealmUser.AuthToken = AuthenticatedUser;

		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Updated User Data at slot!\nUSER_SLOT=%s"), *NamespacedSlotId);
	}
}

void UBeamUserSlots::SetAuthenticationDataAtSlot(FUserSlot SlotId, const FString& AccessToken, const FString& RefreshToken, const int64& IssuedAt, const int64& ExpiresIn, const FBeamCid& Cid,
                                                 const FBeamPid& Pid, const UObject* CallingContext)
{
	const auto NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext);
	SetAuthenticationDataAtNamespacedSlot(NamespacedSlotId, AccessToken, RefreshToken, IssuedAt, ExpiresIn, Cid, Pid);
}

void UBeamUserSlots::SetGamerTagAtSlot(FUserSlot SlotId, const FBeamGamerTag& GamerTag, const UObject* CallingContext)
{
	const auto NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext);

	// This is here since you need to be authenticated to get the gamer tag anyways...
	ensureAlwaysMsgf(AuthenticatedUserMapping.Contains(NamespacedSlotId), TEXT("This must always be called after SetAuthenticationDataAtSlot."));

	const auto UserSlotIdx = AuthenticatedUserMapping.FindRef(NamespacedSlotId);
	auto& ExistingRealmUser = AuthenticatedUsers[UserSlotIdx];
	ExistingRealmUser.GamerTag = GamerTag;

	UE_LOG(LogBeamUserSlots, Verbose, TEXT("Updated GamerTag at slot!\nUSER_SLOT=%s, GAMERTAG=%llu"), *NamespacedSlotId, GamerTag.AsLong);
}

void UBeamUserSlots::SetAccountIdAtSlot(FUserSlot SlotId, const FBeamAccountId& AccountId, const UObject* CallingContext)
{
	const auto NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext);

	// This is here since you need to be authenticated to get the gamer tag anyways...
	ensureAlwaysMsgf(AuthenticatedUserMapping.Contains(NamespacedSlotId), TEXT("This must always be called after SetAuthenticationDataAtSlot."));

	const auto UserSlotIdx = AuthenticatedUserMapping.FindRef(NamespacedSlotId);
	auto& ExistingRealmUser = AuthenticatedUsers[UserSlotIdx];
	ExistingRealmUser.AccountId = AccountId;

	UE_LOG(LogBeamUserSlots, Verbose, TEXT("Updated GamerTag at slot!\nUSER_SLOT=%s, GAMERTAG=%llu"), *NamespacedSlotId, AccountId.AsLong);
}


void UBeamUserSlots::SetEmailAtSlot(FUserSlot SlotId, const FString& Email, const UObject* CallingContext)
{
	const auto NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext);

	// This is here since you need to be authenticated to get the email anyways...
	ensureAlwaysMsgf(AuthenticatedUserMapping.Contains(NamespacedSlotId), TEXT("This must always be called after SetAuthenticationDataAtSlot."));

	const auto UserSlotIdx = AuthenticatedUserMapping.FindRef(NamespacedSlotId);
	auto& ExistingRealmUser = AuthenticatedUsers[UserSlotIdx];
	ExistingRealmUser.Email = Email;

	UE_LOG(LogBeamUserSlots, Verbose, TEXT("Updated Email at slot!\nUSER_SLOT=%s, EMAIL=%s"), *NamespacedSlotId, *Email);
}

void UBeamUserSlots::SetPIDAtSlot(FUserSlot SlotId, const FBeamPid& Pid, const UObject* CallingContext)
{
	const auto NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext);

	// This is here since you need to be authenticated to get the email anyways...
	ensureAlwaysMsgf(AuthenticatedUserMapping.Contains(NamespacedSlotId), TEXT("This must always be called after SetAuthenticationDataAtSlot."));

	const auto UserSlotIdx = AuthenticatedUserMapping.FindRef(NamespacedSlotId);
	auto& ExistingRealmUser = AuthenticatedUsers[UserSlotIdx];
	ExistingRealmUser.RealmHandle.Pid = Pid;

	UE_LOG(LogBeamUserSlots, Verbose, TEXT("Updated PID at slot!\nUSER_SLOT=%s, PID=%s"), *NamespacedSlotId, *Pid.AsString);
}

void UBeamUserSlots::SetExternalIdsAtSlot(const FUserSlot& SlotId, const TArray<FBeamExternalIdentity> ExternalIdentities, const UObject* CallingContext)
{
	const auto NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext);

	// This is here since you need to be authenticated to get the email anyways...
	ensureAlwaysMsgf(AuthenticatedUserMapping.Contains(NamespacedSlotId), TEXT("This must always be called after SetAuthenticationDataAtSlot."));

	const auto UserSlotIdx = AuthenticatedUserMapping.FindRef(NamespacedSlotId);
	auto& ExistingRealmUser = AuthenticatedUsers[UserSlotIdx];
	ExistingRealmUser.ExternalIdentities = ExternalIdentities;

	FString Identities;
	for (FBeamExternalIdentity ExternalIdentity : ExternalIdentities)
		Identities += FString::Printf(TEXT("%s/%s:%s, "), *ExternalIdentity.ProviderService, *ExternalIdentity.ProviderNamespace, *ExternalIdentity.UserId);

	UE_LOG(LogBeamUserSlots, Verbose, TEXT("Updated Email at slot!\nUSER_SLOT=%s, IDENTITIES=[%s]"), *NamespacedSlotId, *Identities);
}

void UBeamUserSlots::TriggerUserAuthenticatedIntoSlot(FUserSlot SlotId, FBeamOperationHandle AuthOp, const UObject* CallingContext)
{
	// Gets the auth'ed user
	FBeamRealmUser AuthenticatedUser;
	GetUserDataAtSlot(SlotId, AuthenticatedUser, CallingContext);

	// Broadcast events
	GlobalUserSlotAuthenticatedCodeHandler.Broadcast(SlotId, AuthenticatedUser, AuthOp, CallingContext);
	GlobalUserSlotAuthenticatedHandler.Broadcast(SlotId, AuthenticatedUser, AuthOp, CallingContext);
}


bool UBeamUserSlots::SaveSlot(FUserSlot SlotId, const UObject* CallingContext)
{
	// When we are running in PIE, we only save if we are configured to do so. Otherwise, we just act like we did. 
#if WITH_EDITOR
	if (IsPIEContext(CallingContext) && !GetDefault<UBeamCoreSettings>()->bPersistRuntimeSlotDataWhenInPIE)
		return true;
#endif

	const auto NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext);

	FBeamRealmUser User;
	const auto bWasAuthenticated = GetUserDataAtSlot(SlotId, User, CallingContext);

#if !WITH_EDITOR
		ensureAlwaysMsgf(!User.RealmHandle.Pid.AsString.IsEmpty(), TEXT("Customer-Scoped Tokens are not allowed in builds! If should never be seeing this!"));
#endif

	// Save the User's Auth data to the slot.
	const auto SavedUserAuthDataPath = GetSavedSlotAuthFilePath(NamespacedSlotId);
	const auto AuthDataForSlot = FUserSlotAuthData{
		User.AuthToken.AccessToken,
		User.AuthToken.RefreshToken,
		User.AuthToken.ExpiresIn,
		User.AuthToken.IssuedAt,
		User.RealmHandle.Cid,
		User.RealmHandle.Pid
	};
	FString JsonSerializedAuthData;
	ensureAlways(FJsonObjectConverter::UStructToJsonObjectString(AuthDataForSlot, JsonSerializedAuthData));

	if (FFileHelper::SaveStringToFile(*JsonSerializedAuthData, *SavedUserAuthDataPath))
	{
		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Saved User Slot - Auth File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAuthDataPath, *JsonSerializedAuthData);
	}
	else
	{
		UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to create Saved User Slot - Auth File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAuthDataPath,
		       *JsonSerializedAuthData);
	}

	// Save the User Account data to the slot.
	const auto SavedUserAccountDataPath = GetSavedSlotAccountFilePath(NamespacedSlotId);
	const auto AccountDataForSlot = FUserSlotAccountData{
		User.AccountId,
		User.GamerTag,
		User.Email,
		User.ExternalIdentities,
	};
	FString JsonSerializedAccountData;
	ensureAlways(FJsonObjectConverter::UStructToJsonObjectString(AccountDataForSlot, JsonSerializedAccountData));

	if (FFileHelper::SaveStringToFile(*JsonSerializedAccountData, *SavedUserAccountDataPath))
	{
		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Saved User Slot - Account File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAccountDataPath,
		       *JsonSerializedAccountData);
	}
	else
	{
		UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to create Saved User Slot - Account File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAccountDataPath,
		       *JsonSerializedAccountData);
	}

	return bWasAuthenticated;
}

void UBeamUserSlots::DeleteUserSlotCacheForPIE()
{
	const auto savedSlots = GetSavedSlotsDirectory();
	TArray<FString> Files;
	FPlatformFileManager::Get().GetPlatformFile().FindFiles(Files, *GetSavedSlotsDirectory(), TEXT(".json"));
	for (FString File : Files)
	{
		if (File.Contains("PIE_"))
		{
			FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*File);
		}
	}
}

void UBeamUserSlots::ClearUserAtSlot(FUserSlot SlotId, const EUserSlotClearedReason& Reason, const bool& bShouldRemoveSavedData, const UObject* CallingContext)
{
	const auto NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext);
	if (FBeamRealmUser ClearedUserData; GetUserDataAtSlot(SlotId, ClearedUserData, CallingContext))
	{
		// Clear serialized data
		if (bShouldRemoveSavedData)
		{
			// Save the User's Auth data to the slot.
			const auto SavedUserAuthDataPath = GetSavedSlotAuthFilePath(NamespacedSlotId);
			const auto AuthDataForSlot = FUserSlotAuthData{TEXT(""), TEXT(""), 0, 0, FString(""), FString("")};
			FString JsonSerializedAuthData;
			ensureAlways(FJsonObjectConverter::UStructToJsonObjectString(AuthDataForSlot, JsonSerializedAuthData));

			if (FFileHelper::SaveStringToFile(*JsonSerializedAuthData, *SavedUserAuthDataPath))
			{
				UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared User Slot - Auth File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAuthDataPath,
				       *JsonSerializedAuthData);
			}
			else
			{
				UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to clear User Slot - Auth File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAuthDataPath,
				       *JsonSerializedAuthData);
			}

			// Save the User Account data to the slot.
			const auto SavedUserAccountDataPath = GetSavedSlotAccountFilePath(NamespacedSlotId);

			const auto AccountDataForSlot = FUserSlotAccountData{-1, -1, TEXT("")};
			FString JsonSerializedAccountData;
			ensureAlways(FJsonObjectConverter::UStructToJsonObjectString(AccountDataForSlot, JsonSerializedAccountData));

			if (FFileHelper::SaveStringToFile(*JsonSerializedAccountData, *SavedUserAccountDataPath))
			{
				UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared User Slot - Account File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAccountDataPath,
				       *JsonSerializedAccountData);
			}
			else
			{
				UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to clear User Slot - Account File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAccountDataPath,
				       *JsonSerializedAccountData);
			}

			UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared Saved User Slot!\nUSER_SLOT=%s"), *SlotId.Name);
		}

		// Remove Slot from list of loaded slots
		const auto LoadedAtIdx = AuthenticatedUserMapping.FindChecked(NamespacedSlotId);
		AuthenticatedUsers.RemoveAt(LoadedAtIdx);
		AuthenticatedUserMapping.Remove(NamespacedSlotId);

		if (LoadedAtIdx < AuthenticatedUsers.Num())
		{
			// We need to update the mapping for all the slots that were loaded after the one we just removed.
			for (auto& UserMapping : AuthenticatedUserMapping)
			{
				if (UserMapping.Value > LoadedAtIdx)
				{
					UserMapping.Value--;
				}
			}
		}

		// Broadcast events
		GlobalUserSlotClearedCodeHandler.Broadcast(Reason, SlotId, ClearedUserData, CallingContext);
		GlobalUserSlotClearedHandler.Broadcast(Reason, SlotId, ClearedUserData, CallingContext);

		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared Authenticated User at Slot!\nUSER_SLOT=%s"), *NamespacedSlotId);
	}
	else
	{
		UE_LOG(LogBeamUserSlots, Verbose, TEXT("No Authenticated User is loaded at Slot!\nUSER_SLOT=%s"), *NamespacedSlotId);
	}
}

void UBeamUserSlots::ClearAllCachedUserDataAtSlot(FUserSlot SlotId)
{
	TArray<FString> AllCachedUserSlots;
	FFileManagerGeneric::Get().FindFiles(AllCachedUserSlots, *GetSavedSlotsDirectory(),TEXT(".json"));

	for (const auto& CachedUserSlotDataFile : AllCachedUserSlots)
	{
		if (!CachedUserSlotDataFile.Contains(SlotId.Name)) continue;

		if (CachedUserSlotDataFile.Contains(TEXT("_Auth.json")))
		{
			// Save the User's Auth data to the slot.
			const auto SavedUserAuthDataPath = GetSavedSlotsDirectory() / CachedUserSlotDataFile;
			const auto AuthDataForSlot = FUserSlotAuthData{TEXT(""), TEXT(""), 0, 0, FString(""), FString("")};
			FString JsonSerializedAuthData;
			ensureAlways(FJsonObjectConverter::UStructToJsonObjectString(AuthDataForSlot, JsonSerializedAuthData));

			if (FFileHelper::SaveStringToFile(*JsonSerializedAuthData, *SavedUserAuthDataPath))
			{
				UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared User Slot - Auth File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *SlotId.Name, *SavedUserAuthDataPath,
				       *JsonSerializedAuthData);
			}
			else
			{
				UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to clear User Slot - Auth File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *SlotId.Name, *SavedUserAuthDataPath,
				       *JsonSerializedAuthData);
			}
		}

		if (CachedUserSlotDataFile.Contains("_Account.json"))
		{
			// Save the User Account data to the slot.
			const auto SavedUserAccountDataPath = GetSavedSlotsDirectory() / CachedUserSlotDataFile;

			const auto AccountDataForSlot = FUserSlotAccountData{-1, -1, TEXT("")};
			FString JsonSerializedAccountData;
			ensureAlways(FJsonObjectConverter::UStructToJsonObjectString(AccountDataForSlot, JsonSerializedAccountData));

			if (FFileHelper::SaveStringToFile(*JsonSerializedAccountData, *SavedUserAccountDataPath))
			{
				UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared User Slot - Account File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *SlotId.Name, *SavedUserAccountDataPath,
				       *JsonSerializedAccountData);
			}
			else
			{
				UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to clear User Slot - Account File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *SlotId.Name, *SavedUserAccountDataPath,
				       *JsonSerializedAccountData);
			}
		}

		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared Saved User Slot!\nUSER_SLOT=%s"), *SlotId.Name);
	}
}

void UBeamUserSlots::ClearAllCachedUserDataAtNamespacedSlot(FString NamespacedSlot)
{
	TArray<FString> AllCachedUserSlots;
	IFileManager::Get().FindFiles(AllCachedUserSlots, *GetSavedSlotsDirectory(),TEXT(".json"));

	for (const auto& CachedUserSlotDataFile : AllCachedUserSlots)
	{
		if (!CachedUserSlotDataFile.Contains(NamespacedSlot)) continue;

		if (CachedUserSlotDataFile.Contains(TEXT("_Auth.json")))
		{			
			const auto SavedUserAuthDataPath = GetSavedSlotsDirectory() / CachedUserSlotDataFile;
			if (IFileManager::Get().Delete(*SavedUserAuthDataPath))
			{
				UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared User Slot - Auth File!\nUSER_SLOT=%s\nFILE_PATH=%s"), *NamespacedSlot, *SavedUserAuthDataPath);
			}
			else
			{
				UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to clear User Slot - Auth File!\nUSER_SLOT=%s\nFILE_PATH=%s"), *NamespacedSlot, *SavedUserAuthDataPath);
			}
		}

		if (CachedUserSlotDataFile.Contains("_Account.json"))
		{
			// Save the User Account data to the slot.
			const auto SavedUserAccountDataPath = GetSavedSlotsDirectory() / CachedUserSlotDataFile;			
			if (IFileManager::Get().Delete(*SavedUserAccountDataPath))
			{
				UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared User Slot - Account File!\nUSER_SLOT=%s\nFILE_PATH=%s"), *NamespacedSlot, *SavedUserAccountDataPath);
			}
			else
			{
				UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to clear User Slot - Account File!\nUSER_SLOT=%s\nFILE_PATH=%s"), *NamespacedSlot, *SavedUserAccountDataPath);
			}
		}

		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared Saved User Slot!\nUSER_SLOT=%s"), *NamespacedSlot);
	}
}

bool UBeamUserSlots::IsUserSlotAuthenticated(FUserSlot SlotId, const UObject* CallingContext)
{
	return AuthenticatedUserMapping.Contains(GetNamespacedSlotId(SlotId, CallingContext));
}


int32 UBeamUserSlots::TryLoadSavedUserAtSlotAndAuth(FUserSlot SlotId, UObject* CallingContext)
{
	FUserSlotAuthData SlotSerializedAuthData;
	FUserSlotAccountData SlotSerializedAccountData;
	const auto Ret = TryLoadSavedUserAtSlot(SlotId, SlotSerializedAuthData, SlotSerializedAccountData, CallingContext);
	if (Ret != LoadSavedUserResult_Failed)
	{
		const auto AccessToken = SlotSerializedAuthData.AccessToken;
		const auto RefreshToken = SlotSerializedAuthData.RefreshToken;
		const auto ExpiresIn = SlotSerializedAuthData.ExpiresIn;
		const auto Cid = SlotSerializedAuthData.Cid;
		auto Pid = SlotSerializedAuthData.Pid;

		SetAuthenticationDataAtSlot(SlotId, AccessToken, RefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), ExpiresIn, Cid, Pid, CallingContext);
		SetAccountIdAtSlot(SlotId, SlotSerializedAccountData.AccountId, CallingContext);
		SetGamerTagAtSlot(SlotId, SlotSerializedAccountData.GamerTag, CallingContext);
		SetEmailAtSlot(SlotId, SlotSerializedAccountData.Email, CallingContext);
		SetExternalIdsAtSlot(SlotId, SlotSerializedAccountData.ExternalIdentities, CallingContext);
	}
	return Ret;
}

int32 UBeamUserSlots::TryLoadSavedUserAtSlot(FUserSlot SlotId, FUserSlotAuthData& OutAuthData, FUserSlotAccountData& OutAccountData, UObject* CallingContext)
{
	FString NamespacedSlotId = GetNamespacedSlotId(SlotId, CallingContext);
	return TryLoadSavedUserAtNamespacedSlot(NamespacedSlotId, OutAuthData, OutAccountData);
}


int32 UBeamUserSlots::TryLoadSavedUserAtNamespacedSlot(FString NamespacedSlotId, FUserSlotAuthData& OutAuthData, FUserSlotAccountData& OutAccountData)
{
	FString SlotAuthFile;
	FString SlotAccountFile;
	const auto SavedAuthDataPath = GetSavedSlotAuthFilePath(NamespacedSlotId);
	const auto SavedAccountDataPath = GetSavedSlotAccountFilePath(NamespacedSlotId);

	bool bLoadedAuthFile = FFileHelper::LoadFileToString(SlotAuthFile, *SavedAuthDataPath);
	bool bLoadedAccountFile = FFileHelper::LoadFileToString(SlotAccountFile, *SavedAccountDataPath);

	// Both files must be there for us to be considered authenticated.
	// If they are not, we'll force the user to re-authenticate.
	if (bLoadedAuthFile && bLoadedAccountFile)
	{
		// We try to deserialize the user slot data
		OutAuthData = {};
		const auto DidDeserializeAuthData = FJsonObjectConverter::JsonObjectStringToUStruct(SlotAuthFile, &OutAuthData);
		ensureAlwaysMsgf(DidDeserializeAuthData, TEXT("Failed deserialization of %s_Auth.json file.\nPath=%s"), *NamespacedSlotId, *SavedAuthDataPath);

		// If the refresh token is there, we can do a quick authentication. 
		if (!OutAuthData.RefreshToken.IsEmpty())
		{
			const auto AccessToken = OutAuthData.AccessToken;
			const auto RefreshToken = OutAuthData.RefreshToken;
			const auto ExpiresIn = OutAuthData.ExpiresIn;
			const auto Cid = OutAuthData.Cid;
			auto Pid = OutAuthData.Pid;

			// We only consider ourselves authenticated if the realm is the same as it was saved.
			const auto TargetRealm = GetDefault<UBeamCoreSettings>()->TargetRealm;
			if (Cid == TargetRealm.Cid && Pid == TargetRealm.Pid)
			{
				// We try to deserialize the user slot data
				OutAccountData = {};
				const auto DidDeserializeAccountData = FJsonObjectConverter::JsonObjectStringToUStruct(SlotAccountFile, &OutAccountData);
				ensureAlwaysMsgf(DidDeserializeAccountData, TEXT("Failed deserialization of %s_Account.json file.\nPath=%s"), *NamespacedSlotId, *SavedAccountDataPath);

				UE_LOG(LogBeamUserSlots, Verbose, TEXT("Loaded user saved at slot!\nUSER_SLOT=%s, CID=%s, PID=%s"), *NamespacedSlotId, *Cid.AsString, *Pid.AsString);
				return OutAuthData.IsExpired() ? LoadSavedUserResult_ExpiredToken : LoadSavedUserResult_Success;
			}

			UE_LOG(LogBeamUserSlots, Warning, TEXT("Failed to load user saved at slot!\nUSER_SLOT=%s, CID=%s, PID=%s, TARGET_CID=%s, TARGET_PID=%s"), *NamespacedSlotId, *Cid.AsString, *Pid.AsString,
			       *TargetRealm.Cid.AsString, *TargetRealm.Pid.AsString);

			return LoadSavedUserResult_Failed;
		}


		// If the refresh token ISN'T there OR if we are now attempting sign-in into a different realm, we fail the fast path for authentication of the user slot. 
		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Invalid user saved at slot!\nUSER_SLOT=%s."), *NamespacedSlotId);
		return LoadSavedUserResult_Failed;
	}

	UE_LOG(LogBeamUserSlots, Verbose, TEXT("No user saved at slot!\nUSER_SLOT=%s."), *NamespacedSlotId);
	return LoadSavedUserResult_Failed;
}

#if WITH_EDITOR
void UBeamUserSlots::GetPiePrefix(const FString& Str, FString& PiePrefix)
{
	const auto String = Str;
	if (String.StartsWith(TEXT("PIE_")))
	{
		PiePrefix = String.Left(FString(TEXT("PIE_N_")).Len());
		return;
	}

	PiePrefix = TEXT("");
}

void UBeamUserSlots::RemovePiePrefix(const FString& Str, FString& WithoutPiePrefix)
{
	const auto String = Str;
	if (String.StartsWith(TEXT("PIE_")))
	{
		WithoutPiePrefix = String.RightChop(FString(TEXT("PIE_N_")).Len());
		return;
	}

	WithoutPiePrefix = Str;
}
#endif

/**
   ______                           __               ______                                             __  
  / ____/___ _____ ___  ___  ____  / /___ ___  __   / ____/________ _____ ___  ___ _      ______  _____/ /__
 / / __/ __ `/ __ `__ \/ _ \/ __ \/ / __ `/ / / /  / /_  / ___/ __ `/ __ `__ \/ _ \ | /| / / __ \/ ___/ //_/
/ /_/ / /_/ / / / / / /  __/ /_/ / / /_/ / /_/ /  / __/ / /  / /_/ / / / / / /  __/ |/ |/ / /_/ / /  / ,<   
\____/\__,_/_/ /_/ /_/\___/ .___/_/\__,_/\__, /  /_/   /_/   \__,_/_/ /_/ /_/\___/|__/|__/\____/_/  /_/|_|  
					 /_/            /____/                                                              
 */

FUniqueNetIdRepl UBeamUserSlots::GetUniqueNetIdForSlot(FUserSlot Slot, UObject* CallingContext)
{
	if (const auto& LocalPlayer = GetLocalPlayerForSlot(Slot, CallingContext))
		return LocalPlayer->GetUniqueNetIdForPlatformUser();
	return FUniqueNetIdRepl::Invalid();
}

APlayerController* UBeamUserSlots::GetPlayerControllerForSlot(FUserSlot Slot, UObject* CallingContext)
{
	if (const auto& LocalPlayer = GetLocalPlayerForSlot(Slot, CallingContext))
		return LocalPlayer->GetPlayerController(CallingContext->GetWorld());
	return nullptr;
}

ULocalPlayer* UBeamUserSlots::GetLocalPlayerForSlot(FUserSlot Slot, UObject* CallingContext)
{
	const auto MappedIdx = GetKnownSlots().Find(Slot);
	if (MappedIdx != INDEX_NONE)
	{
		if (const auto& LocalPlayer = CallingContext->GetWorld()->GetGameInstance()->GetLocalPlayerByIndex(MappedIdx))
			return LocalPlayer;
	}
	else if (Slot.IsTestSlot())
	{
		// In test slots, you can add a "_Local_NUM" to map it to a local player
		if (Slot.Name.Contains("_Local"))
		{
			const auto LocalStartIdx = Slot.Name.Find(TEXT("Local"));
			const auto Local = Slot.Name.RightChop(LocalStartIdx);

			TArray<FString> LocalArr;
			Local.ParseIntoArray(LocalArr, TEXT("_"));
			if (LocalArr.Num() >= 2)
			{
				const auto LocalIdxStr = LocalArr[1];
				int32 LocalIdx;
				if (FDefaultValueHelper::ParseInt(LocalIdxStr, LocalIdx))
				{
					if (const auto& LocalPlayer = CallingContext->GetWorld()->GetGameInstance()->GetLocalPlayerByIndex(LocalIdx))
						return LocalPlayer;
				}
			}
		}
	}

	return nullptr;
}

void UBeamUserSlots::SaveSlot(FUserSlot SlotId, int32 PIEInstance, int64 GamerTag, const FString& AccessToken, const FString& RefreshToken, const int64& IssuedAt, const int64& ExpiresIn, const FBeamCid& Cid,
                              const FBeamPid& Pid)
{
	// When we are running in PIE, we only save if we are configured to do so. Otherwise, we just act like we did. 
#if WITH_EDITOR
	if (!GetDefault<UBeamCoreSettings>()->bPersistRuntimeSlotDataWhenInPIE)
		return;
#endif

	const auto NamespacedSlotId = GetNamespacedSlotId(SlotId, PIEInstance);

	// Save the User's Auth data to the slot.
	const auto SavedUserAuthDataPath = GetSavedSlotAuthFilePath(NamespacedSlotId);
	const auto AuthDataForSlot = FUserSlotAuthData{
		AccessToken,
		RefreshToken,
		ExpiresIn,
		IssuedAt,
		Cid,
		Pid
	};
	FString JsonSerializedAuthData;
	ensureAlways(FJsonObjectConverter::UStructToJsonObjectString(AuthDataForSlot, JsonSerializedAuthData));

	if (FFileHelper::SaveStringToFile(*JsonSerializedAuthData, *SavedUserAuthDataPath))
	{
		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Saved User Slot - Auth File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAuthDataPath, *JsonSerializedAuthData);
	}
	else
	{
		UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to create Saved User Slot - Auth File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAuthDataPath,
		       *JsonSerializedAuthData);
	}

	// Save the User Account data to the slot.
	const auto SavedUserAccountDataPath = GetSavedSlotAccountFilePath(NamespacedSlotId);
	const auto AccountDataForSlot = FUserSlotAccountData{
		FBeamAccountId(),
		FBeamGamerTag(GamerTag),
		"",
		{},
	};
	FString JsonSerializedAccountData;
	ensureAlways(FJsonObjectConverter::UStructToJsonObjectString(AccountDataForSlot, JsonSerializedAccountData));

	if (FFileHelper::SaveStringToFile(*JsonSerializedAccountData, *SavedUserAccountDataPath))
	{
		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Saved User Slot - Account File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAccountDataPath,
		       *JsonSerializedAccountData);
	}
	else
	{
		UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to create Saved User Slot - Account File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *NamespacedSlotId, *SavedUserAccountDataPath,
		       *JsonSerializedAccountData);
	}
}
