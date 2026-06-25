
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/FcmConfigStatus.h"

#include "BeamFarmMsCheckFcmConfigRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsCheckFcmConfigRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBeamFarmMsCheckFcmConfigRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsCheckFcmConfig",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsCheckFcmConfigRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsCheckFcmConfigSuccess, FBeamRequestContext, Context, UBeamFarmMsCheckFcmConfigRequest*, Request, UFcmConfigStatus*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsCheckFcmConfigError, FBeamRequestContext, Context, UBeamFarmMsCheckFcmConfigRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsCheckFcmConfigComplete, FBeamRequestContext, Context, UBeamFarmMsCheckFcmConfigRequest*, Request);

using FBeamFarmMsCheckFcmConfigFullResponse = FBeamFullResponse<UBeamFarmMsCheckFcmConfigRequest*, UFcmConfigStatus*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsCheckFcmConfigFullResponse, FBeamFarmMsCheckFcmConfigFullResponse);
