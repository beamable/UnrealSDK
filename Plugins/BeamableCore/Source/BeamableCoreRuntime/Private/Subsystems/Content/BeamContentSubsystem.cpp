// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Content/BeamContentSubsystem.h"

#include "AutoGen/Rows/ClientContentInfoTableRow.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/GameplayStatics.h"

void UBeamContentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ContentApi = GEngine->GetEngineSubsystem<UBeamContentApi>();
}

FBeamOperationHandle UBeamContentSubsystem::InitializeWhenUnrealReady()
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
	auto RuntimeSettings = GetMutableDefault<UBeamRuntimeSettings>();
	TArray<FSoftObjectPath> BakedContentPaths;
	for (const auto& BeamRuntimeContentCache : RuntimeSettings->BakedContentManifests)
		BakedContentPaths.Add(BeamRuntimeContentCache.ToSoftObjectPath());

	const auto Handle = RuntimeSettings->ContentStreamingManager.RequestAsyncLoad(BakedContentPaths, FStreamableDelegate::CreateLambda([this, Op, BakedContentPaths, RuntimeSettings]()
	{
		for (int i = 0; i < RuntimeSettings->BakedContentManifests.Num(); ++i)
		{
			const auto LoadedObject = RuntimeSettings->BakedContentManifests[i];
			checkf(LoadedObject, TEXT("Failed to find the content manifest at path %s. Cook content again so that we can correctly set up the baked content objects."),
			       *BakedContentPaths[i].ToString())

			const auto BakedContentManifest = LoadedObject.Get();
			const auto ManifestId = BakedContentManifest->ManifestId;
			BakedContent.Add(ManifestId, BakedContentManifest);
		}

		GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
	}));

	// If we don't have any baked content, this Operation is a no-op.
	if (BakedContentPaths.Num() == 0)
		GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});

	return Op;
}

FBeamOperationHandle UBeamContentSubsystem::OnUserSignedIn(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsFirstAuth)
{
	// If this is the first time we are authenticated with beamable, we'll go fetch the content from our backend
	if (bIsFirstAuth)
	{
		FBeamOperationEventHandlerCode OpHandler;
		OpHandler.BindLambda([](const TArray<FUserSlot>&, FBeamOperationEvent OpEvent)
		{
			if (OpEvent.EventType == ERROR)
			{
				// TODO: How should we handle when S3 explodes for some reason?
			}
		});
		FBeamOperationHandle Op = GEngine->GetEngineSubsystem<UBeamRequestTracker>()->CPP_BeginOperation({UserSlot}, GetName(), OpHandler);

		const auto ManifestId = FBeamContentManifestId{TEXT("global")};
		const auto Request = UGetManifestPublicRequest::Make(FOptionalBeamContentManifestId(ManifestId), GetTransientPackage());

		const auto Handler = FOnGetManifestPublicFullResponse::CreateLambda([this, ManifestId, Op](FGetManifestPublicFullResponse Resp)
		{
			if (Resp.State == Success)
			{
				UBeamRuntimeContentCache* Cache = NewObject<UBeamRuntimeContentCache>();
				Cache->ManifestId = ManifestId;

				const auto NumEntries = Resp.SuccessData->CsvData->GetRowMap().Num();
				Cache->Cache.Reserve(NumEntries);
				Cache->Hashes.Reserve(NumEntries);

				LiveContent.Add(ManifestId, Cache);

				DownloadLiveContentObjectsData(ManifestId, Resp.SuccessData, FSimpleDelegate::CreateLambda([Op, this, Cache, ManifestId]
				                               {
					                               GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
				                               }),
				                               FSimpleDelegate::CreateLambda([Op]
				                               {
					                               GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, {});
				                               }));
			}
		});
		FBeamRequestContext Ctx;
		ContentApi->CPP_GetManifestPublic(Request, Handler, Ctx, Op, this);
		return Op;
	}

	return Super::OnUserSignedIn(UserSlot, BeamRealmUser, bIsFirstAuth);
}

struct FDownloadContentState
{
	FClientContentInfoTableRow* ContentReference;
	TUnrealRequestPtr Request;
};

