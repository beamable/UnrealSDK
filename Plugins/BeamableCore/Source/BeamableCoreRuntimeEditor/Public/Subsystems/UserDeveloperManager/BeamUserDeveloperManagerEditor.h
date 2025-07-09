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
	static constexpr int DeveloperUserTypeLocal = 1;
	static constexpr int DeveloperUserTypeShared = 2;

	GENERATED_BODY()


	UPROPERTY()
	UBeamCli* BeamCli;

	UPROPERTY()
	UBeamUserSlots* BeamUserSlots;

	UPROPERTY()
	TMap<FBeamGamerTag, UDeveloperUserStreamData*> LocalUserDeveloperCache;

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
	void GetAllUsers(FString NameFilter, FString TagFilter, TArray<UDeveloperUserStreamData*>& AllUsers);

	UFUNCTION(BlueprintCallable)
	void RemoveUser(FBeamGamerTag GamerTag);


	UFUNCTION(BlueprintCallable)
	void CopyUserToTarget(FBeamGamerTag TemplateGamerTag, EBeamDeveloperUserType DeveloperUserType, FBeamOperationEventHandler OperationEventHandle);

	UFUNCTION(BlueprintCallable)
	void SetUserInfo(FBeamGamerTag GamerTag, FString Alias, FString Description, bool CreateCopyOnPIE, TArray<FString> Tags);

	void TriggerOnPreBeginPIE(const FBeamPIE_Settings* Settings);

protected:
	void RunPsCommand(FBeamOperationHandle FirstEventOp);

	void RebuildLocalDeveloperUserCache(TArray<UDeveloperUserStreamData*> AllEntries);

	void UpdateLocalDeveloperUserCache(TArray<UDeveloperUserStreamData*> ToUpdate, TArray<UDeveloperUserStreamData*> ToRemove);

	void TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const FBeamOperationHandle& BeamOperationHandle, const UObject* Context);
};
