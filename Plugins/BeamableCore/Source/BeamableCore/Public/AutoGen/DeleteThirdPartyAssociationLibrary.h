
#pragma once

#include "CoreMinimal.h"
#include "DeleteThirdPartyAssociation.h"

#include "DeleteThirdPartyAssociationLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteThirdPartyAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DeleteThirdPartyAssociation To JSON String")
	static FString DeleteThirdPartyAssociationToJsonString(const UDeleteThirdPartyAssociation* Serializable, const bool Pretty);		
};