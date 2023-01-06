#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamSemanticType.h"

#include "BeamPid.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamPid : public FBeamSemanticType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString AsString;

	FBeamPid() = default;

	FBeamPid(const FString& Pid) : AsString(Pid)
	{				
	}

	FBeamPid(const FBeamPid& Other) : FBeamSemanticType(Other), AsString(Other.AsString)
	{
	}

	explicit operator FString() const { return AsString; }

	friend bool operator==(const FBeamPid& Lhs, const FBeamPid& RHS)
	{
		return Lhs.AsString.Equals(RHS.AsString);
	}

	friend bool operator!=(const FBeamPid& Lhs, const FBeamPid& RHS)
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
