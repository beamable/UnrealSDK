// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/UserDeveloperManager/BeamUserDeveloperManagerEditor.h"

#include <string>

#include "PIE/BeamPIEConfig.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerCreateUserBatchCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerCreateUserCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerPsCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerRemoveUserCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerSaveUserCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliDeveloperUserManagerUpdateInfoCommand.h"


void UBeamUserDeveloperManagerEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	BeamUserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();

	BeamCli = GEditor->GetEditorSubsystem<UBeamCli>();

	UserSlotAuthenticatedHandler = BeamUserSlots->GlobalUserSlotAuthenticatedCodeHandler.AddUObject(this, &UBeamUserDeveloperManagerEditor::TriggerOnUserSlotAuthenticated);
}

void UBeamUserDeveloperManagerEditor::Deinitialize()
{
	Super::Deinitialize();

	BeamUserSlots->GlobalUserSlotAuthenticatedCodeHandler.Remove(UserSlotAuthenticatedHandler);
}

FBeamOperationHandle UBeamUserDeveloperManagerEditor::OnRealmInitialized(FBeamRealmHandle NewRealm)
{
	if (!BeamCli->IsInstalled())
	{
		UE_LOG(LogBeamCli, Error, TEXT("Editor Subsystem %s - Content depends on the CLI. It was not found locally. This system is not guaranteed to work because of this."), *GetName());
		return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}

	// Start up the PS command for the current realm
	const auto Op = RequestTracker->CPP_BeginOperation({}, GetName(), FBeamOperationEventHandlerCode::CreateLambda([this](FBeamOperationEvent Event)
	{
		DeleteAllOfSpecificType(BEAM_CAPTURED);
	}));
	RunPsCommand(Op);

	return Op;
}


void UBeamUserDeveloperManagerEditor::TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const FBeamOperationHandle& BeamOperationHandle, const UObject* Context)
{
	if (Context)
	{
		const auto WorldContext = GEngine->GetWorldContextFromWorld(Context->GetWorld());
		if (WorldContext && WorldContext->WorldType == EWorldType::PIE)
		{
			TArray<FBeamRealmUser> RealmUsers = {BeamRealmUser};

			UBeamCliDeveloperUserManagerSaveUserCommand* SaveUserCommand = NewObject<UBeamCliDeveloperUserManagerSaveUserCommand>();
			SaveUserCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerSaveUserStreamData*>& Stream, const TArray<int64>&,
			                                         const FBeamOperationHandle&)
			{
				auto Data = Stream.Last();
				for (auto SavedUser : Data->SavedUsers)
				{
					UE_LOG(LogTemp, Display, TEXT("Saved user %lld"), SavedUser->GamerTag);
				}
			};
			SaveUserCommand->OnCompleted = [this](const int& ResCode, const FBeamOperationHandle& Handler)
			{
				if (ResCode == 0)
				{
					RequestTracker->TriggerOperationSuccess(Handler, TEXT(""));
				}
				else
				{
					RequestTracker->TriggerOperationError(Handler, TEXT(""));
				}
			};
			// 0 - Captured
			// 1 - Local
			// 2 - Shared
			int UserType = 0;
			if (LocalUserDeveloperCache.Contains(BeamRealmUser.GamerTag))
			{
				UserType = LocalUserDeveloperCache[BeamRealmUser.GamerTag]->DeveloperUserType;
			}

			TArray<FString> AccessToken;
			TArray<FString> RefreshToken;
			TArray<FString> ExpiresIn;
			TArray<FString> Pid;
			TArray<FString> Cid;
			TArray<FString> GamerTag;


			for (auto RealmUser : RealmUsers)
			{
				AccessToken.Add(RealmUser.AuthToken.AccessToken);
				RefreshToken.Add(RealmUser.AuthToken.RefreshToken);
				ExpiresIn.Add(FString::Printf(TEXT("%lld"), RealmUser.AuthToken.ExpiresIn));
				Pid.Add(RealmUser.RealmHandle.Pid.AsString);
				Cid.Add(RealmUser.RealmHandle.Cid.AsString);
				GamerTag.Add(RealmUser.GamerTag.AsString);
			}

			auto args = {
				FString::Printf(TEXT("--access-token %s"), *FString::Join(AccessToken, TEXT(" "))),
				FString::Printf(TEXT("--refresh-token %s"), *FString::Join(RefreshToken, TEXT(" "))),
				FString::Printf(TEXT("--expires-in %s"), *FString::Join(ExpiresIn, TEXT(" "))),
				FString::Printf(TEXT("--pid %s"), *FString::Join(Pid, TEXT(" "))),
				FString::Printf(TEXT("--cid %s"), *FString::Join(Cid, TEXT(" "))),
				FString::Printf(TEXT("--gamer-tag %s"), *FString::Join(GamerTag, TEXT(" "))),
				FString::Printf(TEXT("--user-type %d"), UserType)
			};

			auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

			BeamCli->RunCommandServer(SaveUserCommand, args, Handler);
		}
	}
}

