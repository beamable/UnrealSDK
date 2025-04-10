#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EmptyRsp.h"

#include "EmptyRspLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEmptyRspLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Push|Utils|Json", DisplayName="EmptyRsp To JSON String")
	static FString EmptyRspToJsonString(const UEmptyRsp* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Push|Utils|Make/Break", DisplayName="Make EmptyRsp", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEmptyRsp* Make(UObject* Outer);

	
};