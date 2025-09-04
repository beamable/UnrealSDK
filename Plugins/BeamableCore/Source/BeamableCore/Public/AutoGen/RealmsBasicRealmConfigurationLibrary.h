#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicRealmConfiguration.h"

#include "RealmsBasicRealmConfigurationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicRealmConfigurationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicRealmConfiguration To JSON String")
	static FString RealmsBasicRealmConfigurationToJsonString(const URealmsBasicRealmConfiguration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicRealmConfiguration", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmsBasicRealmConfiguration* Make(UWebSocketConfiguration* WebsocketConfig, FString MicroserviceURI, FString PortalURI, FString MicroserviceEcrURI, FString StorageBrowserURI, FString Environment, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicRealmConfiguration", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicRealmConfiguration* Serializable, UWebSocketConfiguration*& WebsocketConfig, FString& MicroserviceURI, FString& PortalURI, FString& MicroserviceEcrURI, FString& StorageBrowserURI, FString& Environment);
};