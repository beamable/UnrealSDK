// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamUserSlots.h"

#include "BeamLogging.h"
#include "JsonObjectConverter.h"

void UBeamUserSlots::Initialize(FSubsystemCollectionBase& Collection)
{
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

bool UBeamUserSlots::GetUserDataAtSlot(const FUserSlot& SlotId, FBeamRealmUser& OutUserData) const
{
	if (AuthenticatedUserMapping.Contains(SlotId))
	{
		const auto idx = AuthenticatedUserMapping.FindChecked(SlotId);
		OutUserData = AuthenticatedUsers[idx];

		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Found User Data At Slot!\nUSER_SLOT=%s"), *SlotId.Name);
		return true;
	}
	OutUserData.AuthToken = FBeamAuthToken{TEXT(""), TEXT(""), 0};
	OutUserData.RealmHandle = FBeamRealmHandle{TEXT(""), TEXT("")};
	return false;
}

bool UBeamUserSlots::GetUserDataWithRefreshTokenAndPid(const FString& RefreshToken, const FString& Pid, FBeamRealmUser& OutUserData, FUserSlot& OutUserSlot) const
{
	for (const auto& UserMapping : AuthenticatedUserMapping)
	{
		OutUserData = AuthenticatedUsers[UserMapping.Value];
		if (OutUserData.AuthToken.RefreshToken == RefreshToken && OutUserData.RealmHandle.Pid == Pid)
		{
			OutUserSlot = UserMapping.Key;
			UE_LOG(LogBeamUserSlots, Verbose, TEXT("Found User Data with PID and RefreshToken At Slot!\nUSER_SLOT=%s"), *OutUserSlot.Name);
			return true;
		}
	}

	OutUserData.AuthToken = FBeamAuthToken{TEXT(""), TEXT(""), 0};
	OutUserData.RealmHandle = FBeamRealmHandle{TEXT(""), TEXT("")};
	return false;
}

void UBeamUserSlots::SetUserAtSlot(const FUserSlot& SlotId, const FString& AccessToken, const FString& RefreshToken, const int64& ExpiresIn, const FString& Cid, const FString& Pid)
{
	const auto AuthenticatedUser = FBeamAuthToken{AccessToken, RefreshToken, ExpiresIn};
	const auto UserRealmData = FBeamRealmHandle{Cid, Pid};
	const auto RealmUser = FBeamRealmUser{UserRealmData, AuthenticatedUser};

	if (!AuthenticatedUserMapping.Contains(SlotId))
	{
		AuthenticatedUsers.Add(RealmUser);
		AuthenticatedUserMapping.Add(SlotId, AuthenticatedUsers.Num() - 1);

		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Added User Data to slot!\nUSER_SLOT=%s"), *SlotId.Name);
	}
	else
	{
		const auto UserSlotIdx = AuthenticatedUserMapping.FindRef(SlotId);
		auto& ExistingRealmUser = AuthenticatedUsers[UserSlotIdx];
		ExistingRealmUser.RealmHandle = UserRealmData;
		ExistingRealmUser.AuthToken = AuthenticatedUser;

		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Updated User Data at slot!\nUSER_SLOT=%s"), *SlotId.Name);
	}
}

void UBeamUserSlots::SaveUserAtSlot(const FUserSlot& SlotId,
                                    const FString& AccessToken, const FString& RefreshToken, const int64& ExpiresIn,
                                    const FString& Cid, const FString& Pid)
{
	SetUserAtSlot(SlotId, AccessToken, RefreshToken, ExpiresIn, Cid, Pid);

	// Save the authenticated user to the slot.
	const auto SavedUserDataPath = GetSavedSlotPath(SlotId);
	const auto DataForSlot = FUserSlotSerializedData{
		AccessToken,
		RefreshToken,
		ExpiresIn,
		Cid,
		Pid
	};
	FString JsonSerializedDefaultData;
	ensureAlways(FJsonObjectConverter::UStructToJsonObjectString(DataForSlot, JsonSerializedDefaultData));

	if (FFileHelper::SaveStringToFile(*JsonSerializedDefaultData, *SavedUserDataPath))
	{
		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Saved User Slot File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *SlotId.Name, *SavedUserDataPath, *JsonSerializedDefaultData);
	}
	else
	{
		UE_LOG(LogBeamUserSlots, Error, TEXT("Failed to create Saved User Slot File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *SlotId.Name, *SavedUserDataPath, *JsonSerializedDefaultData);
	}
}

void UBeamUserSlots::ClearUserAtSlot(const FUserSlot& SlotId, const EUserSlotClearedReason& Reason, const bool& bShouldRemoveSavedData)
{
	if (FBeamRealmUser ClearedUserData; GetUserDataAtSlot(SlotId, ClearedUserData))
	{
		// Clear serialized data
		if (bShouldRemoveSavedData)
		{
			SaveUserAtSlot(SlotId, TEXT(""), TEXT(""), 0, TEXT(""),TEXT(""));
			UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared Saved User Slot!\nUSER_SLOT=%s"), *SlotId.Name);
		}

		// Remove Slot from list of loaded slots
		const auto LoadedAtIdx = AuthenticatedUserMapping.FindChecked(SlotId);
		AuthenticatedUsers.RemoveAt(LoadedAtIdx);
		AuthenticatedUserMapping.Remove(SlotId);

		// Broadcast events
		GlobalUserSlotClearedCodeHandler.Broadcast(Reason, SlotId, ClearedUserData);
		GlobalUserSlotClearedHandler.Broadcast(Reason, SlotId, ClearedUserData);

		UE_LOG(LogBeamUserSlots, Verbose, TEXT("Cleared Authenticated User at Slot!\nUSER_SLOT=%s"), *SlotId.Name);
	}
	else
	{
		UE_LOG(LogBeamUserSlots, Verbose, TEXT("No Authenticated User is loaded at Slot!\nUSER_SLOT=%s"), *SlotId.Name);
	}
}

FString UBeamUserSlots::GetSavedSlotPath(const FUserSlot& SlotId)
{
	return FPaths::ProjectSavedDir() / TEXT("Beamable") / TEXT("UserSlots") / SlotId.Name + TEXT(".json");
}

bool UBeamUserSlots::TryLoadSavedUserAtSlot(const FUserSlot& SlotId)
{
	FString SlotFile;
	const auto SavedUserDataPath = GetSavedSlotPath(SlotId);

	// If the file is there
	if (FFileHelper::LoadFileToString(SlotFile, *SavedUserDataPath))
	{
		// We try to deserialize the user slot data
		FUserSlotSerializedData SlotSerializedData;
		const auto DidDeserialize = FJsonObjectConverter::JsonObjectStringToUStruct(SlotFile, &SlotSerializedData);
		ensureAlwaysMsgf(DidDeserialize, TEXT("Failed deserialization of %s.json file.\nPath=%s"), *SlotId.Name, *SavedUserDataPath);

		// If the refresh token is there, we can do a quick authentication. 
		if (!SlotSerializedData.RefreshToken.IsEmpty())
		{
			const auto AccessToken = SlotSerializedData.AccessToken;
			const auto RefreshToken = SlotSerializedData.RefreshToken;
			const auto ExpiresIn = SlotSerializedData.ExpiresIn;
			const auto Cid = SlotSerializedData.Cid;
			const auto Pid = SlotSerializedData.Pid;

			SetUserAtSlot(SlotId, AccessToken, RefreshToken, ExpiresIn, Cid, Pid);
			UE_LOG(LogBeamUserSlots, Verbose, TEXT("Loaded user saved at slot!\nUSER_SLOT=%s, CID=%s, PID=%s"), *SlotId.Name, *Cid, *Pid);
			return true;
		}

		// If the refresh token ISN'T there, we fail the fast path for authentication of the user slot. 
		UE_LOG(LogBeamUserSlots, Verbose, TEXT("No user saved at slot!\nUSER_SLOT=%s."), *SlotId.Name);
		return false;
	}

	// If the file ISN'T there, we create the file with default values and fail the authentication.
	const auto DefaultDataForSlot = FUserSlotSerializedData{
		TEXT(""),
		TEXT(""),
		0,
		TEXT(""),
		TEXT("")
	};

	FString JsonSerializedDefaultData;
	ensureAlways(FJsonObjectConverter::UStructToJsonObjectString(DefaultDataForSlot, JsonSerializedDefaultData));

	UE_LOG(LogBeamUserSlots, Verbose, TEXT("No user saved at slot!\nUSER_SLOT=%s."), *SlotId.Name);

	FFileHelper::SaveStringToFile(*JsonSerializedDefaultData, *SavedUserDataPath);
	UE_LOG(LogBeamUserSlots, Verbose, TEXT("Saved Default Empty User Slot File!\nUSER_SLOT=%s\nFILE_PATH=%s\nFILE_CONTENTS=%s"), *SlotId.Name, *SavedUserDataPath, *JsonSerializedDefaultData);

	return false;
}
