// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Content/BeamEditorContent.h"

#include <string>

#include "EditorStyleSet.h"
#include "Content/BeamContentCache.h"
#include "Content/BeamContentCacheSerializer.h"
#include "Content/DownloadContentState.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Kismet/KismetStringLibrary.h"
#include "Misc/FileHelper.h"
#include "Serialization/ObjectWriter.h"
#include "Settings/ProjectPackagingSettings.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/CLI/BeamCli.h"
#include "Subsystems/CLI/Autogen/BeamCliContentHistoryCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentHistorySyncChangelistCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentHistorySyncContentCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentLocalManifestCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentPsCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentPublishCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentPullCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentResolveCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentRestoreCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentSaveCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentSnapshotCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentSnapshotListCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentSyncCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliContentTagSetCommand.h"
#include "Widgets/Notifications/SNotificationList.h"

void UBeamEditorContent::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Display, TEXT("Initializing Beam Editor - Content System!"))

	ContentApi = GEngine->GetEngineSubsystem<UBeamContentApi>();
	Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	EditorAssetSubsystem = Collection.InitializeDependency<UEditorAssetSubsystem>();


	// Grab all existing ContentObject classes so we can present them as options in the editing UI and correctly parse them.
	ContentTypeStringToContentClass.Add("", UBeamContentObject::StaticClass());
	ContentClassToContentTypeString.Add(UBeamContentObject::StaticClass(), "");
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UBeamContentObject::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			FName TypeName = It->GetFName();
			FString ContentTypeId = It->GetDefaultObject<UBeamContentObject>()->BuildContentTypeString();

			UE_LOG(LogTemp, Display, TEXT("Initializing Beam Editor Content System - TYPE=%s, TYPE_ID=%s"),
			       *TypeName.ToString(), *ContentTypeId);
			AllContentTypes.Add(*It);
			AllContentTypeNames.Add(MakeShared<FName>(TypeName));
			ContentTypeStringToContentClass.Add(ContentTypeId, *It);
			ContentClassToContentTypeString.Add(*It, ContentTypeId);
		}
	}
	AllContentTypes.Sort([](const UClass& A, const UClass& B)
	{
		FString ContentTypeIdA = A.GetDefaultObject<UBeamContentObject>()->BuildContentTypeString();
		FString ContentTypeIdB = B.GetDefaultObject<UBeamContentObject>()->BuildContentTypeString();
		return ContentTypeIdA.Compare(ContentTypeIdB) < 0;
	});
	AllContentTypeNames.Sort([](const TSharedPtr<FName>& A, const TSharedPtr<FName>& B)
	{
		return A.Get()->Compare(*B.Get()) < 0;
	});
}

void UBeamEditorContent::Deinitialize()
{
	Super::Deinitialize();
	FEditorDelegates::PreBeginPIE.Remove(OnWillEnterPIE);
}

FBeamOperationHandle UBeamEditorContent::InitializeWhenEditorReady()
{
	// We get the operation for this. 
	UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Initializing after Unreal Editor is ready"), *GetName())

	// By default, just return an empty completed operation
	const auto Op = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetName(), {});

	// Ensure we are properly configured with at least one path for baked content.
	const auto EditorSettings = GetMutableDefault<UBeamEditorSettings>();

	// If we are initializing the Editor Settings
	if (EditorSettings->CookedManifestsPath.IsEmpty())
	{
		EditorSettings->CookedManifestsPath.Add(FDirectoryPath{DefaultBeamableCookedContentManifestsPath});
		// We save this out to the default editor configuration so that this default is always versioned (unless we save config with these parameters, changes to settings objects are local to this developer)
		EditorSettings->SaveConfig(CPF_Config, *EditorSettings->GetDefaultConfigFilename());
	}

	// Ensure that all directories in the cooked manifest paths array exist.
	for (const auto& CookedManifestsPath : EditorSettings->CookedManifestsPath)
	{
		if (!EditorAssetSubsystem->DoesDirectoryExist(CookedManifestsPath.Path))
		{
			EditorAssetSubsystem->MakeDirectory(CookedManifestsPath.Path);
		}
	}

	RequestTracker->TriggerOperationSuccess(Op, {});
	return Op;
}

FBeamOperationHandle UBeamEditorContent::OnRealmInitialized(FBeamRealmHandle NewRealm)
{
	// Ensure the CLI is installed
	if (!Cli->IsInstalled())
	{
		UE_LOG(LogBeamCli, Error, TEXT("Editor Subsystem %s - Content depends on the CLI. It was not found locally. This system is not guaranteed to work because of this."), *GetName());
		return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}

	// Start up the PS command for the current realm
	const auto PsOp = RequestTracker->CPP_BeginOperation({}, GetName(), {});
	RunPsCommand(PsOp);
	const auto HistoryOp = RequestTracker->CPP_BeginOperation({}, GetName(), {});
	RunHistoryPsCommand(HistoryOp);

	// Wait for both listen commands to be set up 
	const auto WaitOnOp = RequestTracker->CPP_BeginOperation({}, GetName(), {});
	RequestTracker->CPP_WaitAll({}, {PsOp, HistoryOp}, {}, FOnWaitCompleteCode::CreateLambda([this, WaitOnOp](FBeamWaitCompleteEvent Evt)
	{
		if (RequestTracker->IsWaitSuccessful(Evt))
			RequestTracker->TriggerOperationSuccess(WaitOnOp, "");

		TArray<FString> Errs;
		if (RequestTracker->IsWaitFailed(Evt, Errs))
		{
			const FString Err = FString::Join(Errs, TEXT("\n"));
			RequestTracker->TriggerOperationError(WaitOnOp, Err);
		}
	}));

	// For now, we just fetch all the manifests that exist.	
	return WaitOnOp;
}

FBeamOperationHandle UBeamEditorContent::PublishManifestOperation(FBeamContentManifestId ManifestId, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Op = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetName(), OnOperationEvent);
	PublishManifest(ManifestId, Op);
	return Op;
}

FBeamOperationHandle UBeamEditorContent::CPP_PublishManifestOperation(FBeamContentManifestId ManifestId, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Op = RequestTracker->CPP_BeginOperation({Editor->GetMainEditorSlot()}, GetName(), OnOperationEvent);
	PublishManifest(ManifestId, Op);
	return Op;
}

void UBeamEditorContent::GetLocalManifestIds(TArray<FBeamContentManifestId>& Keys) const
{
	Keys.Reserve(LocalManifestCache.Num());
	LocalManifestCache.GetKeys(Keys);
}

bool UBeamEditorContent::TryGetLocalManifestById(const FBeamContentManifestId& Id, ULocalContentManifestStreamData*& Manifest)
{
	if (LocalManifestCache.Contains(Id))
	{
		Manifest = LocalManifestCache.FindChecked(Id);
		return true;
	}

	return false;
}

void UBeamEditorContent::PublishManifest(FBeamContentManifestId ContentManifestId, FBeamOperationHandle Op)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();


	FSlowTask* SlowTask = new FSlowTask(1, FText::FromString(TEXT("Publishing Content...")));
	SlowTask->Initialize();
	SlowTask->MakeDialog();

	UBeamCliContentPublishCommand* PublishCommand = NewObject<UBeamCliContentPublishCommand>();
	PublishCommand->OnCompleted = [this, PublishCommand, SlowTask, Op](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode == 0)
		{
			RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		}
		else
		{
			const auto Err = NewObject<UBeamCliErrorData>();
			Err->Errors = TArray<FBeamCliError>{PublishCommand->Errors};
			const auto Str = Err->Errors[0].Message;
			RequestTracker->TriggerOperationErrorWithData(Op, Str, Err);
		}

		SlowTask->Destroy();
		delete SlowTask;
	};

	TArray<FString> Params;
	Params.Append({TEXT("--manifest-ids"), ContentManifestId.AsString});
	Params.Append({TEXT("--auto-snapshot-type SharedOnly")});

	Cli->RunCommandServer(PublishCommand, Params, {});
	SlowTask->EnterProgressFrame();
}

bool UBeamEditorContent::DownloadManifest(FBeamContentManifestId ContentManifestId, FString& Err)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();

	FSlowTask* SlowTask = new FSlowTask(1, FText::FromString(TEXT("Downloading Content...")));
	SlowTask->Initialize();
	SlowTask->MakeDialog();

	bool Res = false;
	UBeamCliContentPullCommand* PullCommand = NewObject<UBeamCliContentPullCommand>();
	PullCommand->OnStreamOutput = [this](const TArray<UBeamCliContentPullStreamData*>& Data, const TArray<int64>&,
	                                     const FBeamOperationHandle&)
	{
		for (const auto& D : Data)
			RebuildLocalManifestCache(D->Manifests);
	};
	PullCommand->OnCompleted = [this, &Res, &Err, SlowTask](const int& ResCode, const FBeamOperationHandle&)
	{
		Res = ResCode == 0;
		Err = Res ? TEXT("") : TEXT("FAILED_DOWNLOAD");
		SlowTask->Destroy();
		delete SlowTask;
	};

	Cli->RunCommandSync(PullCommand, {FString::Printf(TEXT("--manifest-ids %s"), *ContentManifestId.AsString)});
	SlowTask->EnterProgressFrame();

	return Res;
}

bool UBeamEditorContent::ForceSyncContent(FBeamContentManifestId ContentManifestId, TArray<FBeamContentId> Ids)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();

	// Do nothing unless ids were specified
	if (Ids.Num() == 0)
		return true;


	UBeamCliContentSyncCommand* SyncCommand = NewObject<UBeamCliContentSyncCommand>();;
	SyncCommand->OnCompleted = [this, ContentManifestId, Ids](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode == 0)
		{
			OnContentRevert.Broadcast(ContentManifestId, Ids);
		}
		else
		{
			OnContentRevertFailed.Broadcast(ContentManifestId, Ids);
		}
	};

	// Get all the Content Ids in the form "type.id1 type.id2".
	auto IdsStr = TArray<FString>{};
	for (FBeamContentId Id : Ids) IdsStr.Add(Id.AsString);
	auto IdsParam = Ids.Num() > 0 ? FString::Printf(TEXT("%s"), *FString::Join(IdsStr, TEXT(","))) : TEXT("");

	// Build the CLI args
	TArray<FString> Params;
	Params.Append({TEXT("--manifest-ids"), ContentManifestId.AsString});
	Params.Append({TEXT("--filter"), IdsParam});
	Params.Append({TEXT("--filter-type"), TEXT("ExactIds")});
	Params.Append({TEXT("--sync-created")});
	Params.Append({TEXT("--sync-deleted")});
	Params.Append({TEXT("--sync-modified")});
	Params.Append({TEXT("--sync-conflicts")});
	Cli->RunCommandServer(SyncCommand, Params, {});

	return true;
}

