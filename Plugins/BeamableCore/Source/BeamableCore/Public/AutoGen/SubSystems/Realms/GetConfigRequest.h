
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/RealmConfigResponse.h"

#include "GetConfigRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetConfigRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetConfigRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetConfigRequest* MakeGetConfigRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetConfigSuccess, FBeamRequestContext, Context, UGetConfigRequest*, Request, URealmConfigResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetConfigError, FBeamRequestContext, Context, UGetConfigRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetConfigComplete, FBeamRequestContext, Context, UGetConfigRequest*, Request);

using FGetConfigFullResponse = FBeamFullResponse<UGetConfigRequest*, URealmConfigResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetConfigFullResponse, FGetConfigFullResponse);