void UBeamUserDeveloperManagerEditor::TriggerOnPreBeginPIE(ULevelEditorPlaySettings* PlaySettings, const FBeamPIE_Settings* Settings)
{
	FScopedSlowTask SlowTask(100, FText::FromString(TEXT("Starting Beam PIE - Copying Users")));
	SlowTask.MakeDialog(false, true);
	SlowTask.EnterProgressFrame(10);

	// If there's no assigned user set-up we don't need to do nothing
	if (Settings->AssignedUsers.Num() == 0)
	{
		return;
	}
	for (auto AssignedUser : Settings->AssignedUsers)
	{
		if (!IsValidUser(AssignedUser.Value.GamerTag))
		{
			return;
		}
	}
	auto BeamCoreSettings = GetDefault<UBeamCoreSettings>();

	// We have this guard to force copy the user if the PID / Cid is different from the target
	auto ShouldCopyPIE = [this, BeamCoreSettings](TTuple<FBeamPIE_UserSlotHandle, FBeamPIE_PerUserSetting> AssignedUser)
	{
		auto DeveloperUser = LocalUserDeveloperCache[AssignedUser.Value.GamerTag.AsLong];
		if (DeveloperUser->Cid != BeamCoreSettings->TargetRealm.Cid || DeveloperUser->Pid != BeamCoreSettings->TargetRealm.Pid)
			return true;

		if (DeveloperUser->DeveloperUserType == EBeamDeveloperUserType::BEAM_SHARED)
			return true;
		
		return AssignedUser.Key.CreateCopyOnPIE;
	};

	TMap<FBeamGamerTag, int32> TemplateAmount;
	for (auto AssignedUser : Settings->AssignedUsers)
	{
		if (!ShouldCopyPIE(AssignedUser))
		{
			continue;
		}
		// Clear the saved users from the previous session
		BeamUserSlots->ClearAllCachedUserDataAtNamespacedSlot(BeamUserSlots->GetNamespacedSlotId(AssignedUser.Key.Slot, AssignedUser.Key.PIEIndex));

		// Count the numbers of each template
		auto UserSlotHandle = AssignedUser.Key;
		if (FBeamGamerTag GamerTag = AssignedUser.Value.GamerTag; TemplateAmount.Contains(GamerTag))
		{
			TemplateAmount[GamerTag]++;
		}
		else
		{
			TemplateAmount.Add(GamerTag, 1);
		}
	}

	TArray<FString> GamerTags;
	TArray<FString> AmountList;

	for (auto TemplateGamerTagAmountKeyPair : TemplateAmount)
	{
		GamerTags.Add(TemplateGamerTagAmountKeyPair.Key.AsString);
		AmountList.Add(std::to_string(TemplateGamerTagAmountKeyPair.Value).data());
	}

	auto args = {
		FString::Printf(TEXT("--templates-list %s"), *FString::Join(GamerTags, TEXT(" "))),
		FString::Printf(TEXT("--amount-list %s"), *FString::Join(AmountList, TEXT(" "))),
		FString::Printf(TEXT("--rolling-buffer-size %d"), 100),
	};

	UBeamCliDeveloperUserManagerCreateUserBatchCommand* CreateUserBatchCommand = NewObject<UBeamCliDeveloperUserManagerCreateUserBatchCommand>();
	CreateUserBatchCommand->OnStreamOutput = [this, Settings, ShouldCopyPIE](const TArray<UBeamCliDeveloperUserManagerCreateUserBatchStreamData*>& Stream, const TArray<int64>&,
	                                                                         const FBeamOperationHandle&)
	{
		auto Data = Stream.Last();

		TMap<long, TArray<UDeveloperUserDataStreamData*>> CreatedUserMap;
		// Build a list with the created users
		for (UDeveloperUserDataStreamData* CreatedUser : Data->CreatedUsers)
		{
			if (CreatedUserMap.Contains(CreatedUser->TemplateGamerTag))
			{
				CreatedUserMap[CreatedUser->TemplateGamerTag].Add(CreatedUser);
			}
			else
			{
				CreatedUserMap.Add(CreatedUser->TemplateGamerTag, {CreatedUser});
			}
		}

		for (auto AssignedUserKeyPair : Settings->AssignedUsers)
		{
			UDeveloperUserDataStreamData* DeveloperUser;
			// If we shouldn't copy the PIE we just skip it
			if (!ShouldCopyPIE(AssignedUserKeyPair))
			{
				continue;
			}
			DeveloperUser = CreatedUserMap[AssignedUserKeyPair.Value.GamerTag.AsLong][0];

			BeamUserSlots->SaveSlot(AssignedUserKeyPair.Key.Slot, AssignedUserKeyPair.Key.PIEIndex,
			                        DeveloperUser->GamerTag,
			                        DeveloperUser->AccessToken,
			                        DeveloperUser->RefreshToken,
			                          DeveloperUser->IssuedAt,
			                        DeveloperUser->ExpiresIn,
			                        DeveloperUser->Cid,
			                        DeveloperUser->Pid);

			CreatedUserMap[AssignedUserKeyPair.Value.GamerTag.AsLong].Remove(DeveloperUser);
		}
	};

	CreateUserBatchCommand->OnCompleted = [this](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode == CLI_ERROR_BACKEND)
		{
			UE_LOG(LogTemp, Error, TEXT("CREATE BATCH CLI COMMAND: CLI_ERROR_BACKEND %d"), ResCode);
		}
		else if (ResCode == CLI_ERROR_UNKNOWN_BACKEND)
		{
			UE_LOG(LogTemp, Error, TEXT("CREATE BATCH CLI COMMAND: CLI_ERROR_UNKNOWN_BACKEND %d"), ResCode);
		}
		else if (ResCode == CLI_ERROR_SAVE_FILE)
		{
			UE_LOG(LogTemp, Error, TEXT("CREATE BATCH CLI COMMAND: CLI_ERROR_SAVE_FILE %d"), ResCode);
		}
		else if (ResCode != 0)
		{
			// Unknown error
		}
		else
		{
		}
	};
	// Before call the CLI we check if there's any assigned user that should be copy
	// If there's no assigned user we just don't call the CLI
	bool NeedCopy = false;
	for (auto AssignedUser : Settings->AssignedUsers)
	{
		if (ShouldCopyPIE(AssignedUser))
		{
			NeedCopy = true;
			continue;
		}
		UDeveloperUserDataStreamData* DeveloperUser = LocalUserDeveloperCache[AssignedUser.Value.GamerTag.AsLong];

		BeamUserSlots->SaveSlot(AssignedUser.Key.Slot, AssignedUser.Key.PIEIndex,
		                        DeveloperUser->GamerTag,
		                        DeveloperUser->AccessToken,
		                        DeveloperUser->RefreshToken,
		                        DeveloperUser->IssuedAt,
		                        DeveloperUser->ExpiresIn,
		                        DeveloperUser->Cid,
		                        DeveloperUser->Pid);
	}

	SlowTask.EnterProgressFrame(50);
	if (NeedCopy)
	{
		BeamCli->RunCommandSync(CreateUserBatchCommand, args);
	}
	SlowTask.EnterProgressFrame(40);
}

