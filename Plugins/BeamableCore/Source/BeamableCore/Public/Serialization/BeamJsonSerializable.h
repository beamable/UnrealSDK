#pragma once

#include "BeamJsonSerializable.generated.h"

/**
 * @brief Shorter name for the default Unreal Json Writer.
 */
typedef TSharedRef<TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>> TUnrealJsonSerializer;

/**
 * @brief Shorter name for the pretty Unreal Json Writer.
 */
typedef TSharedRef<TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>> TUnrealPrettyJsonSerializer;


USTRUCT(BlueprintType)
struct FBeamJsonSerializable
{
	GENERATED_BODY()

	/**
	 * @brief Owner UObject that will be used for all NewObject calls within this deserialization chain.
	 * Typically will be the Request UObject so that the entire stack of UObjects created during deserialization gets released.
	 * We need this because Blueprints don't support TArray<FCustom> declarations as properties of FCustom itself.
	 * But it does support TArray<UCustom*> declarations.
	 * So, we don't use UStructs for our Serializable Types that are code-gen'ed.
	 * The tradeoff here being, we allocate memory on deserialization, but we get this layer entirely exposed to blueprints by default which is really good for prototyping.
	 * In the unlikely case we bump into performance problems in certain deserialization cases, we can opt-out of generating that type's CPP file and manually write an optimized version.
	 */
	UPROPERTY()
	UObject* OuterOwner;
	
	virtual ~FBeamJsonSerializable();

	virtual void BeamSerialize(TUnrealJsonSerializer& Serializer) const;

	virtual void BeamSerialize(TUnrealPrettyJsonSerializer& Serializer) const;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const;

	virtual void BeamDeserialize(const FString& JsonString);

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag);
};
