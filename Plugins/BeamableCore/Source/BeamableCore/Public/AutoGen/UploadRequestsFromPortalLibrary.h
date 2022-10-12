
#pragma once

#include "CoreMinimal.h"
#include "UploadRequestsFromPortal.h"

#include "UploadRequestsFromPortalLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UUploadRequestsFromPortalLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize UploadRequestsFromPortal To JSON String")
	static FString UploadRequestsFromPortalToJsonString(const UUploadRequestsFromPortal* Serializable, const bool Pretty);		
};