bool UBeamEditorContent::ResolveConflict(FBeamContentManifestId ContentManifestId, TArray<FBeamContentId> Ids, bool bUseRealm)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();

	// Do nothing unless ids were specified
	if (Ids.Num() == 0)
		return true;


	UBeamCliContentResolveCommand* ResolveCommand = NewObject<UBeamCliContentResolveCommand>();;
	ResolveCommand->OnCompleted = [this, ContentManifestId, Ids](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode == 0)
		{
			OnContentRevert.Broadcast(ContentManifestId, Ids);
		}
		else
		{
			OnContentRevertFailed.Broadcast(ContentManifestId, Ids);
		}
	};

	// Get all the Content Ids in the form "type.id1 type.id2".
	auto IdsStr = TArray<FString>{};
	for (FBeamContentId Id : Ids) IdsStr.Add(Id.AsString);
	auto IdsParam = Ids.Num() > 0 ? FString::Printf(TEXT("%s"), *FString::Join(IdsStr, TEXT(" "))) : TEXT("");

	// Build the CLI args
	TArray<FString> Params;
	Params.Append({TEXT("--manifest-ids"), ContentManifestId.AsString});
	Params.Append({TEXT("--filter"), IdsParam});
	Params.Append({TEXT("--filter-type"), TEXT("ExactIds")});
	Params.Append({TEXT("--use"), bUseRealm ? TEXT("realm") : TEXT("local")});
	Cli->RunCommandServer(ResolveCommand, Params, {});

	return true;
}

UClass* UBeamEditorContent::GetContentTypeByTypeId(FString TypeId)
{
	if (const auto ClassPtr = ContentTypeStringToContentClass.Find(TypeId))
		return *ClassPtr;

	return nullptr;
}

void UBeamEditorContent::FindSubTypesOfContentType(const TArray<FString>& TypeNames, TMap<FString, FArrayOfString>& OutMappings)
{
	for (const auto& Pair : ContentTypeStringToContentClass)
	{
		const FString CurrentId = Pair.Key;
		for (const auto& TypeName : TypeNames)
		{
			if (CurrentId.StartsWith(TypeName))
			{
				if (!OutMappings.Contains(TypeName))
				{
					TArray<FString> Array;
					OutMappings.Add(TypeName, FArrayOfString{Array});
				}
				OutMappings[TypeName].Values.Add(CurrentId);
			}
		}
	}

	for (TPair<FString, FArrayOfString> OutMapping : OutMappings)
		OutMapping.Value.Values.Sort();
}

bool UBeamEditorContent::CreateNewContent(const FBeamContentManifestId& ManifestId, const FString& ContentName,
                                          TSubclassOf<UBeamContentObject> ContentObjectSubType, TArray<FString> Tags,
                                          UBeamContentObject*& ContentObject, FString& ErrMsg)
{
	ContentObject = NewObject<UBeamContentObject>(this, ContentObjectSubType.Get());

	// We add it to the object and to the local manifest.
	const auto TypeName = ContentObject->GetClass()->GetFName().ToString();

	auto RepeatedNameCount = 0;
	auto NewContentId = ContentName.IsEmpty()
		                    ? FString::Format(TEXT("{0}.{1}_{2}"), {
			                                      ContentObject->BuildContentTypeString(), TypeName, RepeatedNameCount
		                                      })
		                    : FString::Format(TEXT("{0}.{1}"), {ContentObject->BuildContentTypeString(), ContentName});

	auto Entries = LocalManifestCache.FindRef(ManifestId)->Entries;
	while (Entries.FindByPredicate([NewContentId](ULocalContentManifestEntryStreamData* Data)
	{
		return Data->FullId.Equals(NewContentId);
	}))
	{
		RepeatedNameCount += 1;
		NewContentId = ContentName.IsEmpty()
			               ? FString::Format(TEXT("{0}.{1}_{2}"), {
				                                 ContentObject->BuildContentTypeString(), TypeName, RepeatedNameCount
			                                 })
			               : FString::Format(TEXT("{0}.{1}_{2}"), {
				                                 ContentObject->BuildContentTypeString(), ContentName, RepeatedNameCount
			                                 });
	}

	// Sets the ID and Tags based on the manifest row.
	ContentObject->Id = NewContentId;
	ContentObject->Tags.Append(Tags);
	if (!SaveContentObject(ManifestId, ContentObject, "", false))
	{
		ErrMsg = FString::Format(TEXT("Failed to save the content object {0}"), {NewContentId});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
		return false;
	}
	LoadedContentObjects.Add(ContentObject->Id, ContentObject);
	return true;
}

bool UBeamEditorContent::GetContent(const FBeamContentManifestId& ManifestId, FBeamContentId ContentId,
                                    UBeamContentObject*& ContentObject)
{
	FString Err;
	const auto bRes = GetContentForEditing(ManifestId, ContentId, ContentObject, Err);
	if (!bRes)
	{
		UE_LOG(LogTemp, Verbose, TEXT("Fallback Content Getter: Failed to find content with ID=%s from Manifest=%s."),
		       *ContentId.AsString, *ManifestId.AsString)
	}
	return bRes;
}

bool UBeamEditorContent::GetContentForEditing(const FBeamContentManifestId& ManifestId, FBeamContentId EditObjectId,
                                              UBeamContentObject*& ContentObject, FString& ErrMsg)
{
	const auto EditingTable = LocalManifestCache.FindRef(ManifestId);
	if (!EditingTable)
	{
		ErrMsg = FString::Format(
			TEXT(
				"Trying to load a content object from a Manifest={0} that is not loaded. Ignore this during packaging."),
			{ManifestId.AsString});
		UE_LOG(LogBeamContent, Display, TEXT("%s"), *ErrMsg);
		return false;
	}

	const auto Entries = EditingTable->Entries;
	if (!Entries.FindByPredicate([EditObjectId](ULocalContentManifestEntryStreamData* data)
	{
		return data->FullId.Equals(EditObjectId.AsString);
	}))
	{
		ErrMsg = FString::Format(
			TEXT("Trying to load a content object that doesn't exist in this manifest. CONTENT_ID={0}"),
			{EditObjectId.AsString});
		UE_LOG(LogBeamContent, Verbose, TEXT("%s"), *ErrMsg);
		return false;
	}

	if (!TryLoadContentObject(ManifestId, EditObjectId, ContentObject))
	{
		ErrMsg = FString::Format(
			TEXT("Trying to load a content object that doesn't exist. CONTENT_ID={0}"), {EditObjectId.AsString});
		UE_LOG(LogBeamContent, Verbose, TEXT("%s"), *ErrMsg);
		return false;
	}

	ErrMsg.Empty();
	return true;
}

bool UBeamEditorContent::SaveContentObject(const FBeamContentManifestId& ManifestId,
                                           UBeamContentObject* EditingObject,
                                           FString PropertyName,
                                           bool bIgnoreReferenceManifest)
{
	// Get the ID and properties for this 
	FString Id = EditingObject->Id;
	FString PropertiesJsonContent;
	EditingObject->ToPropertiesJson(PropertiesJsonContent);

	// Log the json
	UE_LOG(LogBeamContent, Verbose, TEXT("Saving content object with ID: %s"), *PropertiesJsonContent);

	// Tags are saved using a different command from the CLI - Check: ContentTagSetCommand
	if (!PropertyName.Equals("Tags"))
	{
		auto SaveCmd = NewObject<UBeamCliContentSaveCommand>();
		SaveCmd->OnCompleted = [this, ManifestId, Id](const int& ResCode, const FBeamOperationHandle&)
		{
			// Trigger a callback saying that a piece of content was modified
			if (ResCode == 0)
			{
				OnContentSaved.Broadcast(ManifestId, {Id});
			}
			else
			{
				OnContentSavedFailed.Broadcast(ManifestId, {Id});
			}
		};

		TArray<FString> Params;
		Params.Append({TEXT("--manifest-ids"), ManifestId.AsString});
		Params.Append({TEXT("--content-ids"), Id});
		Params.Append({TEXT("--content-properties"), FString::Printf(TEXT("%s"), *PropertiesJsonContent)});
		if (bIgnoreReferenceManifest)
			Params.Append({TEXT("--force")});

		Cli->RunCommandServer(SaveCmd, Params, {});
	}
	else
	{
		auto SetTagCmd = NewObject<UBeamCliContentTagSetCommand>();
		SetTagCmd->OnCompleted = [this, ManifestId, Id](const int& ResCode, const FBeamOperationHandle&)
		{
			// Trigger a callback saying that a piece of content was modified
			if (ResCode == 0)
			{
				OnContentSaved.Broadcast(ManifestId, {Id});
			}
			else
			{
				OnContentSavedFailed.Broadcast(ManifestId, {Id});
			}
		};


		TArray<FString> Params;
		Params.Append({FString::Printf(TEXT("\"%s\""), *UKismetStringLibrary::JoinStringArray(EditingObject->Tags, TEXT(",")))});
		Params.Append({TEXT("--manifest-ids"), ManifestId.AsString});
		Params.Append({TEXT("--filter"), Id});
		Params.Append({TEXT("--filter-type"), TEXT("ExactIds")});
		// If there's no tag in the field we pass the clear
		if (EditingObject->Tags.Num() == 0)
		{
			Params.Append({TEXT("--clear")});
		}


		Cli->RunCommandServer(SetTagCmd, Params, {});
	}

	return true;
}

bool UBeamEditorContent::DeleteContentObject(const FBeamContentManifestId& ManifestId, FBeamContentId Id,
                                             FString& ErrMsg)
{
	const auto Entries = LocalManifestCache[ManifestId]->Entries;
	if (const auto Entry = Entries.FindByPredicate([Id](ULocalContentManifestEntryStreamData* Data)
	{
		return Data->FullId.Equals(Id.AsString);
	}))
	{
		const auto FilePath = (*Entry)->JsonFilePath;
		IFileManager& FileManager = IFileManager::Get();
		const auto bDeleted = FileManager.Delete(*FilePath);
		if (bDeleted) return true;

		ErrMsg = FString::Format(TEXT("Failed to delete the content object {0}"), {Id.AsString});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
		return false;
	}

	ErrMsg = FString::Format(TEXT("Failed to delete the content object {0}"), {Id.AsString});
	UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
	return false;
}

