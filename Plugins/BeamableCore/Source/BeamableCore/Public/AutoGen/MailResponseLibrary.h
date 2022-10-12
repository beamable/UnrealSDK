
#pragma once

#include "CoreMinimal.h"
#include "MailResponse.h"

#include "MailResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailResponse To JSON String")
	static FString MailResponseToJsonString(const UMailResponse* Serializable, const bool Pretty);		
};