bool UBeamUserDeveloperManagerEditor::IsValidUser(FBeamGamerTag GamerTag)
{
	return !GamerTag.AsString.IsEmpty() && LocalUserDeveloperCache.Contains(GamerTag);
}

UDeveloperUserDataStreamData* UBeamUserDeveloperManagerEditor::GetUserWithGamerTag(FBeamGamerTag GamerTag)
{
	if (LocalUserDeveloperCache.Contains(GamerTag))
	{
		return LocalUserDeveloperCache[GamerTag];
	}
	return nullptr;
}

void UBeamUserDeveloperManagerEditor::GetUsersWithFilter(FString NameFilter, FString TagFilter, TArray<UDeveloperUserDataStreamData*>& AllUsers)
{
	AllUsers.Empty();
	TArray<UDeveloperUserDataStreamData*> Result;
	for (auto DeveloperUser : LocalUserDeveloperCache)
	{
		Result.Add(DeveloperUser.Value);
	}

	if (NameFilter != TEXT(""))
	{
		Result.RemoveAll([NameFilter](UDeveloperUserDataStreamData* Data)
		{
			return !Data->Alias.Contains(NameFilter) && !FString::Printf(TEXT("%llu"), Data->GamerTag).Contains(NameFilter);
		});
	}

	if (TagFilter != TEXT(""))
	{
		TArray<FString> Tags;
		TagFilter.ParseIntoArray(Tags, TEXT(","));
		Result.RemoveAll([Tags](UDeveloperUserDataStreamData* Data)
		{
			bool ContainsAll = true;
			for (auto FilterTag : Tags)
			{
				FilterTag.TrimStartAndEndInline();

				bool Contains = false;
				for (auto Tag : Data->Tags)
				{
					Contains |= Tag.Contains(FilterTag);
				}
				ContainsAll &= Contains;
			}

			return !ContainsAll;
		});
	}

	Result.Sort([](const UDeveloperUserDataStreamData& A, const UDeveloperUserDataStreamData& B)
	{
		if (A.DeveloperUserType != B.DeveloperUserType)
		{
			return A.DeveloperUserType > B.DeveloperUserType;
		}

		auto Source = FString::Printf(TEXT("%s%lld"), *A.Alias, A.CreatedDate);
		auto Target = FString::Printf(TEXT("%s%lld"), *B.Alias, B.CreatedDate);
		return Source.Compare(Target) < 0;
	});

	AllUsers = Result;
}