bool UBeamEditorContent::DuplicateContent(const FBeamContentManifestId& ManifestId, FBeamContentId Id, FString& ErrMsg, FString& CreatedId)
{
	const auto Entries = LocalManifestCache[ManifestId]->Entries;
	if (const auto Entry = Entries.FindByPredicate([Id](ULocalContentManifestEntryStreamData* Data)
	{
		return Data->FullId.Equals(Id.AsString);
	}))
	{
		const auto FilePath = (*Entry)->JsonFilePath;
		IFileManager& FileManager = IFileManager::Get();

		// Extract file components
		FString FileDirectory = FPaths::GetPath(FilePath);
		FString FileName = FPaths::GetBaseFilename(FilePath);
		FString FileExtension = FPaths::GetExtension(FilePath);

		// Parse existing suffix from filename
		FString BaseFileName = FileName;
		int32 ExistingSuffix = 0;

		// Check if filename ends with "_Number" pattern
		int32 LastUnderscoreIndex;
		if (FileName.FindLastChar(TEXT('_'), LastUnderscoreIndex))
		{
			FString SuffixPart = FileName.Mid(LastUnderscoreIndex + 1);
			if (SuffixPart.IsNumeric())
			{
				ExistingSuffix = FCString::Atoi(*SuffixPart);
				BaseFileName = FileName.Left(LastUnderscoreIndex);
			}
		}

		// Start with the next logical number
		int32 CopyIndex = ExistingSuffix + 1;
		FString DuplicateFilePath;

		do
		{
			FString NewFileName = BaseFileName + FString::Printf(TEXT("_%d"), CopyIndex);
			DuplicateFilePath = FPaths::Combine(FileDirectory, NewFileName + TEXT(".") + FileExtension);
			CopyIndex++;
		}
		while (FileManager.FileExists(*DuplicateFilePath));

		// Copy the file
		uint32 bCopied = FileManager.Copy(*DuplicateFilePath, *FilePath);
		CreatedId = FPaths::GetBaseFilename(DuplicateFilePath);
		if (bCopied == 0)
		{
			return true;
		}

		ErrMsg = FString::Format(TEXT("Failed to duplicate the content object {0}"), {Id.AsString});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);

		return false;
	}

	ErrMsg = FString::Format(TEXT("Failed to find the content object {0} for duplication"), {Id.AsString});
	UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
	return false;
}

bool UBeamEditorContent::TryRenameContent(const FBeamContentManifestId& ManifestId, const FBeamContentId& ContentId,
                                          const FString& NewContentName, FText& Err)
{
	UBeamContentObject* Obj;
	const auto bContentFound = GetContent(ManifestId, ContentId, Obj);
	ensureAlways(bContentFound);

	if (!IsValidContentName(NewContentName, Err))
		return false;

	const FString ContentTypeString = Obj->BuildContentTypeString();
	const FString NewId = ContentTypeString + TEXT(".") + NewContentName;

	const FBeamContentId NewContentId = FBeamContentId{NewId};

	const auto OldContentPath = GetJsonBlobPath(ContentId.AsString, ManifestId);
	const auto NewContentPath = GetJsonBlobPath(NewContentId.AsString, ManifestId);
	const auto bNewNameIsAvailable = !IFileManager::Get().FileExists(*NewContentPath);
	if (!bNewNameIsAvailable)
	{
		Err = FText::FromString(TEXT("The provided content id is already in use."));
		return false;
	}

	if (!IFileManager::Get().Move(*NewContentPath, *OldContentPath))
	{
		Err = FText::FromString(TEXT("Failed renaming the file."));
		return false;
	}

	return true;
}

bool UBeamEditorContent::TryGetFilteredListOfContent(const FBeamContentManifestId ManifestId, const FString& NameFilter,
                                                     const FString& TypeFilter,
                                                     const EBeamLocalContentStatus& ContentStatusFilter,
                                                     const EBeamContentObjectSupportLevel& SupportLevelFilter,
                                                     TArray<UBeamContentLocalView*>& FoundLocalContent)
{
	if (!LocalManifestCache.Contains(ManifestId))
		return false;

	const auto manifest = LocalManifestCache[ManifestId];

	TArray<FString> Names;
	TArray<FString> Ids;
	TArray<FString> Types;
	TArray<bool> IsInConflicts;
	TArray<UBeamContentObject*> ObjectsInManifest;
	TArray<EBeamLocalContentStatus> StatusesInManifest;
	auto Rows = manifest->Entries;

	for (const auto Row : Rows)
	{
		// Find the closest match of all possible C++ classes for this type by walking up the hierarchy of types encoded in the id.
		UClass* ObjectClass;
		TEnumAsByte<EBeamContentObjectSupportLevel> SupportLevel;
		UBeamContentObject::GetClassForTypeId(ContentTypeStringToContentClass, Row->TypeName, ObjectClass, SupportLevel);

		// Use the supported type name for filtering.
		FString SupportedTypeName = ContentClassToContentTypeString[ObjectClass];

		const auto bPassNameFilter = NameFilter.IsEmpty() || Row->Name.Contains(NameFilter);
		const auto bPassTypeFilter = TypeFilter.IsEmpty() || (ContentTypeStringToContentClass.Contains(SupportedTypeName) && ContentTypeStringToContentClass[SupportedTypeName]->GetName().Contains(TypeFilter));
		const auto bPassStatusFilter = (static_cast<uint8>(Row->CurrentStatus) & static_cast<uint8>(ContentStatusFilter)) > 0;
		const auto bPassSupportLevelFilter = SupportLevelFilter == EBeamContentObjectSupportLevel::None || (static_cast<uint8>(SupportLevel) & static_cast<uint8>(SupportLevelFilter)) > 0;

		if (bPassNameFilter && bPassTypeFilter && bPassStatusFilter && bPassSupportLevelFilter)
		{
			UBeamContentObject* Obj = nullptr;
			FString Err;
			if (GetContent(ManifestId, Row->FullId, Obj))
			{
				Obj->SupportLevel = SupportLevel;
				ObjectsInManifest.Add(Obj);
				Ids.Add(Row->FullId);
				Names.Add(Row->Name);
				Types.Add(SupportedTypeName);
				IsInConflicts.Add(Row->IsInConflict);
				StatusesInManifest.Add(static_cast<EBeamLocalContentStatus>(Row->CurrentStatus));
			}
		}
	}

	// Convert them into the Local View
	for (int i = 0; i < ObjectsInManifest.Num(); ++i)
	{
		FoundLocalContent.Add(NewObject<UBeamContentLocalView>());
		FoundLocalContent[FoundLocalContent.Num() - 1]->ContentFullId = FText::FromString(Ids[i]);
		FoundLocalContent[FoundLocalContent.Num() - 1]->ContentName = FText::FromString(Names[i]);
		FoundLocalContent[FoundLocalContent.Num() - 1]->ContentTypeName = FText::FromString(Types[i]);
		FoundLocalContent[FoundLocalContent.Num() - 1]->LocalStatus = StatusesInManifest[i];
		FoundLocalContent[FoundLocalContent.Num() - 1]->ContentObject = ObjectsInManifest[i];
		FoundLocalContent[FoundLocalContent.Num() - 1]->bIsInConflict = IsInConflicts[i];
	}

	//Content needs to be sorted to as following : newly created content/modified/unmodified/deletions
	FoundLocalContent.Sort([](const UBeamContentLocalView& BeamContent1, const UBeamContentLocalView& BeamContent2)
	{
		if (BeamContent1.LocalStatus == BeamContent2.LocalStatus)
			return BeamContent1.ContentName.ToString() < BeamContent2.ContentName.ToString();
		else if (BeamContent1.LocalStatus == EBeamLocalContentStatus::Beam_LocalContentCreated)
			return true;
		else if (BeamContent1.LocalStatus == EBeamLocalContentStatus::Beam_LocalContentModified && BeamContent2.LocalStatus != EBeamLocalContentStatus::Beam_LocalContentCreated)
			return true;
		else if (BeamContent1.LocalStatus == EBeamLocalContentStatus::Beam_LocalContentUpToDate &&
			BeamContent2.LocalStatus != EBeamLocalContentStatus::Beam_LocalContentCreated && BeamContent2.LocalStatus != EBeamLocalContentStatus::Beam_LocalContentModified)
			return true;

		return false;
	});

	return true;
}

bool UBeamEditorContent::TryGetFilteredListOfContentHistory(const FBeamContentManifestId ManifestId, const FString& PublishedByFilter, const FString& AffectedContentIdsFilter,
                                                            TArray<UBeamContentHistoryEntryView*>& FoundHistoryEntries)
{
	if (!LocalContentHistoryEntriesCache.Contains(ManifestId))
		return false;

	const auto* EntriesPage = LocalContentHistoryEntriesCache[ManifestId];
	if (!EntriesPage)
		return false;

	for (const auto* Entry : EntriesPage->Entries)
	{
		if (!Entry)
			continue;

		// Apply PublishedBy filter (case-insensitive substring match)
		const bool bPassPublishedByFilter = PublishedByFilter.IsEmpty() ||
			Entry->PublishedBy.Contains(PublishedByFilter) ||
			Entry->PublishedByName.Contains(PublishedByFilter);

		// Apply AffectedContentIds filter (check if any of the filter IDs are in the entry's affected content)
		bool bPassAffectedContentIdsFilter = AffectedContentIdsFilter.IsEmpty();
		if (!bPassAffectedContentIdsFilter)
		{
			for (const FString& Id : Entry->AffectedContentIds)
			{
				if (Id.Contains(AffectedContentIdsFilter))
				{
					bPassAffectedContentIdsFilter = true;
					break;
				}
			}
		}

		// Both filters must pass (AND logic)
		if (bPassPublishedByFilter && bPassAffectedContentIdsFilter)
		{
			auto* HistoryView = NewObject<UBeamContentHistoryEntryView>();
			HistoryView->ManifestUid = Entry->ManifestUid;
			HistoryView->PublishedDate = FDateTime::FromUnixTimestamp(Entry->CreatedDate / 1000);
			HistoryView->PublishedBy = FText::FromString(Entry->PublishedBy);
			HistoryView->PublishedByName = FText::FromString(Entry->PublishedByName);
			HistoryView->AffectedContentIds = Entry->AffectedContentIds;

			FoundHistoryEntries.Add(HistoryView);
		}
	}

	// Sort by date (newest first)
	FoundHistoryEntries.Sort([](const UBeamContentHistoryEntryView& A, const UBeamContentHistoryEntryView& B)
	{
		return A.PublishedDate > B.PublishedDate;
	});

	return true;
}

