#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmConfiguration.h"

#include "RealmConfigurationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmConfigurationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmConfiguration To JSON String")
	static FString RealmConfigurationToJsonString(const URealmConfiguration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmConfiguration", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmConfiguration* Make(UWebSocketConfiguration* WebsocketConfig, FString MicroserviceURI, FString PortalURI, FString MicroserviceEcrURI, FString StorageBrowserURI, FString Environment, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmConfiguration", meta=(NativeBreakFunc))
	static void Break(const URealmConfiguration* Serializable, UWebSocketConfiguration*& WebsocketConfig, FString& MicroserviceURI, FString& PortalURI, FString& MicroserviceEcrURI, FString& StorageBrowserURI, FString& Environment);
};