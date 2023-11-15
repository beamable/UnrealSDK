// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Content/BeamContentSubsystem.h"

#include "HttpModule.h"
#include "BeamNotifications/SubSystems/BeamContentNotifications.h"
#include "Interfaces/IHttpResponse.h"
#include "Content/DownloadContentState.h"

#if WITH_EDITOR
#include "BeamableCoreRuntimeEditor/Public/Subsystems/Content/BeamEditorContent.h"
#endif

void UBeamContentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ContentApi = GEngine->GetEngineSubsystem<UBeamContentApi>();
}

void UBeamContentSubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	FBeamOperationHandle Op = GEngine->GetEngineSubsystem<UBeamRequestTracker>()->CPP_BeginOperation({}, GetName(), {});

	// Grab all existing ContentObject classes so we can correctly deserialize content we fetch from the content API.
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UBeamContentObject::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			UE_LOG(LogTemp, Display, TEXT("Initializing Beam Runtime Content System - Found Content Type %s"), *It->GetFName().ToString())
			AllContentTypes.Add(*It);
		}
	}

	// Go through list of baked content manifests and load up the baked BeamRuntimeContentCache the baked		
	auto                    CoreSettings    = GetMutableDefault<UBeamCoreSettings>();
	auto                    RuntimeSettings = GetMutableDefault<UBeamRuntimeSettings>();
	TArray<FSoftObjectPath> BakedContentPaths;
	for (const auto& BeamRuntimeContentCache : CoreSettings->BakedContentManifests)
		BakedContentPaths.Add(BeamRuntimeContentCache.ToSoftObjectPath());

	const auto Handle = RuntimeSettings->ContentStreamingManager.RequestAsyncLoad(BakedContentPaths, FStreamableDelegate::CreateLambda([this, Op, BakedContentPaths, RuntimeSettings, CoreSettings]()
	{
		for (int i = 0; i < CoreSettings->BakedContentManifests.Num(); ++i)
		{
			const auto LoadedObject = CoreSettings->BakedContentManifests[i];
			checkf(LoadedObject, TEXT("Failed to find the content manifest at path %s. Cook content again so that we can correctly set up the baked content objects."),
			       *BakedContentPaths[i].ToString())

			const auto BakedContentManifest = LoadedObject.Get();
			const auto ManifestId           = BakedContentManifest->ManifestId;
			BakedContent.Add(ManifestId, BakedContentManifest);
		}

		GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
	}));

	// If we don't have any baked content, this Operation is a no-op.
	if (BakedContentPaths.Num() == 0)
		GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});

	ResultOp = Op;
}

void UBeamContentSubsystem::OnBeamableStarting_Implementation(FBeamOperationHandle& ResultOp)
{
	FBeamOperationEventHandlerCode                                        OpHandler;
	OpHandler.BindLambda([](const TArray<FUserSlot>&, FBeamOperationEvent OpEvent)
	{
		if (OpEvent.EventType == OET_ERROR)
		{
			// TODO: How should we handle when S3 explodes for some reason?
		}
	});
	FBeamOperationHandle Op = GEngine->GetEngineSubsystem<UBeamRequestTracker>()->CPP_BeginOperation({}, GetName(), OpHandler);

	const auto ManifestId                 = FBeamContentManifestId{TEXT("global")};
	const auto bShouldDownloadIndividuals = GetDefault<UBeamRuntimeSettings>()->bDownloadIndividualContentOnStart;
	FetchContentManifest(ManifestId, bShouldDownloadIndividuals, Op, this);
	ResultOp = Op;
}

void UBeamContentSubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	// The result Op is a completed Op as we don't have anything else to do async if we are not fetching content.
	Super::OnUserSignedIn_Implementation(UserSlot, BeamRealmUser, bIsOwnerUserAuth, ResultOp);

	// We also set up the content refresh notification here whenever the owner user signs in (we need to set this up again as websocket connections are established per-UserSlot).
	const auto NotificationHandler = FOnContentRefreshNotificationCode::CreateLambda([this](const FContentRefreshNotificationMessage& ContentRefreshNotificationMessage)
	{
		// Our legacy solution here is that we delay grabbing the content so as to not make every single logged in client bombard the content service with
		// requests at the same time. We delay by a random amount in seconds as defined by the refresh message.
		const int32 DelayCount = FMath::RandRange(0, ContentRefreshNotificationMessage.Delay);

		// Configure an operation to run refresh the given content manifest some time in the future.
		FTimerHandle H;
		GetWorld()->GetTimerManager().SetTimer(H, FTimerDelegate().CreateLambda([this, ContentRefreshNotificationMessage]
		{
			const auto DelayedFetchAllOpHandler = FBeamOperationEventHandlerCode::CreateLambda([](const TArray<FUserSlot>&, FBeamOperationEvent OpEvent)
			{
				if (OpEvent.EventType == OET_ERROR)
				{
					// TODO: How should we handle when S3 explodes for some reason?
				}
			});

			const FBeamOperationHandle DelayedFetchAllOp = GEngine->GetEngineSubsystem<UBeamRequestTracker>()->CPP_BeginOperation({}, GetName(), DelayedFetchAllOpHandler);
			FetchContentManifest(ContentRefreshNotificationMessage.Manifest.Id, true, DelayedFetchAllOp, this);
			UE_LOG(LogBeamContent, Warning, TEXT("Delay for ContentRefresh is over. Fetching the updated content manifest."));
		}), DelayCount, false, DelayCount);

		UE_LOG(LogBeamContent, Warning, TEXT("Received ContentRefresh notification. Fetching content in %d seconds."), DelayCount);
	});
	GEngine->GetEngineSubsystem<UBeamContentNotifications>()->CPP_SubscribeToContentRefresh(UserSlot, Runtime->DefaultNotificationChannel, NotificationHandler);
}

