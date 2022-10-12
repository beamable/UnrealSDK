
#pragma once

#include "CoreMinimal.h"
#include "SendMsg.h"

#include "SendMsgLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USendMsgLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SendMsg To JSON String")
	static FString SendMsgToJsonString(const USendMsg* Serializable, const bool Pretty);		
};