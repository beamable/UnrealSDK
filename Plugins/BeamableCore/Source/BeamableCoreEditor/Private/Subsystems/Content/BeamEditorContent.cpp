// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Content/BeamEditorContent.h"

#include "IContentBrowserSingleton.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "AutoGen/BaseContentReference.h"
#include "Factories/DataTableFactory.h"
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
}

void UBeamEditorContent::Deinitialize()
{
	Super::Deinitialize();
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
	const auto BeamEditorSettings = GetMutableDefault<UBeamEditorSettings>();

	if (BeamEditorSettings->CookedManifestsPath.IsEmpty()) BeamEditorSettings->CookedManifestsPath.Add(FDirectoryPath{DefaultBeamableCookedContentManifestsPath});
	if (BeamEditorSettings->UncookedManifestsPath.IsEmpty()) BeamEditorSettings->UncookedManifestsPath.Add(FDirectoryPath{DefaultBeamableUncookedContentManifestsPath});

	// Ensure that all directories in the cooked manifest paths array exist.
	for (const auto& CookedManifestsPath : BeamEditorSettings->CookedManifestsPath)
	{
		if (!EditorAssetSubsystem->DoesDirectoryExist(CookedManifestsPath.Path))
			EditorAssetSubsystem->MakeDirectory(CookedManifestsPath.Path);
	}

	// Ensure that all directories in the uncooked manifest paths array exist AND are added to the project settings as excluded from cooked builds.
	for (const auto& UncookedManifestsPath : BeamEditorSettings->UncookedManifestsPath)
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

	const auto GetManifestsRequest = UBasicContentGetManifestsRequest::Make(GetTransientPackage());
	const auto GetManifestsHandler = FOnBasicContentGetManifestsFullResponse::CreateUObject(this, &UBeamEditorContent::EnsureGlobalManifest_OnGetManifests, Op);
	FBeamRequestContext Ctx;
	ContentApi->CPP_GetManifests(EditorSlot, GetManifestsRequest, GetManifestsHandler, Ctx, Op, this);

	return Op;
}