void UBeamUserDeveloperManagerEditor::DeleteUsers(TArray<FBeamGamerTag> GamerTags)
{
	UBeamCliDeveloperUserManagerRemoveUserCommand* RemoveCommand = NewObject<UBeamCliDeveloperUserManagerRemoveUserCommand>();

	RemoveCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerRemoveUserStreamData*>& Stream, const TArray<int64>&,
	                                       const FBeamOperationHandle&)
	{
	};
	RemoveCommand->OnCompleted = [this](const int&, const FBeamOperationHandle&)
	{
	};

	TArray<FString> StringGamerTags;
	for (auto GamerTag : GamerTags)
	{
		StringGamerTags.Add(GamerTag.AsString);
	}

	auto args = {
		FString::Printf(TEXT("--gamer-tag %s"), *FString::Join(StringGamerTags, TEXT(" "))),
	};

	auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	BeamCli->RunCommandServer(RemoveCommand, args, Handler);
}

void UBeamUserDeveloperManagerEditor::DeleteAllOfSpecificType(EBeamDeveloperUserType DeveloperUserType)
{
	TArray<FBeamGamerTag> GamerTags;
	for (auto UserDeveloperKeyPair : LocalUserDeveloperCache)
	{
		if (UserDeveloperKeyPair.Value->DeveloperUserType == DeveloperUserType)
		{
			GamerTags.Add(UserDeveloperKeyPair.Key);
		}
	}
	if (GamerTags.Num() > 0)
	{
		DeleteUsers(GamerTags);
	}
}

