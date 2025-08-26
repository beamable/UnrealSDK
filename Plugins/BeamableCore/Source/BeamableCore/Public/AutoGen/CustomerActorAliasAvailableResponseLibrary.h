#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorAliasAvailableResponse.h"

#include "CustomerActorAliasAvailableResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorAliasAvailableResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorAliasAvailableResponse To JSON String")
	static FString CustomerActorAliasAvailableResponseToJsonString(const UCustomerActorAliasAvailableResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorAliasAvailableResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="CustomerId, Outer", NativeMakeFunc))
	static UCustomerActorAliasAvailableResponse* Make(FString Alias, bool bAvailable, FOptionalString CustomerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorAliasAvailableResponse", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorAliasAvailableResponse* Serializable, FString& Alias, bool& bAvailable, FOptionalString& CustomerId);
};