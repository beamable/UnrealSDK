#pragma once

#include "BeamContentObject.h"
#include "BeamBackend/ReplacementTypes/BeamRemoteContentManifestEntry.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "Engine/DataTable.h"

#include "BeamContentCache.generated.h"


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

	void SerializeToBinary(FArchive& Ar,const TMap<FString, UClass*>& ContentTypeStringToContentClass,const TMap<UClass*, FString>& ContentClassToContentTypeString)
	{
		if (Ar.IsSaving())
		{
			Ar << ManifestId.AsString;

			int32 CashSize = Cache.Num();
		
			Ar << CashSize; // Serialize the number of items in the Cache map
			for (const TPair<FBeamContentId, UBeamContentObject*>& ItemPairCache : Cache)
			{
				FString ContentId = ItemPairCache.Key.AsString;
				UBeamContentObject* ContentObject = ItemPairCache.Value; 

				Ar << ContentId;

				FString ContentTypeString  = ContentClassToContentTypeString[ContentObject->GetClass()];
				Ar << ContentTypeString;
				
				if (ContentObject)
				{
					ContentObject->GetClass()->SerializeTaggedProperties(Ar,(uint8*) ContentObject,ContentObject->GetClass(),nullptr);
					
					ContentObject->SerializeUObjects(Ar);
				}
			}

			
			int32 HashSize = Hashes.Num();
			Ar << HashSize; 
			for (const TPair<FBeamContentId, FString>& ItemPairCache : Hashes)
			{
				FString ContentId = ItemPairCache.Key.AsString; 
				FString ContentHash = ItemPairCache.Value; 

				Ar << ContentId;
				Ar << ContentHash;
			}
			int32 LatestManifestSize = LatestRemoteManifest.Num();
			
			Ar << LatestManifestSize; 
			for (const FBeamRemoteContentManifestEntry& Entry : LatestRemoteManifest)
			{
				FString Uri = Entry.Uri;
				FString Version = Entry.Version;
				
				Ar<<Uri;
				Ar<<Version;
			}
		}
		else
		{
			
			Ar << ManifestId.AsString;

			int32 CashSize;
			Ar << CashSize; 
			for (int32 i = 0; i < CashSize; i++)
			{
				FString ContentId;
				Ar<<ContentId;

				FString ContentClassTypeString;
				Ar<<ContentClassTypeString;
				
				UBeamContentObject* ContentObject ;
				UBeamContentObject::NewFromTypeId(ContentTypeStringToContentClass, ContentClassTypeString, ContentObject);
				
				if (ContentObject)
				{
					ContentObject->GetClass()->SerializeTaggedProperties(Ar,(uint8*) ContentObject,ContentObject->GetClass(),nullptr);

					ContentObject->SerializeUObjects(Ar);

					Cache.Add(ContentId,ContentObject);
				}
				
			}

			int32 HashSize;
			Ar << HashSize; 
			for (int32 i = 0; i < HashSize; i++)
			{
				FString ContentId ;
				FString ContentHash ;

				Ar << ContentId;
				Ar << ContentHash;

				Hashes.Add(ContentId,ContentHash);
			}
			
			int32 LatestManifestSize ;
			Ar << LatestManifestSize;
			
			for (int32 i = 0; i < LatestManifestSize; i++)
			{
				FString Uri ;
				FString Version ;
				Ar<<Uri;
				Ar<<Version;

				FBeamRemoteContentManifestEntry LatestManifestEntry;
				LatestManifestEntry.Uri = Uri;
				LatestManifestEntry.Version = Version;

				LatestRemoteManifest.Add(LatestManifestEntry);
			}
			
		}
	}
};