bool UBeamEditorContent::TryGetHistoryChangelistView(const FBeamContentManifestId& ManifestId, const FString& ManifestUid, UBeamContentHistoryChangelistView*& ChangelistView)
{
	// Check if the changelist exists in the cache
	UContentHistoryChangelistStreamData** ChangelistData = LocalContentHistoryChangelistCache.Find(ManifestUid);
	if (!ChangelistData || !*ChangelistData)
	{
		return false;
	}

	// Create the view object
	ChangelistView = NewObject<UBeamContentHistoryChangelistView>();
	ChangelistView->ManifestUid = (*ChangelistData)->ManifestUid;
	ChangelistView->PublishedDate = FDateTime::FromUnixTimestamp((*ChangelistData)->PublishedAt / 1000);
	ChangelistView->PublishedBy = FText::FromString((*ChangelistData)->PublishedBy);

	// Look up PublishedByName from LocalContentHistoryEntriesCache using binary search
	FText PublishedByName = FText::GetEmpty();
	if (UContentHistoryEntriesPageStreamData** EntriesPage = LocalContentHistoryEntriesCache.Find(ManifestId))
	{
		if (*EntriesPage && (*EntriesPage)->Entries.Num() > 0)
		{
			const int64 PublishedAtTimestamp = (*ChangelistData)->PublishedAt;
			const TArray<UContentHistoryEntryStreamData*>& Entries = (*EntriesPage)->Entries;

			// Binary search for the entry with a matching timestamp
			int32 Left = 0;
			int32 Right = Entries.Num() - 1;

			while (Left <= Right)
			{
				const int32 Mid = Left + (Right - Left) / 2;
				const UContentHistoryEntryStreamData* Entry = Entries[Mid];

				if (!Entry) break;

				// Found the timestamp
				if (Entry->CreatedDate == PublishedAtTimestamp)
				{
					// Check if ManifestUid matches
					if (Entry->ManifestUid == ManifestUid)
					{
						PublishedByName = FText::FromString(Entry->PublishedByName);
						break;
					}

					// Same timestamp but different ManifestUid - search nearby entries
					int32 SearchIdx = Mid - 1;
					while (SearchIdx >= 0 && Entries[SearchIdx] && Entries[SearchIdx]->CreatedDate == PublishedAtTimestamp)
					{
						if (Entries[SearchIdx]->ManifestUid == ManifestUid)
						{
							PublishedByName = FText::FromString(Entries[SearchIdx]->PublishedByName);
							break;
						}
						SearchIdx--;
					}

					if (PublishedByName.IsEmpty())
					{
						SearchIdx = Mid + 1;
						while (SearchIdx < Entries.Num() && Entries[SearchIdx] && Entries[SearchIdx]->CreatedDate == PublishedAtTimestamp)
						{
							if (Entries[SearchIdx]->ManifestUid == ManifestUid)
							{
								PublishedByName = FText::FromString(Entries[SearchIdx]->PublishedByName);
								break;
							}
							SearchIdx++;
						}
					}
					break;
				}
				// Still searching... do binary search split
				else
				{
					if (Entry->CreatedDate < PublishedAtTimestamp) Right = Mid - 1;
					if (Entry->CreatedDate > PublishedAtTimestamp) Left = Mid + 1;
				}
			}
		}
	}
	ChangelistView->PublishedByName = PublishedByName;

	// Populate Created content
	for (const auto& Pair : (*ChangelistData)->Created)
	{
		if (!Pair.Value) continue;

		auto* EntryView = NewObject<UBeamContentHistoryChangelistEntryView>();
		EntryView->FullId = Pair.Value->FullId;
		EntryView->Name = FText::FromString(Pair.Value->Name);
		EntryView->TypeName = FText::FromString(Pair.Value->TypeName);
		EntryView->OldVersion = Pair.Value->OldVersion;
		EntryView->OldChecksum = Pair.Value->OldChecksum;
		EntryView->OldTags = Pair.Value->OldTags;
		EntryView->NewVersion = Pair.Value->NewVersion;
		EntryView->NewChecksum = Pair.Value->NewChecksum;
		EntryView->NewTags = Pair.Value->NewTags;
		EntryView->ChangeDate = FDateTime::FromUnixTimestamp(Pair.Value->ChangeDate / 1000);
		EntryView->ChangeStatus = static_cast<EBeamLocalContentStatus>(Pair.Value->ChangeStatus);

		FBeamContentHistoryContentEntryId HistoryId;
		HistoryId.ContentId = FBeamContentId(Pair.Key);
		HistoryId.ManifestUid = ManifestUid;
		EntryView->HistoryEntryId = HistoryId;

		ChangelistView->Entries.Add(EntryView);
	}

	// Populate Modified content
	for (const auto& Pair : (*ChangelistData)->Modified)
	{
		if (!Pair.Value) continue;

		auto* EntryView = NewObject<UBeamContentHistoryChangelistEntryView>();
		EntryView->FullId = Pair.Value->FullId;
		EntryView->Name = FText::FromString(Pair.Value->Name);
		EntryView->TypeName = FText::FromString(Pair.Value->TypeName);
		EntryView->OldVersion = Pair.Value->OldVersion;
		EntryView->OldChecksum = Pair.Value->OldChecksum;
		EntryView->OldTags = Pair.Value->OldTags;
		EntryView->NewVersion = Pair.Value->NewVersion;
		EntryView->NewChecksum = Pair.Value->NewChecksum;
		EntryView->NewTags = Pair.Value->NewTags;
		EntryView->ChangeDate = FDateTime::FromUnixTimestamp(Pair.Value->ChangeDate / 1000);
		EntryView->ChangeStatus = static_cast<EBeamLocalContentStatus>(Pair.Value->ChangeStatus);

		FBeamContentHistoryContentEntryId HistoryId;
		HistoryId.ContentId = FBeamContentId(Pair.Key);
		HistoryId.ManifestUid = ManifestUid;
		EntryView->HistoryEntryId = HistoryId;

		ChangelistView->Entries.Add(EntryView);
	}

	// Populate Removed content
	for (const auto& Pair : (*ChangelistData)->Removed)
	{
		if (!Pair.Value) continue;

		auto* EntryView = NewObject<UBeamContentHistoryChangelistEntryView>();
		EntryView->FullId = Pair.Value->FullId;
		EntryView->Name = FText::FromString(Pair.Value->Name);
		EntryView->TypeName = FText::FromString(Pair.Value->TypeName);
		EntryView->OldVersion = Pair.Value->OldVersion;
		EntryView->OldChecksum = Pair.Value->OldChecksum;
		EntryView->OldTags = Pair.Value->OldTags;
		EntryView->NewVersion = Pair.Value->NewVersion;
		EntryView->NewChecksum = Pair.Value->NewChecksum;
		EntryView->NewTags = Pair.Value->NewTags;
		EntryView->ChangeDate = FDateTime::FromUnixTimestamp(Pair.Value->ChangeDate / 1000);
		EntryView->ChangeStatus = static_cast<EBeamLocalContentStatus>(Pair.Value->ChangeStatus);

		FBeamContentHistoryContentEntryId HistoryId;
		HistoryId.ContentId = FBeamContentId(Pair.Key);
		HistoryId.ManifestUid = ManifestUid;
		EntryView->HistoryEntryId = HistoryId;

		ChangelistView->Entries.Add(EntryView);
	}

	return true;
}

bool UBeamEditorContent::GetHistoryContent(const FString& ManifestUid, const FBeamContentId& ContentId, UBeamContentObject*& ContentObject)
{
	FBeamContentHistoryContentEntryId HistoryId;
	HistoryId.ContentId = ContentId;
	HistoryId.ManifestUid = ManifestUid;

	if (UBeamContentObject** FoundObject = LoadedContentHistoryObjects.Find(HistoryId))
	{
		ContentObject = *FoundObject;
		return true;
	}

	UE_LOG(LogBeamContent, Verbose, TEXT("Failed to find history content with ContentId=%s from ManifestUid=%s."),
	       *ContentId.AsString, *ManifestUid);
	return false;
}

void UBeamEditorContent::ApplyContentSnapshot(FBeamContentManifestId ManifestId, FBeamPid Realm, FString Path, bool DeleteAfterRestore, bool AddAfterRestore, FBeamSnapshotRestored OnApplyCompleted)
{
	auto List = NewObject<UBeamCliContentRestoreCommand>();
	List->OnCompleted = [List, OnApplyCompleted, this](const int& ErrorCode, const FBeamOperationHandle&)
	{
		if (ErrorCode == 0)
		{
			OnApplyCompleted.ExecuteIfBound();
		}
		else
		{
			for (FBeamCliError Error : List->Errors)
			{
				UE_LOG(LogBeamContent, Log, TEXT("ERROR applying snapshot: %s"), *Error.Message);
				auto value = FString::Printf(TEXT("ERROR applying snapshot: %s"), *Error.Message);
				ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
			}
			OnApplyCompleted.ExecuteIfBound();
		}
	};

	FString Args;

	Args += !ManifestId.AsString.IsEmpty() ? FString::Printf(TEXT("--manifest-id %s"), *ManifestId.AsString) : TEXT("");
	Args += !Realm.AsString.IsEmpty() ? FString::Printf(TEXT("--pid %s"), *Realm.AsString) : TEXT("");
	Args += FString::Printf(TEXT("--name \"%s\""), *Path);
	Args += DeleteAfterRestore ? TEXT(" --delete-after-restore") : TEXT("");
	Args += AddAfterRestore ? TEXT(" --additive-restore") : TEXT("");

	Cli->RunCommandServer(List, {Args}, {});
}

void UBeamEditorContent::CreateContentSnapshot(FBeamContentManifestId ManifestId, FBeamPid Realm, FString Name, bool bIsAutoSnapshot, FBeamSnapshotCreated OnSnapshotCreated)
{
	auto CreateCmd = NewObject<UBeamCliContentSnapshotCommand>();
	CreateCmd->OnCompleted = [CreateCmd, OnSnapshotCreated, this](const int& ErrorCode, const FBeamOperationHandle&)
	{
		if (ErrorCode == 0)
		{
			OnSnapshotCreated.ExecuteIfBound();
		}
		else
		{
			for (FBeamCliError Error : CreateCmd->Errors)
			{
				UE_LOG(LogBeamContent, Log, TEXT("ERROR creating snapshot: %s"), *Error.Message);
				auto value = FString::Printf(TEXT("ERROR creating snapshot: %s"), *Error.Message);
				ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
			}
			OnSnapshotCreated.ExecuteIfBound();
		}
	};

	FString Args;

	Args += !ManifestId.AsString.IsEmpty() ? FString::Printf(TEXT("--manifest-id %s"), *ManifestId.AsString) : TEXT("");
	Args += !Realm.AsString.IsEmpty() ? FString::Printf(TEXT("--pid %s"), *Realm.AsString) : TEXT("");
	Args += FString::Printf(TEXT("--name \"%s\""), *Name);
	if (bIsAutoSnapshot)
	{
		Args += TEXT(" --auto-snapshot");
	}

	Cli->RunCommandServer(CreateCmd, {Args}, {});
}

