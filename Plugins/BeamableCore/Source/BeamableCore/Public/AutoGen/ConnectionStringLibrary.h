#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ConnectionString.h"

#include "ConnectionStringLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UConnectionStringLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ConnectionString To JSON String")
	static FString ConnectionStringToJsonString(const UConnectionString* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ConnectionString", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UConnectionString* Make(FString ConnectionString, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ConnectionString", meta=(NativeBreakFunc))
	static void Break(const UConnectionString* Serializable, FString& ConnectionString);
};