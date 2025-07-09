#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ConnectionStringResponse.h"

#include "ConnectionStringResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UConnectionStringResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ConnectionStringResponse To JSON String")
	static FString ConnectionStringResponseToJsonString(const UConnectionStringResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ConnectionStringResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="ConnectionString, Outer", NativeMakeFunc))
	static UConnectionStringResponse* Make(FOptionalString ConnectionString, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ConnectionStringResponse", meta=(NativeBreakFunc))
	static void Break(const UConnectionStringResponse* Serializable, FOptionalString& ConnectionString);
};