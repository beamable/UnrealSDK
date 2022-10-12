
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GetProductsResponse.h"

#include "GetSteamProductsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSteamProductsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Steam Id")
	int64 SteamId;

	// Body Params
	

	// Beam Base Request Declaration
	UGetSteamProductsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetSteamProductsRequest* MakeGetSteamProductsRequest(int64 _SteamId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamProductsSuccess, FBeamRequestContext, Context, UGetSteamProductsRequest*, Request, UGetProductsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamProductsError, FBeamRequestContext, Context, UGetSteamProductsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSteamProductsComplete, FBeamRequestContext, Context, UGetSteamProductsRequest*, Request);

using FGetSteamProductsFullResponse = FBeamFullResponse<UGetSteamProductsRequest*, UGetProductsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetSteamProductsFullResponse, FGetSteamProductsFullResponse);
