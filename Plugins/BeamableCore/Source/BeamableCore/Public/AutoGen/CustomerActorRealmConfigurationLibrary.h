#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorRealmConfiguration.h"

#include "CustomerActorRealmConfigurationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorRealmConfigurationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorRealmConfiguration To JSON String")
	static FString CustomerActorRealmConfigurationToJsonString(const UCustomerActorRealmConfiguration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorRealmConfiguration", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCustomerActorRealmConfiguration* Make(FString Environment, UWebSocketConfiguration* WebsocketConfig, FString MicroserviceUri, FString MicroserviceEcrUri, FString PortalUri, FString StorageBrowserUri, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorRealmConfiguration", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorRealmConfiguration* Serializable, FString& Environment, UWebSocketConfiguration*& WebsocketConfig, FString& MicroserviceUri, FString& MicroserviceEcrUri, FString& PortalUri, FString& StorageBrowserUri);
};