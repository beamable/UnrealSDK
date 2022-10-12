
#pragma once

#include "CoreMinimal.h"
#include "GamerTagAssociation.h"

#include "GamerTagAssociationLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGamerTagAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GamerTagAssociation To JSON String")
	static FString GamerTagAssociationToJsonString(const UGamerTagAssociation* Serializable, const bool Pretty);		
};