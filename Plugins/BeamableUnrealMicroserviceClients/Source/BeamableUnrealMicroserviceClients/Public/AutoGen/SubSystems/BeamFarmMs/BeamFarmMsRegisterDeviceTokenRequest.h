
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterDeviceTokenRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterResult.h"

#include "BeamFarmMsRegisterDeviceTokenRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsRegisterDeviceTokenRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URegisterDeviceTokenRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsRegisterDeviceTokenRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsRegisterDeviceToken",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsRegisterDeviceTokenRequest* Make(FString _Token, FString _Environment, FString _Platform, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsRegisterDeviceTokenSuccess, FBeamRequestContext, Context, UBeamFarmMsRegisterDeviceTokenRequest*, Request, URegisterResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsRegisterDeviceTokenError, FBeamRequestContext, Context, UBeamFarmMsRegisterDeviceTokenRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsRegisterDeviceTokenComplete, FBeamRequestContext, Context, UBeamFarmMsRegisterDeviceTokenRequest*, Request);

using FBeamFarmMsRegisterDeviceTokenFullResponse = FBeamFullResponse<UBeamFarmMsRegisterDeviceTokenRequest*, URegisterResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsRegisterDeviceTokenFullResponse, FBeamFarmMsRegisterDeviceTokenFullResponse);