FString UBeamUserDeveloperManagerEditor::GetNextNewUserAlias()
{
	int32 NewUserIndex = 0;
	for (auto UserDeveloperKeyPair : LocalUserDeveloperCache)
	{
		if (UserDeveloperKeyPair.Value->Alias.Contains(DEVELOPER_USER_NEW_USER_NAME))
		{
			NewUserIndex++;
		}
	}
	if (NewUserIndex != 0)
	{
		return FString::Printf(TEXT("%s %d"), *DEVELOPER_USER_NEW_USER_NAME, NewUserIndex);
	}

	return DEVELOPER_USER_NEW_USER_NAME;
}

void UBeamUserDeveloperManagerEditor::CreateNewUserOperation(FString Alias, EBeamDeveloperUserType DeveloperUserType, FBeamOperationEventHandler OperationEventHandle)
{
	auto OperationHandler = RequestTracker->BeginOperation({}, GetName(), OperationEventHandle);
	UBeamCliDeveloperUserManagerCreateUserCommand* CreateUserCommand = NewObject<UBeamCliDeveloperUserManagerCreateUserCommand>();

	CreateUserCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerCreateUserStreamData*>& Stream, const TArray<int64>&,
	                                           const FBeamOperationHandle&)
	{
	};
	CreateUserCommand->OnCompleted = [this, OperationHandler](const int& Res, const FBeamOperationHandle&)
	{
		if (Res == 0)
		{
			RequestTracker->TriggerOperationSuccess(OperationHandler, TEXT(""));
		}
		else
		{
			RequestTracker->TriggerOperationError(OperationHandler, TEXT(""));
		}
	};

	auto args = {
		FString::Printf(TEXT("--alias \"%s\""), *Alias),
		FString::Printf(TEXT("--description \"\"")),
		FString::Printf(TEXT("--user-type %d"), DeveloperUserType),
	};

	auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	BeamCli->RunCommandServer(CreateUserCommand, args, Handler);
}


void UBeamUserDeveloperManagerEditor::CopyTemplateToNewUserOperation(UDeveloperUserDataStreamData* UserData, EBeamDeveloperUserType DeveloperUserType, FBeamOperationEventHandler OperationEventHandle)
{
	auto OperationHandler = RequestTracker->BeginOperation({}, GetName(), OperationEventHandle);
	UBeamCliDeveloperUserManagerCreateUserCommand* CreateUserCommand = NewObject<UBeamCliDeveloperUserManagerCreateUserCommand>();

	CreateUserCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerCreateUserStreamData*>& Stream, const TArray<int64>&,
	                                           const FBeamOperationHandle&)
	{
	};
	CreateUserCommand->OnCompleted = [this, OperationHandler](const int& Res, const FBeamOperationHandle&)
	{
		if (Res == 0)
		{
			RequestTracker->TriggerOperationSuccess(OperationHandler, TEXT(""));
		}
		else
		{
			RequestTracker->TriggerOperationError(OperationHandler, TEXT(""));
		}
	};

	FString TagsStr = "";

	for (auto tag : UserData->Tags)
	{
		TagsStr += FString::Printf(TEXT("--tags \"%s\" "), *tag);
	}

	auto args = {
		FString::Printf(TEXT("--template \"%lld\""), UserData->GamerTag),
		FString::Printf(TEXT("--alias \"%s Copy\""), *UserData->Alias),
		FString::Printf(TEXT("--description \"%s\""), *UserData->Description),
		FString::Printf(TEXT("--user-type %d"), DeveloperUserType),
		FString::Printf(TEXT("%s"), *TagsStr),
	};

	auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	BeamCli->RunCommandServer(CreateUserCommand, args, Handler);
}

