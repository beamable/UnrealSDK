#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Enums/BeamContentType.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Dom/JsonObject.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamTag.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamTag : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FOptionalString Name = FOptionalString();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category="Beam")
	FOptionalString Value = FOptionalString();

	FBeamTag() = default;

	FBeamTag(FString Name, FString Val) : Name(FOptionalString(Name)), Value(FOptionalString(Val))
	{
	}

	friend bool operator==(const FBeamTag& Lhs, const FBeamTag& RHS)
	{
		return Lhs.Name.Val.Equals(RHS.Name.Val) && Lhs.Value.Val.Equals(RHS.Value.Val);
	}

	friend bool operator!=(const FBeamTag& Lhs, const FBeamTag& RHS)
	{
		return !(Lhs == RHS);
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeOptional<FString>("name", &Name, Serializer);
		UBeamJsonUtils::SerializeOptional<FString>("value", &Value, Serializer);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeOptional<FString>("name", &Name, Serializer);
		UBeamJsonUtils::SerializeOptional<FString>("value", &Value, Serializer);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
		UBeamJsonUtils::DeserializeOptional<FString>("value", Bag, Value, OuterOwner);
	}
};
