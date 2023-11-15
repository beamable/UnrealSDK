// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Content/BeamEditorContent.h"

#include "HttpModule.h"
#include "IContentBrowserSingleton.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "AutoGen/BaseContentReference.h"
#include "Content/BeamContentCache.h"
#include "Content/DownloadContentState.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/FileHelper.h"
#include "Settings/ProjectPackagingSettings.h"
#include "Subsystems/BeamEditor.h"

void UBeamEditorContent::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Display, TEXT("Initializing Beam Editor - Content System!"))

	ContentApi = GEngine->GetEngineSubsystem<UBeamContentApi>();
	AssetEditorSubsystem = Collection.InitializeDependency<UAssetEditorSubsystem>();
	EditorAssetSubsystem = Collection.InitializeDependency<UEditorAssetSubsystem>();

	LocalContentManifestDataTableHandler = AssetEditorSubsystem->OnAssetOpenedInEditor().AddUObject(this, &UBeamEditorContent::HandleAssetOpenedInEditor);

	// Grab Asset Tools module to help us create assets here.
	AssetToolsModule = &FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	ContentBrowserModule = &FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");


	// Grab all existing ContentObject classes so we can present them as options in the editing UI and correctly parse them.
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UBeamContentObject::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			UE_LOG(LogTemp, Display, TEXT("Initializing Beam Editor Content System - Found Content Type %s"), *It->GetFName().ToString())

			AllContentTypes.Add(*It);
			AllContentTypeNames.Add(MakeShared<FName>(It->GetFName()));
		}
	}


	// Set up delegate to ensure only existing baked content will be configured in the RuntimeSettings configuration.
	// The reason this doesn't stick is because the ModifyCookDelegate doesn't seem to run in the same process as the editor.
	// This means that, even though the asset change will be visible by the editor process the RuntimeSettings ones won't until the editor is restarted. 
	OnWillEnterPIE = FEditorDelegates::PreBeginPIE.AddLambda([this](bool Cond)
	{
		UBeamCoreSettings* EditorSettings = GetMutableDefault<UBeamCoreSettings>();
		const auto NumBakedContent = EditorSettings->BakedContentManifests.Num(); 
		for (int i = NumBakedContent - 1; i >= 0; --i)
		{
			const auto BeamRuntimeContentCache = EditorSettings->BakedContentManifests[i];
			const auto CookedAssetPath = BeamRuntimeContentCache.ToSoftObjectPath().GetAssetPathString();
			UE_LOG(LogBeamContent, Warning, TEXT("On Will Enter PIE: Cooked content manifest path = %s"), *CookedAssetPath)
			if (!EditorAssetSubsystem->DoesAssetExist(CookedAssetPath))
			{
				EditorSettings->BakedContentManifests.RemoveAt(i);
			}
		}
		
		if(NumBakedContent != EditorSettings->BakedContentManifests.Num())
			EditorSettings->SaveConfig(CPF_Config, *EditorSettings->GetDefaultConfigFilename());		
	});
}


void UBeamEditorContent::Deinitialize()
{
	Super::Deinitialize();
	FEditorDelegates::PreBeginPIE.Remove(OnWillEnterPIE);
	// Clean up asset opened handlers
	{
		AssetEditorSubsystem->OnAssetOpenedInEditor().Remove(LocalContentManifestDataTableHandler);
	}
}

FBeamOperationHandle UBeamEditorContent::InitializeWhenEditorReady()
{
	// We get the operation for this. 
	UE_LOG(LogBeamEditor, Display, TEXT("Editor Subsystem %s - Initializing after Unreal Editor is ready"), *GetName())

	// By default, just return an empty completed operation
	const auto Op = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetName(), {});

	// Ensure we are properly configured with at least one path for baked content.
	const auto EditorSettings = GetMutableDefault<UBeamEditorSettings>();

	const auto bIsCookedManifestPathsEmpty = EditorSettings->CookedManifestsPath.IsEmpty();
	const auto bIsUncookedManifestPathsEmpty = EditorSettings->UncookedManifestsPath.IsEmpty();

	if (bIsCookedManifestPathsEmpty) EditorSettings->CookedManifestsPath.Add(FDirectoryPath{DefaultBeamableCookedContentManifestsPath});
	if (bIsUncookedManifestPathsEmpty) EditorSettings->UncookedManifestsPath.Add(FDirectoryPath{DefaultBeamableUncookedContentManifestsPath});

	// We save this out to the default editor configuration so that this default is always versioned (unless we save config with these parameters, changes to settings objects are local to this developer)
	if (bIsCookedManifestPathsEmpty || bIsUncookedManifestPathsEmpty)
		EditorSettings->SaveConfig(CPF_Config, *EditorSettings->GetDefaultConfigFilename());


	// Ensure that all directories in the cooked manifest paths array exist.
	for (const auto& CookedManifestsPath : EditorSettings->CookedManifestsPath)
	{
		if (!EditorAssetSubsystem->DoesDirectoryExist(CookedManifestsPath.Path))
			EditorAssetSubsystem->MakeDirectory(CookedManifestsPath.Path);
	}

	// Ensure that all directories in the uncooked manifest paths array exist AND are added to the project settings as excluded from cooked builds.
	for (const auto& UncookedManifestsPath : EditorSettings->UncookedManifestsPath)
	{
		if (!EditorAssetSubsystem->DoesDirectoryExist(UncookedManifestsPath.Path))
			EditorAssetSubsystem->MakeDirectory(UncookedManifestsPath.Path);

		auto ProjectPackagingSettings = GetMutableDefault<UProjectPackagingSettings>();
		const auto bAlreadyContains = ProjectPackagingSettings->DirectoriesToNeverCook.FindByPredicate([&UncookedManifestsPath](FDirectoryPath path)
		{
			return path.Path == UncookedManifestsPath.Path;
		});
		if (!bAlreadyContains)
		{
			ProjectPackagingSettings->DirectoriesToNeverCook.Add(UncookedManifestsPath);
		}
	}

	RequestTracker->TriggerOperationSuccess(Op, {});
	return Op;
}

FBeamOperationHandle UBeamEditorContent::InitializeFromRealm(FBeamRealmHandle NewRealm)
{
	// For now, we just need to make sure at least one "global" manifest exists.
	return EnsureGlobalManifest();
}

void UBeamEditorContent::GetLocalManifestIds(TArray<FString>& Keys) const
{
	TArray<FBeamContentManifestId> Ids;
	Keys.Reserve(LocalManifests.GetKeys(Ids));
	for (const auto& Id : Ids)
	{
		Keys.Add(Id.AsString);
	}
}

bool UBeamEditorContent::TryGetLocalManifestById(const FBeamContentManifestId& Id, UDataTable*& Manifest)
{
	if (LocalManifests.Contains(Id))
	{
		Manifest = LocalManifests.FindChecked(Id);
		return true;
	}

	return false;
}


FBeamOperationHandle UBeamEditorContent::EnsureGlobalManifest()
{
	const auto EditorSlot = Editor->GetMainEditorSlot();
	const auto Op = RequestTracker->BeginOperation({Editor->GetMainEditorSlot()}, GetName(), {});

	const auto GetManifestsRequest = UBasicContentGetManifestsRequest::Make(GetTransientPackage(), {});
	const auto GetManifestsHandler = FOnBasicContentGetManifestsFullResponse::CreateUObject(this, &UBeamEditorContent::EnsureGlobalManifest_OnGetManifests, Op);
	FBeamRequestContext Ctx;
	ContentApi->CPP_GetManifests(EditorSlot, GetManifestsRequest, GetManifestsHandler, Ctx, Op, this);

	return Op;
}