void UBeamContentSubsystem::PrepareContentDownloadRequest(FBeamContentManifestId ManifestId, FClientContentInfoTableRow* ContentEntry, FDownloadContentState& Item)
{
	FBeamContentId  Id         = ContentEntry->ContentId;
	FString         ContentUri = ContentEntry->Uri;
	TArray<FString> Tags       = ContentEntry->Tags;
	FOptionalString Checksum   = FOptionalString{ContentEntry->Version};

	TUnrealRequestPtr ptr = FHttpModule::Get().CreateRequest();
	ptr->SetVerb("GET");
	ptr->SetURL(ContentUri);
	ptr->SetHeader(UBeamBackend::HEADER_ACCEPT, UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);
	Item = {ManifestId, Id, Tags, Checksum, ptr};
}


void UBeamContentSubsystem::DownloadLiveContentObjectsData(const FBeamContentManifestId Id, FSimpleDelegate OnSuccess, FSimpleDelegate OnError)
{
	TArray<FClientContentInfoTableRow*> Rows;
	if (LiveContent.Contains(Id))
	{
		const UBeamContentCache* ContentCache = LiveContent.FindChecked(Id);
		ContentCache->LatestRemoteManifest->GetAllRows(TEXT(""), Rows);
		DownloadLiveContentObjectsData(Id, Rows, ContentCache->Hashes, OnSuccess, OnError);
	}
	else
	{
		// TODO: When we go into the Session service implementation and figure out online/offline modes and recovery, we need to revisit this.
		UE_LOG(LogBeamContent, Error, TEXT("Failed to download data on account of missing the live content manifest. This should only be seen when not connected to the internet."));
	}
}

