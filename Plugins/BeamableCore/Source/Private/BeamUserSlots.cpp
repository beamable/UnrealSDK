// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamUserSlots.h"

#include "JsonObjectConverter.h"

void UBeamUserSlots::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Warning, TEXT("Initializing UBeamBackend Subsystem!"));

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
	}
	else
	{
		const auto UserSlotIdx = AuthenticatedUserMapping.FindRef(SlotId);
		auto& ExistingRealmUser = AuthenticatedUsers[UserSlotIdx];
		ExistingRealmUser.RealmHandle = UserRealmData;
		ExistingRealmUser.AuthToken = AuthenticatedUser;
	}
}

void UBeamUserSlots::AuthenticateUserAtSlot(const FUserSlot& SlotId,
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

	UE_LOG(LogTemp, Verbose, TEXT("Creating Default %s File\n\n%s"), *SlotId.SlotName, *JsonSerializedDefaultData);
	FFileHelper::SaveStringToFile(*JsonSerializedDefaultData, *SavedUserDataPath);
}

void UBeamUserSlots::ClearUserAtSlot(const FUserSlot& SlotId)
{
	AuthenticateUserAtSlot(SlotId, TEXT(""), TEXT(""), 0, TEXT(""),TEXT(""));
}

FString UBeamUserSlots::GetSavedSlotPath(const FUserSlot& SlotId)
{
	return FPaths::ProjectSavedDir() / TEXT("Beamable") / TEXT("UserSlots") / SlotId.SlotName + TEXT(".json");
}

bool UBeamUserSlots::TryAuthenticateSavedUserAtSlot(const FUserSlot& SlotId)
{
	FString SlotFile;
	const auto SavedUserDataPath = GetSavedSlotPath(SlotId);

	// If the file is there
	if (FFileHelper::LoadFileToString(SlotFile, *SavedUserDataPath))
	{
		// We try to deserialize the user slot data
		FUserSlotSerializedData SlotSerializedData;
		const auto DidDeserialize = FJsonObjectConverter::JsonObjectStringToUStruct(SlotFile, &SlotSerializedData);
		ensureAlwaysMsgf(DidDeserialize, TEXT("Failed deserialization of %s.json file.\nPath=%s"), *SlotId.SlotName, *SavedUserDataPath);

		// If the refresh token is there, we can do a quick authentication. 
		if (!SlotSerializedData.RefreshToken.IsEmpty())
		{
			const auto AccessToken = SlotSerializedData.AccessToken;
			const auto RefreshToken = SlotSerializedData.RefreshToken;
			const auto ExpiresIn = SlotSerializedData.ExpiresIn;
			const auto Cid = SlotSerializedData.Cid;
			const auto Pid = SlotSerializedData.Pid;

			SetUserAtSlot(SlotId, AccessToken, RefreshToken, ExpiresIn, Cid, Pid);
			return true;
		}

		// If the refresh token ISN'T there, we fail the fast path for authentication of the user slot. 
		UE_LOG(LogTemp, Verbose, TEXT("No user saved at slot %s."), *SlotId.SlotName);
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

	UE_LOG(LogTemp, Verbose, TEXT("No user saved at slot %s."), *SlotId.SlotName);
	UE_LOG(LogTemp, Verbose, TEXT("Creating Default %s File\n\n%s"), *SlotId.SlotName, *JsonSerializedDefaultData);
	FFileHelper::SaveStringToFile(*JsonSerializedDefaultData, *SavedUserDataPath);

	return false;
}
