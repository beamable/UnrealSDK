#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmConfiguration.h"

#include "RealmConfigurationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmConfigurationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RealmConfiguration To JSON String")
	static FString RealmConfigurationToJsonString(const URealmConfiguration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RealmConfiguration", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmConfiguration* Make(UWebSocketConfiguration* WebsocketConfig, FString MicroserviceURI, FString PortalURI, FString MicroserviceEcrURI, FString StorageBrowserURI, FString Environment, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RealmConfiguration", meta=(NativeBreakFunc))
	static void Break(const URealmConfiguration* Serializable, UWebSocketConfiguration*& WebsocketConfig, FString& MicroserviceURI, FString& PortalURI, FString& MicroserviceEcrURI, FString& StorageBrowserURI, FString& Environment);
};