void UBeamContentSubsystem::DownloadLiveContentObjectsData(const FBeamContentManifestId Id, const TArray<FClientContentInfoTableRow*> Rows, const TMap<FBeamContentId, FString> Checksums, FSimpleDelegate OnSuccess, FSimpleDelegate OnError)
{
	// We keep track of each content we are downloading (the bool indicates whether or not we managed to write the file
	// locally and add it to the local manifest. 
	TArray<FDownloadContentState> DownloadContentOperations;
	if (Rows.Num() == 0)
	{
		OnSuccess.ExecuteIfBound();
		return;
	}

	for (const auto ContentEntry : Rows)
	{
		if (ContentEntry->Type == EContentType::BEAM_content)
		{
			// We only download changed content from the given manifest
			const auto Checksum = Checksums.Find({ContentEntry->ContentId});
			if (!Checksum || !ContentEntry->Version.Equals(*Checksum))
			{
				FDownloadContentState Item;
				PrepareContentDownloadRequest(Id, ContentEntry, Item);
				DownloadContentOperations.Add(Item);
				UE_LOG(LogBeamContent, Warning, TEXT("Detected Changes in Content Id %s. Preparing to fetch its JSON blob."), *Item.Id.AsString);
			}
		}
	}

	// For each download that we'll make, register a lambda that:
	//  - Tries to save the downloaded file to the local '.beamable' folder.
	//  - Checks to see if it was the last download and, if so, invoke the appropriate on success/error callback.		
	for (int DownloadIdx = 0; DownloadIdx < DownloadContentOperations.Num(); ++DownloadIdx)
	{
		const auto& DownloadContentOperation = DownloadContentOperations[DownloadIdx];
		DownloadContentOperation.Request->OnProcessRequestComplete().BindLambda([this, DownloadContentOperations, DownloadContentOperation, Id, OnSuccess, OnError]
		(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool)
			{
#if WITH_EDITOR
				if (GEditor && !GEditor->IsPlayingSessionInEditor())
					return;
#endif
				if (HttpResponse->GetResponseCode() == 200)
				{
					UpdateDownloadedContent(HttpResponse->GetContentAsString(), DownloadContentOperation);
				}

				bool bAreAllFinished = true;
				bool bAreAllSuccess  = true;
				bool bAreAnyFailed   = false;

				TArray<FBeamContentId> FailedDownloads;
				for (const auto& Download : DownloadContentOperations)
				{
					const auto bIsSuccess = Download.Request->GetStatus() == EHttpRequestStatus::Succeeded;
					const auto bIsFailure = Download.Request->GetStatus() == EHttpRequestStatus::Failed;

					bAreAllFinished &= bIsSuccess || bIsFailure;
					bAreAllSuccess &= bIsSuccess;
					bAreAnyFailed |= bIsFailure;
					FailedDownloads.Add(FBeamContentId(Download.Id));
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


void UBeamContentSubsystem::UpdateDownloadedContent(FString UriResponse, FDownloadContentState DownloadState)
{
	// We create the object from the downloaded JSON and store it in the created cache.
	const auto ContentId        = FBeamContentId(DownloadState.Id);
	const auto LiveContentCache = LiveContent.FindChecked(DownloadState.ManifestId);

	const auto TypeTag = DownloadState.Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });
	checkf(TypeTag, TEXT("Missing content tag that informs the correct type. ManifestId=%s, ContentId=%s"), *DownloadState.ManifestId.AsString, *ContentId.AsString)

	const auto TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);

	// Otherwise, find the UClass for the content type. Load the JSON and deserialize it into the UBeamContentObject.
	const auto Type = AllContentTypes.FindByPredicate([TypeName](const UClass* Class) { return Class->GetFName().ToString().Equals(TypeName); });
	checkf(Type, TEXT("TypeTag for entry did not match any of the existing classes. ManifestId=%s, ContentId=%s"), *DownloadState.ManifestId.AsString, *ContentId.AsString)

	const auto ContentObject = NewObject<UBeamContentObject>(GetTransientPackage(), *Type);
	ContentObject->FromBasicJson(UriResponse);
	ContentObject->Tags = DownloadState.Tags;


	LiveContentCache->Cache.Add(ContentId, ContentObject);
	LiveContentCache->Hashes.Add(ContentId, ContentObject->CreatePropertiesHash());

	UE_LOG(LogBeamContent, Warning, TEXT("Downloaded content with id=%s and hash=%s, from manifest=%s"), *ContentId.AsString, *LiveContentCache->Hashes.FindChecked(ContentId), *DownloadState.ManifestId.AsString)
}


bool UBeamContentSubsystem::TryGetContent(FBeamContentId ContentId, UBeamContentObject*& OutContent)
{
	return TryGetContentFromManifest(FBeamContentManifestId{"global"}, ContentId, OutContent);
}

bool UBeamContentSubsystem::TryGetContentFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId, UBeamContentObject*& OutContent)
{
	if (LiveContent.Contains(ManifestId))
	{
		const auto LiveManifest = LiveContent.FindRef(ManifestId);
		if (LiveManifest->Cache.Contains(ContentId))
		{
			OutContent = LiveManifest->Cache.FindRef(ContentId);
			return true;
		}

		const auto CookedManifest = BakedContent.FindRef(ManifestId);
		if (!CookedManifest)
		{
			UE_LOG(LogBeamContent, Warning, TEXT("No content with Id=%s was downloaded yet. Since the Manifest with Id=%s wasn't Baked, we can't provide this content."), *ContentId.AsString, *ManifestId.AsString)
			return false;
		}

		if (CookedManifest->Cache.Contains(ContentId))
		{
			OutContent = CookedManifest->Cache.FindRef(ContentId);
			return true;
		}

		return false;
	}

	const auto CookedManifest = BakedContent.FindRef(ManifestId);
	if (!CookedManifest)
	{
		UE_LOG(LogBeamContent, Warning, TEXT("No content with Id=%s was downloaded yet. Since the Manifest with Id=%s wasn't Baked, we can't provide this content."), *ContentId.AsString, *ManifestId.AsString)
		return false;
	}

	if (CookedManifest->Cache.Contains(ContentId))
	{
		OutContent = CookedManifest->Cache.FindRef(ContentId);
		return true;
	}

	return false;
}

bool UBeamContentSubsystem::TryGetBakedContent(FBeamContentId ContentId, UBeamContentObject*& OutContent)
{
	return TryGetBakedContentFromManifest(FBeamContentManifestId{"global"}, ContentId, OutContent);
}

bool UBeamContentSubsystem::TryGetBakedContentFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId, UBeamContentObject*& OutContent)
{
	checkf(BakedContent.Contains(ManifestId), TEXT("Manifest must exist in at least the baked content"))
	const auto CookedManifest = BakedContent.FindRef(ManifestId);
	if (CookedManifest->Cache.Contains(ContentId))
	{
		OutContent = CookedManifest->Cache.FindRef(ContentId);
		return true;
	}
	return false;
}

