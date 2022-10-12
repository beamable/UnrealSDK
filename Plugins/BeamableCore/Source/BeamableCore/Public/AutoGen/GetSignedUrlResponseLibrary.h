
#pragma once

#include "CoreMinimal.h"
#include "GetSignedUrlResponse.h"

#include "GetSignedUrlResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSignedUrlResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetSignedUrlResponse To JSON String")
	static FString GetSignedUrlResponseToJsonString(const UGetSignedUrlResponse* Serializable, const bool Pretty);		
};