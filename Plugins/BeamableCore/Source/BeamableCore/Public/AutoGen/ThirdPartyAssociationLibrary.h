
#pragma once

#include "CoreMinimal.h"
#include "ThirdPartyAssociation.h"

#include "ThirdPartyAssociationLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UThirdPartyAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ThirdPartyAssociation To JSON String")
	static FString ThirdPartyAssociationToJsonString(const UThirdPartyAssociation* Serializable, const bool Pretty);		
};