void UBeamEditorContent::EnsureGlobalManifest_OnGetManifests(FBasicContentGetManifestsFullResponse Response, const FBeamOperationHandle Op)
{
	if (Response.State == RS_Error)
	{
		// TODO: Open popup explaining that we failed to get the content manifests and as such the content service is not fine. Have option to try again
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == RS_Success)
	{
		for (const auto Manifest : Response.SuccessData->Manifests)
		{
			ManifestIds.Add(Manifest->Id);
			UE_LOG(LogBeamContent, Display, TEXT("Manifest Found = %s"), *Manifest->Id.AsString)
		}

		if (Response.SuccessData->Manifests.Num() == 0)
		{
			UE_LOG(LogBeamContent, Error, TEXT("No Manifest Found!"))

			const TArray<UReferenceSuperset*> EmptySuperset{};
			UBasicContentPostManifestRequest* EmptyManifest = UBasicContentPostManifestRequest::Make(Global_Manifest, EmptySuperset, GetTransientPackage(), {});

			const auto Handler = FOnBasicContentPostManifestFullResponse::CreateUObject(this, &UBeamEditorContent::EnsureGlobalManifest_OnPostManifest, Op);
			FBeamRequestContext Ctx;
			ContentApi->CPP_PostManifest(Editor->GetMainEditorSlot(), EmptyManifest, Handler, Ctx, Op, this);
			return;
		}

		// For the case where we already have content manifests, we need to make sure we have the local manifests created locally correctly.
		for (const auto& Manifest : Response.SuccessData->Manifests)
		{
			const auto Id = Manifest->Id;
			ManifestIds.Add(Id);

			const auto ManifestAssetName = TEXT("BCM_") + Id.AsString.Mid(0, 1).ToUpper() + Id.AsString.Mid(
				1, Id.AsString.Len() - 1);

			const auto UncookedAssetPath = DefaultBeamableUncookedContentManifestsPath / ManifestAssetName;
			const auto CookedAssetPath = DefaultBeamableCookedContentManifestsPath / ManifestAssetName;

			const auto bExistsInCooked = EditorAssetSubsystem->DoesAssetExist(CookedAssetPath);
			const auto bExistsInUncooked = EditorAssetSubsystem->DoesAssetExist(UncookedAssetPath);
			// If the asset doesn't exist, let's create it.
			if (!bExistsInCooked && !bExistsInUncooked)
			{
				FString Name, PackageName;
				AssetToolsModule->Get().CreateUniqueAssetName(UncookedAssetPath, TEXT(""), PackageName, Name);
				const FString PackagePath = FPackageName::GetLongPackagePath(PackageName);

				// Create object and package
				UPackage* Package = CreatePackage(*PackageName);
				UDataTableFactory* MyFactory = NewObject<UDataTableFactory>();
				MyFactory->Struct = FLocalContentManifestRow::StaticStruct();
				UDataTable* LocalManifest = Cast<UDataTable>(
					AssetToolsModule->Get().CreateAsset(Name, PackagePath, UDataTable::StaticClass(), MyFactory));

				FSavePackageArgs SaveArgs;
				SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
				UPackage::Save(Package, LocalManifest, *FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()), SaveArgs);
				// Add the newly created global manifest to the local manifest list
				LocalManifests.Add(Id, LocalManifest);
				auto NewEditorState = NewObject<ULocalContentManifestEditorState>();
				NewEditorState->ManifestId = Id;
				NewEditorState->EditingTable = LocalManifest;
				EditorStates.Add(Id, NewEditorState);

				// Inform asset registry
				IAssetRegistry::Get()->AssetCreated(LocalManifest);


				// Tell content browser to show the newly created asset					
				TArray<UObject*> Objects;
				Objects.Add(LocalManifest);
				ContentBrowserModule->Get().SyncBrowserToAssets(Objects);

				UE_LOG(LogTemp, Verbose, TEXT("Created Local Manifest with Id=%s!"), *Id.AsString)

				FEditorStateChangedHandlerCode OnSyncSuccess;
				FEditorStateChangedHandlerCode OnSyncError;
				OnSyncSuccess.BindLambda([this, Op, LocalManifest]
				{
					if (LocalManifest->MarkPackageDirty())
					{
						EditorAssetSubsystem->SaveLoadedAsset(LocalManifest);
						RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
					}
					else
					{
						RequestTracker->TriggerOperationError(Op, TEXT(""));
					}
				});
				OnSyncError.BindLambda([this, Op]
				{
					RequestTracker->TriggerOperationError(Op, TEXT(""));
				});

				SynchronizeRemoteManifestWithLocalManifest(Id, Manifest, LocalManifest, OnSyncSuccess, OnSyncError);
			}
			// Otherwise, let's load it and keep it in the LocalManifests map
			else
			{
				// Add the newly created global manifest to the local manifest list
				UDataTable* LocalManifest = nullptr;
				if (bExistsInCooked)
					LocalManifest = Cast<UDataTable>(EditorAssetSubsystem->LoadAsset(CookedAssetPath));
				if (bExistsInUncooked)
					LocalManifest = Cast<UDataTable>(EditorAssetSubsystem->LoadAsset(UncookedAssetPath));

				// For us to be here, we should have the manifest loaded in one of these two paths.
				check(LocalManifest != nullptr)


				UE_LOG(LogTemp, Verbose, TEXT("Loaded Local Manifest with Id=%s!"), *Id.AsString)
				LocalManifests.Add(Id, LocalManifest);
				auto NewEditorState = NewObject<ULocalContentManifestEditorState>();
				NewEditorState->ManifestId = Id;
				NewEditorState->EditingTable = LocalManifest;
				EditorStates.Add(Id, NewEditorState);
				RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
			}
		}

		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}


void UBeamEditorContent::EnsureGlobalManifest_OnPostManifest(FBasicContentPostManifestFullResponse Response,
                                                             const FBeamOperationHandle Op)
{
	if (Response.State == RS_Error)
	{
		// TODO: Open popup explaining that we failed to get the content manifests and as such the content service is not fine. Have option to try again			
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == RS_Success)
	{
		UE_LOG(LogBeamContent, Warning, TEXT("Found no content manifests so creating a default = %s - %lld"), *Response.SuccessData->Id.AsString, Response.SuccessData->Created)

		const auto Id = Response.SuccessData->Id;
		const auto ManifestAssetName = GetManifestDataTableName(Id);

		const auto UncookedAssetPath = DefaultBeamableUncookedContentManifestsPath / ManifestAssetName;
		const auto CookedAssetPath = DefaultBeamableCookedContentManifestsPath / ManifestAssetName;

		const auto bExistsInCooked = EditorAssetSubsystem->DoesAssetExist(CookedAssetPath);
		const auto bExistsInUncooked = EditorAssetSubsystem->DoesAssetExist(UncookedAssetPath);
		// If the asset doesn't exist, let's create it.
		if (!bExistsInCooked && !bExistsInUncooked)
		{
			FString Name, PackageName;
			AssetToolsModule->Get().CreateUniqueAssetName(UncookedAssetPath, TEXT(""), PackageName, Name);
			const FString PackagePath = FPackageName::GetLongPackagePath(PackageName);

			// Create object and package
			UPackage* Package = CreatePackage(*PackageName);
			UDataTableFactory* MyFactory = NewObject<UDataTableFactory>();
			MyFactory->Struct = FLocalContentManifestRow::StaticStruct();
			UDataTable* Manifest = Cast<UDataTable>(AssetToolsModule->Get().CreateAsset(Name, PackagePath, UDataTable::StaticClass(), MyFactory));

			// TODO: convert the received manifest into the local manifest format.

			FSavePackageArgs SaveArgs;
			SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
			UPackage::Save(Package, Manifest, *FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()), SaveArgs);

			// Add the newly created global manifest to the local manifest list
			LocalManifests.Add(Global_Manifest, Manifest);
			auto NewEditorState = NewObject<ULocalContentManifestEditorState>();
			NewEditorState->ManifestId = Global_Manifest;
			NewEditorState->EditingTable = Manifest;
			EditorStates.Add(Global_Manifest, NewEditorState);

			// Inform asset registry
			IAssetRegistry::Get()->AssetCreated(Manifest);

			// Tell content browser to show the newly created asset					
			TArray<UObject*> Objects;
			Objects.Add(Manifest);
			ContentBrowserModule->Get().SyncBrowserToAssets(Objects);
		}
		else
		{
			// Load the manifest that is already there
			UDataTable* Manifest;
			if (bExistsInCooked) Manifest = Cast<UDataTable>(EditorAssetSubsystem->LoadAsset(CookedAssetPath));
			if (bExistsInUncooked) Manifest = Cast<UDataTable>(EditorAssetSubsystem->LoadAsset(UncookedAssetPath));

			// Add the newly created global manifest to the local manifest list
			LocalManifests.Add(Global_Manifest, Manifest);
			auto NewEditorState = NewObject<ULocalContentManifestEditorState>();
			NewEditorState->ManifestId = Global_Manifest;
			NewEditorState->EditingTable = Manifest;
			EditorStates.Add(Global_Manifest, NewEditorState);
		}

		RequestTracker->TriggerOperationSuccess(Op, Response.SuccessData->Id.AsString);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

FBeamOperationHandle UBeamEditorContent::PublishManifest(FBeamContentManifestId ContentManifestId, FBeamOperationEventHandler Handler)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();
	const auto Op = RequestTracker->BeginOperation({EditorSlot}, GetName(), Handler);

	UContentPublishState* PublishState;
	if (WorkingPublishStates.Contains(ContentManifestId))
	{
		PublishState = WorkingPublishStates[ContentManifestId];
		PublishState->CurrentChangeSet.ToAdd.Reset();
		PublishState->CurrentChangeSet.ToModify.Reset();
		PublishState->CurrentChangeSet.ToDelete.Reset();
		PublishState->References.Reset();
	}
	else
	{
		PublishState = NewObject<UContentPublishState>();
		WorkingPublishStates.Add(ContentManifestId, PublishState);
	}

	FBeamRequestContext Ctx;
	const auto ManifestRequest = UBasicContentGetManifestRequest::Make(FOptionalBeamContentManifestId(ContentManifestId), GetTransientPackage(), {});
	const auto ManifestRequestHandler = FOnBasicContentGetManifestFullResponse::CreateUObject(this, &UBeamEditorContent::PublishManifest_OnGetManifest, Op, ContentManifestId);
	ContentApi->CPP_GetManifest(EditorSlot, ManifestRequest, ManifestRequestHandler, Ctx, Op, this);

	return Op;
}

