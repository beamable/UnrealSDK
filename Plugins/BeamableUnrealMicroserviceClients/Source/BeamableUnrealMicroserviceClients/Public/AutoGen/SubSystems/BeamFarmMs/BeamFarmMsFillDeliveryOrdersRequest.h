
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/FillDeliveryOrdersResult.h"

#include "BeamFarmMsFillDeliveryOrdersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsFillDeliveryOrdersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBeamFarmMsFillDeliveryOrdersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsFillDeliveryOrders",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsFillDeliveryOrdersRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsFillDeliveryOrdersSuccess, FBeamRequestContext, Context, UBeamFarmMsFillDeliveryOrdersRequest*, Request, UFillDeliveryOrdersResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsFillDeliveryOrdersError, FBeamRequestContext, Context, UBeamFarmMsFillDeliveryOrdersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsFillDeliveryOrdersComplete, FBeamRequestContext, Context, UBeamFarmMsFillDeliveryOrdersRequest*, Request);

using FBeamFarmMsFillDeliveryOrdersFullResponse = FBeamFullResponse<UBeamFarmMsFillDeliveryOrdersRequest*, UFillDeliveryOrdersResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsFillDeliveryOrdersFullResponse, FBeamFarmMsFillDeliveryOrdersFullResponse);
