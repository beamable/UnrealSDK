#pragma once

#include "CoreMinimal.h"

#include "BeamAuthToken.generated.h"

USTRUCT(BlueprintType)
struct FBeamAuthToken
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,Category="Beam")
	FString AccessToken;
	UPROPERTY(BlueprintReadOnly,Category="Beam")
	FString RefreshToken;
	UPROPERTY(BlueprintReadOnly,Category="Beam")
	int64 ExpiresIn = -1;
	UPROPERTY(BlueprintReadOnly,Category="Beam")
	int64 IssuedAt = -1;

	friend bool operator==(const FBeamAuthToken& Lhs, const FBeamAuthToken& RHS)
	{
		return Lhs.AccessToken == RHS.AccessToken
			&& Lhs.RefreshToken == RHS.RefreshToken
			&& Lhs.ExpiresIn == RHS.ExpiresIn
			&& Lhs.IssuedAt == RHS.IssuedAt;
	}

	friend bool operator!=(const FBeamAuthToken& Lhs, const FBeamAuthToken& RHS)
	{
		return !(Lhs == RHS);
	}
};
