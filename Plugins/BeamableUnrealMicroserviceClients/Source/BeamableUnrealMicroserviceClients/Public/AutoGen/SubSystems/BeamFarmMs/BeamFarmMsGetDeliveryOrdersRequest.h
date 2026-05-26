
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetDeliveryOrdersResult.h"

#include "BeamFarmMsGetDeliveryOrdersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsGetDeliveryOrdersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBeamFarmMsGetDeliveryOrdersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsGetDeliveryOrders",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsGetDeliveryOrdersRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsGetDeliveryOrdersSuccess, FBeamRequestContext, Context, UBeamFarmMsGetDeliveryOrdersRequest*, Request, UGetDeliveryOrdersResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsGetDeliveryOrdersError, FBeamRequestContext, Context, UBeamFarmMsGetDeliveryOrdersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsGetDeliveryOrdersComplete, FBeamRequestContext, Context, UBeamFarmMsGetDeliveryOrdersRequest*, Request);

using FBeamFarmMsGetDeliveryOrdersFullResponse = FBeamFullResponse<UBeamFarmMsGetDeliveryOrdersRequest*, UGetDeliveryOrdersResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsGetDeliveryOrdersFullResponse, FBeamFarmMsGetDeliveryOrdersFullResponse);