void UBeamEditorContent::DeleteContentSnapshot(FBeamContentManifestId ManifestId, FBeamPid Realm, FString Path, FBeamSnapshotDeleted OnSnapshotDeleted)
{
	// Delete the snapshot file directly using File Utilities
	IFileManager& FileManager = IFileManager::Get();

	if (FileManager.FileExists(*Path))
	{
		if (FileManager.Delete(*Path, false, true))
		{
			OnSnapshotDeleted.ExecuteIfBound();
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Failed to delete snapshot file: %s"), *Path);
			auto value = FString::Printf(TEXT("Failed to delete snapshot file: %s"), *Path);
			ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
			OnSnapshotDeleted.ExecuteIfBound();
		}
	}
	else
	{
		UE_LOG(LogBeamContent, Warning, TEXT("Snapshot file does not exist: %s"), *Path);
		auto value = FString::Printf(TEXT("Snapshot file does not exist: %s"), *Path);
		ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
		OnSnapshotDeleted.ExecuteIfBound();
	}
}

void UBeamEditorContent::RenameContentSnapshot(FBeamContentManifestId ManifestId, FBeamPid Realm, FString OldPath, FString NewName, FBeamSnapshotRenamed OnSnapshotRenamed)
{
	FString NewPath = FPaths::GetPath(OldPath) / NewName + FPaths::GetExtension(OldPath);
	IFileManager& FileManager = IFileManager::Get();

	if (FileManager.FileExists(*OldPath))
	{
		if (FileManager.Move(*NewPath, *OldPath))
		{
			OnSnapshotRenamed.ExecuteIfBound();
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Failed to rename snapshot from %s to %s"), *OldPath, *NewPath);
			auto value = FString::Printf(TEXT("Failed to rename snapshot from %s to %s"), *OldPath, *NewPath);
			ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
			OnSnapshotRenamed.ExecuteIfBound();
		}
	}
	else
	{
		UE_LOG(LogBeamContent, Warning, TEXT("Snapshot file does not exist: %s"), *OldPath);
		auto value = FString::Printf(TEXT("Snapshot file does not exist: %s"), *OldPath);
		ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
		OnSnapshotRenamed.ExecuteIfBound();
	}
}

void UBeamEditorContent::RefreshContentSnapshots(FBeamContentManifestId ManifestId, FBeamPid Realm, FBeamSnapshotRefreshed OnRefreshCompleted)
{
	auto List = NewObject<UBeamCliContentSnapshotListCommand>();
	List->OnStreamOutput = [OnRefreshCompleted](TArray<UBeamCliContentSnapshotListStreamData*>& StreamData, TArray<long long>&, const FBeamOperationHandle&)
	{
		TArray<UBeamSnapshotLocalView*> SnapshotLocalViews;
		for (UBeamCliContentSnapshotListStreamData* Data : StreamData)
		{
			for (UManifestSnapshotItemStreamData* SharedSnapshot : Data->SharedSnapshots)
			{
				auto SnapshotView = NewObject<UBeamSnapshotLocalView>();
				SnapshotView->Name = FText::FromString(SharedSnapshot->Name);
				SnapshotView->bIsSharedSnapshot = SharedSnapshot->IsAutoSnapshot;
				SnapshotView->bIsSharedSnapshot = true;
				SnapshotView->Author = FText::FromString(SharedSnapshot->Author->Email);
				SnapshotView->ManifestID = FText::FromString(SharedSnapshot->ManifestId);
				SnapshotView->TimeStamp = FDateTime::FromUnixTimestampDecimal(SharedSnapshot->SavedTimestamp * 0.001);
				SnapshotView->Realm = FText::FromString(SharedSnapshot->ProjectData->RealmName);
				SnapshotView->PID = FText::FromString(SharedSnapshot->ProjectData->PID);
				SnapshotView->Path = SharedSnapshot->Path;

				SnapshotView->Contents.Reserve(SharedSnapshot->Contents.Num());
				const FBeamContentManifestId SnapshotManifestId{SharedSnapshot->ManifestId};

				for (UContentSnapshotListItemStreamData* Content : SharedSnapshot->Contents)
				{
					FBeamSnapshotContentEntry LocalViewContent;
					LocalViewContent.Name = FText::FromString(Content->Name);
					LocalViewContent.CurrentStatus = static_cast<EBeamLocalContentStatus>(Content->CurrentStatus);

					SnapshotView->Contents.Add(LocalViewContent);
				}

				SnapshotLocalViews.Add(SnapshotView);
			}

			for (UManifestSnapshotItemStreamData* LocalSnapshot : Data->LocalSnapshots)
			{
				auto SnapshotView = NewObject<UBeamSnapshotLocalView>();
				SnapshotView->Name = FText::FromString(LocalSnapshot->Name);
				SnapshotView->bIsSharedSnapshot = LocalSnapshot->IsAutoSnapshot;
				SnapshotView->bIsSharedSnapshot = false;
				SnapshotView->Author = FText::FromString(LocalSnapshot->Author->Email);
				SnapshotView->ManifestID = FText::FromString(LocalSnapshot->ManifestId);
				SnapshotView->TimeStamp = FDateTime::FromUnixTimestampDecimal(LocalSnapshot->SavedTimestamp * 0.001);
				SnapshotView->Realm = FText::FromString(LocalSnapshot->ProjectData->RealmName);
				SnapshotView->PID = FText::FromString(LocalSnapshot->ProjectData->PID);
				SnapshotView->Path = LocalSnapshot->Path;

				SnapshotView->Contents.Reserve(LocalSnapshot->Contents.Num());
				const FBeamContentManifestId SnapshotManifestId{LocalSnapshot->ManifestId};

				for (UContentSnapshotListItemStreamData* Content : LocalSnapshot->Contents)
				{
					FBeamSnapshotContentEntry LocalViewContent;
					LocalViewContent.Name = FText::FromString(Content->Name);
					LocalViewContent.CurrentStatus = static_cast<EBeamLocalContentStatus>(Content->CurrentStatus);

					SnapshotView->Contents.Add(LocalViewContent);
				}

				SnapshotLocalViews.Add(SnapshotView);
			}
		}

		// TODO: Sort...
		// TODO: Make sure that the LocalView for the object where this is true "SharedSnapshot->IsAutoSnapshot == true" is always at the top of the list.

		OnRefreshCompleted.ExecuteIfBound(SnapshotLocalViews);
	};

	List->OnCompleted = [List](const int& ErrorCode, const FBeamOperationHandle&)
	{
		if (ErrorCode != 0)
		{
			// TODO Handle error.
			for (FBeamCliError Error : List->Errors)
			{
			}
		}
	};

	FString Args;
	if (!ManifestId.AsString.IsEmpty())
		Args += FString::Printf(TEXT("--manifest-id %s"), *ManifestId.AsString);
	if (!Realm.AsString.IsEmpty())
		Args += FString::Printf(TEXT("--pid %s"), *Realm.AsString);

	Cli->RunCommandServer(List, {Args}, {});
}

void UBeamEditorContent::CopyContentSnapshots(FString OldPath, bool bIsSharedSnapshot, FBeamSnapshotCopied OnSnapshotsCopied)
{
	IFileManager& FileManager = IFileManager::Get();

	// Check if source file exists
	if (!FileManager.FileExists(*OldPath))
	{
		UE_LOG(LogBeamContent, Error, TEXT("Source snapshot file does not exist: %s"), *OldPath);
		auto value = FString::Printf(TEXT("Source snapshot file does not exist: %s"), *OldPath);
		ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
		OnSnapshotsCopied.ExecuteIfBound();
		return;
	}

	// Normalize the path to use consistent separators (convert to platform format)
	FString NormalizedOldPath = OldPath;
	FPaths::NormalizeFilename(NormalizedOldPath);

	// Parse the old path to determine source and destination
	FString NewPath;

	if (bIsSharedSnapshot)
	{
		// Copy from local (.beamable/local/contentSnapshots) to shared (.beamable/shared/contentSnapshots)
		if (NormalizedOldPath.Contains(TEXT("/local/contentSnapshots/")))
		{
			NewPath = NormalizedOldPath.Replace(TEXT("/local/contentSnapshots/"), TEXT("/shared/contentSnapshots/"));
		}
		else if (NormalizedOldPath.Contains(TEXT("\\local\\contentSnapshots\\")))
		{
			NewPath = NormalizedOldPath.Replace(TEXT("\\local\\contentSnapshots\\"), TEXT("\\shared\\contentSnapshots\\"));
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Invalid local snapshot path format: %s (normalized: %s)"), *OldPath, *NormalizedOldPath);
			auto value = FString::Printf(TEXT("Invalid local snapshot path format: %s"), *OldPath);
			ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
			OnSnapshotsCopied.ExecuteIfBound();
			return;
		}
	}
	else
	{
		// Copy from shared (.beamable/shared/contentSnapshots) to local (.beamable/local/contentSnapshots)
		if (NormalizedOldPath.Contains(TEXT("/shared/contentSnapshots/")))
		{
			NewPath = NormalizedOldPath.Replace(TEXT("/shared/contentSnapshots/"), TEXT("/local/contentSnapshots/"));
		}
		else if (NormalizedOldPath.Contains(TEXT("\\shared\\contentSnapshots\\")))
		{
			NewPath = NormalizedOldPath.Replace(TEXT("\\shared\\contentSnapshots\\"), TEXT("\\local\\contentSnapshots\\"));
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Invalid shared snapshot path format: %s (normalized: %s)"), *OldPath, *NormalizedOldPath);
			auto value = FString::Printf(TEXT("Invalid shared snapshot path format: %s"), *OldPath);
			ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
			OnSnapshotsCopied.ExecuteIfBound();
			return;
		}
	}

	// Ensure the destination directory exists
	FString DestinationDir = FPaths::GetPath(NewPath);
	if (!FileManager.DirectoryExists(*DestinationDir))
	{
		if (!FileManager.MakeDirectory(*DestinationDir, true))
		{
			UE_LOG(LogBeamContent, Error, TEXT("Failed to create destination directory: %s"), *DestinationDir);
			auto value = FString::Printf(TEXT("Failed to create destination directory: %s"), *DestinationDir);
			ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
			OnSnapshotsCopied.ExecuteIfBound();
			return;
		}
	}

	// Copy the file
	if (FileManager.Copy(*NewPath, *OldPath, true, true) == COPY_OK)
	{
		UE_LOG(LogBeamContent, Log, TEXT("Successfully copied snapshot from %s to %s"), *OldPath, *NewPath);
		FString SnapshotType = bIsSharedSnapshot ? TEXT("shared") : TEXT("local");
		auto value = FString::Printf(TEXT("Successfully copied snapshot to %s location"), *SnapshotType);
		OnSnapshotsCopied.ExecuteIfBound();
	}
	else
	{
		UE_LOG(LogBeamContent, Error, TEXT("Failed to copy snapshot from %s to %s"), *OldPath, *NewPath);
		auto value = FString::Printf(TEXT("Failed to copy snapshot from %s to %s"), *OldPath, *NewPath);
		ShowNotification(TEXT("Error"), FText::FromString(value), 5.0f, 1.0f);
		OnSnapshotsCopied.ExecuteIfBound();
	}
}