void UBeamContentSubsystem::DownloadLiveContentObjectsData(const FBeamContentManifestId Id,
                                                           const UClientManifestCsvResponse* PublicRemoteManifest,
                                                           FSimpleDelegate OnSuccess,
                                                           FSimpleDelegate OnError)
{
	// We keep track of each content we are downloading (the bool indicates whether or not we managed to write the file
	// locally and add it to the local manifest. 
	TArray<FDownloadContentState> DownloadContentOperations;

	// First we build up the list of download requests we'll have to make (we only care about the 'public' content)
	// If the content exists in the local manifest, we compare it's checksum to make sure it's modified and we need to download it.
	// If the content doesn't exist in the local manifest OR if it's local file is missing, we fetch it.
	TArray<FClientContentInfoTableRow*> Rows;
	PublicRemoteManifest->CsvData->GetAllRows(TEXT(""), Rows);

	
	if (Rows.Num() == 0)
	{
		OnSuccess.ExecuteIfBound();
		return;
	}

	for (const auto ContentEntry : Rows)
	{
		if (ContentEntry->Type == EContentType::BEAM_content)
		{
			const auto RowName = FName(ContentEntry->ContentId);
			TUnrealRequestPtr ptr = FHttpModule::Get().CreateRequest();
			ptr->SetVerb("GET");
			ptr->SetURL(ContentEntry->Uri);
			ptr->SetHeader(UBeamBackend::HEADER_ACCEPT, UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);
			DownloadContentOperations.Add(FDownloadContentState{ContentEntry, ptr});
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
				if (HttpResponse->GetResponseCode() == 200)
				{
					const auto Row = DownloadContentOperation.ContentReference;
					// We create the object from the downloaded JSON and store it in the created cache.
					const auto ContentId = FBeamContentId(Row->ContentId);
					const auto LiveContentCache = LiveContent.FindChecked(Id);

					const auto TypeTag = Row->Tags.FindByPredicate([](FString Tag) { return Tag.StartsWith(UBeamContentObject::Beam_Tag_Type); });
					checkf(TypeTag, TEXT("Missing content tag that informs the correct type. ManifestId=%s, ContentId=%s"), *Id.AsString, *ContentId.AsString)

					const auto TypeName = UBeamContentObject::GetTypeClassNameFromTypeTag(*TypeTag);

					// Otherwise, find the UClass for the content type. Load the JSON and deserialize it into the UBeamContentObject.
					const auto Type = AllContentTypes.FindByPredicate([TypeName](const UClass* Class) { return Class->GetFName().ToString().Equals(TypeName); });
					checkf(Type, TEXT("TypeTag for entry did not match any of the existing classes. ManifestId=%s, ContentId=%s"), *Id.AsString, *ContentId.AsString)

					const auto ContentObject = NewObject<UBeamContentObject>(GetTransientPackage(), *Type);
					ContentObject->FromBasicJson(HttpResponse->GetContentAsString());
					ContentObject->Tags = Row->Tags;

					UE_LOG(LogBeamContent, Warning, TEXT("Downloaded content with id=%s, from manifest=%s"), *ContentId.AsString, *Id.AsString)

					LiveContentCache->Cache.Add(ContentId, ContentObject);
					LiveContentCache->Hashes.Add(ContentId, ContentObject->CreatePropertiesMD5Hash());
				}

				bool bAreAllFinished = true;
				bool bAreAllSuccess = true;
				bool bAreAnyFailed = false;

				TArray<FBeamContentId> FailedDownloads;
				for (const auto& Download : DownloadContentOperations)
				{
					const auto bIsSuccess = Download.Request->GetStatus() == EHttpRequestStatus::Succeeded;
					const auto bIsFailure = Download.Request->GetStatus() == EHttpRequestStatus::Failed;

					bAreAllFinished &= bIsSuccess || bIsFailure;
					bAreAllSuccess &= bIsSuccess;
					bAreAnyFailed |= bIsFailure;
					FailedDownloads.Add(FBeamContentId(Download.ContentReference->ContentId));
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
		if (CookedManifest->Cache.Contains(ContentId))
		{
			OutContent = CookedManifest->Cache.FindRef(ContentId);
			return true;
		}

		return false;
	}

	const auto CookedManifest = BakedContent.FindRef(ManifestId);
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