void UBeamUserDeveloperManagerEditor::UpdateDeveloperUserInfo(FBeamGamerTag GamerTag, FString Alias, FString Description, TArray<FString> Tags)
{
	UBeamCliDeveloperUserManagerUpdateInfoCommand* UpdateInfoCommand = NewObject<UBeamCliDeveloperUserManagerUpdateInfoCommand>();

	UpdateInfoCommand->OnStreamOutput = [this](const TArray<UBeamCliDeveloperUserManagerUpdateInfoStreamData*>& Stream, const TArray<int64>&,
	                                           const FBeamOperationHandle&)
	{
	};
	UpdateInfoCommand->OnCompleted = [this](const int&, const FBeamOperationHandle&)
	{
	};

	FString TagsStr = "";

	for (auto tag : Tags)
	{
		TagsStr += FString::Printf(TEXT("--tags \"%s\" "), *tag);
	}

	auto args = {
		FString::Printf(TEXT("--gamer-tag \"%s\""), *GamerTag.AsString),
		FString::Printf(TEXT("--alias \"%s\""), *Alias),
		FString::Printf(TEXT("--description \"%s\""), *Description),
		FString::Printf(TEXT("%s"), *TagsStr),
	};


	auto Handler = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	BeamCli->RunCommandServer(UpdateInfoCommand, args, Handler);
}

void UBeamUserDeveloperManagerEditor::RunPsCommand(FBeamOperationHandle OperationHandle)
{
	auto WatchCommand = NewObject<UBeamCliDeveloperUserManagerPsCommand>();
	WatchCommand->OnStreamOutput = [this, OperationHandle](TArray<UBeamCliDeveloperUserManagerPsStreamData*>& Stream, TArray<int64>&, const FBeamOperationHandle&)
	{
		const auto Data = Stream.Last();
		if (Data->EventType == EVT_TYPE_FullRebuild)
		{
			RebuildLocalDeveloperUserCache(Data->DeveloperUserReport->UpdatedUsers);
			if (RequestTracker->IsOperationActive(OperationHandle))
			{
				RequestTracker->TriggerOperationSuccess(OperationHandle, TEXT(""));
			}
			OnDeveloperUserInfoFullRebuild.Broadcast();
		}

		if (Data->EventType == EVT_TYPE_ChangedUserInfo)
		{
			UpdateLocalDeveloperUserCache(Data->DeveloperUserReport->UpdatedUsers, Data->DeveloperUserReport->DeletedUsers);

			OnDeveloperUserInfoChange.Broadcast();
		}
	};
	WatchCommand->OnCompleted = [this, WatchCommand, OperationHandle](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode != 0)
		{
			// If we completed without receiving the first event, we trigger an error of the first event.
			if (WatchCommand->Stream.Num() == 0) RequestTracker->TriggerOperationError(OperationHandle, TEXT("Failed to fetch initial full-rebuild event"));

			const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
			BeamCli->RunCommand(WatchCommand, {TEXT("-w"), ReqProcess}, {});
		}
	};

	const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
	BeamCli->RunCommand(WatchCommand, {TEXT("-w"), ReqProcess}, {});
}


void UBeamUserDeveloperManagerEditor::RebuildLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> AllEntries)
{
	LocalUserDeveloperCache.Reset();

	for (const auto& Entry : AllEntries)
	{
		LocalUserDeveloperCache.Add(Entry->GamerTag, Entry);
	}
}

void UBeamUserDeveloperManagerEditor::UpdateLocalDeveloperUserCache(TArray<UDeveloperUserDataStreamData*> ToUpdate, TArray<UDeveloperUserDataStreamData*> ToRemove)
{
	for (const auto& Entry : ToUpdate)
	{
		if (LocalUserDeveloperCache.Contains(Entry->GamerTag))
		{
			LocalUserDeveloperCache[Entry->GamerTag] = Entry;
		}
		else
		{
			LocalUserDeveloperCache.Add(Entry->GamerTag, Entry);
		}
	}

	for (const auto& Entry : ToRemove)
	{
		if (LocalUserDeveloperCache.Contains(Entry->GamerTag))
		{
			LocalUserDeveloperCache.Remove(Entry->GamerTag);
		}
	}
}
