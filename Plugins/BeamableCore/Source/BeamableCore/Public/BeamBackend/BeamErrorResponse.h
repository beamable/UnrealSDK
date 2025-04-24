#pragma once
#include "JsonObjectConverter.h"

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
	int64 status = 400;

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

UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamErrorResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Beam|Json", DisplayName="JSON String to Beam Error")
	static FBeamErrorResponse JsonStringToBeamErrorResponse(FString Json)
	{
		FBeamErrorResponse Err;
		FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Err);
		return Err;
	}
};
