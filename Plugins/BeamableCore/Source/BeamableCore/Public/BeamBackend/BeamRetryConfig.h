#pragma once

#include "CoreMinimal.h"

#include "BeamRetryConfig.generated.h"

/**
 * @brief Holds data defining how a request needs to be sent out. 
 */
USTRUCT(BlueprintType)
struct FBeamRetryConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Timeout;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> RetryFalloffValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RetryMaxAttempt = -1;

	friend bool operator==(const FBeamRetryConfig& Lhs, const FBeamRetryConfig& RHS)
	{
		return Lhs.Timeout == RHS.Timeout
			&& Lhs.RetryFalloffValues == RHS.RetryFalloffValues
			&& Lhs.RetryMaxAttempt == RHS.RetryMaxAttempt;
	}

	friend bool operator!=(const FBeamRetryConfig& Lhs, const FBeamRetryConfig& RHS)
	{
		return !(Lhs == RHS);
	}
};

