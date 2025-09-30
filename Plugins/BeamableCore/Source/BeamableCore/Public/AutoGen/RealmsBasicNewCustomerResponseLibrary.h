#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicNewCustomerResponse.h"

#include "RealmsBasicNewCustomerResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicNewCustomerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicNewCustomerResponse To JSON String")
	static FString RealmsBasicNewCustomerResponseToJsonString(const URealmsBasicNewCustomerResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicNewCustomerResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Alias, Outer", NativeMakeFunc))
	static URealmsBasicNewCustomerResponse* Make(bool bActivationPending, FString Name, FString ProjectName, FBeamCid Cid, FBeamPid Pid, UTokenResponse* Token, FOptionalString Alias, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicNewCustomerResponse", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicNewCustomerResponse* Serializable, bool& bActivationPending, FString& Name, FString& ProjectName, FBeamCid& Cid, FBeamPid& Pid, UTokenResponse*& Token, FOptionalString& Alias);
};