
#pragma once

#include "CoreMinimal.h"
#include "TransferThirdPartyAssociation.h"

#include "TransferThirdPartyAssociationLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTransferThirdPartyAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TransferThirdPartyAssociation To JSON String")
	static FString TransferThirdPartyAssociationToJsonString(const UTransferThirdPartyAssociation* Serializable, const bool Pretty);		
};