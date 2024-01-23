#pragma once

#include "CoreMinimal.h"
#include "Misc/DefaultValueHelper.h"
#include "Serialization/BeamSemanticType.h"

#include "BeamGamerTag.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamGamerTag : public FBeamSemanticType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString AsString;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 AsLong = -1;

	FBeamGamerTag() = default;

	FBeamGamerTag(const FString& GamerTag) : AsString(GamerTag)
	{		
		FDefaultValueHelper::ParseInt64(GamerTag, AsLong);
	}

	FBeamGamerTag(const int64& GamerTag) : AsLong(GamerTag)
	{		
		AsString = FString::Printf(TEXT("%llu"), GamerTag);
	}

	FBeamGamerTag(const FBeamGamerTag& Other) : FBeamSemanticType(Other), AsString(Other.AsString), AsLong(Other.AsLong)
	{
	}

	friend bool operator==(const FBeamGamerTag& Lhs, const FBeamGamerTag& RHS)
	{
		return Lhs.AsString.Equals(RHS.AsString) && Lhs.AsLong == RHS.AsLong;
	}

	friend bool operator!=(const FBeamGamerTag& Lhs, const FBeamGamerTag& RHS)
	{
		return !(Lhs == RHS);
	}

	explicit operator FString() const { return AsString; }
	explicit operator int64() const { return AsLong; }

	virtual const void* GetAddr(int Representation) const override
	{
		if (Representation == 0)
			return &AsString;

		if (Representation == 1)
			return &AsLong;

		return nullptr;
	}

	virtual void Set(const void* Data, FString RepresentationTypeName) override
	{
		if (RepresentationTypeName == TNameOf<FString>::GetName())
		{
			const auto GamerTag = *((FString*)Data);
			AsString = GamerTag;
			FDefaultValueHelper::ParseInt64(GamerTag, AsLong);;			
		}

		if (RepresentationTypeName == TNameOf<int64>::GetName())
		{
			const auto GamerTag = *((int64*)Data);
			AsString = FString::Printf(TEXT("%llu"), GamerTag);
			AsLong = GamerTag;
		}
	}

	virtual int GetSerializationRepresentation(FString RepresentationTypeName) const override
	{
		if (RepresentationTypeName == TNameOf<FString>::GetName()) return 0;
		if (RepresentationTypeName == TNameOf<int64>::GetName()) return 1;
		return -1;
	}
};

FORCEINLINE uint32 GetTypeHash(const FBeamGamerTag& GamerTag) { return GetTypeHash(GamerTag.AsString); }

