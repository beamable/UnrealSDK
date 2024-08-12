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

	/**
	 * @brief The HttpCodes for which we should retry this request.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam|Retry Cases")
	TArray<int64> HttpResponseCodes;

	/**
	 * @brief Custom beamable error codes (see FBeamErrorResponse::error) for which we should retry this request.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam|Retry Cases")
	TArray<FString> CustomErrorCodes;

	/**
	 * @brief Timeout for the request (in seconds).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam|Retry Rules")
	int64 Timeout = 10;

	/**
	 * @brief How much time will we wait between each request.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam|Retry Rules")
	TArray<float> RetryFalloffValues;

	/**
	 * @brief How many times will we retry. -1 is "infinite" but... avoid doing this as it makes no sense design wise.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam|Retry Rules")
	int RetryMaxAttempt = -1;

	friend bool operator==(const FBeamRetryConfig& Lhs, const FBeamRetryConfig& RHS)
	{
		return Lhs.HttpResponseCodes == RHS.HttpResponseCodes
			&& Lhs.CustomErrorCodes == RHS.CustomErrorCodes
			&& Lhs.Timeout == RHS.Timeout
			&& Lhs.RetryFalloffValues == RHS.RetryFalloffValues
			&& Lhs.RetryMaxAttempt == RHS.RetryMaxAttempt;
	}

	friend bool operator!=(const FBeamRetryConfig& Lhs, const FBeamRetryConfig& RHS)
	{
		return !(Lhs == RHS);
	}
};