void UBeamEditorContent::SyncContentHistoryChangelist(FString ManifestUid)
{
	if (ManifestUid.IsEmpty())
	{
		UE_LOG(LogBeamContent, Verbose, TEXT("Skipping content history sync for empty manifest UID"));
		return;
	}

	// This is initialized here but completed in the HistoryPs callbacks (unless an error occurred).
	FString Msg = FString::Printf(TEXT("Synchronizing Content History Changelist for manifest %s..."), *ManifestUid);
	HistoryChangelistSyncSlowTask = new FSlowTask(2, FText::FromString(Msg));
	HistoryChangelistSyncSlowTask->Initialize();
	HistoryChangelistSyncSlowTask->MakeDialog();

	auto SyncCmd = NewObject<UBeamCliContentHistorySyncChangelistCommand>();
	SyncCmd->OnCompleted = [this, SyncCmd](const int& ErrorCode, const FBeamOperationHandle&)
	{
		if (ErrorCode != 0)
		{
			for (FBeamCliError Error : SyncCmd->Errors)
			{
				UE_LOG(LogBeamContent, Error, TEXT("ERROR syncing content history changelist: %s"), *Error.Message);
			}

			// Close the slow task in the error case.
			if (HistoryChangelistSyncSlowTask)
			{
				HistoryChangelistSyncSlowTask->Destroy();
				delete HistoryChangelistSyncSlowTask;
			}
		}
	};

	FString Args = FString::Printf(TEXT("--manifest-uid %s"), *ManifestUid);
	Cli->RunCommandServer(SyncCmd, {Args}, {});
}

FString UBeamEditorContent::GetJsonBlobPath(FString RowName, FBeamContentManifestId ManifestId)
{
	return DefaultBeamableProjectContentObjects / GetDefault<UBeamCoreSettings>()->TargetRealm.Pid.AsString / ManifestId.AsString / RowName + TEXT(".json");
}

void UBeamEditorContent::BakeManifest(FBeamContentManifestId Manifest)
{
	UBeamContentCache* Cache = NewObject<UBeamContentCache>(this);

	Cache->ManifestId = Manifest;

	for (const auto& Entry : LocalManifestCache[Manifest]->Entries)
	{
		const auto Hash = Entry->Hash;
		const bool bNotInCache = !Cache->Hashes.Contains(Entry->FullId);
		const bool bInCacheButModified = Cache->Hashes.Contains(Entry->FullId) && !Cache->Hashes[Entry->FullId].Equals(Hash);
		if (bNotInCache || bInCacheButModified)
		{
			// Create a new BeamContentObject instance of each content Object
			UBeamContentObject* Content;
			LoadContentObjectInstance(LocalManifestCache[Manifest], Entry->FullId, Content, Cache);

			// Add it to the BCC_ BeamRuntimeContentCache.
			Cache->Cache.Add(Entry->FullId, Content);
			Cache->Hashes.Add(Entry->FullId, Hash);
		}
	}

	auto CoreSettings = GetMutableDefault<UBeamCoreSettings>();

	const FString BakedContentPath = FPaths::ProjectContentDir() + CoreSettings->BakedContentFolderName + "/" +
		CoreSettings->GlobalBakedContentFileName;

	TArray<uint8> SerializedData;

	auto Serializer = NewObject<UBeamContentCacheSerializer>(GetTransientPackage(), GetDefault<UBeamCoreSettings>()->DefaultContentSerializer);
	FArchive* Writer = Serializer->GetDefaultContentCacheSerializer(SerializedData, true);
	FBeamContentCacheSerializationContext Ctx(nullptr, true, *Writer, ContentTypeStringToContentClass, ContentClassToContentTypeString);
	Cache->SerializeToBinary(Ctx, Serializer);
	delete Writer;

	if (FFileHelper::SaveArrayToFile(SerializedData, *BakedContentPath))
	{
		UE_LOG(LogBeamContent, Log, TEXT("Saved new baked content."));
	}
	else
	{
		UE_LOG(LogBeamContent, Error, TEXT("Error while baking new content."));
	}

	//Add the baked folder to the project settings so that it doesnt get packaged in the .PAK and gets coppied as it is with the packaged game
	if (UProjectPackagingSettings* PackagingSettings = GetMutableDefault<UProjectPackagingSettings>())
	{
		bool PathAlreadyAdded = false;
		for (FDirectoryPath& DirectoryPath : PackagingSettings->DirectoriesToAlwaysStageAsNonUFS)
		{
			if (DirectoryPath.Path == CoreSettings->BakedContentFolderName)
			{
				PathAlreadyAdded = true;
			}
		}
		if (!PathAlreadyAdded)
		{
			PackagingSettings->DirectoriesToAlwaysStageAsNonUFS.Add(FDirectoryPath{CoreSettings->BakedContentFolderName});

			PackagingSettings->SaveConfig(CPF_Config, *PackagingSettings->GetDefaultConfigFilename());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to retrieve packaging settings."));
	}
}

bool UBeamEditorContent::DeleteCachedContentFolder(FString& ErrorMessage)
{
	const FString CachedContentPath = UBeamContentCache::CACHE_FOLDER();

	// Check if the directory exists
	if (!FPaths::DirectoryExists(CachedContentPath))
	{
		ErrorMessage = FString::Printf(TEXT("Failed to delete cached content folder, Directory does not exist: %s"), *CachedContentPath);
		return false;
	}

	// Delete the directory and all its contents
	IFileManager& FileManager = IFileManager::Get();
	const bool bDeleteSuccess = FileManager.DeleteDirectory(*CachedContentPath, false, true);

	if (bDeleteSuccess)
	{
		UE_LOG(LogBeamContent, Log, TEXT("Successfully deleted cached content folder: %s"), *CachedContentPath);
		ErrorMessage.Empty();
		return true;
	}
	else
	{
		ErrorMessage = FString::Printf(TEXT("Failed to delete cached content folder: %s"), *CachedContentPath);
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrorMessage);
		return false;
	}
}

void UBeamEditorContent::RebuildLocalManifestCache(const TArray<ULocalContentManifestStreamData*>& Data)
{
	for (const auto& d : Data)
	{
		ManifestIds.AddUnique(d->ManifestId);
		LocalManifestCache.Add(d->ManifestId, d);
		UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Found Manifest with Id %s"), *GetName(),
		       *d->ManifestId)
	}
}

void UBeamEditorContent::UpdateLocalManifestCache(ULocalContentManifestStreamData* ToUpdate, ULocalContentManifestStreamData* ToClear)
{
	const auto ManifestId = FBeamContentManifestId{ToUpdate->ManifestId};

	if (auto Existing = LocalManifestCache.FindOrAdd(ManifestId, ToUpdate))
	{
		// Let's start by removing all entries in the update/remove
		Existing->Entries.RemoveAll([ToUpdate, ToClear](const ULocalContentManifestEntryStreamData* ContentEntry)
		{
			bool bContainedInToUpdate = ToUpdate->Entries.ContainsByPredicate([&ContentEntry](const ULocalContentManifestEntryStreamData* E)
			{
				return ContentEntry->FullId == E->FullId;
			});

			bool bContainedInToClear = ToClear->Entries.ContainsByPredicate([&ContentEntry](const ULocalContentManifestEntryStreamData* E)
			{
				return ContentEntry->FullId == E->FullId;
			});
			return bContainedInToUpdate || bContainedInToClear;
		});

		// Then... we re-add the updated versions of the asset.
		for (const auto Entry : ToUpdate->Entries)
		{
			Existing->Entries.Add(DuplicateObject<ULocalContentManifestEntryStreamData>(Entry, GetTransientPackage()));
			if (LoadedContentObjects.Contains(Entry->FullId))
			{
				auto CachedObjInstance = LoadedContentObjects[Entry->FullId];
				const auto FilePath = Entry->JsonFilePath;
				FString FileContents;
				if (FFileHelper::LoadFileToString(FileContents, *FilePath))
				{
					CachedObjInstance->FromBasicJson(FileContents);
					CachedObjInstance->Id = Entry->FullId;
					CachedObjInstance->Version = Entry->Hash;
				}
			}
		}
	}
}

