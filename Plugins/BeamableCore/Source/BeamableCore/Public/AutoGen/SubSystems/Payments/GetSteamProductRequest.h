
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#include "GetSteamProductRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSteamProductRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku", Category="Beam")
	FString Sku = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetSteamProductRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetSteamProduct",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetSteamProductRequest* Make(FString _Sku, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamProductSuccess, FBeamRequestContext, Context, UGetSteamProductRequest*, Request, UGetProductResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamProductError, FBeamRequestContext, Context, UGetSteamProductRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSteamProductComplete, FBeamRequestContext, Context, UGetSteamProductRequest*, Request);

using FGetSteamProductFullResponse = FBeamFullResponse<UGetSteamProductRequest*, UGetProductResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetSteamProductFullResponse, FGetSteamProductFullResponse);