int UBeamContentSubsystem::GetIdsOfContentType(TSubclassOf<UBeamContentObject> Type, TArray<FBeamContentId>& Ids, bool bGetInherited)
{
	// TODO: We either need to cache the results (and invalidate when content updates) OR we need to change our RuntimeCache data structure into a search tree. 
	Ids.Reset();
	Ids.Reserve(256);
	for (const auto& Content : LiveContent)
	{
		for (const auto& Cache : Content.Value->Cache)
		{
			const auto Class         = Cache.Value->GetClass();
			const auto bIsType       = !bGetInherited && Class == Type.Get();
			const auto bInheritsFrom = bGetInherited && Class->IsChildOf(Type);

			if (bIsType || bInheritsFrom)Ids.AddUnique(Cache.Key);
		}
	}

	for (const auto& Content : BakedContent)
	{
		for (const auto& Cache : Content.Value->Cache)
		{
			const auto Class         = Cache.Value->GetClass();
			const auto bIsType       = !bGetInherited && Class == Type.Get();
			const auto bInheritsFrom = bGetInherited && Class->IsChildOf(Type);

			if (bIsType || bInheritsFrom)Ids.AddUnique(Cache.Key);
		}
	}
	return Ids.Num();
}

void UBeamContentSubsystem::FetchContentManifest(FBeamContentManifestId ManifestId, bool bDownloadIndividualContent, FBeamOperationHandle Op, UObject* CallingContext)
{
	const auto Request = UGetManifestPublicRequest::Make(FOptionalBeamContentManifestId(ManifestId), GetTransientPackage(), {});
	const auto Handler = FOnGetManifestPublicFullResponse::CreateLambda([this, ManifestId, Op, bDownloadIndividualContent](FGetManifestPublicFullResponse Resp)
	{
		if (Resp.State == RS_Success)
		{
			UBeamContentCache* Cache = NewObject<UBeamContentCache>();
			Cache->ManifestId        = ManifestId;


			UDataTable* ManifestCopy = NewObject<UDataTable>();
			ManifestCopy->CreateTableFromOtherTable(Resp.SuccessData->CsvData);

			const auto NumEntries       = ManifestCopy->GetRowMap().Num();
			Cache->LatestRemoteManifest = ManifestCopy;
			Cache->Cache.Reserve(NumEntries);
			Cache->Hashes.Reserve(NumEntries);

			if (LiveContent.Contains(ManifestId))
			{
				LiveContent[ManifestId]->LatestRemoteManifest = ManifestCopy;
			}
			else
			{
				LiveContent.Add(ManifestId, Cache);
			}

			if (bDownloadIndividualContent)
			{
				DownloadLiveContentObjectsData(ManifestId, FSimpleDelegate::CreateLambda([Op, this, Cache, ManifestId]
				{
					ContentManifestsUpdated.Broadcast({ManifestId});
					GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
				}), FSimpleDelegate::CreateLambda([Op]
				{
					GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, {});
				}));
			}
			else
			{
				ContentManifestsUpdated.Broadcast({ManifestId});
				GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
			}
			return;
		}

		if (Resp.State == RS_Error)
		{
			GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, {});
		}
	});

	FBeamRequestContext Ctx;
	ContentApi->CPP_GetManifestPublic(Request, Handler, Ctx, Op, CallingContext);
}

void UBeamContentSubsystem::FetchIndividualContent(FBeamContentManifestId ManifestId, TArray<FBeamContentId> ContentToDownloadFetch, FBeamOperationHandle Op, UObject* CallingContext)
{
	ensureAlwaysMsgf(LiveContent.Contains(ManifestId), TEXT("Content Manifest %s was never fetched. Please ensure that the FetchContentManifest operation is called at least once for all of your manifests."), *ManifestId.AsString);

	const auto Cache = LiveContent.FindRef(ManifestId);

	TArray<FClientContentInfoTableRow*> ManifestRows;
	for (auto ToDownloadFetch : ContentToDownloadFetch)
	{
		const auto Row = Cache->LatestRemoteManifest->FindRow<FClientContentInfoTableRow>(FName(ToDownloadFetch.AsString), TEXT(""));
		ensureAlwaysMsgf(Row, TEXT("Content Manifest %s does not contain a content with Id %s. Please ensure that this Id is of this manifest."), *ManifestId.AsString, *ToDownloadFetch.AsString);
		if (Row) ManifestRows.Add(Row);
	}

	if (ManifestRows.Num() > 0)
	{
		DownloadLiveContentObjectsData(ManifestId, ManifestRows, Cache->Hashes, FSimpleDelegate::CreateLambda([this, Op]
		{
			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
		}), FSimpleDelegate::CreateLambda([this, Op]
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, {});
		}));
	}
	else
	{
		Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
	}
}
