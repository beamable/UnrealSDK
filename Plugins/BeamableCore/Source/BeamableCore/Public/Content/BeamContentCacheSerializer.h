#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "BeamContentCacheSerializer.generated.h"

class BEAMABLECORE_API FBeamMemoryWriter : public FMemoryWriter
{
public:
	FBeamMemoryWriter(TArray<uint8, TSizedDefaultAllocator<32>>& InBytes, bool bIsPersistent = false, bool bSetOffset = false, const FName InArchiveName = NAME_None)
		: FMemoryWriter(InBytes, bIsPersistent, bSetOffset, InArchiveName)
	{
	}

private:
	virtual FArchive& operator<<(struct FSoftObjectPtr& Value) override;

	/**
	 * The for UObject* serialization we implement this custom way to handle it.
	 * 
	 * The case is for using UObject* in contents, the serialization wouldn't work correctly if this content contains a reference for a UObject*.
	 * In order to fix it, we save the path for the class that will be serialized and recreate the object in the deserialization.
	 * 
	 * IMPORTANT: It works for most of the cases, but you want to do you won serialization you just need to override the Serialize(FArchive* Ar) in the UObject target.
	 */
	virtual FArchive& operator<<(class UObject*& Res) override;
};

class BEAMABLECORE_API FBeamMemoryReader : public FMemoryReader
{
public:
	FBeamMemoryReader(const TArray<uint8>& InBytes, bool bIsPersistent = false)
		: FMemoryReader(InBytes, bIsPersistent)
	{
	}

private:
	virtual FArchive& operator<<(struct FSoftObjectPtr& Value) override;

	/**
	 * The for UObject* serialization we implement this custom way to handle it.
	 * 
	 * The case is for using UObject* in contents, the serialization wouldn't work correctly if this content contains a reference for a UObject*.
	 * In order to fix it, we save the path for the class that will be serialized and recreate the object in the deserialization.
	 * 
	 * IMPORTANT: It works for most of the cases, but you want to do you won serialization you just need to override the Serialize(FArchive* Ar) in the UObject target.
	 */
	virtual FArchive& operator<<(class UObject*& Res) override;
};

struct BEAMABLECORE_API FBeamContentCacheSerializationContext
{
	FBeamContentCacheSerializationContext(UGameInstance* Instance, bool bIsSaving, FArchive& Ar, const TMap<FString, UClass*>& TypeToContentClass, const TMap<UClass*, FString>& ContentClassToType);

	TWeakObjectPtr<UGameInstance> GameInstance;
	bool bIsSaving;
	FArchive& TargetAr;
	const TMap<FString, UClass*>& TypeToContentClass;
	const TMap<UClass*, FString>& ContentClassToType;

	bool IsBakeTime() const;
};

/**
 * Configure a subclass of this type in @link UBeamCoreSettings::DefaultSerializer @endlink . This type will be instantiated in order to serialize content to its binary format.
 *
 * There are two moments this happens:
 *  - At runtime, whenever we need to load or update the local content cache (we keep this cache to improve loading times on games with a lot of content).
 *  - At editor time, whenever we run the Baking Content utility (games with a lot of content object might want to ship builds with baked content to reduce the initial content download time).
 *
 *  When writing @link SerializeBeamContentCacheHeader @endlink , be careful when reading things from the @link FBeamContentCacheSerializationContext::GameInstance @endlink since that is ONLY valid at runtime.
 *  So... when baking content, your logic will need to account for that.
 */
UCLASS(NotBlueprintable, NotBlueprintType)
class BEAMABLECORE_API UBeamContentCacheSerializer : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * We take ownership of the returned FArchive* memory. DO NOT CACHE IT. It'll be very short-lived.
	 *
	 * This defaults to @link FBeamMemoryWriter @endlink and @link FBeamMemoryReader @endlink depending on @param bIsSaving . 
	 */
	virtual FArchive* GetDefaultContentCacheSerializer(TArray<uint8>& Data, bool bIsSaving);

	/**
	 * Return true when the cache is valid; false, if we are supposed to invalidate the cache.
	 * 
	 * This defaults to your project's version and the Beamable SDK version --- if either of those are updated in relation to the cache, we'll invalidate the cache.
	 */
	virtual bool SerializeBeamContentCacheHeader(FBeamContentCacheSerializationContext& Ctx);
};
