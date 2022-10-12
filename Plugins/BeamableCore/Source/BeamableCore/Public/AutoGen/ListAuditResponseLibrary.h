
#pragma once

#include "CoreMinimal.h"
#include "ListAuditResponse.h"

#include "ListAuditResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListAuditResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ListAuditResponse To JSON String")
	static FString ListAuditResponseToJsonString(const UListAuditResponse* Serializable, const bool Pretty);		
};