void UBeamEditorContent::RunPsCommand(FBeamOperationHandle FirstEventOp)
{
	auto WatchCommand = NewObject<UBeamCliContentPsCommand>();
	WatchCommand->OnStreamOutput = [this, FirstEventOp](TArray<UBeamCliContentPsStreamData*>& Stream, TArray<int64>&, const FBeamOperationHandle&)
	{
		const auto Data = Stream.Last();
		if (Data->EventType == EVT_TYPE_CONTENT_PS_FullRebuild)
		{
			RebuildLocalManifestCache(Data->RelevantManifestsAgainstLatest);
			RequestTracker->TriggerOperationSuccess(FirstEventOp, TEXT(""));
			OnContentFullRebuild.Broadcast();
		}

		if (Data->EventType == EVT_TYPE_CONTENT_PS_RemotePublished)
		{
			UE_LOG(LogBeamContent, Display,
			       TEXT(
				       "Remote content publish detected. PUBLISHER=%s, CONTENT_ID=%s"
			       ), *Data->PublisherEmail,
			       *FString::Join(Data->SyncReports[0]->ConflictingContents, TEXT(", ")));


			// Bubble this up to the UI so we can add a UE UI-notification with relevant information.
			if (Data->SyncReports.Num() > 0)
			{
				const auto SyncReport = Data->SyncReports[0];

				const auto ConflictsDetectedOnIds = SyncReport->ConflictingContents;
				const auto AutoSyncedIds = SyncReport->AutoSynchedContents;
				const auto DeletedCreatedContentIds = SyncReport->DeletedCreatedContents;
				const auto ReferenceUpdatedIds = SyncReport->ReferenceUpdatedContents;

				const auto Title = FString(TEXT("[Beamable] Content Published to Realm - By ")) + Data->PublisherEmail;
				auto Body = FString(TEXT(""));

				if (ConflictsDetectedOnIds.Num() > 0)
				{
					Body += TEXT("Conflicts: \n");
					for (FString ConflictsDetectedOnId : ConflictsDetectedOnIds)
						Body += FString::Printf(TEXT("\t- %s\n"), *ConflictsDetectedOnId);
				}

				if (AutoSyncedIds.Num() > 0)
				{
					Body += TEXT("Downloaded Content: \n");
					for (FString AutoSyncedId : AutoSyncedIds)
						Body += FString::Printf(TEXT("\t- %s\n"), *AutoSyncedId);
				}

				if (DeletedCreatedContentIds.Num() > 0)
				{
					Body += TEXT("Deleted Content: \n");
					for (FString DeletedCreatedContentId : DeletedCreatedContentIds)
						Body += FString::Printf(TEXT("\t- %s\n"), *DeletedCreatedContentId);
				}

				// Create and send the notification
				FNotificationInfo Info{FText::FromString(Title)};
				Info.SubText = FText::FromString(Body);

				//Set a default expire duration and other parameters

				Info.ExpireDuration = 20.0f;
				Info.FadeOutDuration = 2.0f;
				Info.Image = ConflictsDetectedOnIds.Num() > 0 ? FAppStyle::GetBrush(TEXT("Icons.Warning")) : FAppStyle::GetBrush(TEXT("Icons.Success"));
				Info.ForWindow = FSlateApplication::Get().GetActiveTopLevelWindow();

				//And call Add Notification, this is pretty much it!
				FUserSlot MainEditorSlot;
				FBeamRealmUser MainEditorDeveloper;
				Editor->TryGetMainEditorSlot(MainEditorSlot, MainEditorDeveloper);
				if (Data->PublisherEmail != MainEditorDeveloper.Email)
				{
					FSlateNotificationManager::Get().AddNotification(Info);
				}
			}


			RebuildLocalManifestCache(Data->RelevantManifestsAgainstLatest);
			OnContentRemotePublish.Broadcast();
		}

		if (Data->EventType == EVT_TYPE_CONTENT_PS_ChangedContent)
		{
			const auto ManifestCount = Data->RelevantManifestsAgainstLatest.Num();
			for (int i = 0; i < ManifestCount; ++i)
			{
				const auto ToUpdate = Data->RelevantManifestsAgainstLatest[i];
				const auto ToRemove = Data->ToRemoveLocalEntries[i];
				UpdateLocalManifestCache(ToUpdate, ToRemove);
			}
			OnContentLocalChange.Broadcast();
		}
	};
	WatchCommand->OnCompleted = [this, WatchCommand, FirstEventOp](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode != 0)
		{
			// If we completed without receiving the first event, we trigger an error of the first event.
			if (WatchCommand->Stream.Num() == 0) RequestTracker->TriggerOperationError(FirstEventOp, TEXT("Failed to fetch initial full-rebuild event"));

			const auto DuplicateCommand = DuplicateObject<UBeamCliContentPsCommand>(WatchCommand, GetTransientPackage());
			const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
			Cli->RunCommand(DuplicateCommand, {TEXT("-w"), ReqProcess}, {});
		}
	};

	const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
	Cli->RunCommand(WatchCommand, {TEXT("-w"), ReqProcess}, {});
}

void UBeamEditorContent::RunHistoryPsCommand(FBeamOperationHandle FirstEventOp)
{
	auto WatchCommand = NewObject<UBeamCliContentHistoryCommand>();
	WatchCommand->OnStreamOutput = [this, FirstEventOp](TArray<UBeamCliContentHistoryStreamData*>& Stream, TArray<int64>&, const FBeamOperationHandle&)
	{
		const auto Data = Stream.Last();

		if (Data->EventType == EVT_TYPE_CONTENT_HISTORY_EntriesLoaded)
		{
			// Update in-memory state using EntriesPage and EntriesToRemove
			if (Data->EntriesPage)
			{
				// The ManifestId key is always "global" for now
				const FBeamContentManifestId GlobalManifestId(Global_Manifest_Name);

				// Get or create the cached page
				UContentHistoryEntriesPageStreamData* CachedPage = LocalContentHistoryEntriesCache.FindOrAdd(GlobalManifestId);
				if (!CachedPage)
				{
					CachedPage = NewObject<UContentHistoryEntriesPageStreamData>(GetTransientPackage());
					LocalContentHistoryEntriesCache.Add(GlobalManifestId, CachedPage);
				}

				// Merge the new entries into the cached page
				for (const auto& Entry : Data->EntriesPage->Entries)
				{
					// Remove any existing entry with the same ManifestUid (update case)
					CachedPage->Entries.RemoveAll([&Entry](const UContentHistoryEntryStreamData* ExistingEntry)
					{
						return ExistingEntry && ExistingEntry->ManifestUid == Entry->ManifestUid;
					});

					// Add the new entry
					CachedPage->Entries.Add(DuplicateObject<UContentHistoryEntryStreamData>(Entry, GetTransientPackage()));
					UE_LOG(LogBeamContent, Display, TEXT("Added content history entry: ManifestUid=%s"), *Entry->ManifestUid);
				}

				// Sort entries by date (newest first)
				CachedPage->Entries.Sort([](const UContentHistoryEntryStreamData& A, const UContentHistoryEntryStreamData& B)
				{
					return A.CreatedDate > B.CreatedDate;
				});

				// Update the date range
				if (CachedPage->Entries.Num() > 0)
				{
					CachedPage->StartDate = CachedPage->Entries[CachedPage->Entries.Num() - 1]->CreatedDate;
					CachedPage->EndDate = CachedPage->Entries[0]->CreatedDate;
				}
			}

			// Remove entries specified in EntriesToRemove
			for (const auto& ManifestUidToRemove : Data->EntriesToRemove)
			{
				const FBeamContentManifestId GlobalManifestId(Global_Manifest_Name);

				// Find the cached page
				if (auto* CachedPage = LocalContentHistoryEntriesCache.Find(GlobalManifestId))
				{
					// Remove entries with matching ManifestUid
					(*CachedPage)->Entries.RemoveAll([&ManifestUidToRemove](const UContentHistoryEntryStreamData* Entry)
					{
						return Entry && Entry->ManifestUid == ManifestUidToRemove;
					});
				}
			}

			if (RequestTracker->IsOperationActive(FirstEventOp)) RequestTracker->TriggerOperationSuccess(FirstEventOp, TEXT(""));
			OnContentHistoryEntriesUpdated.Broadcast();
		}

		if (Data->EventType == EVT_TYPE_CONTENT_HISTORY_ChangelistsLoaded)
		{
			// Update in-memory state using ChangelistsPage and ChangelistsToRemove
			for (const auto& Changelist : Data->ChangelistsPage->Changelists)
			{
				// Store changelist keyed by its ManifestUid as FString
				LocalContentHistoryChangelistCache.Add(Changelist->ManifestUid, DuplicateObject<UContentHistoryChangelistStreamData>(Changelist, GetTransientPackage()));

				// Collect all content IDs from Changelist maps
				TArray<FString> AllContentIds;
				TArray<FString> ContentIdsToSync;
				TArray<FString> ContentIdsToNotSync;

				// Add content ids in this changelist to a list
				for (const auto& Pair : Changelist->Created) AllContentIds.Add(Pair.Key);
				for (const auto& Pair : Changelist->Modified) AllContentIds.Add(Pair.Key);
				for (const auto& Pair : Changelist->Removed) AllContentIds.Add(Pair.Key);

				// Filter out content IDs that already exist locally
				for (const auto& ContentId : AllContentIds)
				{
					const auto* Entry = Changelist->Created.Find(ContentId);
					if (!Entry) Entry = Changelist->Modified.Find(ContentId);
					if (!Entry) Entry = Changelist->Removed.Find(ContentId);

					if (Entry && *Entry)
					{
						// Check if the JSON file exists locally
						if ((*Entry)->JsonFilePath.IsEmpty() || !FPaths::FileExists((*Entry)->JsonFilePath))
							ContentIdsToSync.Add(ContentId);
						else
							ContentIdsToNotSync.Add(ContentId);
					}
				}

				// Only run sync command if there are content IDs to sync
				if (ContentIdsToSync.Num() > 0)
				{
					auto SyncCommand = NewObject<UBeamCliContentHistorySyncContentCommand>();
					SyncCommand->OnStreamOutput = [this, Changelist](TArray<UBeamCliContentHistorySyncContentStreamData*>& Stream, TArray<int64>&, const FBeamOperationHandle&)
					{
						// Content has been synced, now load into memory
						const auto SyncData = Stream.Last();
						for (const auto& ContentEntry : SyncData->ContentEntries) LoadContentHistoryObject(Changelist->ManifestUid, ContentEntry);

						if (HistoryChangelistSyncSlowTask)
						{
							HistoryChangelistSyncSlowTask->Destroy();
							delete HistoryChangelistSyncSlowTask;
						}

						OnContentHistoryContentSynced.Broadcast();
					};

					const FString ManifestUidArg = FString::Printf(TEXT("--manifest-uid %s"), *Changelist->ManifestUid);
					const FString ContentIdsArg = FString::Printf(TEXT("--content-ids %s"), *FString::Join(ContentIdsToSync, TEXT(" ")));
					Cli->RunCommandServer(SyncCommand, {ManifestUidArg, ContentIdsArg}, {});

					if (HistoryChangelistSyncSlowTask)
					{
						FString BulletList;
						for (const FString& ContentId : ContentIdsToSync)
						{
							BulletList += FString::Printf(TEXT("  • %s\n"), *ContentId);
						}

						FString NotSyncBulletList;
						for (const FString& ContentId : ContentIdsToNotSync)
						{
							NotSyncBulletList += FString::Printf(TEXT("  • %s\n"), *ContentId);
						}


						FString Message = FString::Printf(
							TEXT("Syncing Content History Changelist\n\n")
							TEXT("Syncing %d content items:\n%s\n")
							TEXT("Skipping %d items (already synced):\n%s"),
							ContentIdsToSync.Num(), *BulletList, ContentIdsToNotSync.Num(), *NotSyncBulletList);
						HistoryChangelistSyncSlowTask->EnterProgressFrame(1, FText::FromString(Message));
					}
				}
				else
				{
					// All content exists locally, just load into memory
					for (const auto& Pair : Changelist->Created) LoadContentHistoryObject(Changelist->ManifestUid, Pair.Value);
					for (const auto& Pair : Changelist->Modified) LoadContentHistoryObject(Changelist->ManifestUid, Pair.Value);
					for (const auto& Pair : Changelist->Removed) LoadContentHistoryObject(Changelist->ManifestUid, Pair.Value);

					if (HistoryChangelistSyncSlowTask)
					{
						HistoryChangelistSyncSlowTask->Destroy();
						delete HistoryChangelistSyncSlowTask;
					}
				}
			}

			// Remove changelists specified in ChangelistsToRemove
			for (const auto& ChangelistToRemove : Data->ChangelistsToRemove)
			{
				// Remove the changelist from the cache using the ManifestUid string
				LocalContentHistoryChangelistCache.Remove(ChangelistToRemove);
			}

			OnContentHistoryChangelistSynced.Broadcast();
		}
	};
	WatchCommand->OnCompleted = [this, WatchCommand, FirstEventOp](const int& ResCode, const FBeamOperationHandle&)
	{
		if (ResCode != 0)
		{
			// If we completed without receiving the first event, we trigger an error of the first event.
			if (WatchCommand->Stream.Num() == 0) RequestTracker->TriggerOperationError(FirstEventOp, TEXT("Failed to fetch initial full-rebuild event"));

			const auto DuplicateCommand = DuplicateObject<UBeamCliContentHistoryCommand>(WatchCommand, GetTransientPackage());
			const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
			Cli->RunCommand(DuplicateCommand, {TEXT("-w"), ReqProcess}, {});
		}
	};

	const auto ReqProcess = FString::Printf(TEXT("--require-process-id %d"), FPlatformProcess::GetCurrentProcessId());
	Cli->RunCommand(WatchCommand, {TEXT("-w"), ReqProcess}, {});
}

