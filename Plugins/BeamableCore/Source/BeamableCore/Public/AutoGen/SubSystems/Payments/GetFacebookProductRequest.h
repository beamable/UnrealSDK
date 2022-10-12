
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GetProductResponse.h"

#include "GetFacebookProductRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetFacebookProductRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku")
	FString Sku;

	// Body Params
	

	// Beam Base Request Declaration
	UGetFacebookProductRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetFacebookProductRequest* MakeGetFacebookProductRequest(FString _Sku, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFacebookProductSuccess, FBeamRequestContext, Context, UGetFacebookProductRequest*, Request, UGetProductResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFacebookProductError, FBeamRequestContext, Context, UGetFacebookProductRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetFacebookProductComplete, FBeamRequestContext, Context, UGetFacebookProductRequest*, Request);

using FGetFacebookProductFullResponse = FBeamFullResponse<UGetFacebookProductRequest*, UGetProductResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetFacebookProductFullResponse, FGetFacebookProductFullResponse);
