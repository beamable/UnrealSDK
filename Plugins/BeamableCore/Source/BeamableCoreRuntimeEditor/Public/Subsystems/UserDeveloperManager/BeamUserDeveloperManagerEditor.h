// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PIE/BeamPIE_Settings.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerCreateUserBatchCommand.h"
#include "Subsystems/CLI/Autogen/StreamData/DeveloperUserDataStreamData.h"

#include "BeamUserDeveloperManagerEditor.generated.h"


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMABLECORERUNTIMEEDITOR_API UBeamUserDeveloperManagerEditor : public UBeamEditorSubsystem
{
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
	inline static const FString DefaultBeamableUserDeveloperPath = TEXT("UserDeveloper");

	inline static const FString DefaultBeamableProjectPath = FPaths::ProjectDir() / TEXT(".beamable");
	inline static const FString DefaultBeamableProjectContentObjects = DefaultBeamableProjectPath / DefaultBeamableUserDeveloperPath;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnDeveloperUserInfoFullRebuild;

	UPROPERTY(BlueprintAssignable)
	FEditorStateChangedEvent OnDeveloperUserInfoChange;

	inline static const int32 EVT_TYPE_FullRebuild = 0;

	inline static const int32 EVT_TYPE_ChangedUserInfo = 1;

	virtual FBeamOperationHandle OnRealmInitialized(FBeamRealmHandle NewRealm) override;

	UFUNCTION(BlueprintCallable)
	void GetAllUsers(TArray<UDeveloperUserDataStreamData*>& AllUsers);

	UFUNCTION(BlueprintCallable)
	void SetUserInfo(FBeamGamerTag GamerTag, FString Alias, FString Description, TArray<FString> Tags);

	void TriggerOnPreBeginPIE(const FBeamPIE_Settings* Settings);

protected:
	void RunPsCommand(FBeamOperationHandle FirstEventOp);

	void RebuildLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> AllEntries);

	void UpdateLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> ToUpdate, TArray<int64> ToRemove);

	void TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const FBeamOperationHandle& BeamOperationHandle, const UObject* Context);
};
