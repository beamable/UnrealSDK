#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSamlpeStatRequestArgs.h"

#include "GetSamlpeStatRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UGetSamlpeStatRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Json", DisplayName="GetSamlpeStatRequestArgs To JSON String")
	static FString GetSamlpeStatRequestArgsToJsonString(const UGetSamlpeStatRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Make GetSamlpeStatRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetSamlpeStatRequestArgs* Make(int64 UserID, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Break GetSamlpeStatRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UGetSamlpeStatRequestArgs* Serializable, int64& UserID);
};