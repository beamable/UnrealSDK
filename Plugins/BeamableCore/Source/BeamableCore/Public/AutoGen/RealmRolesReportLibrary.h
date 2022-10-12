
#pragma once

#include "CoreMinimal.h"
#include "RealmRolesReport.h"

#include "RealmRolesReportLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URealmRolesReportLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RealmRolesReport To JSON String")
	static FString RealmRolesReportToJsonString(const URealmRolesReport* Serializable, const bool Pretty);		
};