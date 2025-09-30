#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmRequestBody.h"

#include "CustomerActorPromoteRealmRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorPromoteRealmRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorPromoteRealmRequestBody To JSON String")
	static FString CustomerActorPromoteRealmRequestBodyToJsonString(const UCustomerActorPromoteRealmRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorPromoteRealmRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Promotions, ContentManifestIds, Outer", NativeMakeFunc))
	static UCustomerActorPromoteRealmRequestBody* Make(FString SourceRealmId, FOptionalArrayOfBeamPromotableType Promotions, FOptionalArrayOfString ContentManifestIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorPromoteRealmRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorPromoteRealmRequestBody* Serializable, FString& SourceRealmId, FOptionalArrayOfBeamPromotableType& Promotions, FOptionalArrayOfString& ContentManifestIds);
};