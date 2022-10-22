#pragma once

#include "CoreMinimal.h"

#include "BeamAuthToken.generated.h"

USTRUCT(BlueprintType)
struct FBeamAuthToken
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString AccessToken;
	UPROPERTY(BlueprintReadOnly)
	FString RefreshToken;
	UPROPERTY(BlueprintReadOnly)
	int64 ExpiresIn;

	friend bool operator==(const FBeamAuthToken& Lhs, const FBeamAuthToken& RHS)
	{
		return Lhs.AccessToken == RHS.AccessToken
			&& Lhs.RefreshToken == RHS.RefreshToken
			&& Lhs.ExpiresIn == RHS.ExpiresIn;
	}

	friend bool operator!=(const FBeamAuthToken& Lhs, const FBeamAuthToken& RHS)
	{
		return !(Lhs == RHS);
	}
};
