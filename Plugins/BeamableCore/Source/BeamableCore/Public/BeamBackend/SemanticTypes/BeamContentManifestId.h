#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamSemanticType.h"

#include "BeamContentManifestId.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamContentManifestId : public FBeamSemanticType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString AsString;

	FBeamContentManifestId() = default;

	FBeamContentManifestId(const FString& ManifestName) : AsString(ManifestName)
	{
	}

	FBeamContentManifestId(const FBeamContentManifestId& Other) : FBeamSemanticType(Other), AsString(Other.AsString)
	{
	}

	explicit operator FString() const { return AsString; }

	friend bool operator==(const FBeamContentManifestId& Lhs, const FBeamContentManifestId& RHS)
	{
		return Lhs.AsString.Equals(RHS.AsString);
	}

	friend bool operator!=(const FBeamContentManifestId& Lhs, const FBeamContentManifestId& RHS)
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
			const auto Pid = *((FString*)Data);
			AsString = Pid;
		}
	}
};

FORCEINLINE uint32 GetTypeHash(const FBeamContentManifestId& ContentManifestId) { return GetTypeHash(ContentManifestId.AsString); }