void UBeamEditorContent::PublishManifest_OnGetManifest(FBasicContentGetManifestFullResponse Response,
                                                       FBeamOperationHandle Op,
                                                       FBeamContentManifestId ContentManifestId)
{
	if (Response.State == RS_Error)
	{
		// TODO: Open popup explaining that we failed to get the content manifests and as such the content service is not fine. Have option to try again
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == RS_Success)
	{
		const auto LocalManifestToPublish = LocalManifests[ContentManifestId];
		const auto PublishState = WorkingPublishStates[ContentManifestId];

		TArray<UBaseContentReference*> LocalContentReferences;
		const auto ContentIds = LocalManifestToPublish->GetRowNames();
		for (const auto& ContentId : ContentIds)
		{
			const auto& EntryInManifest = *LocalManifestToPublish->FindRow<FLocalContentManifestRow>(ContentId, TEXT(""));
			const auto TypeTag = EntryInManifest.Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });

			UBeamContentObject* Obj;
			if (TryLoadContentObject(ContentManifestId, ContentId, UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag), Obj))
			{
				auto Reference = NewObject<UBaseContentReference>();
				Reference->Content = NewObject<UContentReference>(Reference);
				Reference->Content->Id = ContentId;
				Reference->Content->Tags = EntryInManifest.Tags;
				Reference->Content->Type = TEXT("content"); // Always content as we don't support other content types via Editor.
				Reference->Content->Checksum = FOptionalString(Obj->CreatePropertiesHash());
				Reference->Content->Uri = TEXT("");
				Reference->Content->Version = TEXT("");
				Reference->Content->Visibility = EContentVisibility::BEAM_public;
				LocalContentReferences.Add(Reference);
			}
			else
			{
				ensureAlwaysMsgf(false, TEXT("Should never see this! This means you have a content in corrupted state: %s"), *ContentId.ToString());
			}
		}

		// TODO
		TArray<UBaseContentReference*> RemoteContentReferences;
		BuildChangeSetForManifest(LocalContentReferences, RemoteContentReferences, PublishState->CurrentChangeSet);


		for (const auto& RemoteContentReference : RemoteContentReferences)
			PublishState->References.Add(MakePublishKey(RemoteContentReference), RemoteContentReference);

		TArray<UBaseContentReference*> ToPush;
		ToPush.Append(PublishState->CurrentChangeSet.ToAdd);
		ToPush.Append(PublishState->CurrentChangeSet.ToModify);

		TArray<UContentDefinition*> ContentDefinitions;
		for (const auto& Push : ToPush)
		{
			if (!Push->Content) continue;
			const auto ContentId = Push->Content->Id;

			auto Def = NewObject<UContentDefinitionWrapper>();
			Def->Id = ContentId;
			Def->Checksum = Push->Content->Checksum.Val;
			Def->Tags = FOptionalArrayOfString(Push->Content->Tags);

			const auto& EntryInManifest = *LocalManifestToPublish->FindRow<FLocalContentManifestRow>(FName(ContentId.AsString), TEXT(""));
			const auto TypeTag = EntryInManifest.Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });

			UBeamContentObject* Obj;
			check(TryLoadContentObject(ContentManifestId, Push->Content->Id, UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag), Obj))
			Obj->ToPropertiesJson(Def->SerializedProperties);

			ContentDefinitions.Add(Def);
		}

		// INFO: Just a helper log for when debugging the publish flow.
#if WITH_EDITOR
		FString Debug;
		for (UContentDefinition* ContentDefinition : ContentDefinitions)
		{
			FString DefJson;
			TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<
				wchar_t>>::Create(&DefJson);
			ContentDefinition->BeamSerialize(JsonSerializer);
			JsonSerializer->Close();
			Debug.Append(DefJson);
			Debug.Append(TEXT("\n"));
		}
		UE_LOG(LogBeamContent, Verbose, TEXT("Content Definitions:\n%s"), *Debug);
