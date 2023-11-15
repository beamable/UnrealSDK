// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\..\..\..\BeamableCore\Public\Content\BeamContentCache.h"
#include "AutoGen/SubSystems/BeamContentApi.h"
#include "Content/BeamContentObject.h"
#include "GameFramework/SaveGame.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "UObject/Object.h"
#include "AutoGen/Rows/ClientContentInfoTableRow.h"
#include "Content/DownloadContentState.h"

#include "BeamContentSubsystem.generated.h"

class UBeamContentObject;
class UBeamContentApi;

UCLASS()
class BEAMABLECORERUNTIME_API ULocalCachedContentSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, SaveGame)
	UBeamContentCache* SavedCache;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContentManifestsUpdated, TArray<FBeamContentManifestId>, UpdatedManifests);

UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamContentSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamContentApi* ContentApi;

	UPROPERTY()
	TMap<FBeamContentManifestId, UBeamContentCache*> LiveContent;

	UPROPERTY()
	TMap<FBeamContentManifestId, UBeamContentCache*> BakedContent;

	UPROPERTY()
	TArray<UClass*> AllContentTypes;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	 * For every cooked content manifest tries to load either a local cache from the latest downloaded content (of previous runs) OR falls back to the cooked content with the build. 
	 */
	virtual void InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp) override;

	/**
	 * Only does something on dedicated server builds. Fetches the content manifest and downloads up-to-date content.
	 */
	virtual void OnBeamableStarting_Implementation(FBeamOperationHandle& ResultOp) override;
	
	/**
	 * If it's the first time this callback is being called (by our automatic auth flows for the owner UserSlot), we pull the latest 'global' manifest (default one) and cache it in-memory (and in a local file).
	 */
	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;

private:
	/**
	 * Given a Client CSV (contains public content only) and its id, we make requests to the URLs where the actual content JSON is stored.
	 * Run OnSuccess if all downloads succeed. OnError, otherwise.
	 */
	void DownloadLiveContentObjectsData(const FBeamContentManifestId Id, FSimpleDelegate OnSuccess, FSimpleDelegate OnError);
	void DownloadLiveContentObjectsData(const FBeamContentManifestId Id, const TArray<FClientContentInfoTableRow*> Rows, const TMap<FBeamContentId, FString> Checksums, FSimpleDelegate OnSuccess, FSimpleDelegate OnError);

	static void PrepareContentDownloadRequest(FBeamContentManifestId ManifestId, FClientContentInfoTableRow* ContentEntry, FDownloadContentState& Item);

	/**
	 * Given a response to a Download Content Request, we update the live runtime cache of content definitions. 
	 */
	void UpdateDownloadedContent(FString UriResponse, FDownloadContentState DownloadState);