bool UBeamEditorContent::IsValidContentName(const FString& ContentName, FText& Err)
{
	FString Errs = TEXT("Found Content Name Errors:\n");
	auto bIsValid = !ContentName.IsEmpty();

	const auto InvalidChars = TArray{TEXT(" "), TEXT(".")};
	for (const auto InvalidChar : InvalidChars)
	{
		const auto bContainsInvalidChar = ContentName.Contains(InvalidChar);
		bIsValid &= !bContainsInvalidChar;

		if (bContainsInvalidChar)
		{
			Errs += FString::Printf(TEXT("- Content cannot have the character [%s] in them."), InvalidChar);
		}
	}

	if (!bIsValid)
		Err = FText::FromString(Errs);
	return bIsValid;
}


UClass** UBeamEditorContent::FindContentTypeByName(FString TypeName)
{
	return AllContentTypes.FindByPredicate([TypeName](const UClass* Class)
	{
		return Class->GetFName().ToString().Equals(TypeName);
	});
}

UClass** UBeamEditorContent::FindContentTypeByTypeId(FString TypeId)
{
	return ContentTypeStringToContentClass.Find(TypeId);
}

void UBeamEditorContent::LoadContentHistoryObject(const FString& ManifestUid, UContentHistoryChangelistEntryStreamData* ContentEntry)
{
	if (!ContentEntry || ContentEntry->JsonFilePath.IsEmpty())
	{
		return;
	}

	// Parse the ManifestUid to create the history entry ID
	FBeamContentHistoryContentEntryId HistoryId;
	HistoryId.ContentId = FBeamContentId(ContentEntry->FullId);
	HistoryId.ManifestUid = ManifestUid;

	// Check if we already have this object loaded - if so, it's a no-op since the file is read-only
	if (LoadedContentHistoryObjects.Contains(HistoryId)) return;

	// Load the JSON file
	FString FileContents;
	if (!FFileHelper::LoadFileToString(FileContents, *ContentEntry->JsonFilePath))
	{
		UE_LOG(LogBeamContent, Warning, TEXT("Failed to load content history file: %s"), *ContentEntry->JsonFilePath);
		return;
	}

	// Create new content object using the closest valid type
	UClass* ObjectClass;
	TEnumAsByte<EBeamContentObjectSupportLevel> SupportLevel;
	UBeamContentObject::GetClassForTypeId(ContentTypeStringToContentClass, ContentEntry->TypeName, ObjectClass, SupportLevel);

	if (ObjectClass)
	{
		UBeamContentObject* ContentObject = NewObject<UBeamContentObject>(GetTransientPackage(), ObjectClass);
		ContentObject->SupportLevel = SupportLevel;
		ContentObject->FromBasicJson(FileContents);
		ContentObject->Id = HistoryId.ContentId.AsString;
		
		
		ContentObject->Version = ContentEntry->NewChecksum;
		if (ContentObject->Version.IsEmpty()) ContentObject->Version = ContentEntry->OldChecksum;
		
		LoadedContentHistoryObjects.Add(HistoryId, ContentObject);

		if (SupportLevel == PartialSupport)
		{
			UE_LOG(LogBeamContent, Warning, TEXT("Loaded content history object with partial support. TYPE=%s, CONTENT_ID=%s"), *ContentEntry->TypeName, *ContentEntry->FullId);
		}
		else if (SupportLevel == NoSupport)
		{
			UE_LOG(LogBeamContent, Warning, TEXT("Loaded content history object with no support (using base type). TYPE=%s, CONTENT_ID=%s"), *ContentEntry->TypeName, *ContentEntry->FullId);
		}
	}
	else
	{
		UE_LOG(LogBeamContent, Error, TEXT("Failed to create content history object. TYPE=%s, CONTENT_ID=%s"), *ContentEntry->TypeName, *ContentEntry->FullId);
	}
}

bool UBeamEditorContent::TryLoadContentObject(const FBeamContentManifestId& OwnerManifest, FBeamContentId ContentId,
                                              UBeamContentObject*& OutLoadedContentObject)
{
	// Hit the cache first.
	if (LoadedContentObjects.Contains(ContentId))
	{
		OutLoadedContentObject = LoadedContentObjects.FindRef(ContentId);
		return true;
	}

	// Otherwise, find the UClass for the content type. Load the JSON and deserialize it into the UBeamContentObject.
	return LoadContentObjectInstance(LocalManifestCache[OwnerManifest], ContentId, OutLoadedContentObject,
	                                 GetTransientPackage());
}

bool UBeamEditorContent::LoadContentObjectInstance(const ULocalContentManifestStreamData* Manifest,
                                                   const FBeamContentId& ContentId,
                                                   UBeamContentObject*& OutNewContentObject, UObject* Outer)
{
	// Make sure the object exists in the manifest
	if (const auto Entry = Manifest->Entries.FindByPredicate([ContentId](ULocalContentManifestEntryStreamData* E)
	{
		return E->FullId.Equals(ContentId.AsString);
	}))
	{
		// Otherwise, find the UClass for the content type. Load the JSON and deserialize it into the UBeamContentObject.
		UClass* ObjectClass;
		TEnumAsByte<EBeamContentObjectSupportLevel> SupportLevel;
		UBeamContentObject::GetClassForTypeId(ContentTypeStringToContentClass, ContentId.GetTypeId(), ObjectClass, SupportLevel);

		// Create the object instance
		if (ObjectClass)
		{
			const auto FilePath = (*Entry)->JsonFilePath;
			FString FileContents;
			if (FFileHelper::LoadFileToString(FileContents, *FilePath))
			{
				const auto ContentObject = NewObject<UBeamContentObject>(Outer, ObjectClass);
				OutNewContentObject = ContentObject;
				OutNewContentObject->SupportLevel = SupportLevel;
				OutNewContentObject->FromBasicJson(FileContents);
				OutNewContentObject->Id = ContentId.AsString;
				OutNewContentObject->Version = (*Entry)->Hash;
				return true;
			}
		}
	}
	return false;
}

void UBeamEditorContent::GetContentTypeToIdMaps(TMap<FName, TArray<TSharedPtr<FName>>>& Map)
{
	for (const auto& LocalManifest : LocalManifestCache)
	{
		const auto Entries = LocalManifest.Value->Entries;
		for (const auto& Entry : Entries)
		{
			FBeamContentId ContentId{Entry->FullId};
			FString ContentTypeId = ContentId.GetTypeId();

			if (const auto ContentType = ContentTypeStringToContentClass.Find(ContentTypeId))
			{
				const auto TypeName = (*ContentType)->GetFName();
				if (!Map.Contains(TypeName))
					Map.Add(TypeName, {});

				if (!Map[TypeName].ContainsByPredicate([Entry](TSharedPtr<FName> N)
				{
					return N->ToString().Equals(Entry->FullId);
				}))
				{
					Map[TypeName].Add(MakeShareable(new FName(Entry->FullId)));
				}
			}
			else
			{
				UE_LOG(LogBeamContent, Warning,
				       TEXT(
					       "Unreal UBeamContentObject implementation not found for content of given type. CONTENT_TYPE_ID=%s, CONTENT_ID=%s"
				       ), *ContentTypeId,
				       *ContentId.AsString);
			}
		}
	}
}

bool UBeamEditorContent::GetContentTypeFromId(FBeamContentId Id, FString& TypeName)
{
	const auto IdStr = Id.AsString;
	for (const auto& LocalManifest : LocalManifestCache)
	{
		const auto Entries = LocalManifest.Value->Entries;
		for (const auto& Entry : Entries)
		{
			if (Entry->FullId.Equals(Id.AsString))
			{
				if (const auto Type = FindContentTypeByTypeId(Id.GetTypeId()))
				{
					TypeName = (*Type)->GetFName().ToString();
					return true;
				}
			}
		}
	}
	TypeName = TEXT("");
	return false;
}

void UBeamEditorContent::ShowNotification(FString Title, FText Body, float ExpireDuration, float FadeOutDuration)
{
	// Create and send the notification
	FNotificationInfo Info{FText::FromString(Title)};
	Info.SubText = Body;

	//Set a default expire duration and other parameters
	Info.ExpireDuration = ExpireDuration;
	Info.FadeOutDuration = FadeOutDuration;

	// Set the icon
	Info.Image = FAppStyle::GetBrush(TEXT("Icons.Error"));

	// We always show this at the top level.
	Info.ForWindow = FSlateApplication::Get().GetActiveTopLevelWindow();

	//And call Add Notification, this is pretty much it!
	FSlateNotificationManager::Get().AddNotification(Info);
}