#endif

		// Send out the post request containing all content objects...
		FBeamRequestContext PostRequest;
		const auto PostContent = UPostContentRequest::Make(ContentDefinitions, GetTransientPackage(), {});
		const auto PostContentHandler = FOnPostContentFullResponse::CreateUObject(this, &UBeamEditorContent::PublishManifest_OnPostContent, Op, ContentManifestId);
		ContentApi->CPP_PostContent({Editor->GetMainEditorSlot()}, PostContent, PostContentHandler, PostRequest, Op, this);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditorContent::PublishManifest_OnPostContent(FPostContentFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId)
{
	if (Response.State == RS_Error)
	{
		// TODO: Open popup explaining that we failed to get the content manifests and as such the content service is not fine. Have option to try again
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == RS_Success)
	{
		const auto PublishState = WorkingPublishStates[ContentManifestId];

		// Update the working set of references 
		for (UContentReference* Content : Response.SuccessData->Content)
		{
			// We simply pass along the content object to the new UBaseContentReference.
			UBaseContentReference* NewRef = NewObject<UBaseContentReference>();
			NewRef->Content = Content;

			// This means that the UContentBaseContentReference* will no longer be tied to the response object and therefore won't be GC'ed.
			Content->Rename(nullptr, NewRef);
			Content->OuterOwner = NewRef;
			Content->Type = "content";

			const auto Key = MakePublishKey(NewRef, UContentVisibilityLibrary::ContentVisibilityToSerializationName(Content->Visibility));

			if (PublishState->References.Contains(Key))
			{
				PublishState->References[Key] = NewRef;
			}
			else
			{
				PublishState->References.Add(Key, NewRef);
			}
		}

		// Clean up the working set of references of all the removed content pieces.
		for (const auto& Delete : PublishState->CurrentChangeSet.ToDelete)
		{
			const auto PublicContentKey = MakePublishKey(Delete, "public");
			const auto PrivateContentKey = MakePublishKey(Delete, "private");
			PublishState->References.Remove(PublicContentKey);
			PublishState->References.Remove(PrivateContentKey);
		}

		TArray<UReferenceSuperset*> Supersets;
		for (const auto& Pair : PublishState->References)
		{
			const auto Ref = Pair.Value;

			auto Asd = NewObject<UReferenceSuperset>();
			Asd->Id = Ref->Content->Id;
			Asd->Checksum = Ref->Content->Checksum;
			Asd->Tags = FOptionalArrayOfString(Ref->Content->Tags);
			Asd->Type = TEXT("content");
			Asd->Uri = Ref->Content->Uri;
			Asd->Version = Ref->Content->Version;
			Asd->Visibility = FOptionalString(
				UContentVisibilityLibrary::ContentVisibilityToSerializationName(Ref->Content->Visibility));

			Supersets.Add(Asd);
		}

		FBeamRequestContext Ctx;
		const auto PostManifestRequest = UBasicContentPostManifestRequest::Make(ContentManifestId, Supersets, this, {});
		const auto PostManifestRequestHandler = FOnBasicContentPostManifestFullResponse::CreateUObject(this, &UBeamEditorContent::PublishManifest_OnPostManifest, Op, ContentManifestId);
		ContentApi->CPP_PostManifest({Editor->GetMainEditorSlot()}, PostManifestRequest, PostManifestRequestHandler, Ctx, Op, this);

		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditorContent::PublishManifest_OnPostManifest(FBasicContentPostManifestFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId) const
{
	if (Response.State == RS_Error)
	{
		// TODO: Open popup explaining that we failed to get the content manifests and as such the content service is not fine. Have option to try again
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == RS_Success)
	{
		// Just notify the caller that we have finished publishing.
		RequestTracker->TriggerOperationSuccess(Op, Response.SuccessData->Id.AsString, Response.Context.RequestId);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

FBeamOperationHandle UBeamEditorContent::DownloadManifest(FBeamContentManifestId ContentManifestId,
                                                          FBeamOperationEventHandlerCode Handler)
{
	const auto EditorSlot = Editor->GetMainEditorSlot();
	const auto Op = RequestTracker->CPP_BeginOperation({EditorSlot}, GetName(), Handler);

	UContentDownloadState* DownloadState;
	if (WorkingDownloadStates.Contains(ContentManifestId))
	{
		DownloadState = WorkingDownloadStates[ContentManifestId];
		DownloadState->CurrentDownloadHandle = -1;
		DownloadState->RemoteManifest = nullptr;
		DownloadState->RemoteToLocalDiff.ToAdd.Reset();
		DownloadState->RemoteToLocalDiff.ToModify.Reset();
		DownloadState->RemoteToLocalDiff.ToDelete.Reset();
	}
	else
	{
		DownloadState = NewObject<UContentDownloadState>();
		WorkingDownloadStates.Add(ContentManifestId, DownloadState);
	}

	FBeamRequestContext Ctx;
	const auto ManifestRequest = UBasicContentGetManifestRequest::Make(FOptionalBeamContentManifestId(ContentManifestId), GetTransientPackage(), {});
	const auto ManifestRequestHandler = FOnBasicContentGetManifestFullResponse::CreateUObject(this, &UBeamEditorContent::DownloadManifest_OnGetManifest, Op, ContentManifestId);
	ContentApi->CPP_GetManifest(EditorSlot, ManifestRequest, ManifestRequestHandler, Ctx, Op, this);
	return Op;
}

void UBeamEditorContent::DownloadManifest_OnGetManifest(FBasicContentGetManifestFullResponse Response,
                                                        FBeamOperationHandle Op,
                                                        FBeamContentManifestId ManifestId)
{
	if (Response.State == RS_Error || Response.State == RS_Cancelled)
	{
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message);
		return;
	}

	if (Response.State == RS_Success)
	{
		// Build change set that says: which content will be added and which will be overwritten (no content is deleted when downloading)
		const auto RemoteManifest = Response.SuccessData;
		const auto LocalManifest = LocalManifests.FindChecked(ManifestId);

		FManifestChangeSet Changes;
		for (auto Reference : RemoteManifest->References)
		{
			if (Reference->GetCurrentType().Equals("content"))
			{
				const auto ContentRef = Reference->Content;
				if (ContentRef->Visibility == EContentVisibility::BEAM_public)
				{
					const auto RowName = FName(ContentRef->Id.AsString);
					const auto LocalRow = LocalManifest->FindRow<FLocalContentManifestRow>(RowName, TEXT(""));
					if (!LocalRow)
						Changes.ToAdd.Add(Reference);
					else if (!LocalRow->Checksum.Equals(ContentRef->Checksum.Val))
						Changes.ToModify.Add(Reference);
				}
			}
		}

		WorkingDownloadStates[ManifestId]->RemoteManifest = RemoteManifest;
		WorkingDownloadStates[ManifestId]->RemoteToLocalDiff = Changes;
		WorkingDownloadStates[ManifestId]->CurrentDownloadHandle = Op;


		// Trigger a sub-event to let the UI react by asking the user whether or not we should continue given the changes that'll happen locally.
		// We expect the user confirmation to eventually call "DownloadManifest_ApplyUserInput(bool)" with true/false given the user's choice of whether or not to apply the changes  
		RequestTracker->TriggerOperationEvent(Op, OET_SUCCESS, 1, {});
	}
}

void UBeamEditorContent::DownloadManifest_ApplyUserInput(FBeamContentManifestId ManifestId, bool AcceptCurrentChanges)
{
	if (AcceptCurrentChanges)
	{
		// TODO: Apply changes locally.
		auto& DownloadState = *WorkingDownloadStates[ManifestId];
		const auto Op = DownloadState.CurrentDownloadHandle;
		const auto LocalManifest = LocalManifests.FindChecked(ManifestId);

		FEditorStateChangedHandlerCode OnSyncSuccess;
		FEditorStateChangedHandlerCode OnSyncError;
		OnSyncSuccess.BindLambda([this, Op, LocalManifest]
		{
			if (LocalManifest->MarkPackageDirty())
			{
				EditorAssetSubsystem->SaveLoadedAsset(LocalManifest);
				RequestTracker->TriggerOperationSuccess(Op, {});
			}
			else
			{
				RequestTracker->TriggerOperationError(Op, {});
			}
		});
		OnSyncError.BindLambda([this, Op]
		{
			RequestTracker->TriggerOperationError(Op, {});
		});
		SynchronizeRemoteManifestWithLocalManifest(ManifestId, DownloadState.RemoteManifest, LocalManifest,
		                                           OnSyncSuccess, OnSyncError);
	}
	else
	{
		// Cleanup working state and send out a cancelled event
		auto& DownloadState = *WorkingDownloadStates[ManifestId];
		RequestTracker->TriggerOperationCancelled(DownloadState.CurrentDownloadHandle, TEXT(""));

		DownloadState.RemoteToLocalDiff = {};
		DownloadState.RemoteManifest = nullptr;
		DownloadState.CurrentDownloadHandle = {};
	}
}


FString UBeamEditorContent::MakePublishKey(const UBaseContentReference* Ref, FString Visibility)
{
	if (Ref->Content)
		return FString::Format(
			TEXT("{0}/{1}"), {
				Ref->Content->Id.AsString,
				(Visibility.Len() > 0 ? Visibility : StaticEnum<EContentVisibility>()->GetNameByValue(static_cast<int64>(Ref->Content->Visibility)).ToString()).ToLower()
			});

	if (Ref->Binary)
		return FString::Format(
			TEXT("{0}/{1}"), {
				Ref->Binary->Id.AsString,
				(Visibility.Len() > 0 ? Visibility : Ref->Binary->Visibility).ToLower()
			});

	return FString::Format(
		TEXT("{0}/{1}"), {
			Ref->Text->Id.AsString,
			(Visibility.Len() > 0 ? Visibility : Ref->Text->Visibility).ToLower()
		});
}

void UBeamEditorContent::BuildChangeSetForManifest(TArray<UBaseContentReference*> LocalReferences, TArray<UBaseContentReference*> RemoteReferences, FManifestChangeSet& ChangeSet)
{
	TSet<FBeamContentId> UnseenIds;
	UnseenIds.Reserve(RemoteReferences.Num());
	for (const auto& RemoteReference : RemoteReferences)
	{
		if (RemoteReference->Content)
			UnseenIds.Add(RemoteReference->Content->Id);
	}

	for (const auto& LocalEntryInManifest : LocalReferences)
	{
		if (!LocalEntryInManifest->Content) continue;

		UnseenIds.Remove(LocalEntryInManifest->Content->Id);
		const auto& RemoteEntryInManifest = RemoteReferences.FindByPredicate([LocalEntryInManifest](const UBaseContentReference* Ref)
		{
			return Ref->Content && Ref->Content->Id == LocalEntryInManifest->Content->Id;
		});

		// We don't support non-content references yet
		if (!LocalEntryInManifest->Content || (RemoteEntryInManifest && !(*RemoteEntryInManifest)->Content))
			continue;

		// If it doesn't exist remotely, that means we're adding it now.
		if (!RemoteEntryInManifest)
		{
			ChangeSet.ToAdd.Add(LocalEntryInManifest);
			continue;
		}

		// If it exists but the checksum OR tags were modified, we consider it modified.
		const auto LocalChecksum = LocalEntryInManifest->Content->Checksum.Val;
		const auto RemoteChecksum = (*RemoteEntryInManifest)->Content->Checksum.Val;

		const auto LocalTags = LocalEntryInManifest->Content->Tags;
		const auto RemoteTags = (*RemoteEntryInManifest)->Content->Tags;
		if (LocalTags != RemoteTags || LocalChecksum != RemoteChecksum) ChangeSet.ToModify.Add(LocalEntryInManifest);
	}

	// For every Remote Content Id that was not present locally, we add it as a deletion.
	for (const auto& UnseenId : UnseenIds)
	{
		const auto& RemoteEntryInManifest = *RemoteReferences.FindByPredicate([UnseenId](const UBaseContentReference* Ref)
		{
			return Ref->Content && Ref->Content->Id == UnseenId;
		});
		ChangeSet.ToDelete.Add(RemoteEntryInManifest);
	}
}

void UBeamEditorContent::HandleAssetOpenedInEditor(UObject* Object, IAssetEditorInstance* AssetEditor)
{
	// use this instead of HandleAssetEditorOpened because it has access to the editor
	const auto DataTable = Cast<UDataTable>(Object);

	// This function runs on every opened asset, so the asset we have *might* not be a Static Mesh
	if (!DataTable)
		return;

	UE_LOG(LogTemp, Error, TEXT("Opening an editor for a DataTable!"))
	const auto bIsLocalContentManifestTable = DataTable->RowStruct == FLocalContentManifestRow::StaticStruct();

	if (!bIsLocalContentManifestTable)
		return;

	UE_LOG(LogTemp, Error, TEXT("Opening an editor for a Local ContentManifest DataTable!"))

	TArray<FBeamContentManifestId> AllManifestIds;
	TArray<ULocalContentManifestEditorState*> AllManifestEditorStates;
	EditorStates.GetKeys(AllManifestIds);
	EditorStates.GenerateValueArray(AllManifestEditorStates);
	const auto EditorStateIdx = AllManifestEditorStates.FindLastByPredicate([DataTable](const ULocalContentManifestEditorState* EditorState) { return EditorState->EditingTable == DataTable; });

	// Don't open if you can't find the DataTable
	if (EditorStateIdx != -1)
	{
		const auto ManifestId = AllManifestIds[EditorStateIdx];


		check(AssetEditor->GetEditorName() == "DataTableEditor"); // i.e. == FDataTableEditor::GetToolkitFName()
		const auto EditorState = AllManifestEditorStates[EditorStateIdx];
		EditorState->Editor = StaticCast<FAssetEditorToolkit*>(AssetEditor);
		EditorState->EditorContentSystem = this;
		EditorState->EditingTable = DataTable;
		EditorState->ManifestId = ManifestId;

		EditorState->PrepareEditingUI();
	}
}

UClass** UBeamEditorContent::FindContentTypeByName(FString TypeName)
{
	return AllContentTypes.FindByPredicate([TypeName](const UClass* Class) { return Class->GetFName().ToString().Equals(TypeName); });
}

bool UBeamEditorContent::TryLoadContentObject(const FBeamContentManifestId& OwnerManifest, FBeamContentId ContentId, FString TypeName, UBeamContentObject*& OutLoadedContentObject)
{
	// Hit the cache first.
	if (LoadedContentObjects.Contains(ContentId))
	{
		OutLoadedContentObject = LoadedContentObjects.FindRef(ContentId);
		return true;
	}

	// Otherwise, find the UClass for the content type. Load the JSON and deserialize it into the UBeamContentObject.
	if (const auto Type = AllContentTypes.FindByPredicate([TypeName](const UClass* Class) { return Class->GetFName().ToString().Equals(TypeName); }))
	{
		const auto RowName = FName(ContentId.AsString);
		const auto ManifestRow = LocalManifests[OwnerManifest]->FindRow<FLocalContentManifestRow>(RowName, TEXT("Saving Object"));
		if (ManifestRow)
		{
			const auto FilePath = GetJsonBlobPath(ContentId.AsString, OwnerManifest);
			FString FileContents;
			if (FFileHelper::LoadFileToString(FileContents, *FilePath))
			{
				const auto ContentObject = NewObject<UBeamContentObject>(GetTransientPackage(), *Type);
				LoadedContentObjects.Add(ContentId, ContentObject);

				OutLoadedContentObject = ContentObject;
				OutLoadedContentObject->FromBasicJson(FileContents);
				return true;
			}
		}

		return false;
	}

	return false;
}

bool UBeamEditorContent::InstantiateContentObject(const UDataTable* Manifest, const FBeamContentId& ContentId, UBeamContentObject*& OutNewContentObject, UObject* Outer)
{
	const auto ManifestRow = Manifest->FindRow<FLocalContentManifestRow>(FName(ContentId.AsString), TEXT("Saving Object"));
	if (ManifestRow)
	{
		const auto TypeTag = ManifestRow->Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });
		const auto TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);

		// Otherwise, find the UClass for the content type. Load the JSON and deserialize it into the UBeamContentObject.
		if (const auto Type = AllContentTypes.FindByPredicate([TypeName](const UClass* Class) { return Class->GetFName().ToString().Equals(TypeName); }))
		{
			const auto FilePath = GetJsonBlobPath(ContentId.AsString, GetManifestIdFromDataTable(Manifest));
			FString FileContents;
			if (FFileHelper::LoadFileToString(FileContents, *FilePath))
			{
				const auto ContentObject = NewObject<UBeamContentObject>(Outer, *Type);
				OutNewContentObject = ContentObject;
				OutNewContentObject->FromBasicJson(FileContents);
				return true;
			}
		}
	}
	return false;
}

