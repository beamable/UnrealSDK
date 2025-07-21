#pragma once
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "Serialization/BeamJsonUtils.h"
#include "AutoGen/ContentDefinition.h"

#include "LocalContentManifestRow.generated.h"

class UBaseContentReference;

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FLocalContentManifestRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Tags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Checksum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FBeamContentManifestId OwnerManifestId;

	/**
	 * @brief We use this to detect renames.
	 */
	FString RowName;
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FManifestChangeSet
{
	GENERATED_BODY()

	TArray<UBaseContentReference*> ToAdd;
	TArray<UBaseContentReference*> ToModify;
	TArray<UBaseContentReference*> ToDelete;
};

UCLASS()
class BEAMABLECORE_API UContentDefinitionWrapper : public UContentDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SerializedProperties;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		Serializer->WriteRawJSONValue(TEXT("properties"), SerializedProperties);
		UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
		UBeamJsonUtils::SerializeOptional<TArray<FMapOfContentMeta>, FMapOfContentMeta>(TEXT("variants"), &Variants, Serializer);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		Serializer->WriteRawJSONValue(TEXT("properties"), SerializedProperties);
		UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
		UBeamJsonUtils::SerializeOptional<TArray<FMapOfContentMeta>, FMapOfContentMeta>(TEXT("variants"), &Variants, Serializer);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
		Checksum = Bag->GetStringField(TEXT("checksum"));
		UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
		UBeamJsonUtils::DeserializeOptional<TArray<FMapOfContentMeta>, FMapOfContentMeta>("variants", Bag, Variants, OuterOwner);

		// Serialize just the properties back... TODO: Write a direct conversion to the code-gen'ed properties map
		const auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&SerializedProperties);
		const auto Props = Bag->GetObjectField(TEXT("properties"));
		FJsonSerializer::Serialize(Props.ToSharedRef(), Writer);
	}
};
