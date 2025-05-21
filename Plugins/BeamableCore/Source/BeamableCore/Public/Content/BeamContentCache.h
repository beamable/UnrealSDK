#pragma once

#include "BeamContentObject.h"
#include "BeamCoreSettings.h"
#include "BeamBackend/ReplacementTypes/BeamRemoteContentManifestEntry.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "Engine/DataTable.h"

#include "BeamContentCache.generated.h"

// TODO: Document and Add a way for people to give me the archive they want to use (Wrap calls with an GetArchiveForContentCache delegate which defaults to these)
// TODO: Add a serialized SDK version to the start of the file --- if SDK versions change we should return false when reading a content cache and discard the cache. 
class BEAMABLECORE_API FBeamMemoryWriter : public FMemoryWriter
{
public:
	FBeamMemoryWriter(TArray<uint8, TSizedDefaultAllocator<32>>& InBytes, bool bIsPersistent = false, bool bSetOffset = false, const FName InArchiveName = NAME_None)
		: FMemoryWriter(InBytes, bIsPersistent, bSetOffset, InArchiveName)
	{
	}

private:
	virtual FArchive& operator<<(struct FSoftObjectPtr& Value)
	{
		// Serialize the FName as a string
		if (IsLoading())
		{
			FString Path;
			*this << Path;
			Value = FSoftObjectPath{Path};
		}
		else
		{
			FString Path = Value.ToSoftObjectPath().GetAssetPathString();
			*this << Path;
		}
		return *this;
	}


	virtual FArchive& operator<<(class UObject*& Res) override
	{
		bool IsNull = Res == nullptr;

		*this << IsNull;

		if (!IsNull)
		{
			FSoftClassPath PathSoftObject = Res->GetClass();
			FString Path = PathSoftObject.GetAssetPathString();
			*this << Path;
			Res->Serialize(*this);
		}
		return *this;
	}
};

class BEAMABLECORE_API FBeamMemoryReader : public FMemoryReader
{
public:
	FBeamMemoryReader(const TArray<uint8>& InBytes, bool bIsPersistent = false)
		: FMemoryReader(InBytes, bIsPersistent)
	{
	}

private:
	virtual FArchive& operator<<(struct FSoftObjectPtr& Value)
	{
		// Serialize the FName as a string
		if (IsLoading())
		{
			FString Path;
			*this << Path;
			Value = FSoftObjectPath{Path};
		}
		else
		{
			FString Path = Value.ToSoftObjectPath().GetAssetPathString();
			*this << Path;
		}
		return *this;
	}