void UBeamEditorContent::GetContentTypeToIdMaps(TMap<FName, TArray<TSharedPtr<FName>>>& Map)
{
	for (const auto& LocalManifest : LocalManifests)
	{
		const auto Ids = LocalManifest.Value->GetRowNames();
		for (const auto& Id : Ids)
		{
			const auto Row = LocalManifest.Value->FindRow<FLocalContentManifestRow>(Id, TEXT(""));
			const auto TypeTag = Row->Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });
			const auto TypeName = FName(UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag));

			if (!Map.Contains(TypeName))
				Map.Add(TypeName, {});

			if (!Map[TypeName].ContainsByPredicate([Id](TSharedPtr<FName> N)
			{
				return N->ToString().Equals(Id.ToString());
			}))
			{
				Map[TypeName].Add(MakeShareable(new FName(Id)));
			}
		}
	}
}

bool UBeamEditorContent::GetContentTypeFromId(FBeamContentId Id, FString& TypeName)
{
	const auto IdStr = Id.AsString;
	for (const auto& LocalManifest : LocalManifests)
	{
		const auto Row = LocalManifest.Value->FindRow<FLocalContentManifestRow>(FName(IdStr), TEXT("Context"));
		if (Row)
		{
			const auto TypeTag = Row->Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });
			TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);
			return true;
		}
	}
	TypeName = TEXT("");
	return false;
}

