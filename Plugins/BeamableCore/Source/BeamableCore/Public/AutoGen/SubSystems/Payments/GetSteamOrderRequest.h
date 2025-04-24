
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/SteamOrderInfoResponse.h"

#include "GetSteamOrderRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSteamOrderRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Order Id", Category="Beam")
	FString OrderId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetSteamOrderRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetSteamOrder",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetSteamOrderRequest* Make(FString _OrderId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamOrderSuccess, FBeamRequestContext, Context, UGetSteamOrderRequest*, Request, USteamOrderInfoResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamOrderError, FBeamRequestContext, Context, UGetSteamOrderRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSteamOrderComplete, FBeamRequestContext, Context, UGetSteamOrderRequest*, Request);

using FGetSteamOrderFullResponse = FBeamFullResponse<UGetSteamOrderRequest*, USteamOrderInfoResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetSteamOrderFullResponse, FGetSteamOrderFullResponse);
