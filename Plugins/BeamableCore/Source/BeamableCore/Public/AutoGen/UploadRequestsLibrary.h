
#pragma once

#include "CoreMinimal.h"
#include "UploadRequests.h"

#include "UploadRequestsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UUploadRequestsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize UploadRequests To JSON String")
	static FString UploadRequestsToJsonString(const UUploadRequests* Serializable, const bool Pretty);		
};