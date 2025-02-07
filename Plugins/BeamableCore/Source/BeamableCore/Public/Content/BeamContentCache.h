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

	bool SerializeToBinary(FArchive& Ar,const TMap<FString, UClass*>& ContentTypeStringToContentClass,const TMap<UClass*, FString>& ContentClassToContentTypeString)
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

				//Save the content id so that we read it while loading to construct the object again
				Ar << ContentId;

				FString ContentTypeString  = ContentClassToContentTypeString[ContentObject->GetClass()];
				Ar << ContentTypeString;
				
				if (ContentObject)
				{
					
					ContentObject->GetClass()->SerializeTaggedProperties(Ar,(uint8*) ContentObject,ContentObject->GetClass(),nullptr);

					int64 PositionBeforeUObjectData = Ar.Tell();

					//Write an empty int to overwrite it again later with the final position after writing the uobject
					int64 UObjectsDataSize = 0;
					Ar << UObjectsDataSize;
					//SerializeTaggedProperties will not serialize UObjects so a custom function for serializing UObjects needs to be called.
					ContentObject->SerializeUObjects(Ar);

					int64 FinalPosition = Ar.Tell();

					//Seek to the placae before the uobject serialization began
					Ar.Seek(PositionBeforeUObjectData);

					//Overwrite the integar we wrote before with the final position after writing the uobject
					Ar<<FinalPosition;
					
					Ar.Seek(FinalPosition);
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
				Ar<<Uri;
				Ar<<Version;
			}
		}
		else
		{
			
			Ar << ManifestId.AsString;

			//Read the number of contents in the serialized file.
			int32 CashSize;
			Ar << CashSize; 
			for (int32 i = 0; i < CashSize; i++)
			{
				FString ContentId;
				Ar<<ContentId;

				//Read the content type string
				FString ContentClassTypeString;
				Ar<<ContentClassTypeString;

				//Construct the object using the ContentTypeID
				UBeamContentObject* ContentObject ;
				UBeamContentObject::NewFromTypeId(ContentTypeStringToContentClass, ContentClassTypeString, ContentObject);
				
				if (ContentObject)
				{
					ContentObject->GetClass()->SerializeTaggedProperties(Ar,(uint8*) ContentObject,ContentObject->GetClass(),nullptr);


					int64 FinalPositionAfterReadingUObjectData;
					//Get the position in which the uobject reading should be finished at
					Ar<<FinalPositionAfterReadingUObjectData;
					
					//SerializeTaggedProperties will not serialize UObjects so a custom function for serializing UObjects needs to be called.
					ContentObject->SerializeUObjects(Ar);

					int64 CurrenArchivePos = Ar.Tell();
					
					if (CurrenArchivePos > FinalPositionAfterReadingUObjectData)
					{
						UE_LOG(LogTemp, Error, TEXT("While serializing a uboject more data was read than possible, ignoring the rest of serialization"));
						return false;
					}
					else if (CurrenArchivePos < FinalPositionAfterReadingUObjectData)
					{
						Ar.Seek(FinalPositionAfterReadingUObjectData);
						UE_LOG(LogTemp, Warning, TEXT("While serializing a Uboject less data was read than it should"));
					}	

					
					Cache.Add(ContentId,ContentObject);
				}
				
			}
			// Read the number of  hash items
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

			// Read the number of manifests
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

		return true;
	}
};