#include "Content/BeamContentCache.h"


bool UBeamContentCache::SerializeToBinary(FBeamContentCacheSerializationContext& Ctx, UBeamContentCacheSerializer* HeaderSerializer)
{
	if (Ctx.TargetAr.IsSaving())
	{	
		// First thing is we write the serializer so that we can invalidate caches that were written with different serializers.
		auto SerializerName = HeaderSerializer->GetClass()->GetName();
		Ctx.TargetAr << SerializerName;

		// Hey --- if you change serialization before this point, please also change the location that we look for the cache in.
		// This essentially forces a cache invalidation and avoids us having to deal with complex cases of backward compatibility in the binary layout of the cache between versions.
		// This is ok since this cache being invalidated every between updates is expected. This is just a simple way of doing it that prevents us
		// from having to figure out complicated but ultimately unnecessary things.
		auto _ = HeaderSerializer->SerializeBeamContentCacheHeader(Ctx);
		Ctx.TargetAr << ManifestId.AsString;

		int32 CashSize = Cache.Num();

		Ctx.TargetAr << CashSize; // Serialize the number of items in the Cache map
		for (const TPair<FBeamContentId, UBeamContentObject*>& ItemPairCache : Cache)
		{
			FString ContentId = ItemPairCache.Key.AsString;
			UBeamContentObject* ContentObject = ItemPairCache.Value;

			//Save the content id so that we read it while loading to construct the object again
			Ctx.TargetAr << ContentId;


			FString ContentTypeString = Ctx.ContentClassToType.Contains(ContentObject->GetClass())
				                            ? Ctx.ContentClassToType[ContentObject->GetClass()]
				                            : TEXT("BEAM_NON_EXISTING_CONTENT_TYPE");
			Ctx.TargetAr << ContentTypeString;

			if (ContentObject)
			{
				ContentObject->GetClass()->SerializeTaggedProperties(Ctx.TargetAr, (uint8*)ContentObject, nullptr, nullptr);
			}
		}

		// Serialize the number of  hash items
		int32 HashSize = Hashes.Num();
		Ctx.TargetAr << HashSize;
		for (const TPair<FBeamContentId, FString>& ItemPairCache : Hashes)
		{
			FString ContentId = ItemPairCache.Key.AsString;
			FString ContentHash = ItemPairCache.Value;
			//Serializing the data for the pair objects in the hash map
			Ctx.TargetAr << ContentId;
			Ctx.TargetAr << ContentHash;
		}

		// Serialize the number of  items inside LatestRemoteManifest
		int32 LatestManifestSize = LatestRemoteManifest.Num();
		Ctx.TargetAr << LatestManifestSize;
		for (const FBeamRemoteContentManifestEntry& Entry : LatestRemoteManifest)
		{
			FString Uri = Entry.Uri;
			FString Version = Entry.Version;

			//Serializing the data inside the manifest entries
			Ctx.TargetAr << Uri;
			Ctx.TargetAr << Version;
		}
	}
	else
	{
		FString OriginalSerializer;
		FString CurrentSerializer = HeaderSerializer->GetClass()->GetName();
		Ctx.TargetAr << OriginalSerializer;

		if (!CurrentSerializer.Equals(OriginalSerializer))
		{
			UE_LOG(LogTemp, Warning, TEXT("This cache was created with a different serializer. It cannot be used with this version. So, we are invalidating it. CACHE_SERIALIZER=%s, CURR_SERIALIZER=%s"),
			       *OriginalSerializer, *CurrentSerializer);
			return false;
		}

		const auto bShouldInvalidate = !HeaderSerializer->SerializeBeamContentCacheHeader(Ctx);
		if (bShouldInvalidate)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalidating Cache due to incompatible header."));
			return false;
		}

		Ctx.TargetAr << ManifestId.AsString;

		//Read the number of contents in the serialized file.
		int32 CacheSize;
		Ctx.TargetAr << CacheSize;

		TArray<FString> IdsStrings;
		IdsStrings.Reserve(CacheSize);
		bool bFoundAtLeastOneCorruptContent = false;
		for (int32 i = 0; i < CacheSize; i++)
		{
			FString ContentId;
			Ctx.TargetAr << ContentId;

			//Read the content type string
			FString ContentClassTypeString;
			Ctx.TargetAr << ContentClassTypeString;

			// If we tried to serialize an object for which we didn't have a matching UBeamContentObject implementation at the time of serialization
			bFoundAtLeastOneCorruptContent |= ContentClassTypeString == TEXT("BEAM_NON_EXISTING_CONTENT_TYPE");

			// Construct the object using the ContentTypeID
			UBeamContentObject* ContentObject;
			UBeamContentObject::NewFromTypeId(Ctx.TypeToContentClass, ContentClassTypeString, ContentObject);
			if (ContentObject)
			{
				ContentObject->GetClass()->SerializeTaggedProperties(Ctx.TargetAr, (uint8*)ContentObject, nullptr, nullptr);

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
		Ctx.TargetAr << HashSize;
		for (int32 i = 0; i < HashSize; i++)
		{
			FString ContentId;
			FString ContentHash;

			Ctx.TargetAr << ContentId;
			Ctx.TargetAr << ContentHash;

			Hashes.Add(ContentId, ContentHash);
		}

		// Read the number of manifests
		int32 LatestManifestSize;
		Ctx.TargetAr << LatestManifestSize;

		for (int32 i = 0; i < LatestManifestSize; i++)
		{
			FString Uri;
			FString Version;
			Ctx.TargetAr << Uri;
			Ctx.TargetAr << Version;

			FBeamRemoteContentManifestEntry LatestManifestEntry;
			LatestManifestEntry.Uri = Uri;
			LatestManifestEntry.Version = Version;

			LatestRemoteManifest.Add(LatestManifestEntry);
		}
	}

	return true;
}
