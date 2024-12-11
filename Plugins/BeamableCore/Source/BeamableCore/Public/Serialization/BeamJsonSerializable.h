#pragma once

#include "Serialization/JsonWriter.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Policies/PrettyJsonPrintPolicy.h"

#include "BeamJsonSerializable.generated.h"

/**
 * @brief Shorter name for the default Unreal Json Writer.
 */
typedef TSharedRef<TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>> TUnrealJsonSerializer;

/**
 * @brief Shorter name for the pretty Unreal Json Writer.
 */
typedef TSharedRef<TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>> TUnrealPrettyJsonSerializer;


/**
 * Implement this as the parent of any UStruct that you wish to serialize in BeamContentObjects.
 * For beamable developers, you should also implement this on any UStructs that are being used as replacement types in code-gen (ie: FBeamFederation and FBeamClientPermission).
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamJsonSerializableUStruct
{
	GENERATED_BODY()
	
	UPROPERTY(Transient, meta=(EditCondition = "false", EditConditionHides))
	TWeakObjectPtr<UObject> OuterOwner = nullptr;

	virtual ~FBeamJsonSerializableUStruct();

	virtual void BeamSerialize(TUnrealJsonSerializer& Serializer) const;

	virtual void BeamSerialize(TUnrealPrettyJsonSerializer& Serializer) const;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const;

	virtual void BeamDeserialize(const FString& JsonString);

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag);
};

/**
 * Implement this as the parent of any UObject that you wish to serialize in BeamContentObjects.
 * For beamable developers, you should also implement this on any UStructs that are being used as replacement types in code-gen (ie: FBeamFederation and FBeamClientPermission).
 */
UINTERFACE()
class BEAMABLECORE_API UBeamJsonSerializableUObject : public UInterface
{
	GENERATED_BODY()
};

class BEAMABLECORE_API IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<UObject> OuterOwner = nullptr;

	void BeamSerializePretty(FString& Result) const;
	void BeamSerializeCondensed(FString& Result) const;
	
	virtual void BeamSerialize(TUnrealJsonSerializer& Serializer) const;

	virtual void BeamSerialize(TUnrealPrettyJsonSerializer& Serializer) const;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const;

	virtual void BeamDeserialize(const FString& JsonString);

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag);
};
