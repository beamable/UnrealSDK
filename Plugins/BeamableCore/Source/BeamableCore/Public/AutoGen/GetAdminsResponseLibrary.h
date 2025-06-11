#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetAdminsResponse.h"

#include "GetAdminsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetAdminsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="GetAdminsResponse To JSON String")
	static FString GetAdminsResponseToJsonString(const UGetAdminsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make GetAdminsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetAdminsResponse* Make(TArray<UAccountPortalView*> Accounts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break GetAdminsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetAdminsResponse* Serializable, TArray<UAccountPortalView*>& Accounts);
};