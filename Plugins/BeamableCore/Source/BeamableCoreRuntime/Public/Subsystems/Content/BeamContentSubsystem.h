// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../BeamableCore/Public/Content/BeamContentCache.h"
#include "AutoGen/SubSystems/BeamContentApi.h"
#include "Content/BeamContentObject.h"
#include "GameFramework/SaveGame.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "UObject/Object.h"
#include "BeamBackend/BeamGenericApi.h"
#include "Content/DownloadContentState.h"

#include "BeamContentSubsystem.generated.h"

class UBeamContentObject;
class UBeamContentApi;

UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API ULocalCachedContentSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, SaveGame)
	UBeamContentCache* SavedCache;

	/**
	 * Gets the correct name for the save slot used to store the given manifest's serialized content cache.  
	 */
	static FString GetSaveSlotForManifest(FBeamContentManifestId Id) { return FString::Printf(TEXT("BEAM_SAVE_CONTENT_MANIFEST_%s"), *Id.AsString); }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContentManifestsUpdated, TArray<FBeamContentManifestId>, UpdatedManifests);

UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamContentSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamContentApi* ContentApi;

	UPROPERTY()
	UBeamGenericApi* GenericApi;

	UPROPERTY()
	TMap<FBeamContentManifestId, UBeamContentCache*> LiveContent;

	UPROPERTY()
	TMap<FBeamContentManifestId, UBeamContentCache*> BakedContent;

	UPROPERTY()
	TArray<UClass*> AllContentTypes;

	UPROPERTY()
	TMap<FString, UClass*> ContentTypeStringToContentClass;
	UPROPERTY()
	TMap<UClass*, FString> ContentClassToContentTypeString;

	TMap<UClass*, TArray<TArray<const FProperty*>>> PathsToContentLinks;
	TMap<UClass*, TArray<TArray<const FProperty*>>> PathsToRecursiveSelves;
	TMap<UClass*, TArray<TArray<const FProperty*>>> PathsToRecursiveProperties;
	TMap<UClass*, TArray<UClass*>> RecursivePropertyTypes;

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
	 * Given a list of FBeamRemoteContentManifestEntry (contains public content only) and a FBeamContentManifestId, we make requests to the URLs where the actual content JSON is stored.
	 * Run OnSuccess if all downloads succeed. OnError, otherwise.
	 */
	void DownloadContentObjects(FBeamContentManifestId ManifestId, TArray<FBeamRemoteContentManifestEntry> Rows, TMap<FBeamContentId, FString> Checksums,
	                            bool bIgnoreFilterMap, FBeamOperationHandle Op);

	// Static helpers
public:
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool AreContentsOfType(TSubclassOf<UBeamContentObject> AllowedType, TArray<FBeamContentId> Contents, TArray<FBeamContentId>& InvalidContentIds);
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool AreContentsOfTypeHierarchy(TSubclassOf<UBeamContentObject> AllowedType, TArray<FBeamContentId> Contents, TArray<FBeamContentId>& InvalidContentIds);
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool ValidateContentsType(TArray<TSubclassOf<UBeamContentObject>> AllowedTypes, TArray<FBeamContentId> Contents, TArray<FBeamContentId>& InvalidContentIds);
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool ValidateContentsTypeHierarchy(TArray<TSubclassOf<UBeamContentObject>> AllowedTypes, TArray<FBeamContentId> Contents, TArray<FBeamContentId>& InvalidContentIds);

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
	 * Checks if the in-memory content caches of the 'global' manfist have the content with the given id.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool IsLoadedContent(FBeamContentId ContentId);

	/**
	 * Checks if the in-memory content caches have the content from the given manifest and with the given id.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool IsLoadedContentFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId);

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
		const bool bFound = TryGetContentFromManifest(ManifestId, ContentId, Obj);
		OutContent = bFound ? Cast<TContentType>(Obj) : nullptr;
		return bFound && OutContent;
	}

	/**
	 * @brief Asks the Beamable server for the newest CSV representing the public content manifest with the given Id.
	 * Updates the runtime content cache's received manifest, but only downloads each individual content if the flag is set.
	 * 
	 * @param ManifestId The ManifestId to fetch. 
	 * @param bDownloadIndividualContent Whether we should download the entire manifest.
	 * @param bIgnoreFilterMap Whether the UBeamRuntimeSettings::IndividualContentDownloadFilter should be used to filter the individual content that is downloaded (only useful when bDownloadIndividualContent is true).
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchContentManifestOperation(FBeamContentManifestId ManifestId, bool bDownloadIndividualContent, bool bIgnoreFilterMap, FBeamOperationEventHandler OnOperationEvent);

	/**	 
	 * @brief Asks the Beamable server for the newest CSV representing the public content manifest with the given Id. Updates the runtime content cache's received manifest, but only downloads each individual content
	 * if the flag is set.
	 * 
	 * @param ManifestId The ManifestId to fetch. 
	 * @param bDownloadIndividualContent Whether we should download the entire manifest.
	 * @param bIgnoreFilterMap Whether the UBeamRuntimeSettings::IndividualContentDownloadFilter should be used to filter the individual content that is downloaded (only useful when bDownloadIndividualContent is true).
	 */
	FBeamOperationHandle CPP_FetchContentManifestOperation(FBeamContentManifestId ManifestId, bool bDownloadIndividualContent, bool bIgnoreFilterMap, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Downloads the newest individual content objects of the given manifest.
	 * 
	 * @param ManifestId The ManifestId for the content manifest containing the given Ids. 
	 * @param ContentToDownload The list of ContentIds, contained in the given manifest, to download the JSON for.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchIndividualContentBatchOperation(FBeamContentManifestId ManifestId, TArray<FBeamContentId> ContentToDownload, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @brief Downloads the newest individual content objects of the given manifest.
	 * 
	 * @param ManifestId The ManifestId for the content manifest containing the given Ids. 
	 * @param ContentToDownloadFetch The list of ContentIds, contained in the given manifest, to download the JSON for.
	 */
	FBeamOperationHandle CPP_FetchIndividualContentBatchOperation(FBeamContentManifestId ManifestId, TArray<FBeamContentId> ContentToDownloadFetch, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Downloads the newest individual content objects of the given manifest.
	 * 
	 * @param ManifestId The ManifestId for the content manifest containing the given Ids. 
	 * @param ContentToDownload The list of ContentIds, contained in the given manifest, to download the JSON for.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Content", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchIndividualContentOperation(FBeamContentManifestId ManifestId, FBeamContentId ContentToDownload, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @brief Downloads the newest individual content objects of the given manifest.
	 * 
	 * @param ManifestId The ManifestId for the content manifest containing the given Ids. 
	 * @param ContentToDownload The list of ContentIds, contained in the given manifest, to download the JSON for.
	 */
	FBeamOperationHandle CPP_FetchIndividualContentOperation(FBeamContentManifestId ManifestId, FBeamContentId ContentToDownload, FBeamOperationEventHandlerCode OnOperationEvent);

	// Operation Definitions
	UFUNCTION()
	void FetchContentManifest(FBeamContentManifestId ManifestId, bool bDownloadIndividualContent, bool bIgnoreFilterMap, FBeamOperationHandle Op);

	UFUNCTION()
	void FetchIndividualContent(FBeamContentManifestId ManifestId, TArray<FBeamContentId> ContentToDownloadFetch, FBeamOperationHandle Op);

	bool EnforceLinks(FBeamContentManifestId ManifestId, TArray<FBeamRemoteContentManifestEntry> ManifestRows, TArray<FBeamContentId>& OutLinksToFetch);
};