	/**
	 * The for UObject* serialization we implement this custom way to handle it.
	 * 
	 * The case is for using UObject* in contents, the serialization wouldn't work correctly if this content contains a reference for a UObject*.
	 * In order to fix it, we save the path for the class that will be serialized and recreate the object in the deserialization.
	 * 
	 * IMPORTANT: It works for most of the cases, but you want to do you won serialization you just need to override the Serialize(FArchive* Ar) in the UObject target.
	 */
	virtual FArchive& operator<<(class UObject*& Res) override
	{
		bool IsNull = false;

		// Reading if the Res in the serialization was Null 
		*this << IsNull;

		if (!IsNull)
		{
			FString Path = "";
			// Getting the class path to load the target class. 
			*this << Path;
			if (this->IsLoading())
			{
				// Recreate the target UObject and calling the serialize method.
				FSoftClassPath PathSoftObject{Path};
				UClass* Class = PathSoftObject.ResolveClass();

				Res = NewObject<UObject>(GetTransientPackage(), Class);

				if (!ensureAlwaysMsgf(
					Res, TEXT("The deserialization of a un-existent class should be impossible, this means the cache wasn't invalidated. Take a look if you bumped your project version or the SDK version correctly.")))
				{
					return *this;
				}
			}
			Res->Serialize(*this);
		}
		return *this;
	}
};


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamContentCache : public UObject
{
	GENERATED_BODY()

	friend class UBeamContentSubsystem;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FBeamContentManifestId ManifestId;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FBeamContentId, UBeamContentObject*> Cache;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FBeamContentId, FString> Hashes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FBeamRemoteContentManifestEntry> LatestRemoteManifest;

	bool SerializeToBinary(FArchive& Ar, const TMap<FString, UClass*>& ContentTypeStringToContentClass, const TMap<UClass*, FString>& ContentClassToContentTypeString)
	{
		if (Ar.IsSaving())
		{
			FString AppVersion = GetProjectAppVersion();

			Ar << AppVersion;
			Ar << GetDefault<UBeamCoreSettings>()->BeamableEnvironment->Version;
			Ar << ManifestId.AsString;

			int32 CashSize = Cache.Num();

			Ar << CashSize; // Serialize the number of items in the Cache map
			for (const TPair<FBeamContentId, UBeamContentObject*>& ItemPairCache : Cache)
			{
				FString ContentId = ItemPairCache.Key.AsString;
				UBeamContentObject* ContentObject = ItemPairCache.Value;

				//Save the content id so that we read it while loading to construct the object again
				Ar << ContentId;


				FString ContentTypeString = ContentClassToContentTypeString.Contains(ContentObject->GetClass())
					                            ? ContentClassToContentTypeString[ContentObject->GetClass()]
					                            : TEXT("BEAM_NON_EXISTING_CONTENT_TYPE");
				Ar << ContentTypeString;

				if (ContentObject)
				{
					ContentObject->GetClass()->SerializeTaggedProperties(Ar, (uint8*)ContentObject, nullptr, nullptr);
				}
			}

			// Serialize the number of  hash items
			int32 HashSize = Hashes.Num();
			Ar << HashSize;
			for (const TPair<FBeamContentId, FString>& ItemPairCache : Hashes)
			{
				FString ContentId = ItemPairCache.Key.AsString;
				FString ContentHash = ItemPairCache.Value;
				//Serializing the data for the pair objects in the hash map
				Ar << ContentId;
				Ar << ContentHash;
			}

			// Serialize the number of  items inside LatestRemoteManifest
			int32 LatestManifestSize = LatestRemoteManifest.Num();
			Ar << LatestManifestSize;
			for (const FBeamRemoteContentManifestEntry& Entry : LatestRemoteManifest)
			{
				FString Uri = Entry.Uri;
				FString Version = Entry.Version;

				//Serializing the data inside the manifest entries
				Ar << Uri;
				Ar << Version;
			}
		}
		else
		{
			FBeamPackageVersion SdkVersion;
			FBeamPackageVersion CurrSdkVersion = GetDefault<UBeamCoreSettings>()->BeamableEnvironment->Version;
			Ar << SdkVersion;
			if (!CurrSdkVersion.Equals(SdkVersion))
			{
				UE_LOG(LogTemp, Warning, TEXT("This cache was created with a different SDK version. It cannot be used with this version. So, we are invalidating it. CACHE_VERSION=%s, CURR_VERSION=%s"),
				       *SdkVersion.ToString(), *CurrSdkVersion.ToString());
				return false;
			}

			FString ProjectAppVersion;
			FString CurrentProjectAppVersion = GetProjectAppVersion();
			Ar << ProjectAppVersion;

			if (!CurrentProjectAppVersion.Equals(ProjectAppVersion))
			{
				UE_LOG(LogTemp, Warning, TEXT("This cache was created with a different project app version. It cannot be used with this version. So, we are invalidating it. CACHE_VERSION=%s, CURR_VERSION=%s"),
				       *ProjectAppVersion, *CurrentProjectAppVersion);
				return false;
			}

			Ar << ManifestId.AsString;

			//Read the number of contents in the serialized file.
			int32 CacheSize;
			Ar << CacheSize;

			TArray<FString> IdsStrings;
			IdsStrings.Reserve(CacheSize);
			bool bFoundAtLeastOneCorruptContent = false;
			for (int32 i = 0; i < CacheSize; i++)
			{
				FString ContentId;
				Ar << ContentId;

				//Read the content type string
				FString ContentClassTypeString;
				Ar << ContentClassTypeString;

				// If we tried to serialize an object for which we didn't have a matching UBeamContentObject implementation at the time of serialization
				bFoundAtLeastOneCorruptContent |= ContentClassTypeString == TEXT("BEAM_NON_EXISTING_CONTENT_TYPE");

				// Construct the object using the ContentTypeID
				UBeamContentObject* ContentObject;
				UBeamContentObject::NewFromTypeId(ContentTypeStringToContentClass, ContentClassTypeString, ContentObject);
				if (ContentObject)
				{
					ContentObject->GetClass()->SerializeTaggedProperties(Ar, (uint8*)ContentObject, nullptr, nullptr);

					IdsStrings.Add(ContentId);
					Cache.Add(ContentId, ContentObject);
				}
			}

			if (bFoundAtLeastOneCorruptContent)
			{
				TArray<FBeamContentId> Contents;
				Cache.GetKeys(Contents);

				UE_LOG(LogTemp, Warning, TEXT("At least one object in the cache was corrupted."
					       "The list below contains all content ids that were successfully deserialized."
					       "\nIf you see a missing content, that was the one that was corrupted. \n%s"),
				       *FString::Join(IdsStrings, TEXT("\n")));
			}

			// Read the number of  hash items
			int32 HashSize;
			Ar << HashSize;
			for (int32 i = 0; i < HashSize; i++)
			{
				FString ContentId;
				FString ContentHash;

				Ar << ContentId;
				Ar << ContentHash;

				Hashes.Add(ContentId, ContentHash);
			}

			// Read the number of manifests
			int32 LatestManifestSize;
			Ar << LatestManifestSize;

			for (int32 i = 0; i < LatestManifestSize; i++)
			{
				FString Uri;
				FString Version;
				Ar << Uri;
				Ar << Version;

				FBeamRemoteContentManifestEntry LatestManifestEntry;
				LatestManifestEntry.Uri = Uri;
				LatestManifestEntry.Version = Version;

				LatestRemoteManifest.Add(LatestManifestEntry);
			}
		}

		return true;
	}

	FString GetProjectAppVersion() const
	{
		FString AppVersion;
		GConfig->GetString(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("ProjectVersion"),
			AppVersion,
			GGameIni
		);

		return AppVersion;
	};
};
