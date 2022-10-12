
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/SteamOrderInfoResponse.h"

#include "GetSteamOrderRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSteamOrderRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Order Id")
	FString OrderId;

	// Body Params
	

	// Beam Base Request Declaration
	UGetSteamOrderRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetSteamOrderRequest* MakeGetSteamOrderRequest(FString _OrderId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamOrderSuccess, FBeamRequestContext, Context, UGetSteamOrderRequest*, Request, USteamOrderInfoResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamOrderError, FBeamRequestContext, Context, UGetSteamOrderRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSteamOrderComplete, FBeamRequestContext, Context, UGetSteamOrderRequest*, Request);

using FGetSteamOrderFullResponse = FBeamFullResponse<UGetSteamOrderRequest*, USteamOrderInfoResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetSteamOrderFullResponse, FGetSteamOrderFullResponse);
