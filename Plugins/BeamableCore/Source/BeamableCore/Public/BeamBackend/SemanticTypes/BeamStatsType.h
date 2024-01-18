#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamSemanticType.h"

#include "BeamStatsType.generated.h"

UENUM(BlueprintType)
enum EBeamStatsDomain { Game, Client };

UENUM(BlueprintType)
enum EBeamStatsVisibility { Public, Private };


USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.BeamStatsTypeLibrary.MakeStatsType", HasNativeBreak="/Script/BeamableCore.BeamStatsTypeLibrary.BreakStatsType"))
struct BEAMABLECORE_API FBeamStatsType : public FBeamSemanticType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString AsString;

	FBeamStatsType() = default;

	FBeamStatsType(const FString& Pid) : AsString(Pid)
	{		
	}

	FBeamStatsType(const FBeamStatsType& Other) : FBeamSemanticType(Other), AsString(Other.AsString)
	{
	}

	explicit operator FString() const { return AsString; }

	friend bool operator==(const FBeamStatsType& Lhs, const FBeamStatsType& RHS)
	{
		return Lhs.AsString.Equals(RHS.AsString);
	}

	friend bool operator!=(const FBeamStatsType& Lhs, const FBeamStatsType& RHS)
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

FORCEINLINE uint32 GetTypeHash(const FBeamStatsType& StatsType) { return GetTypeHash(StatsType.AsString); }
