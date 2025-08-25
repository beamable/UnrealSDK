// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PIE/BeamPIE_Settings.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerCreateUserBatchCommand.h"
#include "Subsystems/CLI/Autogen/StreamData/DeveloperUserDataStreamData.h"

#include "BeamUserDeveloperManagerEditor.generated.h"

UENUM(BlueprintType)
enum EBeamDeveloperUserType
{
	BEAM_CAPTURED = 0,
	BEAM_LOCAL = 1,
	BEAM_SHARED = 2
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamUserDeveloperManagerEditor : public UBeamEditorSubsystem
{
	static constexpr int32 DEVELOPER_USER_TYPE_LOCAL = 1;
	static constexpr int32 DEVELOPER_USER_TYPE_SHARED = 2;

	static constexpr int32 EVT_TYPE_FullRebuild = 0;
	static constexpr int32 EVT_TYPE_ChangedUserInfo = 1;

	static constexpr int32 CLI_ERROR_BACKEND = 400;
	static constexpr int32 CLI_ERROR_UNKNOWN_BACKEND = 500;
	static constexpr int32 CLI_ERROR_SAVE_FILE = 300;

	const FString DEVELOPER_USER_NEW_USER_NAME = "New User";
	
	GENERATED_BODY()


	UPROPERTY()
	UBeamCli* BeamCli;

	UPROPERTY()
	UBeamUserSlots* BeamUserSlots;

	UPROPERTY()
	TMap<FBeamGamerTag, UDeveloperUserDataStreamData*> LocalUserDeveloperCache;

	/**
	 * @brief Stored lambda delegate handle for what this subsystem does when a user slot is authenticated.
	 */
	FDelegateHandle UserSlotAuthenticatedHandler;


	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

public:
	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnDeveloperUserInfoFullRebuild;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnDeveloperUserInfoChange;

	virtual FBeamOperationHandle OnRealmInitialized(FBeamRealmHandle NewRealm) override;

	/**
	 * @brief Get users that matches the name filter and a tag filter
	 */
	UFUNCTION(BlueprintCallable)
	void GetUsersWithFilter(FString NameFilter, FString TagFilter, TArray<UDeveloperUserDataStreamData*>& AllUsers);

	/**
	 * Get the First User of the List with the given GamerTag
	 */
	UFUNCTION(BlueprintCallable)
	UDeveloperUserDataStreamData* GetUserWithGamerTag(FBeamGamerTag GamerTag);
	
	/**
	 * Delete a user from the local files
	 * OBS: It will NOT delete the user from the portal
	 */
	UFUNCTION(BlueprintCallable)
	void DeleteUsers(TArray<FBeamGamerTag> GamerTags);

	/**
	 * Delete all users for a type from the local files
	 * OBS: It will NOT delete the user from the portal
	 */
	UFUNCTION(BlueprintCallable)
	void DeleteAllOfSpecificType(EBeamDeveloperUserType DeveloperUserType);

	/**
	 * Get the next New User Alias
	 */
	UFUNCTION(BlueprintCallable)
	FString GetNextNewUserAlias();

	
	/**
	 * Create a new user
	 */
	UFUNCTION(BlueprintCallable)
	void CreateNewUserOperation(FString Alias, EBeamDeveloperUserType DeveloperUserType, FBeamOperationEventHandler OperationEventHandle);

	
	/**
	 * Create a new user and copy the stats and inventory to the created user from a template gamer tag
	 */
	UFUNCTION(BlueprintCallable)
	void CopyTemplateToNewUserOperation(UDeveloperUserDataStreamData* UserData, EBeamDeveloperUserType DeveloperUserType, FBeamOperationEventHandler OperationEventHandle);

	/**
	 * Create a new user and copy the stats and inventory to the created user from a template gamer tag
	 */
	UFUNCTION(BlueprintCallable)
	void UpdateDeveloperUserInfo(FBeamGamerTag GamerTag, FString Alias, FString Description, TArray<FString> Tags);

	/**
	 * Copy the users to the Saved folder to be loaded by the cache login
	 */
	void TriggerOnPreBeginPIE(ULevelEditorPlaySettings* PlaySettings, const FBeamPIE_Settings* Settings);

	bool IsValidUser(FBeamGamerTag GamerTag);
	
	/**
	 * A utility that cast a soft object path to a UWorld Soft Pointer
	 */
	UFUNCTION(BlueprintPure)
	static void CastSoftReferenceToWorld(FSoftObjectPath SourcePointer, TSoftObjectPtr<UWorld>& CastedPointer)
	{
		if (SourcePointer.IsValid())
		{
			TSoftObjectPtr<UWorld> variable(SourcePointer);

			CastedPointer = variable;
		}
	}

	UFUNCTION(BlueprintPure)
	static bool ComparePIEUserSlotHandle(const FBeamPIE_UserSlotHandle& A, const FBeamPIE_UserSlotHandle& B)
	{
		return A == B;
	}

	UFUNCTION(BlueprintCallable)
	static TArray<FBeamPIE_UserSlotHandle> GetSortedKeysAssignedUsers(TMap<FBeamPIE_UserSlotHandle, FBeamPIE_PerUserSetting> AssignedUsers)
	{
		TArray<FBeamPIE_UserSlotHandle> AssignedUserArray;
		AssignedUsers.GenerateKeyArray(AssignedUserArray);

		AssignedUserArray.Sort([](const FBeamPIE_UserSlotHandle& A, const  FBeamPIE_UserSlotHandle& B)
		{
			if (A.PIEIndex != B.PIEIndex)
			{
				return A.PIEIndex < B.PIEIndex;
			}

			return A.Slot.Name.Compare(B.Slot.Name) < 0;
		});
		
		return AssignedUserArray;
	}


	UFUNCTION(BlueprintCallable)
	static bool TryGetValidUserSlotHandle(int SelectedPIEIndex, bool CreateCopyOnPIE, FString SelectedSlotName, TMap<FBeamPIE_UserSlotHandle, FBeamPIE_PerUserSetting> AssignedUsers, FBeamPIE_UserSlotHandle& UserSlotHandle)
	{
		auto UserSlots = GetDefault<UBeamCoreSettings>()->RuntimeUserSlots;

		TArray<FBeamPIE_UserSlotHandle> UserSlotHandles;

		for (auto AssignedUser : AssignedUsers)
		{
			if (AssignedUser.Key.PIEIndex == SelectedPIEIndex)
			{
				UserSlotHandles.Add(AssignedUser.Key);
				UserSlots.Remove(AssignedUser.Key.Slot);
			}
		}

		if (UserSlotHandles.Num() == 0)
		{
			UserSlotHandle = FBeamPIE_UserSlotHandle(SelectedPIEIndex, CreateCopyOnPIE, FUserSlot(SelectedSlotName));
			return true;
		}

		// There's no remaining user slot
		if (UserSlots.Num() == 0)
		{
			return false;
		}
		
		
		UserSlotHandle = FBeamPIE_UserSlotHandle(SelectedPIEIndex, CreateCopyOnPIE, UserSlots[0]);
		return true;
	}

protected:
	void RunPsCommand(FBeamOperationHandle OperationHandle);

	void RebuildLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> AllEntries);

	void UpdateLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> ToUpdate, TArray<UDeveloperUserDataStreamData*> ToRemove);

	void TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const FBeamOperationHandle& BeamOperationHandle, const UObject* Context);
};
