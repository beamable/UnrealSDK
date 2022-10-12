
#pragma once

#include "CoreMinimal.h"
#include "AccountRolesReport.h"

#include "AccountRolesReportLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountRolesReportLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountRolesReport To JSON String")
	static FString AccountRolesReportToJsonString(const UAccountRolesReport* Serializable, const bool Pretty);		
};