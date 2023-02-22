#pragma once

#include "CoreMinimal.h"
#include "Misc/DefaultValueHelper.h"
#include "Serialization/BeamSemanticType.h"

#include "BeamCid.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamCid : public FBeamSemanticType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString AsString;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 AsLong = -1;

	FBeamCid() = default;

	FBeamCid(const FString& Cid) : AsString(Cid)
	{
		FDefaultValueHelper::ParseInt64(Cid, AsLong);
	}

	FBeamCid(const int64& Cid) : AsLong(Cid)
	{
		AsString = FString::Printf(TEXT("%llu"), Cid);
	}

	FBeamCid(const FBeamCid& Other) : FBeamSemanticType(Other), AsString(Other.AsString), AsLong(Other.AsLong)
	{
	}

	friend bool operator==(const FBeamCid& Lhs, const FBeamCid& RHS)
	{
		return Lhs.AsString.Equals(RHS.AsString)
			&& Lhs.AsLong == RHS.AsLong;
	}

	friend bool operator!=(const FBeamCid& Lhs, const FBeamCid& RHS)
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
			const auto Cid = *((FString*)Data);
			AsString = Cid;
			FDefaultValueHelper::ParseInt64(Cid, AsLong);;
		}

		if (RepresentationTypeName == TNameOf<int64>::GetName())
		{
			const auto Cid = *((int64*)Data);
			AsString = FString::Printf(TEXT("%llu"), Cid);
			AsLong = Cid;
		}
	}

	virtual int GetSerializationRepresentation(FString RepresentationTypeName) const override
	{
		if (RepresentationTypeName == TNameOf<FString>::GetName()) return 0;
		if (RepresentationTypeName == TNameOf<int64>::GetName()) return 1;
		return -1;
	}
};
