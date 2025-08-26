#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmResponse.h"

#include "CustomerActorPromoteRealmResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorPromoteRealmResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorPromoteRealmResponse To JSON String")
	static FString CustomerActorPromoteRealmResponseToJsonString(const UCustomerActorPromoteRealmResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorPromoteRealmResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Scopes, Outer", NativeMakeFunc))
	static UCustomerActorPromoteRealmResponse* Make(FString SourceRealmId, FOptionalArrayOfPromotionScope Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorPromoteRealmResponse", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorPromoteRealmResponse* Serializable, FString& SourceRealmId, FOptionalArrayOfPromotionScope& Scopes);
};