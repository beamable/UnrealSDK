
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#include "GetGoogleplayProductRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGoogleplayProductRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku", Category="Beam")
	FString Sku = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetGoogleplayProductRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetGoogleplayProduct",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetGoogleplayProductRequest* Make(FString _Sku, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGoogleplayProductSuccess, FBeamRequestContext, Context, UGetGoogleplayProductRequest*, Request, UGetProductResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGoogleplayProductError, FBeamRequestContext, Context, UGetGoogleplayProductRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetGoogleplayProductComplete, FBeamRequestContext, Context, UGetGoogleplayProductRequest*, Request);

using FGetGoogleplayProductFullResponse = FBeamFullResponse<UGetGoogleplayProductRequest*, UGetProductResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetGoogleplayProductFullResponse, FGetGoogleplayProductFullResponse);
