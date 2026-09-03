
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UnregisterDeviceTokenRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UnregisterResult.h"

#include "BeamFarmMsUnregisterDeviceTokenRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsUnregisterDeviceTokenRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUnregisterDeviceTokenRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsUnregisterDeviceTokenRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsUnregisterDeviceToken",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsUnregisterDeviceTokenRequest* Make(FString _Token, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsUnregisterDeviceTokenSuccess, FBeamRequestContext, Context, UBeamFarmMsUnregisterDeviceTokenRequest*, Request, UUnregisterResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsUnregisterDeviceTokenError, FBeamRequestContext, Context, UBeamFarmMsUnregisterDeviceTokenRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsUnregisterDeviceTokenComplete, FBeamRequestContext, Context, UBeamFarmMsUnregisterDeviceTokenRequest*, Request);

using FBeamFarmMsUnregisterDeviceTokenFullResponse = FBeamFullResponse<UBeamFarmMsUnregisterDeviceTokenRequest*, UUnregisterResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsUnregisterDeviceTokenFullResponse, FBeamFarmMsUnregisterDeviceTokenFullResponse);