void UBeamEditorContent::EnsureGlobalManifest_OnGetManifests(FBasicContentGetManifestsFullResponse Response, const FBeamOperationHandle Op)
{
	if (Response.State == Error)
	{
		// TODO: Open popup explaining that we failed to get the content manifests and as such the content service is not fine. Have option to try again
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == Success)
	{
		for (const auto Manifest : Response.SuccessData->Manifests)
		{
			ManifestIds.Add(Manifest->Id);
			UE_LOG(LogBeamContent, Display, TEXT("Manifest Found = %s"), *Manifest->Id.AsString)
		}

		if (ManifestIds.Num() == 0)
		{
			UE_LOG(LogBeamContent, Error, TEXT("No Manifest Found!"))

			const TArray<UReferenceSuperset*> EmptySuperset{};
			UBasicContentPostManifestRequest* EmptyManifest = UBasicContentPostManifestRequest::Make(Global_Manifest, EmptySuperset, GetTransientPackage());

			const auto Handler = FOnBasicContentPostManifestFullResponse::CreateUObject(this, &UBeamEditorContent::EnsureGlobalManifest_OnPostManifest, Op);
			FBeamRequestContext Ctx;
			ContentApi->CPP_PostManifest(Editor->GetMainEditorSlot(), EmptyManifest, Handler, Ctx, Op, this);
			return;
		}

		// For the case where we already have content manifests, we need to make sure we have the local manifests created locally correctly.
		for (const auto& Id : ManifestIds)
		{
			const auto ManifestAssetName = TEXT("BCM_") + Id.AsString.Mid(0, 1).ToUpper() + Id.AsString.Mid(1, Id.AsString.Len() - 1);

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
				LocalManifests.Add(Id, Manifest);
				auto NewEditorState = NewObject<ULocalContentManifestEditorState>();
				NewEditorState->ManifestId = Id;
				NewEditorState->EditingTable = Manifest;
				EditorStates.Add(Id, NewEditorState);

				// Inform asset registry
				IAssetRegistry::Get()->AssetCreated(Manifest);


				// Tell content browser to show the newly created asset					
				TArray<UObject*> Objects;
				Objects.Add(Manifest);
				ContentBrowserModule->Get().SyncBrowserToAssets(Objects);

				UE_LOG(LogTemp, Verbose, TEXT("Created Local Manifest with Id=%s!"), *Id.AsString)
			}
			// Otherwise, let's load it and keep it in the LocalManifests map
			else
			{
				// Add the newly created global manifest to the local manifest list
				UDataTable* Manifest = nullptr;
				if (bExistsInCooked)
					Manifest = Cast<UDataTable>(EditorAssetSubsystem->LoadAsset(CookedAssetPath));
				if (bExistsInUncooked)
					Manifest = Cast<UDataTable>(EditorAssetSubsystem->LoadAsset(UncookedAssetPath));

				// For us to be here, we should have the manifest loaded in one of these two paths.
				check(Manifest != nullptr)


				UE_LOG(LogTemp, Verbose, TEXT("Loaded Local Manifest with Id=%s!"), *Id.AsString)
				LocalManifests.Add(Id, Manifest);
				auto NewEditorState = NewObject<ULocalContentManifestEditorState>();
				NewEditorState->ManifestId = Id;
				NewEditorState->EditingTable = Manifest;
				EditorStates.Add(Id, NewEditorState);
			}
		}

		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditorContent::EnsureGlobalManifest_OnPostManifest(FBasicContentPostManifestFullResponse Response, const FBeamOperationHandle Op)
{
	if (Response.State == Error)
	{
		// TODO: Open popup explaining that we failed to get the content manifests and as such the content service is not fine. Have option to try again			
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == Success)
	{
		UE_LOG(LogBeamContent, Warning, TEXT("Found no content manifests so creating a default = %s - %lld"), *Response.SuccessData->Id.AsString, Response.SuccessData->Created)

		const auto Id = Response.SuccessData->Id;
		const auto ManifestAssetName = TEXT("BCM_") + Id.AsString.Mid(0, 1).ToUpper() + Id.AsString.Mid(1, Id.AsString.Len() - 1);

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
	const auto ManifestRequest = UBasicContentGetManifestRequest::Make(FOptionalBeamContentManifestId(ContentManifestId), GetTransientPackage());
	const auto ManifestRequestHandler = FOnBasicContentGetManifestFullResponse::CreateUObject(this, &UBeamEditorContent::PublishManifest_OnGetManifest, Op, ContentManifestId);
	ContentApi->CPP_GetManifest(EditorSlot, ManifestRequest, ManifestRequestHandler, Ctx, Op, this);

	return Op;
}

void UBeamEditorContent::PublishManifest_OnGetManifest(FBasicContentGetManifestFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId)
{
	if (Response.State == Error)
	{
		// TODO: Open popup explaining that we failed to get the content manifests and as such the content service is not fine. Have option to try again
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == Success)
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
				Reference->Content->Checksum = FOptionalString(Obj->CreatePropertiesMD5Hash());
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
			TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&DefJson);
			ContentDefinition->BeamSerialize(JsonSerializer);
			JsonSerializer->Close();
			Debug.Append(DefJson);
			Debug.Append(TEXT("\n"));
		}
		UE_LOG(LogBeamContent, Verbose, TEXT("Content Definitions:\n%s"), *Debug);
#endif

		// Send out the post request containing all content objects...
		FBeamRequestContext PostRequest;
		const auto PostContent = UPostContentRequest::Make(ContentDefinitions, GetTransientPackage());
		const auto PostContentHandler = FOnPostContentFullResponse::CreateUObject(this, &UBeamEditorContent::PublishManifest_OnPostContent, Op, ContentManifestId);
		ContentApi->CPP_PostContent({Editor->GetMainEditorSlot()}, PostContent, PostContentHandler, PostRequest, Op, this);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditorContent::PublishManifest_OnPostContent(FPostContentFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId)
{
	if (Response.State == Error)
	{
		// TODO: Open popup explaining that we failed to get the content manifests and as such the content service is not fine. Have option to try again
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == Success)
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
		const auto PostManifestRequest = UBasicContentPostManifestRequest::Make(ContentManifestId, Supersets, this);
		const auto PostManifestRequestHandler = FOnBasicContentPostManifestFullResponse::CreateUObject(this, &UBeamEditorContent::PublishManifest_OnPostManifest, Op, ContentManifestId);
		ContentApi->CPP_PostManifest({Editor->GetMainEditorSlot()}, PostManifestRequest, PostManifestRequestHandler, Ctx, Op, this);

		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
}

void UBeamEditorContent::PublishManifest_OnPostManifest(FBasicContentPostManifestFullResponse Response, FBeamOperationHandle Op, FBeamContentManifestId ContentManifestId) const
{
	if (Response.State == Error)
	{
		// TODO: Open popup explaining that we failed to get the content manifests and as such the content service is not fine. Have option to try again
		RequestTracker->TriggerOperationError(Op, Response.ErrorData.message, Response.Context.RequestId);
		return;
	}

	if (Response.State == Success)
	{
		// Just notify the caller that we have finished publishing.
		RequestTracker->TriggerOperationSuccess(Op, Response.SuccessData->Id.AsString, Response.Context.RequestId);
		return;
	}

	RequestTracker->TriggerOperationCancelled(Op, TEXT(""), Response.Context.RequestId);
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

bool UBeamEditorContent::TryLoadContentObject(const FBeamContentManifestId& OwnerManifest, const FBeamContentId& ContentId, FString TypeName, UBeamContentObject*& OutLoadedContentObject)
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
		const auto ManifestRow = LocalManifests[OwnerManifest]->FindRow<FLocalContentManifestRow>(FName(ContentId.AsString), TEXT("Saving Object"));

		const auto FileContents = ManifestRow->JsonBlob;
		const auto ContentObject = NewObject<UBeamContentObject>(GetTransientPackage(), *Type);
		LoadedContentObjects.Add(ContentId, ContentObject);

		OutLoadedContentObject = ContentObject;
		OutLoadedContentObject->FromBasicJson(FileContents);

		return true;
	}

	return false;
}