void UBeamEditorContent::SynchronizeRemoteManifestWithLocalManifest(const FBeamContentManifestId Id,
                                                                    const UContentBasicManifest* RemoteManifest,
                                                                    UDataTable* LocalManifest,
                                                                    FEditorStateChangedHandlerCode OnSuccess,
                                                                    FEditorStateChangedHandlerCode OnError)
{
	// We keep track of each content we are downloading (the bool indicates whether or not we managed to write the file
	// locally and add it to the local manifest. 
	TArray<FDownloadContentState> DownloadContentOperations;

	// First we build up the list of download requests we'll have to make (we only care about the 'public' content)
	// If the content exists in the local manifest, we compare it's checksum to make sure it's modified and we need to download it.
	// If the content doesn't exist in the local manifest OR if it's local file is missing, we fetch it.
	FBeamRealmUser EditorUser;
	const auto EditorSlot = Editor->GetMainEditorSlot(EditorUser);
	for (auto Reference : RemoteManifest->References)
	{
		if (Reference->GetCurrentType().Equals("content"))
		{
			const auto ContentRef = Reference->Content;
			if (ContentRef->Visibility == EContentVisibility::BEAM_public)
			{
				const auto RowName = FName(ContentRef->Id.AsString);
				const auto LocalContent = LocalManifest->FindRow<FLocalContentManifestRow>(RowName, TEXT(""));
				const auto LocalContentFileExists = IFileManager::Get().FileExists(
					*GetJsonBlobPath(RowName.ToString(), Id));
				if (!LocalContentFileExists || !LocalContent || LocalContent->Checksum != ContentRef->Checksum.Val)
				{
					TUnrealRequestPtr ptr = FHttpModule::Get().CreateRequest();
					ptr->SetVerb("GET");
					ptr->SetURL(ContentRef->Uri);
					ptr->SetHeader(UBeamBackend::HEADER_ACCEPT, UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);
					DownloadContentOperations.Add(FDownloadContentState{Id, ContentRef->Id, ContentRef->Tags, ContentRef->Checksum, ptr});
				}
			}
		}
	}

	// For each download that we'll make, register a lambda that:
	//  - Tries to save the downloaded file to the local '.beamable' folder.
	//  - Checks to see if it was the last download and, if so, invoke the appropriate on success/error callback.
	for (int DownloadIdx = 0; DownloadIdx < DownloadContentOperations.Num(); ++DownloadIdx)
	{
		const auto& DownloadContentOperation = DownloadContentOperations[DownloadIdx];
		DownloadContentOperation.Request->OnProcessRequestComplete().BindLambda(
			[this, DownloadContentOperations, DownloadContentOperation, Id, LocalManifest, OnSuccess, OnError]
		(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse,
		 bool)
			{
				if (HttpResponse->GetResponseCode() == 200)
				{
					const auto ContentId = DownloadContentOperation.Id.AsString;

					const auto ContentFileContents = HttpResponse->GetContentAsString();
					const auto FilePath = GetJsonBlobPath(ContentId, Id);

					if (!FFileHelper::SaveStringToFile(ContentFileContents, *FilePath))
					{
						UE_LOG(LogBeamContent, Error, TEXT("Failed to save content to path %s"), *FilePath);
						return;
					}

					// We check if the row already exists, if it does we simply update it. Otherwise we add it.
					const auto RowName = FName(ContentId);
					if (const auto ExistingRow = LocalManifest->FindRow<FLocalContentManifestRow>(RowName, TEXT("")))
					{
						ExistingRow->OwnerManifestId = Id;
						ExistingRow->RowName = ContentId;
						ExistingRow->Checksum = DownloadContentOperation.Checksum.Val;
						ExistingRow->Tags = DownloadContentOperation.Tags;
					}
					else
					{
						FLocalContentManifestRow Row;
						Row.OwnerManifestId = Id;
						Row.RowName = ContentId;
						Row.Checksum = DownloadContentOperation.Checksum.Val;
						Row.Tags = DownloadContentOperation.Tags;
						LocalManifest->AddRow(RowName, Row);
					}

					// Clear from cache if it's there					
					UBeamContentObject* ClearedFromCache;
					LoadedContentObjects.RemoveAndCopyValue(FBeamContentId(ContentId), ClearedFromCache);
				}

				bool bAreAllFinished = true;
				bool bAreAllSuccess = true;
				bool bAreAnyFailed = false;
				for (const auto& Download : DownloadContentOperations)
				{
					const auto DidSave = IFileManager::Get().FileExists(
						*GetJsonBlobPath(Download.Id.AsString, Id));

					const auto bIsSuccess = Download.Request->GetStatus() ==
						EHttpRequestStatus::Succeeded;
					const auto bIsFailure = Download.Request->GetStatus() ==
						EHttpRequestStatus::Failed || (Download.Request->GetStatus() != EHttpRequestStatus::Processing
							&& !DidSave);

					bAreAllFinished &= bIsSuccess || bIsFailure;
					bAreAllSuccess &= bIsSuccess;
					bAreAnyFailed |= bIsFailure;
				}

				if (bAreAllFinished)
				{
					if (bAreAllSuccess)
					{
						OnSuccess.ExecuteIfBound();
					}

					if (bAreAnyFailed)
					{
						OnError.ExecuteIfBound();
					}
				}
			});
		DownloadContentOperation.Request->ProcessRequest();
	}
}

void UBeamEditorContent::PreChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo ChangedType)
{
	// We early out if the selection was changed in a data table that is not the one being managed by this editor.
	FBeamContentManifestId ManifestId;
	UDataTable* EditingTable;

	if (!GetChangingManifest(Changed, ManifestId, EditingTable)) return;

	UE_LOG(LogTemp, Warning, TEXT("CAlled pre-change from BEAM EDITOR CONTENT!!!"))
}

