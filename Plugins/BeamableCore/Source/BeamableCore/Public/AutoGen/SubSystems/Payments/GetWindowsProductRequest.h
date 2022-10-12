
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GetProductResponse.h"

#include "GetWindowsProductRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetWindowsProductRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku")
	FString Sku;

	// Body Params
	

	// Beam Base Request Declaration
	UGetWindowsProductRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetWindowsProductRequest* MakeGetWindowsProductRequest(FString _Sku, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetWindowsProductSuccess, FBeamRequestContext, Context, UGetWindowsProductRequest*, Request, UGetProductResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetWindowsProductError, FBeamRequestContext, Context, UGetWindowsProductRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetWindowsProductComplete, FBeamRequestContext, Context, UGetWindowsProductRequest*, Request);

using FGetWindowsProductFullResponse = FBeamFullResponse<UGetWindowsProductRequest*, UGetProductResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetWindowsProductFullResponse, FGetWindowsProductFullResponse);
