
#pragma once

#include "CoreMinimal.h"
#include "ListAuditRequestBody.h"

#include "ListAuditRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListAuditRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ListAuditRequestBody To JSON String")
	static FString ListAuditRequestBodyToJsonString(const UListAuditRequestBody* Serializable, const bool Pretty);		
};