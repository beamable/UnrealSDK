
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#include "GetItunesProductRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetItunesProductRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku", Category="Beam")
	FString Sku = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetItunesProductRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetItunesProduct",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetItunesProductRequest* Make(FString _Sku, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetItunesProductSuccess, FBeamRequestContext, Context, UGetItunesProductRequest*, Request, UGetProductResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetItunesProductError, FBeamRequestContext, Context, UGetItunesProductRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetItunesProductComplete, FBeamRequestContext, Context, UGetItunesProductRequest*, Request);

using FGetItunesProductFullResponse = FBeamFullResponse<UGetItunesProductRequest*, UGetProductResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetItunesProductFullResponse, FGetItunesProductFullResponse);
