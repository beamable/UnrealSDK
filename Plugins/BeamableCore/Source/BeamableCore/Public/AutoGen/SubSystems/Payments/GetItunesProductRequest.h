
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GetProductResponse.h"

#include "GetItunesProductRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetItunesProductRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku")
	FString Sku;

	// Body Params
	

	// Beam Base Request Declaration
	UGetItunesProductRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetItunesProductRequest* MakeGetItunesProductRequest(FString _Sku, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetItunesProductSuccess, FBeamRequestContext, Context, UGetItunesProductRequest*, Request, UGetProductResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetItunesProductError, FBeamRequestContext, Context, UGetItunesProductRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetItunesProductComplete, FBeamRequestContext, Context, UGetItunesProductRequest*, Request);

using FGetItunesProductFullResponse = FBeamFullResponse<UGetItunesProductRequest*, UGetProductResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetItunesProductFullResponse, FGetItunesProductFullResponse);