public:
	/**
	 * @brief Called whenever we successfully fetch one or more content manifests AND update the internal state of that manifest. 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnContentManifestsUpdated ContentManifestsUpdated;


	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamContentSubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamContentSubsystem>(); }

	/**
	 * Tries to get a UBeamContentObject with the given Id from the 'global' (default) manifest.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetContent(FBeamContentId ContentId, UBeamContentObject*& OutContent);

	/**
	 * Tries to get a UBeamContentObject with the given Id from the manifest with the given Id.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetContentFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId, UBeamContentObject*& OutContent);

	/**
	 * Tries to get a UBeamContentObject with the given Id from the 'global' (default) manifest. This will always return the most recent baked content (either the cooked one or a downloaded and saved one). 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetBakedContent(FBeamContentId ContentId, UBeamContentObject*& OutContent);

	/**
	* Tries to get a UBeamContentObject with the given Id from the manifest with the given Id. This will always return the most recent baked content (either the cooked one or a downloaded and saved one).
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetBakedContentFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId, UBeamContentObject*& OutContent);

	/**
	 * Tries to get a UBeamContentObject with the given Id from the 'global' (default) manifest.
	 * CPP helper that casts to the content type the caller expects that the object with the given ContentId to be.
	 */
	template <typename TContentType>
	bool TryGetContentOfType(FBeamContentId ContentId, TContentType*& OutContent)
	{
		return TryGetContentOfTypeFromManifest<TContentType>(FBeamContentManifestId{"global"}, ContentId, OutContent);
	}

	/**
	 * @brief Gets all content ids for all loaded content objects of a certain type. It returns all content subtypes of the given type too, unless specified otherwise.
	 * @return The number of objects that match that. 
	 */
	UFUNCTION(BlueprintCallable)
	int GetIdsOfContentType(TSubclassOf<UBeamContentObject> Type, TArray<FBeamContentId>& Ids, bool bGetInherited = true);

	/**
	 * Tries to get a UBeamContentObject with the given Id from the manifest with the given Id.
	 * CPP helper that casts to the content type the caller expects that the object with the given ContentId to be.
	 */
	template <typename TContentType>
	bool TryGetContentOfTypeFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId, TContentType*& OutContent)
	{
		static_assert(TIsDerivedFrom<TContentType, UBeamContentObject>::Value, "TContentType must be a UBeamContentObject.");
		UBeamContentObject* Obj;
		const bool          bFound = TryGetContentFromManifest(ManifestId, ContentId, Obj);
		OutContent                 = Cast<TContentType>(Obj);
		return bFound && OutContent;
	}

	/**
	 * @brief Asks the Beamable server for the newest CSV representing the public content manifest with the given Id. Updates the runtime content cache's received manifest, but only downloads each individual content
	 * if the flag is set.
	 * 
	 * @param ManifestId The ManifestId to fetch. 
	 * @param bDownloadIndividualContent Whether or not we should download the entire manifest.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchContentManifestOperation(FBeamContentManifestId ManifestId, bool bDownloadIndividualContent, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
		FetchContentManifest(ManifestId, bDownloadIndividualContent, Handle, CallingContext);
		return Handle;
	}

	/**	 
	 * @brief Asks the Beamable server for the newest CSV representing the public content manifest with the given Id. Updates the runtime content cache's received manifest, but only downloads each individual content
	 * if the flag is set.
	 * 
	 * @param ManifestId The ManifestId to fetch. 
	 * @param bDownloadIndividualContent Whether or not we should download the entire manifest.
	 */
	FBeamOperationHandle CPP_FetchContentManifestOperation(FBeamContentManifestId ManifestId, bool bDownloadIndividualContent, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
		FetchContentManifest(ManifestId, bDownloadIndividualContent, Handle, CallingContext);
		return Handle;
	}

	UFUNCTION()
	void FetchContentManifest(FBeamContentManifestId ManifestId, bool bDownloadIndividualContent, FBeamOperationHandle Op, UObject* CallingContext);

	/**
	 * @brief Downloads the newest individual content objects of the given manifest.
	 * 
	 * @param ManifestId The ManifestId for the content manifest containing the given Ids. 
	 * @param ContentToDownload The list of ContentIds, contained in the given manifest, to download the JSON for.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchIndividualContentBatchOperation(FBeamContentManifestId ManifestId, TArray<FBeamContentId> ContentToDownload, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
		FetchIndividualContent(ManifestId, ContentToDownload, Handle, CallingContext);
		return Handle;
	}

	/**
	 * @brief Downloads the newest individual content objects of the given manifest.
	 * 
	 * @param ManifestId The ManifestId for the content manifest containing the given Ids. 
	 * @param ContentToDownload The list of ContentIds, contained in the given manifest, to download the JSON for.
	 */
	FBeamOperationHandle CPP_FetchIndividualContentBatchOperation(FBeamContentManifestId ManifestId, TArray<FBeamContentId> ContentToDownloadFetch, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
		FetchIndividualContent(ManifestId, ContentToDownloadFetch, Handle, CallingContext);
		return Handle;
	}

	/**
	 * @brief Downloads the newest individual content objects of the given manifest.
	 * 
	 * @param ManifestId The ManifestId for the content manifest containing the given Ids. 
	 * @param ContentToDownload The list of ContentIds, contained in the given manifest, to download the JSON for.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchIndividualContentOperation(FBeamContentManifestId ManifestId, FBeamContentId ContentToDownload, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
		FetchIndividualContent(ManifestId, {ContentToDownload}, Handle, CallingContext);
		return Handle;
	}

	/**
	 * @brief Downloads the newest individual content objects of the given manifest.
	 * 
	 * @param ManifestId The ManifestId for the content manifest containing the given Ids. 
	 * @param ContentToDownload The list of ContentIds, contained in the given manifest, to download the JSON for.
	 */
	FBeamOperationHandle CPP_FetchIndividualContentOperation(FBeamContentManifestId ManifestId, FBeamContentId ContentToDownload, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
		FetchIndividualContent(ManifestId, {ContentToDownload}, Handle, CallingContext);
		return Handle;
	}

	UFUNCTION()
	void FetchIndividualContent(FBeamContentManifestId ManifestId, TArray<FBeamContentId> ContentToDownloadFetch, FBeamOperationHandle Op, UObject* CallingContext);
};
