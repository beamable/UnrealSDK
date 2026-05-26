
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliverOrderRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliverOrderResult.h"

#include "BeamFarmMsDeliverOrderRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsDeliverOrderRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UDeliverOrderRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsDeliverOrderRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsDeliverOrder",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsDeliverOrderRequest* Make(FString _OrderId, int64 _ItemInstanceId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsDeliverOrderSuccess, FBeamRequestContext, Context, UBeamFarmMsDeliverOrderRequest*, Request, UDeliverOrderResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsDeliverOrderError, FBeamRequestContext, Context, UBeamFarmMsDeliverOrderRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsDeliverOrderComplete, FBeamRequestContext, Context, UBeamFarmMsDeliverOrderRequest*, Request);

using FBeamFarmMsDeliverOrderFullResponse = FBeamFullResponse<UBeamFarmMsDeliverOrderRequest*, UDeliverOrderResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsDeliverOrderFullResponse, FBeamFarmMsDeliverOrderFullResponse);
