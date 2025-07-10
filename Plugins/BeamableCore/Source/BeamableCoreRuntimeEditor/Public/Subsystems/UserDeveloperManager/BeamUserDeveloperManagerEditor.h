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

	GENERATED_BODY()


	UPROPERTY()
	UBeamCli* BeamCli;

	UPROPERTY()
	UBeamUserSlots* BeamUserSlots;

	UPROPERTY()
	TMap<FBeamGamerTag, UDeveloperUserDataStreamData*> LocalUserDeveloperCache;

	TMap<int32, TArray<FBeamRealmUser>> CapturedUsers;

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
	 * Delete a user from the local files
	 * OBS: It will NOT delete the user from the portal
	 */
	UFUNCTION(BlueprintCallable)
	void DeleteUser(FBeamGamerTag GamerTag);

	/**
	 * Create a new user and copy the stats and inventory to the created user from a template gamer tag
	 */
	UFUNCTION(BlueprintCallable)
	void CopyTemplateToNewUserOperation(FBeamGamerTag TemplateGamerTag, EBeamDeveloperUserType DeveloperUserType, FBeamOperationEventHandler OperationEventHandle);

	/**
	 * Create a new user and copy the stats and inventory to the created user from a template gamer tag
	 */
	UFUNCTION(BlueprintCallable)
	void UpdateDeveloperUserInfo(FBeamGamerTag GamerTag, FString Alias, FString Description, TArray<FString> Tags);

	/**
	 * Copy the users to the Saved folder to be loaded by the cache login
	 */
	void TriggerOnPreBeginPIE(const FBeamPIE_Settings* Settings);

	/**
	 * Get the mutable reference to the PieSettings
	 */

	void GetMutablePIESettings()
	{
		
	}

protected:
	void RunPsCommand(FBeamOperationHandle OperationHandle);

	void RebuildLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> AllEntries);

	void UpdateLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> ToUpdate, TArray<UDeveloperUserDataStreamData*> ToRemove);

	void TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const FBeamOperationHandle& BeamOperationHandle, const UObject* Context);
};
