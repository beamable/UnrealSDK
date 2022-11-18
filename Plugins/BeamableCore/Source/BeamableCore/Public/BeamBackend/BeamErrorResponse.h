#pragma once

#include "BeamErrorResponse.generated.h"

/**
* @brief Maps to the response our server sends when a request fails. 
 */
USTRUCT(BlueprintType)
struct FBeamErrorResponse
{
	GENERATED_BODY()

	/**
	 * @brief The HTTP Status Code. 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="Status")
	int64 status;

	/**
	 * @brief Beamable's own Error Code.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="Error")
	FString error;

	/**
	 * @brief The Beamable service where the error originated.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="Service")
	FString service;

	/**
	 * @brief A more detailed message about the error.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="Message")
	FString message;
};
