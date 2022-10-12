
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/GetElasticContainerRegistryURI.h"

#include "GetRegistryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRegistryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetRegistryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetRegistryRequest* MakeGetRegistryRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRegistrySuccess, FBeamRequestContext, Context, UGetRegistryRequest*, Request, UGetElasticContainerRegistryURI*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRegistryError, FBeamRequestContext, Context, UGetRegistryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRegistryComplete, FBeamRequestContext, Context, UGetRegistryRequest*, Request);

using FGetRegistryFullResponse = FBeamFullResponse<UGetRegistryRequest*, UGetElasticContainerRegistryURI*>;
DECLARE_DELEGATE_OneParam(FOnGetRegistryFullResponse, FGetRegistryFullResponse);