void UBeamEditorContent::PostChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo ChangedType)
{
	FBeamContentManifestId ManifestId;
	UDataTable* EditingTable;

	if (!GetChangingManifest(Changed, ManifestId, EditingTable)) return;

	UE_LOG(LogTemp, Warning, TEXT("CAlled post-change from BEAM EDITOR CONTENT!!!"))

	TArray<FString> JsonBlobFileNames;
	IFileManager::Get().FindFiles(JsonBlobFileNames, *(DefaultBeamableProjectContentObjects / ManifestId.AsString));

	auto Rows = Changed->GetRowNames();
	Rows.Sort([](FName n1, FName n2) { return n1.FastLess(n2); });
	JsonBlobFileNames.Sort();

	// Handle deletion case
	TArray<FString> RemovedRows;
	if (Rows.Num() < JsonBlobFileNames.Num())
	{
		for (int i = JsonBlobFileNames.Num() - 1; i >= 0; --i)
		{
			const auto JsonBlobFileName = JsonBlobFileNames[i];
			FString JsonRowName, Extension;
			JsonBlobFileName.Split(".", &JsonRowName, &Extension, ESearchCase::CaseSensitive, ESearchDir::FromEnd);
			// If we are not in sync, it means we deleted this row so let's delete the file for it.
			if (!Rows.Contains(FName(JsonRowName)))
			{
				const auto FullPath = DefaultBeamableProjectContentObjects / ManifestId.AsString / JsonBlobFileName;
				IFileManager::Get().Delete(*FullPath);
				Rows.Remove(FName(JsonRowName));
			}
		}
	}

	TArray<FString> MissingTypeTags;
	for (int i = 0; i < Rows.Num(); i++)
	{
		FString Row = Rows[i].ToString();
		auto EntryInManifest = EditingTable->FindRow<FLocalContentManifestRow>(FName(Row),
		                                                                       TEXT("Validating Manifest"));

		// Handle case where we are missing the type tag value (which is what tells us what type to deserialize into)
		auto TypeTag = EntryInManifest->Tags.FindByPredicate([](FString Tag)
		{
			return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type);
		});
		if (!TypeTag)
		{
			MissingTypeTags.Add(Row);
		}
		else
		{
			// Handle rename case (if the row name no longer matches the json file name)
			const auto PrevName = EntryInManifest->RowName;
			bool bWasRenamed = !PrevName.Equals(Row);
			if (bWasRenamed)
			{
				FString OldName = PrevName, Discard;
				OldName.Split(".", &OldName, &Discard, ESearchCase::CaseSensitive, ESearchDir::FromEnd);

				const auto TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);
				UBeamContentObject* Obj;
				if (TryLoadContentObject(ManifestId, OldName, TypeName, Obj) ||
					TryLoadContentObject(ManifestId, Row, TypeName, Obj))
				{
					const auto TypePrefix = Obj->BuildContentTypeString();
					if (!Row.StartsWith(TypePrefix))
					{
						if (Row.Contains("."))
						{
							const auto ErrMsg = FString::Format(TEXT("Content Ids (Row Names) must be in the format <ContentType>.<Name>. If you just type in the Name, we guarantee the prefix is added correctly."), {Row});
							UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);

							// We need to delay as we can't use FDataTableEditorUtils functions without triggering another PostChange call.
							// This does not loop infinitely, but it causes a problem that gets the DataTable UI in a bad state and requires closing/opening again to fix.
							// Basically, because the call to PostChange inside RenameRow runs before the rest of this first chain of PostChange invocations, the UI's PostChange
							// callback for the RenameRow chain gets run before the one for the original change here. This causes all sorts of problems.
							FTimerDelegate DelayedRename;
							DelayedRename.BindLambda([this, Row, OldName, EditingTable]()
							{
								FDataTableEditorUtils::RenameRow(EditingTable, FName(OldName), FName(Row));
								EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
							});
							GEditor->GetEditorWorldContext().World()->GetTimerManager().SetTimerForNextTick(DelayedRename);

							bWasRenamed = false;
							//EditorContentSystem->EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
						}
						else
						{
							FName FixedName = FName(Obj->BuildContentTypeString() + TEXT(".") + Row);
							if (EditingTable->FindRow<FLocalContentManifestRow>(FixedName, ""))
							{
								const auto ErrMsg = FString::Format(TEXT("Content Id {0} already exists."), {FixedName.ToString()});
								UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);

								// We need to delay as we can't use FDataTableEditorUtils functions without triggering another PostChange call.
								// This does not loop infinitely, but it causes a problem that gets the DataTable UI in a bad state and requires closing/opening again to fix.
								// Basically, because the call to PostChange inside RenameRow runs before the rest of this first chain of PostChange invocations, the UI's PostChange
								// callback for the RenameRow chain gets run before the one for the original change here. This causes all sorts of problems.
								FTimerDelegate DelayedRename;
								DelayedRename.BindLambda([this, Row, OldName, EditingTable]()
								{
									FDataTableEditorUtils::RenameRow(EditingTable, FName(OldName), FName(Row));
									EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
								});
								GEditor->GetEditorWorldContext().World()->GetTimerManager().SetTimerForNextTick(DelayedRename);
								bWasRenamed = false;
							}
							else
							{
								const auto UserInputNewNameRow = EditingTable->FindRow<FLocalContentManifestRow>(FName(Row), "");
								EditingTable->AddRow(FixedName, *UserInputNewNameRow);
								EditingTable->RemoveRow(FName(Row));
								Row = FixedName.ToString();
								EntryInManifest = EditingTable->FindRow<FLocalContentManifestRow>(FixedName, "");
								TypeTag = EntryInManifest->Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });
								EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
								bWasRenamed = true;
							}
						}
					}
				}


				if (bWasRenamed)
				{
					const auto OldRow = EntryInManifest->RowName;
					const auto OldPath = GetJsonBlobPath(OldRow, ManifestId);
					const auto NewPath = GetJsonBlobPath(Row, ManifestId);

					// If the old file doesn't exist, we can just use the new one. 
					if (!IFileManager::Get().FileExists(*OldPath))
					{
						EntryInManifest->RowName = Row;
						UE_LOG(LogBeamContent, Display, TEXT("Content Renamed. Moving JsonBlob from %s to %s."),
						       *OldPath,
						       *EntryInManifest->RowName);
					}
					else if (IFileManager::Get().Move(*NewPath, *OldPath))
					{
						EntryInManifest->RowName = Row;
						UE_LOG(LogBeamContent, Display, TEXT("Content Renamed. Moving JsonBlob from %s to %s."),
						       *OldPath,
						       *EntryInManifest->RowName);
					}
				}
			}

			// Handle custom validation case
			const auto TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);
			UBeamContentObject* Obj;
			if (!TryLoadContentObject(ManifestId, Row, TypeName, Obj))
			{
				const auto ErrMsg = FString::Format(TEXT("Trying to load a content object that doesn't exist {0}"), {Row});
				UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
			}
			else
			{
				// If the object was renamed, let's make sure it's in memory representation is also updated with the new Id
				if (bWasRenamed)
				{
					Obj->Id = Row;
					FString JsonContent;
					Obj->ToBasicJson(JsonContent);
					if (FFileHelper::SaveStringToFile(JsonContent, *GetJsonBlobPath(EntryInManifest->RowName, ManifestId)))
					{
						EntryInManifest->Checksum = Obj->CreatePropertiesHash();
						EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
					}
				}

				if (const auto ValidationErrorCode = Obj->IsValidRowForType(*TypeTag, *EntryInManifest);
					ValidationErrorCode)
				{
					Obj->FixManifestRowForType(ValidationErrorCode, *EntryInManifest);
				}
			}
		}
	}

	if (MissingTypeTags.Num() > 0)
	{
		const auto ErrMsg = FString::Format(TEXT("Found a content object that doesn't have a type tag. Please add a type tag in the format of \"{0}ConcreteContentTypeName\" to the manifest row: {1}."),
		                                    {UBeamContentObject::Beam_Tag_Type, FString::Join(MissingTypeTags, TEXT(", "))});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
	}
}

bool UBeamEditorContent::GetOrCreateContent(const FBeamContentManifestId& ManifestId, const FString& ContentName, TSubclassOf<UBeamContentObject> ContentObjectSubType, UBeamContentObject*& ContentObject, FString& ErrMsg)
{
	ensure(!ContentName.IsEmpty());
	const auto ContentTypeString = GetMutableDefault<UBeamContentObject>(ContentObjectSubType)->BuildContentTypeString();
	const auto ContentId = FString::Format(TEXT("{0}.{1}"), {ContentTypeString, ContentName});

	if (!GetContentForEditing(ManifestId, ContentId, ContentObject, ErrMsg))
		return CreateNewContent(ManifestId, ContentName, ContentObjectSubType, ContentObject, ErrMsg);

	return true;
}

bool UBeamEditorContent::CreateNewContent(const FBeamContentManifestId& ManifestId, const FString& ContentName, TSubclassOf<UBeamContentObject> ContentObjectSubType, UBeamContentObject*& ContentObject, FString& ErrMsg)
{
	ContentObject = NewObject<UBeamContentObject>(this, ContentObjectSubType.Get());

	// We add it to the object and to the local manifest.
	const auto TypeName = ContentObject->GetClass()->GetFName().ToString();
	const auto TypeTagVal = FString::Format(*UBeamContentObject::Beam_Tag_TypeFmt, {TypeName});

	auto RepeatedNameCount = 0;
	auto RowName = ContentName.IsEmpty() ? FString::Format(TEXT("{0}.New_{1}_{2}"), {ContentObject->BuildContentTypeString(), TypeName, RepeatedNameCount}) : FString::Format(TEXT("{0}.{1}"), {ContentObject->BuildContentTypeString(), ContentName});

	const auto EditingTable = LocalManifests.FindRef(ManifestId);
	while (EditingTable->FindRow<FLocalContentManifestRow>(FName(RowName), TEXT("Ensure Name is Unique")))
	{
		RepeatedNameCount += 1;
		RowName = ContentName.IsEmpty() ? FString::Format(TEXT("{0}.New_{1}_{2}"), {ContentObject->BuildContentTypeString(), TypeName, RepeatedNameCount}) : FString::Format(TEXT("{0}.{1}_{2}"), {ContentObject->BuildContentTypeString(), ContentName, RepeatedNameCount});
	}

	// Initialize the editing Object
	FLocalContentManifestRow EntryInManifest;
	EntryInManifest.OwnerManifestId = ManifestId;
	EntryInManifest.Tags.Add(TypeTagVal);

	// Sets the ID and Tags based on the manifest row.
	ContentObject->Id = RowName;
	ContentObject->Tags.Append(EntryInManifest.Tags);

	FString JsonContent;
	ContentObject->ToBasicJson(JsonContent);

	const auto FilePath = GetJsonBlobPath(RowName, ManifestId);

	if (FFileHelper::SaveStringToFile(JsonContent, *FilePath))
	{
		EntryInManifest.Checksum = ContentObject->CreatePropertiesHash();
		EditorAssetSubsystem->SaveLoadedAsset(EditingTable);

		// Stores the created row struct into the data table
		// We do it this way, instead of FDataTableEditorUtils::AddRow(), so that the change callback is aware of the Row data when we create a new one.
		FDataTableEditorUtils::BroadcastPreChange(EditingTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
		EditingTable->AddRow(FName(RowName), EntryInManifest);
		FDataTableEditorUtils::BroadcastPostChange(EditingTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);


		// Adds the editing object to the list of cached content objects (so that we don't need to keep deserializing it all the time).
		LoadedContentObjects.Add(ContentObject->Id, ContentObject);

		// Saves the data-table with the new content object in it.
		EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
	}
	else
	{
		ErrMsg = FString::Format(TEXT("Failed to save the content object {0}"), {RowName});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
		return false;
	}
	ErrMsg.Empty();
	return true;
}

bool UBeamEditorContent::GetContent(const FBeamContentManifestId& ManifestId, FBeamContentId ContentId, UBeamContentObject*& ContentObject)
{
	FString Err;
	const auto bRes = GetContentForEditing(ManifestId, ContentId, ContentObject, Err);
	if (!bRes) UE_LOG(LogTemp, Warning, TEXT("Fallback Content Getter: Failed to find content with ID=%s from Manifest=%s."), *ContentId.AsString, *ManifestId.AsString)
	return bRes;
}

bool UBeamEditorContent::GetContentForEditing(const FBeamContentManifestId& ManifestId, FBeamContentId EditObjectId, UBeamContentObject*& ContentObject, FString& ErrMsg)
{
	const auto EditingTable = LocalManifests.FindRef(ManifestId);
	if (!EditingTable)
	{
		ErrMsg = FString::Format(TEXT("Trying to load a content object from a Manifest={0} that is not loaded. Ignore this during packaging."), {ManifestId.AsString});
		UE_LOG(LogBeamContent, Warning, TEXT("%s"), *ErrMsg);
		return false;
	}

	const auto Entry = EditingTable->FindRow<FLocalContentManifestRow>(FName(EditObjectId.AsString), TEXT("Edit Content Start"));
	if (!Entry)
	{
		ErrMsg = FString::Format(TEXT("Trying to load a content object that doesn't exist in this manifest."), {UBeamContentObject::Beam_Tag_Type, EditObjectId.AsString});
		UE_LOG(LogBeamContent, Warning, TEXT("%s"), *ErrMsg);
		return false;
	}

	const auto& EntryInManifest = *Entry;

	const auto TypeTag = EntryInManifest.Tags.FindByPredicate([](FString Tag)
	{
		return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type);
	});
	if (!TypeTag)
	{
		ErrMsg = FString::Format(TEXT("Trying to load a content object that doesn't have a type tag. Please add a type tag in the format of \"{0}ConcreteContentTypeName\" to the manifest row: {1}."), {UBeamContentObject::Beam_Tag_Type, EditObjectId.AsString});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
		return false;
	}

	const auto TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);
	if (!TryLoadContentObject(ManifestId, EditObjectId, TypeName, ContentObject))
	{
		ErrMsg = FString::Format(TEXT("Trying to load a content object that doesn't exist {0}"), {EditObjectId.AsString});
		UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
		return false;
	}

	ErrMsg.Empty();
	return true;
}

