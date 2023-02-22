#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamSemanticType.h"

#include "BeamContentId.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamContentId : public FBeamSemanticType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString AsString;

	FBeamContentId() = default;

	FBeamContentId(const FName& ContentId) : AsString(ContentId.ToString())
	{
	}
	
	FBeamContentId(const FString& ContentId) : AsString(ContentId)
	{
	}

	FBeamContentId(const FBeamContentId& Other) : FBeamSemanticType(Other), AsString(Other.AsString)
	{
	}

	explicit operator FString() const { return AsString; }

	friend bool operator==(const FBeamContentId& Lhs, const FBeamContentId& RHS)
	{
		return Lhs.AsString.Equals(RHS.AsString);
	}

	friend bool operator!=(const FBeamContentId& Lhs, const FBeamContentId& RHS)
	{
		return !(Lhs == RHS);
	}

	virtual const void* GetAddr(int Representation) const override
	{
		if (Representation == 0)
			return &AsString;

		return nullptr;
	}

	virtual void Set(const void* Data, FString RepresentationTypeName) override
	{
		if (RepresentationTypeName == TNameOf<FString>::GetName())
		{
			const auto ContentId = *((FString*)Data);
			AsString = ContentId;
		}
	}
};

FORCEINLINE uint32 GetTypeHash(const FBeamContentId& ContentId) { return GetTypeHash(ContentId.AsString); }
