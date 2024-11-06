#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamSemanticType.h"

#include "BeamClientPermission.generated.h"

Expose_TNameOf(bool);

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamClientPermission : public FBeamJsonSerializableUStruct, public FBeamSemanticType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString AsString;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool AsBool = false;

	FBeamClientPermission() = default;

	FBeamClientPermission(const bool& ClientWritable) : AsBool(ClientWritable)
	{
		AsString = AsBool ? TEXT("true") : TEXT("false");
	}

	FBeamClientPermission(const FBeamClientPermission& Other) : FBeamSemanticType(Other), AsBool(Other.AsBool)
	{
		AsString = AsBool ? TEXT("true") : TEXT("false");
	}

	friend bool operator==(const FBeamClientPermission& Lhs, const FBeamClientPermission& RHS)
	{
		return Lhs.AsBool == RHS.AsBool;
	}

	friend bool operator!=(const FBeamClientPermission& Lhs, const FBeamClientPermission& RHS)
	{
		return !(Lhs == RHS);
	}

	explicit operator FString() const { return AsString; }
	explicit operator bool() const { return AsBool; }

	virtual const void* GetAddr(int Representation) const override
	{
		if (Representation == 0)
			return &AsString;

		if (Representation == 1)
			return &AsBool;

		return nullptr;
	}

	virtual void Set(const void* Data, FString RepresentationTypeName) override
	{
		if (RepresentationTypeName == TNameOf<FString>::GetName())
		{
			const auto JsonString = *((FString*)Data);
			AsBool = JsonString.Contains(TEXT("true"));
			AsString = AsBool ? TEXT("true") : TEXT("false");
		}

		if (RepresentationTypeName == TNameOf<bool>::GetName())
		{
			AsBool = *((bool*)Data);
			AsString = AsBool ? TEXT("true") : TEXT("false");
		}
	}

	virtual int GetSerializationRepresentation(FString RepresentationTypeName) const override
	{
		if (RepresentationTypeName == TNameOf<FString>::GetName()) return 0;
		if (RepresentationTypeName == TNameOf<bool>::GetName()) return 1;
		return -1;
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("write_self"), AsBool);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("write_self"), AsBool);
	}


	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		AsBool = Bag->GetBoolField(TEXT("write_self"));
		AsString = AsBool ? TEXT("true") : TEXT("false");
	}
};
