
#pragma once

#include "CoreMinimal.h"
#include "UploadRequestFromPortal.h"

#include "UploadRequestFromPortalLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UUploadRequestFromPortalLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize UploadRequestFromPortal To JSON String")
	static FString UploadRequestFromPortalToJsonString(const UUploadRequestFromPortal* Serializable, const bool Pretty);		
};