bool UBeamEditorContent::SaveContentObject(const FBeamContentManifestId& ManifestId, UBeamContentObject* EditingObject, FString& ErrMsg)
{
	const auto EditingTable = LocalManifests.FindRef(ManifestId);
	auto& EntryInManifest = *EditingTable->FindRow<FLocalContentManifestRow>(FName(EditingObject->Id), TEXT("Edit Content Start"));

	FString JsonContent;
	EditingObject->ToBasicJson(JsonContent);

	const auto FilePath = GetJsonBlobPath(EditingObject->Id, ManifestId);
	if (FFileHelper::SaveStringToFile(JsonContent, *FilePath))
	{
		EntryInManifest.Checksum = EditingObject->CreatePropertiesHash();
		EditorAssetSubsystem->SaveLoadedAsset(EditingTable);
		FDataTableEditorUtils::BroadcastPostChange(EditingTable, FDataTableEditorUtils::EDataTableChangeInfo::RowData);
		ErrMsg.Empty();
		return true;
	}

	ErrMsg = FString::Format(TEXT("Failed to save the content object {0}"), {EditingObject->Id});
	UE_LOG(LogBeamContent, Error, TEXT("%s"), *ErrMsg);
	return false;
}

bool UBeamEditorContent::CreateNewContentInManifest(const FBeamContentManifestId& ManifestId, const FString& ContentName, const int& ContentTypeIndex, UBeamContentObject*& ContentObject, FString& ErrMsg)
{
	const TSubclassOf<UBeamContentObject> ContentObjectSubType = AllContentTypes[ContentTypeIndex];
	return CreateNewContent(ManifestId, ContentName, ContentObjectSubType, ContentObject, ErrMsg);
}


bool UBeamEditorContent::GetChangingManifest(const UDataTable* Changed, FBeamContentManifestId& ManifestId, UDataTable*& EditingTable) const
{
	// We early out if the selection was changed in a data table that is not the one being managed by this editor.
	TArray<FBeamContentManifestId> LoadedManifestsIds;
	TArray<UDataTable*> LoadedManifests;
	this->LocalManifests.GenerateKeyArray(LoadedManifestsIds);
	this->LocalManifests.GenerateValueArray(LoadedManifests);

	ManifestId = FBeamContentManifestId{"BEAM_INVALID!!!!"};
	for (int i = 0; i < LoadedManifests.Num(); ++i)
	{
		if (LoadedManifests[i] == Changed)
		{
			ManifestId = LoadedManifestsIds[i];
			EditingTable = LoadedManifests[i];
		}
	}
	if (ManifestId.AsString.Equals(TEXT("BEAM_INVALID!!!!")) || !EditingTable) return false;
	return true;
}


FString UBeamEditorContent::GetJsonBlobPath(FString RowName, FBeamContentManifestId ManifestId)
{
	return DefaultBeamableProjectContentObjects / ManifestId.AsString / RowName + TEXT(".json");
}

FString UBeamEditorContent::GetManifestDataTableName(const FBeamContentManifestId Id)
{
	return TEXT("BCM_") + Id.AsString.Mid(0, 1).ToUpper() + Id.AsString.Mid(1, Id.AsString.Len() - 1);
}

FBeamContentManifestId UBeamEditorContent::GetManifestIdFromDataTable(const UDataTable* Table)
{
	FString Discard;
	FString Name;
	if (Table->GetName().Split("_", &Discard, &Name))
	{
		return FBeamContentManifestId{Name.Mid(0, 1).ToLower() + Name.Mid(1, Name.Len() - 1)};
	}
	return {};
}


void UBeamEditorContent::BakeManifest(UDataTable* LocalManifest, UBeamContentCache* Cache)
{
	FString ManifestName = LocalManifest->GetFName().ToString();
	int32 UnderscoreIdx;
	ensureAlwaysMsgf(ManifestName.FindChar('_', UnderscoreIdx), TEXT("Content Manifests must have their name prefixed with 'BCM_'. %s"), *LocalManifest->GetFName().ToString());

	ManifestName.RightChopInline(UnderscoreIdx + 1);
	ManifestName.ToLowerInline();

	const auto ManifestId = FBeamContentManifestId{ManifestName};
	Cache->ManifestId = ManifestId;
	LocalManifest->ForeachRow("", TFunctionRef<void (const FName&, const FLocalContentManifestRow& Value)>(
		                          [this, Cache, ManifestId, LocalManifest](const FName& RowName, const FLocalContentManifestRow& RowData)
		                          {
			                          const bool bNotInCache = !Cache->Hashes.Contains(RowName);
			                          const bool bInCacheButModified = Cache->Hashes.Contains(RowName) && !Cache->Hashes[RowName].Equals(RowData.Checksum);
			                          if (bNotInCache || bInCacheButModified)
			                          {
				                          // Create a new BeamContentObject instance of each content Object
				                          UBeamContentObject* Content;
				                          InstantiateContentObject(LocalManifest, RowName, Content, Cache);

				                          // Add it to the BCC_ BeamRuntimeContentCache.
				                          Cache->Cache.Add(RowName, Content);
				                          Cache->Hashes.Add(RowName, RowData.Checksum);			                          	
			                          }
		                          }));

	EditorAssetSubsystem->SaveLoadedAsset(Cache, false);

	// Update the settings for it.
	UBeamCoreSettings* EditorSettings = GetMutableDefault<UBeamCoreSettings>();
	const auto CookedAssetPath = EditorAssetSubsystem->GetPathNameForLoadedAsset(Cache);
	EditorSettings->BakedContentManifests.AddUnique(TSoftObjectPtr<UBeamContentCache>{CookedAssetPath});
	EditorSettings->SaveConfig(CPF_Config, *EditorSettings->GetDefaultConfigFilename());
}
