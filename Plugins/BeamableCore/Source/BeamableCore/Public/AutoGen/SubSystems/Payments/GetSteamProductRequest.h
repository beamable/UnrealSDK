
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GetProductResponse.h"

#include "GetSteamProductRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSteamProductRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku")
	FString Sku;

	// Body Params
	

	// Beam Base Request Declaration
	UGetSteamProductRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetSteamProductRequest* MakeGetSteamProductRequest(FString _Sku, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamProductSuccess, FBeamRequestContext, Context, UGetSteamProductRequest*, Request, UGetProductResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamProductError, FBeamRequestContext, Context, UGetSteamProductRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSteamProductComplete, FBeamRequestContext, Context, UGetSteamProductRequest*, Request);

using FGetSteamProductFullResponse = FBeamFullResponse<UGetSteamProductRequest*, UGetProductResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetSteamProductFullResponse, FGetSteamProductFullResponse);
