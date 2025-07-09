#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UriResponse.h"

#include "UriResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUriResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="UriResponse To JSON String")
	static FString UriResponseToJsonString(const UUriResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make UriResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Uri, Outer", NativeMakeFunc))
	static UUriResponse* Make(FOptionalString Uri, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break UriResponse", meta=(NativeBreakFunc))
	static void Break(const UUriResponse* Serializable, FOptionalString& Uri);
};