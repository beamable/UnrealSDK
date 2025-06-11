#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/NewCustomerResponse.h"

#include "NewCustomerResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UNewCustomerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="NewCustomerResponse To JSON String")
	static FString NewCustomerResponseToJsonString(const UNewCustomerResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make NewCustomerResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Alias, Outer", NativeMakeFunc))
	static UNewCustomerResponse* Make(bool bActivationPending, FString Name, FString ProjectName, FBeamCid Cid, FBeamPid Pid, UTokenResponse* Token, FOptionalString Alias, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break NewCustomerResponse", meta=(NativeBreakFunc))
	static void Break(const UNewCustomerResponse* Serializable, bool& bActivationPending, FString& Name, FString& ProjectName, FBeamCid& Cid, FBeamPid& Pid, UTokenResponse*& Token, FOptionalString& Alias);
};